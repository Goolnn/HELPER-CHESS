#ifndef GOOLNN_HELPERCHESS_TOOL_BYTE
#define GOOLNN_HELPERCHESS_TOOL_BYTE

typedef unsigned char Byte;

class Bytes{
    private:
        Byte* data=nullptr;             //数据位置
        unsigned int size=0;            //数据大小
        
    public:
        Bytes(Byte*,unsigned int);
        ~Bytes();

        Byte* getData();                //获取数据位置
        unsigned int getSize();         //获取数据大小
        
};

void PrintBytes(Byte*,unsigned int);
void PrintBytes(Bytes*);

#endif
