#ifndef GOOLNN_HELPERCHESS_NET_DATAPACK
#define GOOLNN_HELPERCHESS_NET_DATAPACK

#include <QString>

#include <windows.h>

#include "tool/Byte.hpp"

using namespace std;

class DataPack{
    public:
        DataPack();
        ~DataPack();

        //写入
        void write(void*,unsigned int);

        void writeShort(short);
        void writeInt(int);
        void writeLong(long);
        void writeFloat(float);
        void writeDouble(double);

        void writeUnsignedShort(unsigned short);
        void writeUnsignedInt(unsigned int);
        void writeUnsignedLong(unsigned long);

        void writeString(QString);

        void writeByte(Byte);
        void writeBytes(Bytes*);

        //读取
        Bytes read(unsigned int);

        short readShort();
        int readInt();
        long readLong();
        float readFloat();
        double readDouble();

        unsigned short readUnsignedShort();
        unsigned int readUnsignedInt();
        unsigned long readUnsignedLong();

        QString readString();

        Byte readByte();
        Bytes readBytes();

        //获取
        Byte* getData();
        unsigned int getSize();
        unsigned int getOffset();

        //操作
        void expand(unsigned int);
        void seek(unsigned int);

    private:
        Byte* data=nullptr;         //数据位置
        unsigned int size=0;        //数据大小
        unsigned int offset=0;      //偏移位置

};

#endif
