#include <hal.h>
#include <Nfc.h>
#include <ndef_bt_wifi.h>

#define BT_NDEF_TYPE_OFFSET	4

//#define DEBUG_DELAY_TICK	1

#ifdef DEBUG_DELAY_TICK
#define ARM_CM_DWT_CYCCNT (*(uint32_t *)0xE0001004)
#endif

/* Wifi settings */
#define WIFI_SSID_MAX_LEN	32
#define WIFI_PASSWORD_MAX_LEN	64

#define WIFI_ATTR_AUTH_TYPE		0x1003
#define WIFI_ATTR_CREDENTIAL	0x100E
#define WIFI_ATTR_ENCRYPT_TYPE	0x100F
#define WIFI_ATTR_MAC_ADDRESS	0x1020
#define WIFI_ATTR_NETWORK_INDEX	0x1026
#define WIFI_ATTR_NET_KEY		0x1027
#define WIFI_ATTR_SSID			0x1045


#define BT_OPERATION_DATATYPE_CLASS_OF_DEVICE		0x0d
#define BT_OPERATION_DATATYPE_HASH					0x0e
#define BT_OPERATION_DATATYPE_RANDOMIZER			0x0f
#define BT_OPERATION_DATATYPE_USERFRIENDLY_NAME		0x09


/*
struct ndef_record {
    char * buffer;
    uint32_t length;

    uint8_t type_length;
    uint32_t type_offset;

    uint8_t id_length;
    uint32_t id_offset;

    uint32_t payload_length;
    uint32_t payload_offset;
};
*/
struct ndef_message{
    size_t length;
    struct ndef_record* records;
};

typedef enum
{
	NFC_CLOSED = 0x01,
	NFC_CARDEMU_BT = 0x02,
	NFC_CARDEMU_WIFI = 0x04,
	NFC_P2P = 0x08,
}nfc_state_s;

static NioWlc_BtWifi_Cb btwifi_cb;

static nfc_state_s nfc_state = NFC_CLOSED;
static char ndef_buffer_snep[256];/* short record */
static char ndef_buffer_ch[256];/* short record */
struct ndef_record record_snep;
struct ndef_record record_ch;

static char bt_ndef_type[] = "application/vnd.bluetooth.ep.oob";
static char bt_ndef_id[] = "0";
static char wifi_ndef_type[] = "application/vnd.wfa.wsc";
static char wifi_ndef_id[] = "0";

static bool NioWlc_ndef_set_type(struct ndef_record *record, char *type);
static bool NioWlc_ndef_set_id(struct ndef_record *record, char* id);
static uint32_t NioWlc_ndef_set_bt_info(struct ndef_record *record, struct bt_info *bt,int bt_len);
static uint32_t NioWlc_ndef_set_wifi_info(struct ndef_record *record, struct wifi_info *wifi,int wifi_len);

static bool NioWlc_ndef_set_type(struct ndef_record *record, char *type)
{
	if(record == NULL|| type == NULL)
		return NXPNCI_ERROR;

	record->type_length = strlen(type);
    record->buffer[record->Wifi_CH_header_offset +1] = record->type_length;

    /* format|type_len|payload_len|Id_len */
    record->type_offset = record->Wifi_CH_header_offset + BT_NDEF_TYPE_OFFSET;
    memcpy(record->buffer + record->type_offset, type, record->type_length);

	return NXPNCI_SUCCESS;
}
static bool NioWlc_ndef_set_id(struct ndef_record *record, char* id)
{
	if(record == NULL|| id == NULL)
		return NXPNCI_ERROR;

	record->id_length= strlen(id);
    record->buffer[record->Wifi_CH_header_offset +3] = record->id_length;

    record->id_offset = record->type_offset + record->type_length;;
    memcpy(record->buffer + record->id_offset, id, record->id_length);

	return NXPNCI_SUCCESS;
}

