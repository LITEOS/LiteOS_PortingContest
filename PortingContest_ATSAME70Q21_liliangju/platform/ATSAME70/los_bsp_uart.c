#include "sam.h"
#include "los_bsp_uart.h"
#include "uart.h"
#include "Board_LED.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

extern void UART_Configure(Uart *uart,
					uint32_t mode,
					uint32_t baudrate,
					uint32_t masterClock);

extern uint8_t UART_GetChar(Uart *uart);
extern void UART_PutChar(Uart *uart, uint8_t c);

void Error_Handler(void)
{
  /* Turn LED4 on */
  LED_On(0);
  while(1)
  {
  }
}


void LOS_EvbUartInit(void)
{
	UART_Configure(UART0,4,115200,30000000);
	return ;
}


/*************************************************************************************************
 *  ���ܣ��򴮿�1����һ���ַ�                                                                    *
 *  ������(1) ��Ҫ�����͵��ַ�                                                                   *
 *  ���أ�                                                                                       *
 *  ˵����                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartWriteByte(char c)
{
	UART_PutChar(UART0, c);
	return ;
}

/*************************************************************************************************
 *  ���ܣ��򴮿�1����һ���ַ���                                                                  *
 *  ������(1) ��Ҫ�����͵��ַ���                                                                 *
 *  ���أ�                                                                                       *
 *  ˵����                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartWriteStr(const char* str)
{
    while (*str)
    {
			UART_PutChar(UART0, *str++);
    }
	return ;
}


/*************************************************************************************************
 *  ���ܣ��Ӵ���1����һ���ַ�                                                                    *
 *  ������(1) �洢���յ����ַ�                                                                   *
 *  ���أ�                                                                                       *
 *  ˵����                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartReadByte(char* c)
{
	UART_GetChar(UART0);
	return ;
}


static char _buffer[256];
void LOS_EvbUartPrintf(char* fmt, ...)
{
    int i;
    va_list ap;
    va_start(ap, fmt);
    vsprintf(_buffer, fmt, ap);
    va_end(ap);

    for (i = 0; _buffer[i] != '\0'; i++)
    {
        LOS_EvbUartWriteByte(_buffer[i]);
    }
	return ;
}

int fputc(int ch, FILE *f)
{
	LOS_EvbUartWriteByte(ch);
	return (ch);
}

