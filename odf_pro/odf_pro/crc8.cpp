#include "crc8.h"

crc8::crc8()
{

}


unsigned char crc8::mycrc8(unsigned char *ptr,unsigned int len)
{
    unsigned char i = 0;
    unsigned char crc = 0;
    while(len--){
        i = 0x80;
        while(i != 0){
            if(((crc & 0x80) != 0) && (((*ptr) & i) != 0)){
                crc <<= 1;
            }
            else if(((crc & 0x80)!= 0) && (((*ptr) & i)==0)){
                crc <<= 1;
                crc ^= 0x31;
            }
            else if(((crc & 0x80) == 0)&& (((*ptr) & i) !=0)){
                crc <<= 1;
                crc ^= 0x31;
            }
            else if(((crc & 0x80) == 0) &&(((*ptr)&i)== 0)){
                crc <<= 1;
            }
            i >>= 1;
        }
        ptr++;
    }
    return(crc);
}

