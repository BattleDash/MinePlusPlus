// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Buffer/UnpooledDirectByteBuf.h>

#include <stdexcept>

namespace mpp
{
UnpooledDirectByteBuf::UnpooledDirectByteBuf(int initialCapacity, int maxCapacity)
    : AbstractByteBuf(maxCapacity), m_buffer(new uint8_t[initialCapacity]), m_capacity(initialCapacity)
{
    WriterIndex(initialCapacity);
}

UnpooledDirectByteBuf::~UnpooledDirectByteBuf()
{
    delete[] m_buffer;
}

int UnpooledDirectByteBuf::Capacity()
{
    return m_capacity;
}

void* UnpooledDirectByteBuf::GetData()
{
    return m_buffer;
}

uint8_t UnpooledDirectByteBuf::_GetByte(int index)
{
    return m_buffer[index];
}

short UnpooledDirectByteBuf::_GetShort(int index)
{
    return (m_buffer[index] << 8) | m_buffer[index + 1];
}

int UnpooledDirectByteBuf::_GetInt(int index)
{
    return (m_buffer[index] << 24) | (m_buffer[index + 1] << 16) | (m_buffer[index + 2] << 8) | m_buffer[index + 3];
}

int64_t UnpooledDirectByteBuf::_GetLong(int index)
{
    return (static_cast<int64_t>(m_buffer[index]) << 56) | (static_cast<int64_t>(m_buffer[index + 1]) << 48) |
           (static_cast<int64_t>(m_buffer[index + 2]) << 40) | (static_cast<int64_t>(m_buffer[index + 3]) << 32) |
           (static_cast<int64_t>(m_buffer[index + 4]) << 24) | (static_cast<int64_t>(m_buffer[index + 5]) << 16) |
           (static_cast<int64_t>(m_buffer[index + 6]) << 8) | m_buffer[index + 7];
}

ByteBuf* UnpooledDirectByteBuf::ReadBytes(int length)
{
    CheckReadableBytes(length);
    UnpooledDirectByteBuf* newBuf = new UnpooledDirectByteBuf(length, length);
    memcpy(newBuf->m_buffer, m_buffer + m_readerIndex, length);
    m_readerIndex += length;
    return newBuf;
}

void UnpooledDirectByteBuf::_SetByte(int index, uint8_t value)
{
    m_buffer[index] = value;
}

void UnpooledDirectByteBuf::_SetShort(int index, short value)
{
    m_buffer[index] = (value >> 8) & 0xFF;
    m_buffer[index + 1] = value & 0xFF;
}

void UnpooledDirectByteBuf::_SetInt(int index, int value)
{
    m_buffer[index] = (value >> 24) & 0xFF;
    m_buffer[index + 1] = (value >> 16) & 0xFF;
    m_buffer[index + 2] = (value >> 8) & 0xFF;
    m_buffer[index + 3] = value & 0xFF;
}

void UnpooledDirectByteBuf::_SetLong(int index, int64_t value)
{
    m_buffer[index] = (value >> 56) & 0xFF;
    m_buffer[index + 1] = (value >> 48) & 0xFF;
    m_buffer[index + 2] = (value >> 40) & 0xFF;
    m_buffer[index + 3] = (value >> 32) & 0xFF;
    m_buffer[index + 4] = (value >> 24) & 0xFF;
    m_buffer[index + 5] = (value >> 16) & 0xFF;
    m_buffer[index + 6] = (value >> 8) & 0xFF;
    m_buffer[index + 7] = value & 0xFF;
}

void UnpooledDirectByteBuf::WriteBytes(void* src, int srcIndex, int length)
{
    memcpy(m_buffer + m_writerIndex, src, length);
    m_writerIndex += length;
}

} // namespace mpp