static uint32_t NioWlc_ndef_set_bt_info(struct ndef_record *record, struct bt_info *bt,int bt_len)
{
	char* payload;
	uint32_t i = 2;
	uint8_t len = 0;

	record->payload_offset = record->id_offset + record->id_length;
	payload = record->buffer + record->payload_offset;

#ifdef Nio_OOBData
	memcpy(&payload[i],bt,bt_len);
	i += bt_len;
#else

	/* Bluetooth Device Address */
	memcpy(&payload[i], bt->mac, MAC_ADDRESS_SIZE);
	i += MAC_ADDRESS_SIZE;

	/* Class Of Device */
	len = 4;
	payload[i++]= len;
	payload[i++]= BT_OPERATION_DATATYPE_CLASS_OF_DEVICE;
	memcpy(&payload[i],bt->ClassOfDev,sizeof(bt->ClassOfDev));
	i += sizeof(bt->ClassOfDev);

	/* Simple Pairing hash */
	len = 0x11;
	payload[i++]= len;
	payload[i++]= BT_OPERATION_DATATYPE_HASH;
	memcpy(&payload[i],bt->HashValue,sizeof(bt->HashValue));
	i += sizeof(bt->HashValue);

	/* Simple Pairing randomizer */
	len = 0x11;
	payload[i++]= len;
	payload[i++]= BT_OPERATION_DATATYPE_RANDOMIZER;
	memcpy(&payload[i],bt->RandomizerValue,sizeof(bt->RandomizerValue));
	i += sizeof(bt->RandomizerValue);

	/* user-friendly name */
	len = 1 + strlen(bt->UserfriendlyName);
	payload[i++]= len;
	payload[i++]= BT_OPERATION_DATATYPE_USERFRIENDLY_NAME;
	memcpy(&payload[i],bt->UserfriendlyName,strlen(bt->UserfriendlyName));
	i += strlen(bt->UserfriendlyName);
#endif

	record->payload_length = i;
	payload[0] = record->payload_length & 0xFF;
	payload[1] = record->payload_length >>8;

	record->buffer[record->Wifi_CH_header_offset+2] = (uint8_t) record->payload_length;
	record->length = record->payload_offset + record->payload_length;

	return NXPNCI_SUCCESS;
}

/* 按照蔚来Fury修改 */
static uint32_t NioWlc_ndef_set_wifi_info(struct ndef_record *record, struct wifi_info *wifi,int wifi_len)
{
	char* payload;
	uint32_t i = 0, len = 0;
	uint32_t credential_offset = 0;
	uint32_t credential_length = 0;

	record->payload_offset = record->id_offset + record->id_length;
	payload = record->buffer + record->payload_offset;

#ifdef Nio_OOBData
	memcpy(payload,wifi,wifi_len);
	i += wifi_len;
#else
	/* Credential */
	payload[i++] = WIFI_ATTR_CREDENTIAL >> 8;
	payload[i++] = WIFI_ATTR_CREDENTIAL & 0xFF;
	credential_offset = i;
	i+=2;

	/* Network Index */
	payload[i++] = WIFI_ATTR_NETWORK_INDEX >> 8;
	payload[i++] = WIFI_ATTR_NETWORK_INDEX & 0xFF;
	/* 固定为1字节 */
	len = 1;
	payload[i++] = len >> 8;
	payload[i++] = len & 0xFF;
	//payload[i++] = 0x01;
	payload[i++] = wifi->network_index;

	/* SSID */
	payload[i++] = WIFI_ATTR_SSID >> 8;
	payload[i++] = WIFI_ATTR_SSID & 0xFF;
	len = strlen(wifi->ssid);
	payload[i++] = len >> 8;
	payload[i++] = len & 0xFF;
	memcpy(&payload[i], wifi->ssid, len);
	i+= len;

	/* Authentication type */
	payload[i++] = WIFI_ATTR_AUTH_TYPE >> 8;
	payload[i++] = WIFI_ATTR_AUTH_TYPE & 0xFF;
	len = 2;
	payload[i++] = len >> 8;
	payload[i++] = len & 0xFF;
	payload[i++] = wifi->auth >> 8;
	payload[i++] = wifi->auth & 0xFF;

	/* Encryption type */
	payload[i++] = WIFI_ATTR_ENCRYPT_TYPE >> 8;
	payload[i++] = WIFI_ATTR_ENCRYPT_TYPE & 0xFF;
	len = 2;
	payload[i++] = len >> 8;
	payload[i++] = len & 0xFF;
	payload[i++] = wifi->crypt >> 8;
	payload[i++] = wifi->crypt & 0xFF;

	/* Network Key */
	payload[i++] = WIFI_ATTR_NET_KEY >> 8;
	payload[i++] = WIFI_ATTR_NET_KEY & 0xFF;
	len = strlen(wifi->password);
	payload[i++] = len >> 8;
	payload[i++] = len & 0xFF;
	memcpy(&payload[i], wifi->password, len);
	i+= len;

	/* MAC address */
	payload[i++] = WIFI_ATTR_MAC_ADDRESS >> 8;
	payload[i++] = WIFI_ATTR_MAC_ADDRESS & 0xFF;
	len = 6;
	payload[i++] = len >> 8;
	payload[i++] = len & 0xFF;
	//memset(&payload[i],0x00,len);
	memcpy(&payload[i], wifi->mac, len);
	i+= len;

	/* Credential length*/
	credential_length = i - credential_offset -2;
	payload[credential_offset++] = credential_length >> 8;
	payload[credential_offset] = credential_length & 0xFF;
#endif

	record->payload_length = i;
	record->buffer[record->Wifi_CH_header_offset + 2] = (uint8_t) record->payload_length;
	record->length = record->payload_offset + record->payload_length;

	return NXPNCI_SUCCESS;
}

