/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#include "header/data.h"

#define defaultDisplay 4

Data::Data(QWidget *Parent, const char *dat, qint64 Size, QVector<int> offsets)
{
    bin = new char[Size];        //Data to disassemble
    memcpy(bin, dat, Size);
    size = Size;                 //Size of all the data (in bytes)
    addrOff = offsets.at(0);     //Address offset (addrOff = data[0])
    fOff = offsets.at(1);        //File offset (read file starting at this byte offset from file start)

    display = new char[size/4 +1];
    //Display data format:
    //Each byte of data get's 2 bits to describe how to display it
    //0=byte  1=half  2=word  4=double word

    //2 bits / byte = 4 bytes data per byte display data
    //extra byte of display data in case size%4 != 0

    //0xAA = 0b10101010 (word format)
    memset(display,0xAA,size/4 +1);
}

Data::~Data(){
    delete[] bin;
}

//Returns
unsigned int Data::getAddressOffset(){
    return addrOff;
}
unsigned int Data::getFileOffset(){
    return fOff;
}
qint64 Data::getSize(){
    return size;
}

char* Data::getData(int address, int size){
    char* ret = new char[size];
    memset(ret, 0, size);

    int addr_abs = address - addrOff;

    int pre_pad = 0;
    if(addr_abs < 0) size+addr_abs > 0? pre_pad-=addr_abs:pre_pad=size;

    int available = (addr_abs+pre_pad)+size < this->size? (size-pre_pad):(this->size-qAbs(addr_abs));
    if(available < 0) available = 0;

    memcpy(&ret[pre_pad],&bin[addr_abs+pre_pad], available);
    return ret;
}

char* Data::getDisplayData(int address, int size){
    int addr_cpy = address-(signed int)addrOff; /*< this->size? address-addrOff:this->size;*/

    char* ret = new char[size];
    memset(ret, defaultDisplay, size);

    int j =0;
    while(addr_cpy < 0 && j < size){
        ret[j] = 4;
        addr_cpy +=4;
        j++;
    }

    for(int i=j; i<size && addr_cpy < this->size; i++){
        //Each byte of data gets 2 bits of display information.
        //i.e. display[i] has display info for the 4 bytes from data[i] to data[i+3]
        //(display[(int)address/4] >>        (address%4)*2)                  &3;
        //     Reference byte           bitfield of desired info     strip all other data
        switch((display[(int)addr_cpy/4] >> (addr_cpy%4)*2)&3){
        case DISP_DWORD: ret[i] = 8; addr_cpy += 8; break;
        case DISP_WORD:  ret[i] = 4; addr_cpy += 4; break;
        case DISP_HALF:  ret[i] = 2; addr_cpy += 2; break;
        case DISP_BYTE:  ret[i] = 1; addr_cpy ++;   break;
        }
    }
    return ret;
}


void Data::setAddressOffset(int offset){
    addrOff = offset;
}

int Data::setDisplayData(int address, int type){
    address -= addrOff;
    if(address<size){

        //Convert 2-bit, compact display data to integers for arithmetic
        int type_arithmetic=defaultDisplay;
        switch(type){
        case DISP_DWORD: type_arithmetic = 8; break;
        case DISP_WORD:  type_arithmetic = 4; break;
        case DISP_HALF:  type_arithmetic = 2; break;
        case DISP_BYTE:  type_arithmetic = 1; break;
        }

        int old_type = (display[(int)address/4] >> (address%4)*2)&3;
        int old_type_arithmetic;
        switch(old_type){
        case DISP_DWORD: old_type_arithmetic = 8; break;
        case DISP_WORD:  old_type_arithmetic = 4; break;
        case DISP_HALF:  old_type_arithmetic = 2; break;
        case DISP_BYTE:  old_type_arithmetic = 1; break;
        }

        //Align to the larger type
        int alignment = old_type_arithmetic>type_arithmetic?old_type_arithmetic:type_arithmetic;
        address -= address%alignment;

        for(int i =0; i<alignment; i++){
            //ref byte                  =  ref byte                         stripped of old data        inserted with new data
            display[(int)(address+i)/4] = (display[(int)(address+i)/4] & ~(3 << ((address+i)%4)*2)) | (type << ((address+i)%4)*2);
        }
    }
    return address+addrOff;

}

void Data::resetData(const char* dat, qint64 Size, QVector<int> offsets){
    Size -= offsets.at(1);
    dat += offsets.at(1);

    delete[] bin;
    bin = new char[Size];
    memcpy(bin,dat,Size);
    size = Size;
    addrOff = offsets.at(0);
    fOff = offsets.at(1);

    delete[] display;
    display = new char[size/4];
    memset(display, 0xAA,size/4);
}
