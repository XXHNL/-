#include "Bluetooth.h"
#include "GPIO.h"
#include "RTX51TNY.h"
#include "Light.h"
#include "UART.h"
#include "Switch.h"
#include "NVIC.h"

void Bluetooth_GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1;    // ָ��Ҫ��ʼ����IO
    GPIO_InitStructure.Mode = GPIO_PullUp;    // ����Ϊ��������
    GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);  // ��ʼ��
}

void Bluetooth_UART_Config(void) {
    // ����1������
    COMx_InitDefine COMx_InitStructure;
    COMx_InitStructure.UART_Mode = UART_8bit_BRTx;  // ����Ϊ8λUARTģʽ
    COMx_InitStructure.UART_BRT_Use = BRT_Timer1;    // ʹ�ö�ʱ��1���ɲ�����
    COMx_InitStructure.UART_BaudRate = 9600ul;       // ���ò�����9600
    COMx_InitStructure.UART_RxEnable = ENABLE;       // ���ý���
    COMx_InitStructure.BaudRateDouble = DISABLE;     // ��ʹ�ò����ʼӱ�
    UART_Configuration(UART1, &COMx_InitStructure);  // ��ʼ������1

    NVIC_UART1_Init(ENABLE, Priority_1);  // �����жϣ����ȼ�ΪPriority_1
    UART1_SW(UART1_SW_P30_P31);  // ʹ��P30��P31��ΪUART1������

    // ����2������
    COMx_InitStructure.UART_Mode = UART_8bit_BRTx;  // ����Ϊ8λUARTģʽ
    COMx_InitStructure.UART_BRT_Use = BRT_Timer1;    // ʹ�ö�ʱ��1���ɲ�����
    COMx_InitStructure.UART_BaudRate = 9600ul;       // ���ò�����9600
    COMx_InitStructure.UART_RxEnable = ENABLE;       // ���ý���
    COMx_InitStructure.BaudRateDouble = DISABLE;     // ��ʹ�ò����ʼӱ�
    UART_Configuration(UART2, &COMx_InitStructure);  // ��ʼ������2

    NVIC_UART2_Init(ENABLE, Priority_1);  // ���ô���2�жϣ����ȼ�ΪPriority_1
    UART2_SW(UART2_SW_P10_P11);  // ʹ��P10��P11��ΪUART2������
}

void task_bluetooth(){
    int i = 0;

    // ��ȡPC���͹����Ĵ�������
    if(COM1.RX_Cnt > 0 && --COM1.RX_TimeOut == 0){
        // �����յ������ݷ��͸�����
        for(i = 0; i < COM1.RX_Cnt; i++){
            TX2_write2buff(RX1_Buffer[i]);
        }
        COM1.RX_Cnt = 0;
    }

    // ��ȡBT���͹����Ĵ�������
    if(COM2.RX_Cnt > 0 && --COM2.RX_TimeOut == 0){
        for(i = 0; i < COM2.RX_Cnt; i++){
            TX1_write2buff(RX2_Buffer[i]);
        }
        for(i = 0; i < COM2.RX_Cnt; i += 8){
            // ������������
            handle_bt_data(&RX2_Buffer[i]);
        }
        COM2.RX_Cnt = 0;
    }
}
