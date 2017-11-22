#include <string.h>
#include <stdio.h>

#include "ZComDef.h"
#include "hal_types.h"  
#include "hal_led.h"
#include "hal_uart.h"
#include "OnBoard.h"

#include "uart.h"

void GetIeeeAddr(uint8 * pIeeeAddr, uint8 *pStr);
void Delay_ms(uint8 Time);

void Uart0_Handle(uint8* ZStackTest_TxBuf)
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

//通过串口输出短地址 IEEE
void PrintAddrInfo(uint16 shortAddr, uint8 *pIeeeAddr)
{
    uint8 strIeeeAddr[17] = {0};
    char  buff[30] = {0};    
    
    //获得短地址   
    sprintf(buff, "shortAddr:%04X   IEEE:", shortAddr);  
 
    //获得IEEE地址
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

void Delay_ms(uint8 Time)//n ms延时
{
  unsigned char i;
  while(Time--)
  {
    for(i=0;i<100;i++)
     MicroWait(10);
  }
}