// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
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

ByteBuf* UnpooledDirectByteBuf::ReadBytes(int length)
{
    CheckReadableBytes(length);
    UnpooledDirectByteBuf* newBuf = new UnpooledDirectByteBuf(length, m_capacity);
    memcpy(newBuf->m_buffer, m_buffer + m_readerIndex, length);
    m_readerIndex += length;
    return newBuf;
}

void UnpooledDirectByteBuf::WriteBytes(void* src, int srcIndex, int length)
{
    memcpy(m_buffer + m_writerIndex, src, length);
    m_writerIndex += length;
}

} // namespace mpp