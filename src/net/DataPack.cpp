#include <iostream>

#include "net/DataPack.hpp"

using namespace std;

DataPack::DataPack(){
    this->data=(Byte*)malloc(1);
    this->size=1;

}

DataPack::~DataPack(){
    delete this->data;

}

void DataPack::write(void* data,unsigned int size){
    if(this->getOffset()+size-this->getSize()>0){
        this->expand(this->getOffset()+size-this->getSize());

    }

    memcpy(this->getData()+this->getOffset(),data,size);
    this->offset+=size;

}

void DataPack::writeShort(short data){
    this->write(&data,sizeof(data));

}

void DataPack::writeInt(int data){
    this->write(&data,sizeof(data));

}

void DataPack::writeLong(long data){
    this->write(&data,sizeof(data));

}

void DataPack::writeFloat(float data){
    this->write(&data,sizeof(data));

}

void DataPack::writeDouble(double data){
    this->write(&data,sizeof(data));

}

void DataPack::writeUnsignedShort(unsigned short data){
    this->write(&data,sizeof(data));

}

void DataPack::writeUnsignedInt(unsigned int data){
    this->write(&data,sizeof(data));

}

void DataPack::writeUnsignedLong(unsigned long data){
    this->write(&data,sizeof(data));

}

void DataPack::writeString(QString data){
    this->writeUnsignedInt(data.toStdString().length()+1);
    this->write((void*)data.toStdString().data(),data.toStdString().length()+1);

}

void DataPack::writeByte(Byte data){
    this->write(&data,sizeof(data));

}

void DataPack::writeBytes(Bytes* data){
    this->write(data->getData(),data->getSize());

}

Bytes DataPack::read(unsigned int size){
    Byte data[size];

    memcpy(data,this->getData()+this->getOffset(),size);
    this->offset+=size;

    Bytes bytes=Bytes(data,size);

    return bytes;

}

short DataPack::readShort(){
    return *(short*)this->read(sizeof(short)).getData();

}

int DataPack::readInt(){
    return *(int*)this->read(sizeof(int)).getData();

}

long DataPack::readLong(){
    return *(long*)this->read(sizeof(long)).getData();

}

float DataPack::readFloat(){
    return *(float*)this->read(sizeof(float)).getData();

}

double DataPack::readDouble(){
    return *(double*)this->read(sizeof(double)).getData();

}

unsigned short DataPack::readUnsignedShort(){
    return *(unsigned short*)this->read(sizeof(unsigned short)).getData();

}

unsigned int DataPack::readUnsignedInt(){
    return *(unsigned int*)this->read(sizeof(unsigned int)).getData();

}

unsigned long DataPack::readUnsignedLong(){
    return *(unsigned long*)this->read(sizeof(unsigned long)).getData();

}

QString DataPack::readString(){
    unsigned int size=this->readUnsignedInt();

    return QString((const char*)this->read(size).getData());

}

Byte DataPack::readByte(){
    return *(Byte*)this->read(sizeof(Byte)).getData();

}

Bytes DataPack::readBytes(){
    unsigned int size=this->readUnsignedInt();

    return Bytes((Byte*)this->read(sizeof(size)).getData(),size);

}

Byte* DataPack::getData(){
    return this->data;

}

unsigned int DataPack::getSize(){
    return this->size;

}

unsigned int DataPack::getOffset(){
    return this->offset;

}

void DataPack::expand(unsigned int size){
    this->size=this->getSize()+size;
    this->data=(Byte*)realloc(this->data,this->getSize());

}

void DataPack::seek(unsigned int offset){
    this->offset=offset;

}
