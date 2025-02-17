#include "dataHandler.h"
#include <cstring>

using namespace DataHandler;

messageHandler::messageHandler(UART *uart){
	this->uart = uart;
}

messageHandler::~messageHandler()
{
	delete [] data;
}

void messageHandler::clearData()
{
	memset(this->data, 0, MAX_DATA_SIZE);
	dataIndex = 0;
}

void messageHandler::getMessages()
{
	char tempBuffer = '\0';
	tempBuffer = this->uart->read();
	if(tempBuffer != '\0'){
		data[dataIndex] = tempBuffer;
		dataIndex++;
		tempBuffer = '\0';
	}

}

void messageHandler::parseMsg()
{
	parser.clearRegisters();
	this->parser.SetStream(data);
	this->parser.getHeader(0);
	this->parser.getBody(0);
	this->parser.WaitForEnd(0);
}

void messageHandler::printMsgStructure()
{

		this->uart->write_string(parser.currentHeader);
		//this->uart->write_string("\t");

		this->uart->write_string(parser.currentBody);
		//this->uart->write_string("\t");

		this->uart->write_string(parser.currentEnd);
		//this->uart->write_string("\t");

		parser.clearRegisters();

}

void messageHandler::printMsgStructure(int option)
{

		if(option == MSG_HEADER)
		{
			this->uart->write_string(parser.currentHeader);
		}

		if(option == MSG_BODY)
		{
			this->uart->write_string(parser.currentBody);
		}

		if(option == MSG_END)
		{
			this->uart->write_string(parser.currentEnd);
		}

		parser.clearRegisters();

}




