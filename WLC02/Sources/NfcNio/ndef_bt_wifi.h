#include <hal.h>
#include <Nfc.h>

/* BlueTooth OOB settings */
#define MAC_ADDRESS_SIZE		6u
#define CLASSOFDEV_ADDRESS_SIZE	3u
#define HASHVALUE_SIZE			16u
#define RANDOMIZERVALUE_SIZE	16u

#define MAX_OOB_DATASIZE (200)


struct bt_info {
#ifdef Nio_OOBData
	uint8_t bt_oob[MAX_OOB_DATASIZE];
#else
	/* big endian */
	uint8_t mac[MAC_ADDRESS_SIZE];
	/* little endian */
	uint8_t ClassOfDev[CLASSOFDEV_ADDRESS_SIZE];
	uint8_t HashValue[HASHVALUE_SIZE];
	uint8_t RandomizerValue[RANDOMIZERVALUE_SIZE];
	char *UserfriendlyName;
#endif
};

typedef enum
{
	WIFI_AUTH_OPEN = 0x01,
	WIFI_AUTH_WPA_PERSONAL = 0x02,
	WIFI_AUTH_SHARED = 0x04,
	WIFI_AUTH_WPA_ENTERPRISE = 0x08,
	WIFI_AUTH_WPA2_ENTERPRISE = 0x10,
	WIFI_AUTH_WPA2_PERSONAL = 0x20,
}auth_type;

typedef enum
{
	WIFI_CRYPT_NONE = 0x01,
	WIFI_CRYPT_WEP = 0x02,
	WIFI_CRYPT_TKIP = 0x04,
	WIFI_CRYPT_AES = 0x08,
	WIFI_CRYPT_MIXED = 0x0c,
}crypt_type;

struct wifi_info {
#ifdef Nio_OOBData
	uint8_t wifi_oob[MAX_OOB_DATASIZE];
#else

	uint8_t network_index;
	char * ssid;
	char * password;
	auth_type auth;
	crypt_type crypt;
	uint8_t mac[MAC_ADDRESS_SIZE];
#endif
};

struct ndef_record {
    char * buffer;
    uint32_t length;

    /* ÎµÀ´ET7ÐÂÔö */
    uint8_t Wifi_CH_header_length;
    uint32_t Wifi_CH_header_offset;

    uint8_t type_length;
    uint32_t type_offset;

    uint8_t id_length;
    uint32_t id_offset;

    uint32_t payload_length;
    uint32_t payload_offset;
};

extern struct ndef_record record_snep;
extern struct ndef_record record_ch;

typedef void (*NioWlc_BtWifi_Cb)(uint32_t mode, uint32_t status);

uint32_t NioWlc_nfc_set_bt_info(struct bt_info *bt,int len);
uint32_t NioWlc_nfc_request_bt_info(struct bt_info *bt,int len);
uint32_t NioWlc_nfc_start_bt_paring(NioWlc_BtWifi_Cb cb);
uint32_t NioWlc_nfc_stop_bt_paring(void);

uint32_t NioWlc_nfc_set_wifi_info(struct wifi_info *wifi,int len);
uint32_t NioWlc_nfc_start_wifi_paring(NioWlc_BtWifi_Cb cb);
uint32_t NioWlc_nfc_stop_wifi_paring(void);
