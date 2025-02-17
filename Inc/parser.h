#pragma once
#include <string>
typedef struct
{
    const char token;
    bool flag;
}token_t;

#define HEADER_SIZE 255
#define BODY_SIZE (HEADER_SIZE*2)
#define END_SIZE HEADER_SIZE

class SimpleParser
{
    public:
        SimpleParser();
        void SetStream(char *stream);
        void getHeader(int x);
        void getBody(int x);
        void WaitForEnd(int x);

        bool isCurrentStreamNull = false;
        char currentHeader[HEADER_SIZE];
        char currentBody[BODY_SIZE];
        char currentEnd[END_SIZE];

        void clearRegisters();

    private:
        char *_stream;
        int _stream_len = 0;
        token_t _tkGt = {.token = '>', .flag = false };
        token_t _tkLt = {.token = '<', .flag = false };
        token_t _tkSl = {.token = '/', .flag = false };



        void _monitor_token(char tk);
};
