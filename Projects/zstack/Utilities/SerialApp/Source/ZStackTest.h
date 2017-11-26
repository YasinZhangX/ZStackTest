/**************************************************************************************************
  Filename:       ZStackTest.h
  Revised:        $Date: 2009-02-25 17:31:49 -0800 (Wed, 25 Feb 2009) $
  Revision:       $Revision: 19273 $

  Description:    This file contains the Serial Transfer Application definitions.


  Copyright 2004-2007 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED �AS IS? WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

#ifndef ZStackTest_H
#define ZStackTest_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "ZComDef.h"

/*********************************************************************
 * CONSTANTS
 */

// These constants are only for example and should be changed to the
// device's needs
#define ZStackTest_ENDPOINT           11

#define ZStackTest_PROFID             0x0F05
#define ZStackTest_DEVICEID           0x0001
#define ZStackTest_DEVICE_VERSION     0
#define ZStackTest_FLAGS              0

#define ZStackTest_MAX_CLUSTERS         4
#define ZStackTest_P2P_CLUSTERID        1
#define ZStackTest_BROADCAST_CLUSTERID  2
#define ZStackTest_GROUP_CLUSTERID      3
#define ZStackTest_CLUSTERID2           4

// Application Events (OSAL) - These are bit weighted definitions.
#define ZStackTest_SEND_EVT           0x0001
#define ZStackTest_RESP_EVT           0x0002
#define ZStackTest_KEY_PRESS_EVT      0x0004
#define ZStackTest_P2P_EVT            0x0008
#define ZStackTest_BROADCAST_EVT      0x0010
#define ZStackTest_GROUP_EVT          0x0020

// OTA Flow Control Delays
#define ZStackTest_ACK_DELAY          1
#define ZStackTest_NAK_DELAY          16

// OTA Flow Control Status
#define OTA_SUCCESS                  ZSuccess
#define OTA_DUP_MSG                 (ZSuccess+1)
#define OTA_SER_BUSY                (ZSuccess+2)

//Project profile
#define FIRST_PART                   FALSE
#define SECOND_PART                  TRUE

// Key Press Delay
#define ZStackTest_KEY_PRESS_DELAY   1500     // delay 1.5 seconds

// Group ID for Flash Command
#define ZStackTest_GROUP                 0x0001

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */
extern byte ZStackTest_TaskID;

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task Initialization for the Serial Transfer Application
 */
extern void ZStackTest_Init( byte task_id );

/*
 * Task Event Processor for the Serial Transfer Application
 */
extern UINT16 ZStackTest_ProcessEvent( byte task_id, UINT16 events );

/*
 * Message Send Functions
 */
extern void ZStackTest_Send_P2P_Message(void);
extern void ZStackTest_Send_Broadcast_Message(void);
extern void ZStackTest_Send_Group_Message(void);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* ZStackTest_H */
