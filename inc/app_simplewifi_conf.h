/*
 * File     :   app_simplewifi_conf.h
 * This file is part of gdm3d-uav project
 * Hardware Description:
 *      SimpleWIFI module connected to STM32F103C8T6 chip via usart2 port
 *      SimpleWIFI is a serial (USART/SPI) to wifi module, it consists of a
 *      stm32xxx chip and a wifi module.
 *      In this project, PA2 and PA3 (USART2), PC14 and PC15 (osc/gpio), PA1
 *      and PA0 are connected to this module. Actually, using the two gpio
 *      (usart2) is enough to control this module, other occupied pins are
 *      considered to extend to soft SPI port if needed.
 * Change logs:
 * Date         Author  Notes
 * 2014-07-10   Roice   the first version
 */

#ifndef __APP_SIMPLEWIFI_CONF_H__
#define __APP_SIMPLEWIFI_CONF_H__
int app_simplewifi_init(void);
#endif
