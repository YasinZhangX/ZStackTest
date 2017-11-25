#include <string.h>
#include <stdio.h>

#include "AF.h"
#include "ZComDef.h"
#include "OnBoard.h"
#include "ZStackTest.h"

#include "hal_types.h"
#include "hal_led.h"
#include "hal_uart.h"

#include "uart.h"

void GetIeeeAddr(uint8 * pIeeeAddr, uint8 *pStr);
void Delay_ms(uint8 Time);

void Uart0_Handle(uint8* ZStackTest_TxBuf)
{
  uint8 cmd[256]={0};
  uint8 tmpbuf[256]={0};

  if(strstr((const char *)ZStackTest_TxBuf,"LED")!=NULL)  //receive cmd "LED"
  {
    if (strstr((const char*)ZStackTest_TxBuf, "LED1ON") != NULL)
    {
      HalLedSet(HAL_LED_1, HAL_LED_MODE_ON);
    }
    if (strstr((const char*)ZStackTest_TxBuf, "LED1OFF") != NULL)
    {
      HalLedSet(HAL_LED_1, HAL_LED_MODE_OFF);
    }
    if (strstr((const char*)ZStackTest_TxBuf, "LED2ON") != NULL)
    {
      HalLedSet(HAL_LED_2, HAL_LED_MODE_ON);
    }
    if (strstr((const char*)ZStackTest_TxBuf, "LED2OFF") != NULL)
    {
      HalLedSet(HAL_LED_2, HAL_LED_MODE_OFF);
    }
    if (strstr((const char*)ZStackTest_TxBuf, "LED3ON") != NULL)
    {
      HalLedSet(HAL_LED_3, HAL_LED_MODE_ON);
    }
    if (strstr((const char*)ZStackTest_TxBuf, "LED3OFF") != NULL)
    {
      HalLedSet(HAL_LED_3, HAL_LED_MODE_OFF);
    }
  }

  if(strstr((const char *)ZStackTest_TxBuf,"AT") != NULL)  //receive cmd "AT"
  {
    sscanf((const char*)ZStackTest_TxBuf, "%*[^+]%*c%[^#]%*c%s", cmd, tmpbuf);
    if (strstr((const char*)cmd, "GETADDR") != NULL) {
      char addrbuff[20] = {0};
      sprintf(addrbuff, "SelfshortAddr:%04X", NLME_GetShortAddr());
      HalUARTWrite (SERIAL_APP_PORT, (uint8 *)addrbuff, strlen(addrbuff));
    }
    if (strstr((const char*)cmd, "P2P") != NULL) {
      ZStackTest_Send_P2P_Message();
    }
    if (strstr((const char*)cmd, "BROADCAST") != NULL) {
      ZStackTest_Send_Broadcast_Message();
    }
    if (strstr((const char*)cmd, "GROUP") != NULL) {
      ZStackTest_Send_Group_Message();
    }
  }
}

//Print short address and IEEE address from UART
void PrintAddrInfo(uint16 shortAddr, uint8 *pIeeeAddr)
{
    uint8 strIeeeAddr[17] = {0};
    char  buff[30] = {0};

    //print shortAddr to buff
    sprintf(buff, "shortAddr:%04X   IEEE:", shortAddr);

    //print IEEE address to strIeeeAddr
    GetIeeeAddr(pIeeeAddr, strIeeeAddr);

    HalUARTWrite (SERIAL_APP_PORT, (uint8 *)buff, strlen(buff));
    Delay_ms(10);
    HalUARTWrite (SERIAL_APP_PORT, strIeeeAddr, 16);
    HalUARTWrite (SERIAL_APP_PORT, "\r\n", 2);
}

void GetIeeeAddr(uint8 * pIeeeAddr, uint8 *pStr)
{
  uint8 i;
  uint8 *xad = pIeeeAddr;

  for (i = 0; i < Z_EXTADDR_LEN*2; xad--)
  {
    uint8 ch;
    ch = (*xad >> 4) & 0x0F;
    *pStr++ = ch + (( ch < 10 ) ? '0' : '7');
    i++;
    ch = *xad & 0x0F;
    *pStr++ = ch + (( ch < 10 ) ? '0' : '7');
    i++;
  }
}

void Delay_ms(uint8 Time) // Delay for n ms
{
  unsigned char i;
  while(Time--)
  {
    for(i=0;i<100;i++)
     MicroWait(10);
  }
}
