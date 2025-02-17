#include "parser.h"
#include "cstring"


//constructor
SimpleParser::SimpleParser(){}


//Set the stream object
void SimpleParser::SetStream(char * stream)
{
	isCurrentStreamNull = false;
	//Ensure stream is not enull of empty
	if (stream[0] != '\0' || stream != nullptr)
	{
	    this->_stream = stream;
	    this->_stream_len = (int)strlen(_stream);
	}else{
		isCurrentStreamNull = true;
	}

}

void SimpleParser::_monitor_token(char tk)
{
    if(tk == _tkGt.token)
    {
        _tkGt.flag = true;
        _tkLt.flag = false;
        _tkSl.flag = false;
    }else if(tk == _tkLt.token)
    {
        _tkGt.flag = false;
        _tkLt.flag = true;
        _tkSl.flag = false;
    }else if(tk == _tkSl.token)
    {
        _tkGt.flag = false;
        _tkLt.flag = false;
        _tkSl.flag = true;
    }
}

void SimpleParser::getHeader(int x)
{
    int index =  0;
    int headerIndex = 0;

    if (!isCurrentStreamNull)
    {
    	while(index < this->_stream_len)
		{
			_monitor_token(this->_stream[index]);

			if(_tkLt.flag && !(_stream[index] == _tkLt.token)){
				this->currentHeader[headerIndex] = _stream[index];
				headerIndex++;

				if(this->_stream[index] == _tkGt.token)
				{
					strcat(this->currentHeader, "\n\r");
					return;
				}
			}
			index++;
		}
    }

}

void SimpleParser::getBody(int x)
{
    int index =  0;
    int bodyIndex = 0;

    if(!isCurrentStreamNull)
    {
    	while(index < this->_stream_len)
		{
			_monitor_token(this->_stream[index]);

			if(_tkGt.flag && !(_stream[index] == _tkGt.token)){
				this->currentBody[bodyIndex] = _stream[index];
				bodyIndex++;

				if(this->_stream[index] == _tkLt.token)
				{
					strcat(this->currentBody, "\n\r");
					return;
				}
			}
			index++;
		}
    }

}

void SimpleParser::WaitForEnd(int x)
{
    int index =  0;
    int endIndex = 0;
    bool _prev_lt = false;

    if(!isCurrentStreamNull)
    {
    	while(index < this->_stream_len)
    	    {
    	        _monitor_token(this->_stream[index]);


    	        //check for lt
    	        if(_tkLt.flag && _stream[index+1] == _tkSl.token)
    	        {
    	            _prev_lt = true;
    	        }

    	        if(_prev_lt && !(_stream[index] == _tkLt.token) && !(_stream[index] == _tkSl.token) ){

    	            this->currentEnd[endIndex] = _stream[index];
    	            endIndex++;

    	            if(this->_stream[index+1] == _tkGt.token)
    	            {
    	            	strcat(this->currentEnd, "\n\r");
    	                return;
    	            }
    	        }

    	        index++;
		}
    }

}

void SimpleParser::clearRegisters()
{

    memset(currentBody, 0, sizeof(currentBody));
    memset(currentHeader, 0, sizeof(currentHeader));
    memset(currentEnd, 0, sizeof(currentEnd));
}
