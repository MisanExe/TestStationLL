
#pragma once
#include "uart_driver.h"
#include "parser.h"

#define MAX_DATA_SIZE 512

#define MSG_HEADER 3
#define MSG_BODY 4
#define MSG_END 5
namespace DataHandler{

 	 //void get

	class messageHandler
	{
		public:
			messageHandler(UART *uart);
			~messageHandler();
			void getMessages();
			void clearData();
			void parseMsg();

			SimpleParser parser;
			void printMsgStructure();
			void printMsgStructure(int option);

			char *data = new char[512];
		private:


			int dataIndex = 0;
			UART *uart;
	};
};
