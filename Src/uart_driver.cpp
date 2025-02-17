#include "uart_driver.h"
#include "gpio_driver.h"
#include "interrupts.h"
#include <cstring>

#define APB2_UART1ENR (1U<<14)
#define APB1_UART2ENR (1U<<17)
#define APB1_UART3ENR (1U<<18)
#define APB1_UART4ENR (1U<<19)
#define APB1_UART5ENR (1U<<20)
#define UART_CR1_ENA	(1U<<13)
#define UART_CR1_TX_ENA (1U<<3)
#define UART_CR1_RX_ENA (1U<<2)
#define UART_CR1_TXEIE (1U<<7)
#define UART_CR1_RXNEIE (1U<<5)


/*
 * Receive
 */
//static char uart_1_received_data = 0;
static RingBuffer uart_2_received_data;
//static char uart_3_received_data = 0;
//static char uart_4_received_data = 0;


static int32_t brr_baudrate(uint32_t baudrate){
	return 0x45;//(CLOCK_SPD_Hz + (baudrate/2))/ (baudrate*16);
}



static void RCC_uart_enable(UART_t *uart)
{
	if (uart == UART1){
		RCC->APB2ENR |= APB2_UART1ENR;
	}
	else if(uart == UART2){
		RCC->APB1ENR |= APB1_UART2ENR;
	}
	else if(uart == UART3){
		RCC->APB1ENR |= APB1_UART3ENR;
	}
	else if(uart == UART4){
		RCC->APB1ENR |= APB1_UART4ENR;
	}
	else if(uart == UART2){
		RCC->APB1ENR |= APB1_UART5ENR;
	}
}


void uart2_init()
{
	//configure pins
	//gpio
	//enable transmit of using tx
	//select work length in USART_CR1
	//usart-dr contains rx or tx data(so we can read from or write to it)
	//dont reset TE bit during transmission
	//configure to 1 stop bit only at the control register
	//enable usart at CR1 register


}


UART::UART(uart_param_t &config, GPIO_t *LED_PORT, uint8_t LED_PIN)
{
	this->_uart = config.uart;

			//enable uart
			config.uart->CR1 &= ~(1u<<13);

		//set rcc
		RCC_uart_enable(config.uart);

		//reset gpio
		gpio::port_config_reset(config.io, config.tx);
		gpio::port_config_reset(config.io, config.rx);

		//set tx as af output
		gpio::port_config_mode(config.io, config.tx, MODE_OUTPUT_50MHZ);
		gpio::port_config_cnf(config.io, config.tx, CNF_OUTPUT_AF_PUSH_PULL);

		//set rx as af input
		gpio::port_config_mode(config.io, config.rx, MODE_INPUT_RESET);
		gpio::port_config_cnf(config.io, config.rx, CNF_INPUT_FLOATING);



		//configure baudrate
		config.uart->BRR = brr_baudrate(115200);

		//set TE and RE on
		config.uart->CR1 |= (1U<<3) | (1U<<2);

		//
		config.uart->CR1 |= (1U<<5);

		//Enable interrupts on receive
		NVIC_EnableIRQ(38);
		//NVIC_EnableIRQ(UART_2_IRQ_POS);



		//enable uart
		config.uart->CR1 |= (1u<<13);

		//init LED
		this->LedPin = LED_PIN;
		this->ledPort = LED_PORT;
		gpio::init_gpio(this->ledPort, this->LedPin, MODE_OUTPUT_10MHZ, CNF_OUTPUT_PUSH_PULL);
		this->isLedAttached = true;


}


UART::~UART(){
	//free string buffer
}

void UART::write(char &ch)
{
	if (this->isLedAttached){
		gpio::SetHIGH(this->ledPort, this->LedPin);
	}
	//wait for transmission complete
	while(! (this->_uart->SR & (1U<<7) )){}
	this->_uart->DR = (ch & 0xFF);

	if (this->isLedAttached){
		gpio::SetLOW(this->ledPort, this->LedPin);
	}

}
void UART::write_string(char *str)
{
	int len = (int)strlen(str);
	for (int i = 0; i < len ; i++)
	{
		this->write(str[i]);
	}
}

//void UART::write_string(const char *str)
//{
//	int len = (int)strlen(str);
//	for (int i = 0; i < len ; i++)
//	{
//		this->write(str[i]);
//	}
//}

void UART::read_and_echo()
{
	if(!this->_rx_buffer.bufferEmpty())
	{
		this->write_string(this->read_string());
	}

}

char UART::read(){

	char ch = uart_2_received_data.read();
//	this->_rx_buffer.write(uart_2_received_data.read());
//	return _rx_buffer.read();
	return ch;
}



bool UART::isDataAvailable()
{
	return !(_rx_buffer.bufferEmpty());
}
//UART interrupt
extern "C" void USART2_IRQHandler(void)
{
	if(UART2->SR & (1U << 5))
	{
		uart_2_received_data.write( (UART2->DR & 0xFF) );
	}
}





