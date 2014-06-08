/* see copyright notice in aclang.h */

#ifndef AC_HASHVALUE_H
#define AC_HASHVALUE_H

#include "ac_config.h"

struct acHashValue
{
    union
    {
        struct
        {
            acUInt32 u32_0;
            acUInt32 u32_1;
            acUInt32 u32_2;
            acUInt32 u32_3;
        };

        struct
        {
            acUInt64 u64_0;
            acUInt64 u64_1;
        };
    };

    acHashValue()
        : u64_0(0)
        , u64_1(0)
    {
    }

    bool equal(acHashValue& other)
    {
        return (u64_0 == other.u64_0) && (u64_1 == other.u64_1);
    }

    int compare(acHashValue& other)
    {
        if(u64_1 == other.u64_1)
        {
            if(u64_0 == other.u64_0)
            {
                return 0;
            }
            if(u64_0 > other.u64_0)
            {
                return 1;
            }
            return -1;
        }
        if(u64_1 > other.u64_1)
        {
            return 1;
        }
        return -1;
    }

    bool operator<(const acHashValue& other) const
    {
        if(u64_1 == other.u64_1)
        {
            if(u64_0 >= other.u64_0)
            {
                return false;
            }
            return true;
        }
        if(u64_1 > other.u64_1)
        {
            return false;
        }
        return true;
    }
};

#endif //AC_HASHVALUE_H
