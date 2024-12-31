#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H
#include "Config.h"

void Bluetooth_GPIO_Config();
void Bluetooth_UART_Config();
void task_bluetooth();
void handle_bt_data(u8 dat[]);

#endif // !__BLUETOOTH_H