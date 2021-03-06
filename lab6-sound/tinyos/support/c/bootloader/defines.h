/* definitions generated by preprocessor, copy into defines.h */

#ifndef	PPINC
//#define	_ATMEGA1281	// device select: _ATMEGAxxxx
#define	_B4096	// boot size select: _Bxxxx (words), powers of two only
#include	<avr/io.h>


/* definitions for UART control */
#ifdef _ATMEGA1281
#define BAUD_RATE_HIGH_REG	UBRR0H
#define	BAUD_RATE_LOW_REG	UBRR0L
#define	UART_CONTROL_REG	UCSR0B
#define	ENABLE_TRANSMITTER_BIT	TXEN0
#define	ENABLE_RECEIVER_BIT	RXEN0
#define	UART_STATUS_REG	UCSR0A
#define UART_DOUBLE_SPEED_BIT	U2X0
#define	TRANSMIT_COMPLETE_BIT	TXC0
#define	RECEIVE_COMPLETE_BIT	RXC0
#define	UART_DATA_REG	UDR0
#else
#define BAUD_RATE_HIGH_REG	UBRR1H
#define	BAUD_RATE_LOW_REG	UBRR1L
#define	UART_CONTROL_REG	UCSR1B
#define	ENABLE_TRANSMITTER_BIT	TXEN1
#define	ENABLE_RECEIVER_BIT	RXEN1
#define	UART_STATUS_REG	UCSR1A
#define UART_DOUBLE_SPEED_BIT	U2X1
#define	TRANSMIT_COMPLETE_BIT	TXC1
#define	RECEIVE_COMPLETE_BIT	RXC1
#define	UART_DATA_REG	UDR1

#endif

/* definitions for SPM control */
#define	SPMCR_REG	SPMCSR
#define	PAGESIZE	128
#define	APP_END	61440 //100000
#define	LARGE_MEMORY

/* definitions for device recognition */
#define	PARTCODE
#ifdef _ATMEGA1281	
#define	SIGNATURE_BYTE_1	0x1E
#define	SIGNATURE_BYTE_2	0x97
#define	SIGNATURE_BYTE_3	0x04
#else
#define SIGNATURE_BYTE_1	0x1E
#define SIGNATURE_BYTE_2	0xA7
#define SIGNATURE_BYTE_3	0x01
#endif

/* indicate that preprocessor result is included */
#define	PPINC
#endif

#ifndef __COUNTER_
#define __COUNTER_
uint32_t counter;
#endif

int BRREG_VALUE;
int blinker;

void init(void);
int baudrateRegister(uint32_t baudrate);

