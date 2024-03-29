/*********************************************************************
 *
 *                  Header for Main Demo App
 *
 *********************************************************************
 * FileName:           MainDemo.h
 * Dependencies:    Compiler.h
 * Processor:          PIC32MX695F512H
 * Compiler:           Microchip  XC32 Compiler
 * Company:          Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2013 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 *
 * Author               Date    	Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * A. Ong					10/22/12       Wifi G Demo        (MRF24WG)
 ********************************************************************/
#ifndef _MAINDEMO_H
#define _MAINDEMO_H


// Include all headers for any enabled TCPIP Stack functions
#include "TCPIP Stack/TCPIP.h"

#if defined(STACK_USE_ZEROCONF_LINK_LOCAL)
    #include "TCPIP Stack/ZeroconfLinkLocal.h"
#endif

#if defined(STACK_USE_ZEROCONF_MDNS_SD)
    #include "TCPIP Stack/ZeroconfMulticastDNS.h"
#endif

#if defined ( EZ_CONFIG_SCAN )
    #include "TCPIP Stack/WFEasyConfig.h"
#endif

#include "WF_Config.h" 


#if defined ( EZ_CONFIG_STORE ) 
    void RestoreWifiConfig(void);
    #define     WF_EEPROM_CFG_VER   0xdeu
#endif

void SaveAppConfig(const APP_CONFIG *AppConfig);


//--------------------------------------------------------------------------------
// These defines use the C preprocessor to create the AppConfig structure elements
//--------------------------------------------------------------------------------
// MDEF(R,N) macro concatenates tokens to form "MY_DEFAULT_<R>BYTE<N>"
// For example MDEF(IP_ADDR_,4) expands to "MY_DEFAULT_IP_ADDR_BYTE4"

#define MDEF(R,N) MY_DEFAULT_ ## R ## BYTE ## N

// BUILD_MYDEFAULT32 invokes the MDEF(R,N) macro 4 times to create a 32 bit
// value from 4 byte values.
//
// For example BUILD_MYDEFAULT32(IP_ADDR_) expands to
// (MY_DEFAULT_IP_ADDR_BYTE4<<24|MY_DEFAULT_IP_ADDR_BYTE3<<16
//  |MY_DEFAULT_IP_ADDR_BYTE2<<8|MY_DEFAULT_IP_ADDR_BYTE1)

#define BUILD_MYDEFAULT32(R) (MDEF(R,4)<<24|MDEF(R,3)<<16|MDEF(R,2)<<8|MDEF(R,1))

// MACD(N) expands to MY_DEFAULT_MAC_BYTE<N>
// For example MACD(1) expands to MY_DEFAULT_MAC_BYTE1

#define MACD(N) MY_DEFAULT_MAC_BYTE ## N

// Used for Wi-Fi assertions
#define WF_MODULE_NUMBER   WF_MODULE_MAIN_DEMO


void DoUARTConfig(void);


// Define a header structure for validating the AppConfig data structure in EEPROM/Flash
typedef struct
{
	unsigned short wConfigurationLength;	// Number of bytes saved in EEPROM/Flash (sizeof(APP_CONFIG))
	unsigned short wOriginalChecksum;		// Checksum of the original AppConfig defaults as loaded from ROM (to detect when to wipe the EEPROM/Flash record of AppConfig due to a stack change, such as when switching from Ethernet to Wi-Fi)
	unsigned short wCurrentChecksum;		// Checksum of the current EEPROM/Flash data.  This protects against using corrupt values if power failure occurs while writing them and helps detect coding errors in which some other task writes to the EEPROM in the AppConfig area.
} NVM_VALIDATION_STRUCT;


void DisplayIPValue(IP_ADDR IPVal);

#endif // _MAINDEMO_H

int start_time;    // starting time for collecting motion sensor data
int end_time;      // stop time for collection

int command;      // command sent by cloud server. 0 means no command at the moment.
int cmd_no;       // command No. sent by cloud server. 0 means NULL at the moment.

int ack;          // acknowledgement code from cloud server for data verification check. 0 means no data received yet.

#define MAXSENSORDATASIZE         56000       //  for collecting MMA8451 Q acceleration sensor XYZ sample output (2 bytes for each X, Y , Z data output; 1 byte for Data Status Register
BYTE motionsensor[MAXSENSORDATASIZE];
int LastSitDownTime;
int LastFallDetectedTime;

#define SERVERIP  {192,168,33,10}       //  for cloud server IP 
