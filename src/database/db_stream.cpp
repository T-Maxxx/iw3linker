#include "db_stream.h"
#include "console.h"
#include <alldecompiled.h>

static byte_t* g_sourcePos;
static byte_t* g_streamOut;
static byte_t* g_streamOutPos;

void DB_IncreaseStreamPos(const int Size_)
{
    QASSERT(g_streamPos);
    g_streamPos += Size_;
}

byte_t *DB_GetStreamPos()
{
    return g_streamPos;
}

void DB_SetSourcePos(byte_t* const Address_)
{
    g_sourcePos = Address_;
}

byte_t* DB_GetSourcePos()
{
    return g_sourcePos;
}

void DB_IncreaseSourcePos(char DoWork_, unsigned int Base_, unsigned int Offset_)
{
    if (DoWork_)
        g_sourcePos = (byte_t*)(Offset_ + Base_);
}

byte_t* DB_GetStreamOut()
{
  return g_streamOut;
}

unsigned int DB_GetStreamOutOffset()
{
  return g_streamOutPos - g_streamOut;
}

void DB_SetStreamOut(byte_t* const Address_)
{
    g_streamOut = Address_;
}

byte_t* DB_GetStreamOutPos()
{
    return g_streamOutPos;
}

void DB_SetStreamOutPos(byte_t* const Address_)
{
    g_streamOutPos = Address_;
}
