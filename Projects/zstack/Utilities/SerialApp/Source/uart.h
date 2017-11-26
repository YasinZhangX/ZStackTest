#ifndef UART_H
#define UART_H
#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Constants
 */
#ifndef TX_BUFF_SZ
#define TX_BUFF_SZ 64
#endif

/*
 * Global variables
 */
extern uint8 UART0_TX_BUFF[TX_BUFF_SZ];          // Rx buffer

/*
 * Global Functions
 */
extern uint8 Uart0_Process(void);
extern void PrintAddrInfo(uint16 shortAddr, uint8 *pIeeeAddr);

#ifdef __cplusplus
}
#endif
#endif /* UART_H */
