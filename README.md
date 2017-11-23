# ZStackTest

本工程的应用主要根据 **SerialApp** 改编而成。
本工程用到的硬件图如下：
![LED&KEY引脚图](https://github.com/YasinZhangX/ZStackTest/raw/master/res/LED-KEY.png "LED&KEY引脚图")

本工程实现以下功能：  

## 第一部分

1、KEY1控制LED1状态取反  

- 关键代码
    ```c
    HalLedSet(HAL_LED_1, HAL_LED_MODE_TOGGLE);
    ```

2、串口0（P0_2和P0_3）打印网络状态变化信息，以及自身与父节点的短地址和MAC地址。直接按S2，也可以获取自身与父节点的短地址和MAC地址
- `NLME_GetShortAddr()` – returns this device’s 16 bit network address.
- `NLME_GetExtAddr()` – returns this device’s 64 bit extended address.
- Use the following functions to get this device’s parent’s addresses (defined in Z-Stack API Doc). Note that the term “Coord” in these functions does not refer to the ZigBee Coordinator, but instead to the device’s parent (MAC Coordinator):
- `NLME_GetCoordShortAddr()` – returns this device’s parent’s 16 bit short address.
- `NLME_GetCoordExtAddr()` – returns this device’s parent’s 64 bit extended address.

3、串口0接收指令，实现LED1亮灭控制。“LEDxON"表示LEDx开，“LEDxOFF”表示LEDx关

- 项目主要代码在 `uart.c` 和 `uart.h` 文件下

## 第二部分

4、单播通信

5、广播通信

6、组播通信

