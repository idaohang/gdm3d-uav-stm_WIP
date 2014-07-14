/*
 * File     :   app_simplewifi_conf.c
 * This file is part of gdm3d-uav project
 * Hardware Description:
 *      SimpleWIFI module connected to STM32F103C8T6 chip via usart2 port
 *      SimpleWIFI is a serial (USART/SPI) to wifi module, it consists of a
 *      stm32xxx chip and a wifi module.
 *      In this project, PA2 and PA3 (USART2), PC14 and PC15 (osc/gpio), PA1
 *      and PA0 are connected to this module. Actually, using the two gpio
 *      (usart2) is enough to control this module, other occupied pins are
 *      considered to extend to soft SPI port if needed.
 * Port Description:
 *      In this app, configuration of usart2 is not needed because RT-Thread
 *      OS has implemented it in it's driver file "usart.c". Initiating the
 *      usart port is a kind of simple thing as uncomment 
 *      "#define RT_USING_USART2" in "board.h" file.
 *      To use the usart port, refer to the I/O device chapter of RT-Thread 
 *      manual.
 * App Description:
 *      This app configures simplewifi module.
 * Change logs:
 * Date         Author  Notes
 * 2014-07-10   Roice   the first version
 */

#include "rtthread.h"

/* USAR receive message structure */
struct rx_msg
{
    rt_device_t dev;
    rt_size_t   size;
};
/* message queue for receiving message */
static struct rt_messagequeue  rx_messagequeue;
static rt_mq_t rx_mq = &rx_messagequeue;
/* mem pool for message queue */
static char msg_pool[1024];
/* receiving buffer for uart thread */
//static char uart_rx_buffer[64];

/* Callback Function */
rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    struct rx_msg msg;
    msg.dev = dev;
    msg.size = size;
rt_kprintf(" i am in the callback function now ");
    /* send message to the queue */
    rt_mq_send(rx_mq, &msg, sizeof(struct rt_messagequeue));
    rt_kprintf(" sent to the message ");
    return RT_EOK;
}

/****************************************************************************
* 名    称：int app_simplewifi_init(void)
* 功    能：configure SimpleWifi module.
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
int app_simplewifi_init(void)
{
    rt_device_t device;
    struct  rx_msg  msg; 
    rt_err_t result = RT_EOK;
char send_instruction[20];

rx_mq = &rx_messagequeue;

rt_kprintf(" start initiating message queue ");
/* initiating message queue */
rt_mq_init(rx_mq, "uart2_rx_mq", &msg_pool[0], sizeof(struct rx_msg), sizeof(msg_pool), RT_IPC_FLAG_FIFO);

	/* start initiating serial device uart2 */
    rt_kprintf(" Start initiating serial device uart2... \r\n");
    device = rt_device_find("uart2");
    if (device != RT_NULL)
    {
        /* set callback function and open this device */
        rt_device_set_rx_indicate(device, uart_input);
        rt_device_open(device, RT_DEVICE_OFLAG_RDWR);
        rt_kprintf(" Done initiating serial device uart2. \r\n");
    }
    else
    {
        rt_kprintf(" Error: Can't find uart2. \r\n");
        return -1;
    }

    /* start initiating simplewifi module */
    rt_kprintf(" Start initiating SimpleWifi module... \r\n");

send_instruction[0]='A';
send_instruction[1]='T';
send_instruction[2]='+';
send_instruction[3]='U';
send_instruction[4]='A';
send_instruction[5]='R';
send_instruction[6]='T';
send_instruction[7]='=';
send_instruction[8]='?';
send_instruction[9]='b';
send_instruction[10]='a';
send_instruction[11]='u';
send_instruction[12]='d';
send_instruction[13]=' ';
send_instruction[14]='r';
send_instruction[15]='a';
send_instruction[16]='t';
send_instruction[17]='e';
send_instruction[18]=0x0d;
send_instruction[19]='\0';

rt_kprintf("start sending");
    rt_device_write(device, 0, &send_instruction[0], 19);
    //rt_device_write(device, 0, "AT+UART=?baud rate", 7);
    result = rt_mq_recv(rx_mq, &msg, sizeof(struct rx_msg), 50);
rt_kprintf("result == %d", result);
    if(result == -RT_ETIMEOUT)
    {
        rt_kprintf("timeout");
    }
    if(result == RT_EOK)
    {
        rt_kprintf("result == RT_EOK");
        //rt_uint32_t rx_length;
        //rx_length = (sizeof(uart_rx_buffer)-1) > msg.size ? msg.size : sizeof(uart_rx_buffer) - 1;
        //rx_length = rt_device_read(msg.dev, 0, &uart_rx_buffer[0], rx_length);
        //uart_rx_buffer[rx_length] = '\0';
       


        //if(device != RT_NULL)
        //    rt_device_write(device, 0, &uart_rx_buffer[0], rx_length);
        //rt_kprintf(uart_rx_buffer);
    }

    return 0;
}

/**/
