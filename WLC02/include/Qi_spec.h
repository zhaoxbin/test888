/*
 * Qi_spec.h
 *
 *  Created on: 2019年7月5日
 *      Author: jiangxl
 */

#ifndef QI_SPEC_H_
#define QI_SPEC_H_

//==========================================================================
//              Timeout Spec, all are in milliseconds
//==========================================================================

#define T_TERMINATE     28

// --------Ping Phase ---------------
#define T_PING          70
#define T_FIRST         20           //
#define T_EXPIRE        90              //Tx shall remove power with T_EXPIRE after the start of the Signal Strength PAcket

//-------- IDentification & Configuration Phase --------
#define T_DELAY_MIN     5
#define T_DELAY_MAX     205
#define T_NEXT          200      //21
#define T_MAX           170      //170
#define T_CONFIG        1700      //21


//-------- Power Transfer Phase --------
#define T_TIMEOUT       3000//1700//(500)  //clock
#define T_POWER         (24000 - 500)  //clock

#define TIME_MARGIN     5
#define LED_TIMEOUT     500


//==========================================================================
//             Packet Spec
//==========================================================================

//ping phase
#define HEADER_SIGNAL_STRENGTH          0x01
#define SIZE_SIGNAL_STRENGTH            1

#define HEADER_END_POWER_TRANSFER       0x02
#define SIZE_END_POWER_TRANSFER         1

//identification & configuration

#define HEADER_POWER_CONTROL_HOLD_OFF   0x06
#define SIZE_POWER_CONTROL_HOLD_OFF     1

#define HEADER_CONFIGURATION            0x51
#define SIZE_CONFIGURATION              5

#define HEADER_IDENTIFICATION           0x71
#define SIZE_IDENTIFICATION             7

#define HEADER_EXTENDED_IDENTIFICATION  0x81
#define SIZE_EXTENDED_IDENTIFICATION    8

//power transfer phase

//#define HEADER_END_POWER_TRANSFER     0x02
//#define SIZE_END_POWER_TRANSFER       1

#define HEADER_CONTROL_ERROR            0x03
#define SIZE_CONTROL_ERROR              1

#define HEADER_RECEIVED_POWER          0x04
#define SIZE_RECEIVED_POWER            1

#define HEADER_CHARGE_STATUS            0x05
#define SIZE_CHARGE_STATUS              1

//identification & configuration / power trasnfer phase

#define HEADER_PROPRIETARY_0X18         0x18
#define SIZE_PROPRIETARY_0X18           1

#define HEADER_PROPRIETARY_0X19         0x19
#define SIZE_PROPRIETARY_0X19           1

#define HEADER_PROPRIETARY_0X28         0x28
#define SIZE_PROPRIETARY_0X28           2

#define HEADER_PROPRIETARY_0X29         0x29
#define SIZE_PROPRIETARY_0X29           2

#define HEADER_PROPRIETARY_0X38         0x38
#define SIZE_PROPRIETARY_0X38           3

#define HEADER_PROPRIETARY_0X48         0x48
#define SIZE_PROPRIETARY_0X48           4

#define HEADER_PROPRIETARY_0X58         0x58
#define SIZE_PROPRIETARY_0X58           5

#define HEADER_PROPRIETARY_0X68         0x68
#define SIZE_PROPRIETARY_0X68           6

#define HEADER_PROPRIETARY_0X78         0x78
#define SIZE_PROPRIETARY_0X78           7

#define HEADER_PROPRIETARY_0X84         0x84
#define SIZE_PROPRIETARY_0X84           8

#define HEADER_PROPRIETARY_0XA4         0xa4
#define SIZE_PROPRIETARY_0XA4           12

#define HEADER_PROPRIETARY_0XC4         0xc4
#define SIZE_PROPRIETARY_0XC4           16

#define HEADER_PROPRIETARY_0XE2         0xe2
#define SIZE_PROPRIETARY_0XE2           20

#define HEADER_PROPRIETARY_0XF2         0xf2
#define SIZE_PROPRIETARY_0XF2           24

#define MAX_MESSAGE_SIZE                24




//==========================================================================
//             End Power Transfer Code
//==========================================================================

#define EPTC_UNKNOWN            0x00

//0x01-The receiver should use this value if it determines that the battery of
// the mobile device is fully charged. On receipt of an end power transfer
// packet containing this value,the transmitter sholud set any "charged"
// indication on its user interface that is associated with the receiver.
#define EPTC_CHARGE_COMPLETE    0x01

//0x02-The receiver may use this value if it has encountered some internal
// problem,e.g. a software or logic error.
#define EPTC_INTERNAL_FAULT     0x02

//0x03-The receiver should use this value if it has measured a temperature
// within the mobile device that exceeds a limit.
#define EPTC_OVER_TEMPERATURE   0x03

//0x04-The receiver should use this value if it has measured a voltage
// within the mobile device that exceeds a limit.
#define EPTC_OVER_VOLTAGE       0x04

//0x05-The receiver should use this value if it has measured a current
// within the mobile device that exceeds a limit.
#define EPTC_OVER_CURRENT       0x05

//0x06-The receiver should use this value if it has determined a problem
// with the battery of the mobile device.
#define EPTC_BATTERY_FAILURE    0x06

//0x07-The receiver should use this value if it desires to renegoticate a
// power transfer contract.
#define EPTC_RECONFIGURE        0x07

//0x08-The receiver should use this value if it determinates that the
// transmitter does not respond to control error packets as expected
// (i.e. does not increase/decrease its primary cell current appropriately).
#define EPTC_NO_RESPONSE        0x08

/*

//调整频率pid参数
#define KP      10
#define KI      5     //Qi手册上,此值是0.05,为了不用浮点数,扩大100倍,下面再用100除掉
#define KD      0
#define MI      3000
#define MPID    20000
#define T_INNER 24

//调整占空比pid参数
#define KP_DUTY         10
#define KI_DUTY         5     //Qi手册上,此值是0.05,为了不用浮点数,扩大100倍,下面再用100除掉
#define KD_DUTY         0
#define MI_DUTY         3000
#define MPID_DUTY       20000
#define T_INNER_DUTY    24
#define SV_DUTY         1     //Qi手册上,此值是-0.01,为了不用浮点数,扩大100倍,下面再用100除掉
                              //计算时,本来减的,用加


typedef struct
{
  BYTE header;
  BYTE message[MAX_MESSAGE_SIZE];
  BYTE msgSize;
}Packet;


typedef union uB0
{
    BYTE   byte;
    struct
    {
        BYTE maxPower       : 6;
        BYTE powerClass     : 2;
    }bits;
}tB0;

typedef union uB2
{
    BYTE   byte;
    struct
    {
        BYTE count          : 3;
        BYTE reservedBits   : 4;
        BYTE Prop           : 1;
    }bits;
}tB2;

typedef union uB3
{
    BYTE   byte;
    struct
    {
        BYTE windowOffset   : 3;
        BYTE windowSize     : 5;
    }bits;
}tB3;

typedef struct
{
    tB0   b0;
    BYTE  reserved1;
    tB2   b2;
    tB3   b3;
    BYTE  reserved2;
}Configuration;


typedef struct
{
  BYTE minorVersion     :4;
  BYTE majorVersion     :4;
}QiVersion;

*/





#endif /* QI_SPEC_H_ */
