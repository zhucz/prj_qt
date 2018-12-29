#ifndef CRC8_H
#define CRC8_H


class crc8
{
public:
    crc8();

    unsigned char mycrc8(unsigned char *src,unsigned int len);
};



#endif // CRC8_H