static void Emu_NdefPush_Cb(unsigned char *pNdefRecord, unsigned short NdefRecordSize)
{
	if (btwifi_cb != NULL)
	{
		btwifi_cb(nfc_state, 1);
	}
}

static uint32_t NioWlc_nfc_start_paring(NioWlc_BtWifi_Cb cb)
{
	btwifi_cb = cb;
	T4T_NDEF_EMU_SetMessage((unsigned char *) record_snep.buffer, record_snep.length, &Emu_NdefPush_Cb);

	return 0;
}

uint32_t NioWlc_nfc_set_bt_info(struct bt_info *bt,int len)
{
#ifdef DEBUG_DELAY_TICK
	uint32_t tick_out = 0;
	uint32_t tick_in = ARM_CM_DWT_CYCCNT;
#endif

	if(bt == NULL)
		return 1;

#ifdef NIO_ET7
	uint8_t Wifi_CH_header[15]=
	{
		/* MB=1b, ME=0b, CF=0b, SR=1b, IL=0b, TNF=001b */
		0x91,
		/* Type Length */
	    0x02,
		/* Payload Length */
	    0x0A,
		/* Record Type */
	    'H','s',
		/* Version Numbe */
	    0x12,
		/* 可选载波 */
		/* MB=1b, ME=1b, CF=0b, SR=1b, IL=0b, TNF=001b */
		0xD1,
		0x02,
		0x04,
		'a','c',
		/* Carrier Flags: CPS=1, "active"  */
		0x01,
		/* Carrier Data Reference Length */
		0x01,
		/* Carrier Data Reference */
		0x30,
		/* Auxiliary Data Reference Count */
		0x00
	};

#endif

	record_snep.buffer = ndef_buffer_snep;

#ifdef NIO_ET7
	memcpy(record_snep.buffer,Wifi_CH_header,sizeof(Wifi_CH_header));
	record_snep.Wifi_CH_header_length = sizeof(Wifi_CH_header);
	record_snep.Wifi_CH_header_offset = sizeof(Wifi_CH_header);

	/*  MB=0b, ME=1b, CF=0b, SR=1b, IL=1b, TNF=010b */
	record_snep.buffer[record_snep.Wifi_CH_header_offset] =0x5A;
#else
	record_snep.Wifi_CH_header_length = 0;
	record_snep.Wifi_CH_header_offset = 0;

	/* 1. format */
	ndef_buffer_snep[0] = 0xDA;

#endif

	/* 2. type */
	NioWlc_ndef_set_type(&record_snep, bt_ndef_type);

	/* 3. id */
	NioWlc_ndef_set_id(&record_snep, bt_ndef_id);

	/* 4. payload */
	/* 4.1 mac address in bigendian */
	NioWlc_ndef_set_bt_info(&record_snep, bt,len);

	//nfc_state = NFC_CARDEMU_BT;

#ifdef DEBUG_DELAY_TICK
	tick_out = ARM_CM_DWT_CYCCNT;
	UART_MESSAGE_1("\nNioWlc_nfc_set_bt_info, run cycle=%d\n\r", tick_out-tick_in);
#endif

	return 0;
}

