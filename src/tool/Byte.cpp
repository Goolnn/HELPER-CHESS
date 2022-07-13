#include <iostream>

#include <string.h>
#include <stdlib.h>

#include <tool/Byte.hpp>

using namespace std;

Bytes::Bytes(Byte* data,unsigned int size){
    this->data=(Byte*)malloc(size);
    this->size=size;

    memcpy(this->data,data,size);
    
}

Bytes::~Bytes(){
    if(this->data!=nullptr){
        free(this->data);

    }

}

Byte* Bytes::getData(){
    return this->data;

}

unsigned int Bytes::getSize(){
    return this->size;

}

void PrintBytes(Byte* data,unsigned int size){
    ios old=ios(nullptr);
    old.copyfmt(cout);

    for(unsigned int i=0;i<size;i++){
        int num=(int)data[i];

        if(num<16){
            cout<<"0";

        }

        cout<<hex<<uppercase<<num;

        if(i!=size-1){
            cout<<" ";

        }else{
            cout<<endl;

        }

    }

    cout.copyfmt(old);

}

void PrintBytes(Bytes* bytes){
    PrintBytes(bytes->getData(),bytes->getSize());

}
