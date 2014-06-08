/* see copyright notice in aclang.h */

/*
#include <memory.h>

#include "ac_utility.h"
#include "ac_gc.h"

dsBuffer::dsBuffer(dsGarbageCollector* gc)
{
    m_gc = gc;
    m_reserve_size = 3 * 1024;
    m_capacity = m_reserve_size;
    m_base_address = gc->mallocRoot(m_capacity);
    m_size = 0;
}

dsBuffer::~dsBuffer()
{
    m_gc->free(m_base_address);
}

void dsBuffer::resize(size_t size)
{
    m_size = size;
    if(size > m_capacity)
    {
        m_capacity = (size / m_reserve_size + 1) * m_reserve_size;
        m_base_address = m_gc->realloc(m_base_address, m_capacity);
    }
}

void dsBuffer::push_back(d_int8 v)
{
    resize(m_size + 1);
    d_int8* p = ((d_int8*)m_base_address) + m_size - 1;
    *p = v;
}

void dsBuffer::push_back(d_int16 v)
{
    resize(m_size + 2);
    d_int16* p = (d_int16*)(((char*)m_base_address) + m_size - 2);
    *p = v;
}

void dsBuffer::push_back(d_int32 v)
{
    resize(m_size + 4);
    d_int32* p = (d_int32*)(((char*)m_base_address) + m_size - 4);
    *p = v;
}

void dsBuffer::push_back(d_int64 v)
{
    resize(m_size + 8);
    d_int64* p = (d_int64*)(((char*)m_base_address) + m_size - 8);
    *p = v;
}

void dsBuffer::push_back(void* v)
{
    resize(m_size + sizeof(v));
    void** p = (void**)(((char*)m_base_address) + m_size - sizeof(v));
    *p = v;
}

void dsBuffer::push_back(void* p, size_t size)
{
    resize(m_size + size);
    void* ptr = (void*)(((char*)m_base_address) + m_size - size);
    memcpy(ptr, p, size);
}

*/
