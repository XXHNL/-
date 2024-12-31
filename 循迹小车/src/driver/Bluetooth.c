#include "Bluetooth.h"
#include "GPIO.h"
#include "RTX51TNY.h"
#include "Light.h"
#include "UART.h"
#include "Switch.h"
#include "NVIC.h"

void Bluetooth_GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1;    // 指定要初始化的IO
    GPIO_InitStructure.Mode = GPIO_PullUp;    // 设置为上拉输入
    GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);  // 初始化
}

void Bluetooth_UART_Config(void) {
    // 串口1的配置
    COMx_InitDefine COMx_InitStructure;
    COMx_InitStructure.UART_Mode = UART_8bit_BRTx;  // 设置为8位UART模式
    COMx_InitStructure.UART_BRT_Use = BRT_Timer1;    // 使用定时器1生成波特率
    COMx_InitStructure.UART_BaudRate = 9600ul;       // 设置波特率9600
    COMx_InitStructure.UART_RxEnable = ENABLE;       // 启用接收
    COMx_InitStructure.BaudRateDouble = DISABLE;     // 不使用波特率加倍
    UART_Configuration(UART1, &COMx_InitStructure);  // 初始化串口1

    NVIC_UART1_Init(ENABLE, Priority_1);  // 启用中断，优先级为Priority_1
    UART1_SW(UART1_SW_P30_P31);  // 使用P30和P31作为UART1的引脚

    // 串口2的配置
    COMx_InitStructure.UART_Mode = UART_8bit_BRTx;  // 设置为8位UART模式
    COMx_InitStructure.UART_BRT_Use = BRT_Timer1;    // 使用定时器1生成波特率
    COMx_InitStructure.UART_BaudRate = 9600ul;       // 设置波特率9600
    COMx_InitStructure.UART_RxEnable = ENABLE;       // 启用接收
    COMx_InitStructure.BaudRateDouble = DISABLE;     // 不使用波特率加倍
    UART_Configuration(UART2, &COMx_InitStructure);  // 初始化串口2

    NVIC_UART2_Init(ENABLE, Priority_1);  // 启用串口2中断，优先级为Priority_1
    UART2_SW(UART2_SW_P10_P11);  // 使用P10和P11作为UART2的引脚
}

void task_bluetooth(){
    int i = 0;

    // 获取PC发送过来的串口数据
    if(COM1.RX_Cnt > 0 && --COM1.RX_TimeOut == 0){
        // 将接收到的数据发送给蓝牙
        for(i = 0; i < COM1.RX_Cnt; i++){
            TX2_write2buff(RX1_Buffer[i]);
        }
        COM1.RX_Cnt = 0;
    }

    // 获取BT发送过来的串口数据
    if(COM2.RX_Cnt > 0 && --COM2.RX_TimeOut == 0){
        for(i = 0; i < COM2.RX_Cnt; i++){
            TX1_write2buff(RX2_Buffer[i]);
        }
        for(i = 0; i < COM2.RX_Cnt; i += 8){
            // 处理蓝牙数据
            handle_bt_data(&RX2_Buffer[i]);
        }
        COM2.RX_Cnt = 0;
    }
}
