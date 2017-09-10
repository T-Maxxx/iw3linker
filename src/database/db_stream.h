#pragma once
#include "types.h"

struct SZoneDataBlock
{
    byte_t *data;
    unsigned int size;
};

struct SZone
{
    SZoneDataBlock blocks[9];
};

struct SStreamDelay
{
    void *Address;
    unsigned int Size;
};

byte_t* __cdecl DB_GetStreamPos();
void DB_SetStreamOutPos(byte_t* const Address_);
void __cdecl DB_IncreaseStreamPos(const int Size_);

byte_t* __cdecl DB_GetSourcePos();
void DB_SetSourcePos(byte_t* const Address_);
void __cdecl DB_IncreaseSourcePos(char DoWork_, unsigned int Base_, unsigned int Offset_);

byte_t* DB_GetStreamOut();
void DB_SetStreamOut(byte_t* const Address_);
byte_t* DB_GetStreamOutPos();
unsigned int DB_GetStreamOutOffset();
