// Copyright BattleDash. All Rights Reserved.

#include <Server/Network/Buffer/UnpooledDirectByteBuf.h>

#include <stdexcept>

namespace mpp
{
UnpooledDirectByteBuf::UnpooledDirectByteBuf(int initialCapacity, int maxCapacity)
    : AbstractByteBuf(maxCapacity), m_buffer(new uint8_t[maxCapacity]), m_capacity(initialCapacity)
{
    WriterIndex(initialCapacity);
}

UnpooledDirectByteBuf::~UnpooledDirectByteBuf()
{
}

int UnpooledDirectByteBuf::Capacity()
{
    return m_capacity;
}

uint8_t UnpooledDirectByteBuf::_GetByte(int index)
{
    return m_buffer[index];
}
} // namespace mpp