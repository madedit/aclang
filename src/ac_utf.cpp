/* see copyright notice in aclang.h */

#include "ac_utf.h"

int dcharToUTF8(acDchar dch, acChar *buf)
{
    if(dch <= 0x7F)
    {
        buf[0] = acChar(dch);
        return 1;
    }
    if(dch <= 0x7FF)
    {
        buf[0] = acChar(0xC0 | (dch >> 6));
        buf[1] = acChar(0x80 | (dch & 0x3F));
        return 2;
    }
    if(dch <= 0xFFFF)
    {
        buf[0] = acChar(0xE0 | (dch >> 12));
        buf[1] = acChar(0x80 | ((dch >> 6) & 0x3F));
        buf[2] = acChar(0x80 | (dch & 0x3F));
        return 3;
    }
    if(dch <= 0x10FFFF)
    {
        buf[0] = acChar(0xF0 | (dch >> 18));
        buf[1] = acChar(0x80 | ((dch >> 12) & 0x3F));
        buf[2] = acChar(0x80 | ((dch >> 6) & 0x3F));
        buf[3] = acChar(0x80 | (dch & 0x3F));
        return 4;
    }

    return 0;
}


int UTF8ToDchar(const acChar *buf, int buf_len, acDchar &dch)
{
    if(buf_len <= 0) return 0;

    acDchar ch = *buf;
    if(ch <= 0x7F)
    {
        dch = ch;
        return 1;
    }

    if(ch <= 0xDF)
    {
        if(buf_len < 2) return 0;

        if(ch >= 0xC2)
        {
            acDchar ch1 = *++buf;
            if((ch1 & 0xC0) == 0x80)
            {
                if((dch = ( ((ch & 0x1F)<<6) | (ch1 & 0x3F) )) >= 0x80)
                {
                    return 2;
                }
            }
        }
    }
    else if(ch <= 0xEF)
    {
        if(buf_len < 3) return 0;

        acDchar ch1, ch2;
        ch1 = *++buf;
        ch2 = *buf;

        bool ok = false;
        if(ch == 0xE0)
        {
            if(ch1>=0xA0 && ch1<=0xBF && (ch2 & 0xC0) == 0x80) ok = true;
        }
        else if(ch ==0xED)
        {
            if(ch1>=0x80 && ch1<=0x9F && (ch2 & 0xC0) == 0x80) ok = true;
        }
        else
        {
            if((ch1 & 0xC0) == 0x80 && (ch2 & 0xC0) == 0x80) ok = true;
        }

        if(ok)
        {
            dch = ( (ch & 0x0F)<<12 ) | ( (ch1 & 0x3F)<<6 ) | (ch2 & 0x3F);
            if(dch >= 0x800 )
            {
                return 3;
            }
        }
    }
    else if(ch <= 0xF4)
    {
        if(buf_len < 3) return 0;

        acDchar ch1, ch2, ch3;
        ch1 = *++buf;
        ch2 = *++buf;
        ch3 = *buf;

        bool ok = false;
        if(ch == 0xF0)
        {
            if(ch1>=0x90 && ch1<=0xBF && (ch2 & 0xC0) == 0x80 && (ch3 & 0xC0) == 0x80)
                ok = true;
        }
        else if(ch == 0xF4)
        {
            if(ch1>=0x80 && ch1<=0x8F && (ch2 & 0xC0) == 0x80 && (ch3 & 0xC0) == 0x80)
                ok = true;
        }
        else
        {
            if((ch1 & 0xC0) == 0x80 && (ch2 & 0xC0) == 0x80 && (ch3 & 0xC0) == 0x80)
                ok = true;
        }

        if(ok)
        {
            dch = ((ch & 0x07)<<18) | ((ch1 & 0x3F) << 12) | ((ch2 & 0x3F) << 6) | (ch3 & 0x3F);
            if(dch >= 0x10000 && dch <= 0x10FFFF)
            {
                return 4;
            }
        }
    }

    return 0;
}


void dcVecToUTF8Str(acDcharVector& dcVec, std::string& str)
{
    str.clear();
    acChar buf[8];

    for(size_t i = 0; i < dcVec.size(); ++i)
    {
        acDchar dch = dcVec[i];
        int len = dcharToUTF8(dch, buf);

        if(len == 0)
        {
            if(dch > 0xFFFFFF)
            {
                str += (acChar)((dch>>24)&0xFF);
            }
            str += (acChar)((dch>>16)&0xFF);
            str += (acChar)((dch>>8)&0xFF);
            str += (acChar)(dch&0xFF);
        }
        else
        {
            for(int j = 0; j < len; ++j)
            {
                str += buf[j];
            }
        }
    }
}
