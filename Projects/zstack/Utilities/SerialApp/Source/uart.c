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

/*
 * variables
 */
uint8 UART0_TX_BUFF[TX_BUFF_SZ];          // Rx buffer
uint8 UART0_TX_STA = 0;                   // Rx state
uint8 UART0_TX_LEN = 0;                   // Rx length

/*
 * Local functions
 */
void Uart0_Handle(void);
void Uart0_Reset(void);
void GetIeeeAddr(uint8 * pIeeeAddr, uint8 *pStr);
void Delay_ms(uint8 Time);

uint8 Uart0_Process()
{
  uint8 Res;

  while (Hal_UART_RxBufLen(SERIAL_APP_PORT) && ((UART0_TX_STA&0x3F) < TX_BUFF_SZ))
  {
    HalUARTRead (SERIAL_APP_PORT, &Res, 1); // read one char from uart0
    UART0_TX_BUFF[UART0_TX_STA & 0x3F]=Res ;
    UART0_TX_STA++;

    if((UART0_TX_STA & 0x80)==0) // receive not finish
    {
      if(UART0_TX_STA & 0x40)  // has received one '#'
      {
        if (Res==0x0D | Res == 0x0A)
          UART0_TX_STA |= 0x80;  // receive one '#'
        else
          UART0_TX_STA &= 0xBF;  // next char isn't '#', cmd not end
      }
      else
      {
        if(Res==0x0D | Res == 0x0A)
          UART0_TX_STA |= 0x40;
      }
    }

    if((UART0_TX_STA & 0x80)==0x80)
    {
      UART0_TX_LEN = (UART0_TX_STA&0x3F)-2;
      Uart0_Handle();
      break;
    }
  }

  Uart0_Reset();
  return UART0_TX_LEN;
}

void Uart0_Handle()
{
  uint8 cmd[64]={0};
  uint8 tmpbuf[64]={0};

  if(strstr((const char *)UART0_TX_BUFF,"LED")!=NULL)  //receive cmd "LED"
  {
    if (strstr((const char*)UART0_TX_BUFF, "LED1ON") != NULL)
    {
      HalLedSet(HAL_LED_1, HAL_LED_MODE_ON);
    }
    if (strstr((const char*)UART0_TX_BUFF, "LED1OFF") != NULL)
    {
      HalLedSet(HAL_LED_1, HAL_LED_MODE_OFF);
    }
    if (strstr((const char*)UART0_TX_BUFF, "LED2ON") != NULL)
    {
      HalLedSet(HAL_LED_2, HAL_LED_MODE_ON);
    }
    if (strstr((const char*)UART0_TX_BUFF, "LED2OFF") != NULL)
    {
      HalLedSet(HAL_LED_2, HAL_LED_MODE_OFF);
    }
    if (strstr((const char*)UART0_TX_BUFF, "LED3ON") != NULL)
    {
      HalLedSet(HAL_LED_3, HAL_LED_MODE_ON);
    }
    if (strstr((const char*)UART0_TX_BUFF, "LED3OFF") != NULL)
    {
      HalLedSet(HAL_LED_3, HAL_LED_MODE_OFF);
    }
  }

  if(strstr((const char *)UART0_TX_BUFF,"AT") != NULL)  //receive cmd "AT"
  {
    sscanf((const char*)UART0_TX_BUFF, "%*[^+]%*c%[^#]%*c%s", cmd, tmpbuf);
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

void Uart0_Reset(void)
{
  memset(UART0_TX_BUFF, 0, 64);
  UART0_TX_STA = 0;
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
