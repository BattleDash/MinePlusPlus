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

void AbstractByteBuf::CheckReadableBytes(int minimumReadableBytes)
{
    if (m_readerIndex > m_writerIndex - minimumReadableBytes)
    {
        std::stringstream ss;
        ss << "readerIndex(" << m_readerIndex << ") + length(" << minimumReadableBytes << ") exceeds writerIndex("
           << m_writerIndex << ")";
        throw std::out_of_range(ss.str());
    }
}

ByteBuf& AbstractByteBuf::ReaderIndex(int readerIndex)
{
    CheckIndexBounds(readerIndex, m_writerIndex, Capacity());
    m_readerIndex = readerIndex;
    return *this;
}

int AbstractByteBuf::WriterIndex()
{
    return m_writerIndex;
}

ByteBuf& AbstractByteBuf::WriterIndex(int writerIndex)
{
    CheckIndexBounds(m_readerIndex, writerIndex, Capacity());
    m_writerIndex = writerIndex;
    return *this;
}

ByteBuf& AbstractByteBuf::SetIndex(int readerIndex, int writerIndex)
{
    CheckIndexBounds(readerIndex, writerIndex, Capacity());
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
    uint8_t v = GetByte(i);
    m_readerIndex = i + 1;
    return v;
}

bool AbstractByteBuf::ReadBoolean()
{
    return ReadByte() != 0;
}

uint8_t AbstractByteBuf::ReadUnsignedByte()
{
    return ReadByte() & 0xFF;
}

short AbstractByteBuf::ReadShort()
{
    short v = _GetShort(m_readerIndex);
    m_readerIndex += 2;
    return v;
}

int AbstractByteBuf::ReadUnsignedShort()
{
    return ReadShort() & 0xFFFF;
}

int AbstractByteBuf::ReadInt()
{
    int v = _GetInt(m_readerIndex);
    m_readerIndex += 4;
    return v;
}

int64_t AbstractByteBuf::ReadLong()
{
    int64_t v = _GetLong(m_readerIndex);
    m_readerIndex += 8;
    return v;
}

wchar_t AbstractByteBuf::ReadWChar()
{
    return static_cast<wchar_t>(ReadShort());
}

char AbstractByteBuf::ReadChar()
{
    return static_cast<char>(ReadShort());
}

wchar_t* AbstractByteBuf::ReadWString(int length)
{
    wchar_t* str = new wchar_t[length + 1];
    for (int i = 0; i < length; i++)
    {
        str[i] = ReadWChar();
    }
    str[length] = 0;
    return str;
}

char* AbstractByteBuf::ReadString(int length)
{
    char* str = new char[length + 1];
    for (int i = 0; i < length; i++)
    {
        str[i] = ReadChar();
    }
    str[length] = 0;
    return str;
}

void AbstractByteBuf::WriteByte(uint8_t value)
{
    _SetByte(m_writerIndex, value);
    m_writerIndex += 1;
}

void AbstractByteBuf::WriteBoolean(bool value)
{
    WriteByte(value ? 1 : 0);
}

void AbstractByteBuf::WriteUnsignedByte(uint8_t value)
{
    WriteByte(value & 0xFF);
}

void AbstractByteBuf::WriteShort(short value)
{
    _SetShort(m_writerIndex, value);
    m_writerIndex += 2;
}

void AbstractByteBuf::WriteUnsignedShort(int value)
{
    WriteShort(value & 0xFFFF);
}

void AbstractByteBuf::WriteInt(int value)
{
    _SetInt(m_writerIndex, value);
    m_writerIndex += 4;
}

void AbstractByteBuf::WriteLong(int64_t value)
{
    _SetLong(m_writerIndex, value);
    m_writerIndex += 8;
}
} // namespace mpp