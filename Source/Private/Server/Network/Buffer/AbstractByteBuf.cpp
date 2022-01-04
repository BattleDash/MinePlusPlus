// Copyright BattleDash. All Rights Reserved.

#include <Server/Network/Buffer/AbstractByteBuf.h>

#include <sstream>
#include <stdexcept>

namespace mpp
{
AbstractByteBuf::AbstractByteBuf(int maxCapacity)
    : m_readerIndex(0), m_writerIndex(0), m_markedReaderIndex(0), m_markedWriterIndex(0), m_maxCapacity(maxCapacity)
{
}

AbstractByteBuf::~AbstractByteBuf()
{
}

bool AbstractByteBuf::IsReadOnly()
{
    return false;
}

ByteBuf* AbstractByteBuf::AsReadOnly()
{
    return this;
}

int AbstractByteBuf::MaxCapacity()
{
    return m_maxCapacity;
}

void AbstractByteBuf::MaxCapacity(int maxCapacity)
{
    m_maxCapacity = maxCapacity;
}

int AbstractByteBuf::ReaderIndex()
{
    return m_readerIndex;
}

void AbstractByteBuf::CheckIndexBounds(int readerIndex, int writerIndex, int capacity)
{
    if (readerIndex < 0 || readerIndex > writerIndex || writerIndex > capacity)
    {
        std::stringstream ss;
        ss << "readerIndex: " << readerIndex << ", writerIndex: " << writerIndex
           << " (expected: 0 <= readerIndex <= writerIndex <= capacity(" << capacity << "))";
        throw std::out_of_range(ss.str());
    }
}

ByteBuf& AbstractByteBuf::ReaderIndex(int readerIndex)
{
    CheckIndexBounds(readerIndex, m_writerIndex, m_maxCapacity);
    m_readerIndex = readerIndex;
    return *this;
}

int AbstractByteBuf::WriterIndex()
{
    return m_writerIndex;
}

ByteBuf& AbstractByteBuf::WriterIndex(int writerIndex)
{
    CheckIndexBounds(m_readerIndex, writerIndex, m_maxCapacity);
    m_writerIndex = writerIndex;
    return *this;
}

ByteBuf& AbstractByteBuf::SetIndex(int readerIndex, int writerIndex)
{
    CheckIndexBounds(readerIndex, writerIndex, m_maxCapacity);
    m_readerIndex = readerIndex;
    m_writerIndex = writerIndex;
    return *this;
}

ByteBuf& AbstractByteBuf::Clear()
{
    m_readerIndex = m_writerIndex = 0;
    return *this;
}

bool AbstractByteBuf::IsReadable()
{
    return m_writerIndex > m_readerIndex;
}

bool AbstractByteBuf::IsReadable(int numBytes)
{
    return m_writerIndex - m_readerIndex >= numBytes;
}

bool AbstractByteBuf::IsWritable()
{
    return Capacity() > m_writerIndex;
}

bool AbstractByteBuf::IsWritable(int numBytes)
{
    return Capacity() - m_writerIndex >= numBytes;
}

int AbstractByteBuf::ReadableBytes()
{
    return m_writerIndex - m_readerIndex;
}

int AbstractByteBuf::WritableBytes()
{
    return Capacity() - m_writerIndex;
}

int AbstractByteBuf::MaxWritableBytes()
{
    return MaxCapacity() - m_writerIndex;
}

ByteBuf& AbstractByteBuf::MarkReaderIndex()
{
    m_markedReaderIndex = m_readerIndex;
    return *this;
}

ByteBuf& AbstractByteBuf::ResetReaderIndex()
{
    m_readerIndex = m_markedReaderIndex;
    return *this;
}

ByteBuf& AbstractByteBuf::MarkWriterIndex()
{
    m_markedWriterIndex = m_writerIndex;
    return *this;
}

ByteBuf& AbstractByteBuf::ResetWriterIndex()
{
    m_writerIndex = m_markedWriterIndex;
    return *this;
}

uint8_t AbstractByteBuf::GetByte(int index)
{
    return _GetByte(index);
}

uint8_t AbstractByteBuf::ReadByte()
{
    int i = m_readerIndex;
    uint8_t b = GetByte(i);
    m_readerIndex = i + 1;
    return b;
}

bool AbstractByteBuf::ReadBoolean()
{
    return ReadByte() != 0;
}

uint8_t AbstractByteBuf::ReadUnsignedByte()
{
    return ReadByte() & 0xFF;
}
} // namespace mpp