uint32_t NioWlc_nfc_request_bt_info(struct bt_info *bt,int len)
{
#ifdef DEBUG_DELAY_TICK
	uint32_t tick_out = 0;
	uint32_t tick_in = ARM_CM_DWT_CYCCNT;
#endif

	uint8_t BT_CH_header[22]=
	{
		/* MB=1b, ME=0b, CF=0b, SR=1b, IL=0b, TNF=001b */
		0x91,
		/* Type Length */
		0x02,
		/* Payload Length */
		0x11,
		/* Record Type */
		'H','r',
		/* Version Numbe */
		0x12,
		/* 冲突选择 */
		/* MB=1b, ME=0b, CF=0b, SR=1b, IL=0b, TNF=001b */
		0x91,
		/* Type Length */
		0x02,
		/* Payload Length */
		0x02,
		/* Record Type */
		'c','r',
		/* Random Numbe */
		0x01,0x02,
		/* 可选载波 */
		/* MB=0b, ME=1b, CF=0b, SR=1b, IL=0b, TNF=001b  */
		0x51,
		0x02,
		0x04,
		'a','c',
		/* Carrier Flags: CPS=1, "active"  */
		0x01,
		/* Carrier Data Reference Length */
		0x01,
		/* Carrier Data Reference */
		0x30,
		/* Auxiliary Data Reference Count */
		0x00
	};


	if(bt == NULL)
		return 1;

	record_ch.buffer = ndef_buffer_ch;

	memcpy(record_ch.buffer,BT_CH_header,sizeof(BT_CH_header));
	record_ch.Wifi_CH_header_length = sizeof(BT_CH_header);
	record_ch.Wifi_CH_header_offset = sizeof(BT_CH_header);

	/*  MB=0b, ME=1b, CF=0b, SR=1b, IL=1b, TNF=010b */
	record_ch.buffer[record_ch.Wifi_CH_header_offset] =0x5A;

	/* 2. type */
	NioWlc_ndef_set_type(&record_ch, bt_ndef_type);

	/* 3. id */
	NioWlc_ndef_set_id(&record_ch, bt_ndef_id);

	/* 4. payload */
	/* 4.1 mac address in bigendian */
	NioWlc_ndef_set_bt_info(&record_ch, bt,len);



#ifdef DEBUG_DELAY_TICK
	tick_out = ARM_CM_DWT_CYCCNT;
	UART_MESSAGE_1("\nNioWlc_nfc_set_bt_info, run cycle=%d\n\r", tick_out-tick_in);
#endif

	return 0;
}

uint32_t NioWlc_nfc_start_bt_paring(NioWlc_BtWifi_Cb cb)
{
	uint32_t ret = 0;
#ifdef DEBUG_DELAY_TICK
	uint32_t tick_out = 0;
	uint32_t tick_in = ARM_CM_DWT_CYCCNT;
#endif

	if(nfc_state == NFC_CARDEMU_BT) {
		ret = NioWlc_nfc_start_paring(cb);
	} else
		ret = 1;

#ifdef DEBUG_DELAY_TICK
	tick_out = ARM_CM_DWT_CYCCNT;
	UART_MESSAGE_1("\NioWlc_nfc_start_bt_paring, run cycle=%d\n\r", tick_out-tick_in);
#endif

	return ret;
}

