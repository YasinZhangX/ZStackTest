# ZStackTest

本工程的应用主要根据 **SerialApp** 改编而成。
本工程用到的硬件图如下：
![LED&KEY引脚图](https://github.com/YasinZhangX/ZStackTest/raw/master/res/LED-KEY.png "LED&KEY引脚图")

本工程实现以下功能：  

## 第一部分

第一部分的代码要求在 `ZStackTest.h` 中设置 `FIRSET PART` 参数为 `TRUE`

1、KEY1控制LED1状态取反  

- 关键代码
    ```c
    HalLedSet(HAL_LED_1, HAL_LED_MODE_TOGGLE);
    ```

2、串口0（P0_2和P0_3）打印网络状态变化信息，以及自身与父节点的短地址和MAC地址。长按 `S1`，也可以获取自身与父节点的短地址和MAC地址
- `NLME_GetShortAddr()` – returns this device’s 16 bit network address.
- `NLME_GetExtAddr()` – returns this device’s 64 bit extended address.
- Use the following functions to get this device’s parent’s addresses (defined in Z-Stack API Doc). Note that the term “Coord” in these functions does not refer to the ZigBee Coordinator, but instead to the device’s parent (MAC Coordinator):
- `NLME_GetCoordShortAddr()` – returns this device’s parent’s 16 bit short address.
- `NLME_GetCoordExtAddr()` – returns this device’s parent’s 64 bit extended address.

3、串口0接收指令，实现LED1亮灭控制。“LEDxON"表示LEDx开，“LEDxOFF”表示LEDx关，指令以 `\r\n` 或 `\n\r` 结尾

- 项目主要代码在 `uart.c` 和 `uart.h` 文件下

串口命令如下：

| 命令 | 功能 |
| ---- | ---- |
|LED1ON|打开LED1|
|LED1OFF|关闭LED1|
|LED2ON|打开LED2|
|LED2OFF|关闭LED2|
|LED3ON|打开LED3|
|LED3OFF|关闭LED3|

## 第二部分

第二部分的代码要求在 `ZStackTest.h` 中设置 `SECOND PART` 参数为 `TRUE`

该部分功能均可通过串口指令触发
|指令|功能|
| --- | --- |
|AT+P2P|点对点发送消息给协调器，消息为“p2p_message”|
|AT+BROADCAST|广播发送消息给所有节点，消息为“broadcast_message”|
|AT+GROUP|分组发送消息给“Group1”,消息为“group_message”|

4、单播通信

发送函数为 `ZStackTest_Send_P2P_Message` , 设置地址为 `ZStackTest_P2P_DstAddr` ,设置 `endpoint` 为 `ZStackTest_epDesc`。

5、广播通信

发送函数为 `ZStackTest_Send_Broadcast_Message` , 设置地址为 `ZStackTest_Broadcast_DstAddr` ,设置 `endpoint` 为 `ZStackTest_epDesc`。

6、组播通信

- 组播通信的验证可以通过长按 `S1` 键来将 设备移出 `Group1`（长按`S1`亦可添加到 `Group1`）,移出 `Group1` 的设备 `LED2` 将会亮起
发送函数为 `ZStackTest_Send_Group_Message` , 设置地址为 `ZStackTest_Group_DstAddr` ,设置 `endpoint` 为 `ZStackTest_epDesc`。

