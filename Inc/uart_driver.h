
#ifndef _UART_DRV_
#define _UART_DRV_
#include <stdint.h>
#include "driver_base.h"
#include "gpio_driver.h"
#include "ringbuffer.h"

#define CLOCK_SPD_Hz 8000000

#define UART_ENABLE_INTERRUPT  4
#define UART_DISABLE_INTERRUPT 5



typedef struct
{
	UART_t *uart;
	GPIO_t *io;
	uint8_t tx;
	uint8_t rx;
	uint8_t tx_ISR_en;
	uint8_t rx_ISR_en;

}uart_param_t;


	class UART{
		public :
			UART(UART_t *uart, GPIO_t *io, uint8_t tx, uint8_t rx);
			UART(uart_param_t &config);
			UART(uart_param_t &config, GPIO_t *LED_PORT, uint8_t LED_PIN);
			~UART();
			void write(char &ch);
			char read();
			char* read_string();
			void write_string(char *str);
			//void write_string(const char *str);
			void read_and_echo();
			bool isDataAvailable();
			char currentString [250];
			//UART(UART_t uart);
		private :
			volatile UART_t *_uart ;
			GPIO_t *ledPort;
			uint8_t LedPin;
			bool isLedAttached = false;
			RingBuffer _rx_buffer;

			/*On init the string buffer is initalized*/
			char *StringBuffer;

	};
#endif