uint32_t NioWlc_nfc_stop_bt_paring(void)
{
	return 0;
}

uint32_t NioWlc_nfc_set_wifi_info(struct wifi_info *wifi,int len)
{
#ifdef DEBUG_DELAY_TICK
	uint32_t tick_out = 0;
	uint32_t tick_in = ARM_CM_DWT_CYCCNT;
#endif

#ifdef NIO_ET7
	uint8_t Wifi_CH_header[15]=
	{
		/* MB=1b, ME=0b, CF=0b, SR=1b, IL=0b, TNF=001b */
		0x91,
		/* Type Length */
	    0x02,
		/* Payload Length */
	    0x0A,
		/* Record Type */
	    'H','s',
		/* Version Numbe */
	    0x12,
		/* 可选载波 */
		/* MB=1b, ME=1b, CF=0b, SR=1b, IL=0b, TNF=001b */
		0xD1,
		0x02,
		0x04,
		'a','c',
		/* Carrier Flags: CPS=1, "active"  */
		0x01,
		/* Carrier Data Reference Length */
		0x01,
		/* Carrier Data Reference */
		0x30,
		/* Auxiliary Data Reference Count */
		0x00
	};

#endif

#ifdef Nio_OOBData
	if(wifi == NULL)
	{
		return 1;
	}
#else
	if(wifi == NULL || wifi->ssid == NULL ||
		wifi->auth > WIFI_AUTH_WPA2_PERSONAL ||
		wifi->crypt > WIFI_CRYPT_MIXED ||
		(wifi->password == NULL && wifi->crypt != WIFI_CRYPT_NONE))
		return 1;

#endif

	record_snep.buffer = ndef_buffer_snep;

#ifdef NIO_ET7
	memcpy(record_snep.buffer,Wifi_CH_header,sizeof(Wifi_CH_header));
	record_snep.Wifi_CH_header_length = sizeof(Wifi_CH_header);
	record_snep.Wifi_CH_header_offset = sizeof(Wifi_CH_header);

	/*  MB=0b, ME=1b, CF=0b, SR=1b, IL=1b, TNF=010b */
	record_snep.buffer[record_snep.Wifi_CH_header_offset] =0x5A;
#else
	record_snep.Wifi_CH_header_length = 0;
	record_snep.Wifi_CH_header_offset = 0;

	/* 1. format */
	ndef_buffer_snep[0] = 0xDA;

#endif

	/* 2. type */
	NioWlc_ndef_set_type(&record_snep, wifi_ndef_type);

	/* 3. id */
	NioWlc_ndef_set_id(&record_snep, wifi_ndef_id);

	/* 4. payload */
	NioWlc_ndef_set_wifi_info(&record_snep, wifi,len);

	nfc_state = NFC_CARDEMU_WIFI;

#ifdef DEBUG_DELAY_TICK
	tick_out = ARM_CM_DWT_CYCCNT;
	UART_MESSAGE_1("\NioWlc_nfc_set_wifi_info, run cycle=%d\n\r", tick_out-tick_in);
#endif

	return 0;
}

uint32_t NioWlc_nfc_start_wifi_paring(NioWlc_BtWifi_Cb cb)
{
	uint32_t ret;
#ifdef DEBUG_DELAY_TICK
	uint32_t tick_out = 0;
	uint32_t tick_in = ARM_CM_DWT_CYCCNT;
#endif

	if(nfc_state == NFC_CARDEMU_WIFI) {
		ret = NioWlc_nfc_start_paring(cb);
	} else
		ret = 1;

#ifdef DEBUG_DELAY_TICK
	tick_out = ARM_CM_DWT_CYCCNT;
	UART_MESSAGE_1("\NioWlc_nfc_start_wifi_paring, run cycle=%d\n\r", tick_out-tick_in);
#endif

	return ret;
}

uint32_t NioWlc_nfc_stop_wifi_paring(void)
{
	return 0;
}
