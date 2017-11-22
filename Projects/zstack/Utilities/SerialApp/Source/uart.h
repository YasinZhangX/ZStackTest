#ifndef UART_H  
#define UART_H  
#ifdef __cplusplus  
extern "C"  
{  
#endif  
  
extern void Uart0_Handle(uint8* ZStackTest_TxBuf);  
extern void PrintAddrInfo(uint16 shortAddr, uint8 *pIeeeAddr);
  
#ifdef __cplusplus  
}  
#endif  
#endif /* UART_H */  