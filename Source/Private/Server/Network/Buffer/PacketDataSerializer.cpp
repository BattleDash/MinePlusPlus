// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Buffer/PacketDataSerializer.h>

#include <stdexcept>

namespace mpp
{
PacketDataSerializer::PacketDataSerializer(ByteBuf* buffer) : m_buffer(buffer)
{
}

int PacketDataSerializer::ReadVarInt()
{
    int value = 0;
    int shift = 0;
    uint8_t b;
    do
    {
        b = m_buffer->ReadByte();
        value |= (b & 127) << shift++ * 7;
        if (shift > 5)
        {
            throw std::runtime_error("VarInt too big");
        }
    } while ((b & 128) == 128);
    return value;
}

String PacketDataSerializer::ReadUtf()
{
    return ReadUtf(32767);
}

String PacketDataSerializer::ReadUtf(int maxLength)
{
    int length = ReadVarInt();
    if (length > maxLength * 4)
    {
        throw std::runtime_error("The received encoded string buffer length is longer than maximum allowed");
    }
    else if (length < 0)
    {
        throw std::runtime_error("The received encoded string buffer length is less than zero");
    }
    else
    {
        //char* test = m_buffer->ReadString(length);
        MPP_LOG(LogLevel::Debug, "Reading " << length << " " << test);
        return String(test);
    }
}

bool PacketDataSerializer::IsReadOnly()
{
    return m_buffer->IsReadOnly();
}

ByteBuf* PacketDataSerializer::AsReadOnly()
{
    return m_buffer->AsReadOnly();
}

int PacketDataSerializer::MaxCapacity()
{
    return m_buffer->MaxCapacity();
}

void PacketDataSerializer::MaxCapacity(int maxCapacity)
{
    m_buffer->MaxCapacity(maxCapacity);
}

int PacketDataSerializer::ReaderIndex()
{
    return m_buffer->ReaderIndex();
}

ByteBuf& PacketDataSerializer::ReaderIndex(int readerIndex)
{
    m_buffer->ReaderIndex(readerIndex);
    return *this;
}

int PacketDataSerializer::WriterIndex()
{
    return m_buffer->WriterIndex();
}

ByteBuf& PacketDataSerializer::WriterIndex(int writerIndex)
{
    m_buffer->WriterIndex(writerIndex);
    return *this;
}

ByteBuf& PacketDataSerializer::SetIndex(int readerIndex, int writerIndex)
{
    m_buffer->SetIndex(readerIndex, writerIndex);
    return *this;
}

ByteBuf& PacketDataSerializer::Clear()
{
    m_buffer->Clear();
    return *this;
}

bool PacketDataSerializer::IsReadable()
{
    return m_buffer->IsReadable();
}

bool PacketDataSerializer::IsReadable(int numBytes)
{
    return m_buffer->IsReadable(numBytes);
}

bool PacketDataSerializer::IsWritable()
{
    return m_buffer->IsWritable();
}

bool PacketDataSerializer::IsWritable(int numBytes)
{
    return m_buffer->IsWritable(numBytes);
}

int PacketDataSerializer::ReadableBytes()
{
    return m_buffer->ReadableBytes();
}

int PacketDataSerializer::WritableBytes()
{
    return m_buffer->WritableBytes();
}

int PacketDataSerializer::MaxWritableBytes()
{
    return m_buffer->MaxWritableBytes();
}

ByteBuf& PacketDataSerializer::MarkReaderIndex()
{
    m_buffer->MarkReaderIndex();
    return *this;
}

ByteBuf& PacketDataSerializer::ResetReaderIndex()
{
    m_buffer->ResetReaderIndex();
    return *this;
}

ByteBuf& PacketDataSerializer::MarkWriterIndex()
{
    m_buffer->MarkWriterIndex();
    return *this;
}

ByteBuf& PacketDataSerializer::ResetWriterIndex()
{
    m_buffer->ResetWriterIndex();
    return *this;
}

uint8_t PacketDataSerializer::GetByte(int index)
{
    return m_buffer->GetByte(index);
}

uint8_t PacketDataSerializer::ReadByte()
{
    return m_buffer->ReadByte();
}

bool PacketDataSerializer::ReadBoolean()
{
    return m_buffer->ReadBoolean();
}

uint8_t PacketDataSerializer::ReadUnsignedByte()
{
    return m_buffer->ReadUnsignedByte();
}

short PacketDataSerializer::ReadShort()
{
    return m_buffer->ReadShort();
}

int PacketDataSerializer::ReadUnsignedShort()
{
    return m_buffer->ReadUnsignedShort();
}

int PacketDataSerializer::ReadInt()
{
    return m_buffer->ReadInt();
}

wchar_t PacketDataSerializer::ReadWChar()
{
    return m_buffer->ReadWChar();
}

char PacketDataSerializer::ReadChar()
{
    return m_buffer->ReadChar();
}

wchar_t* PacketDataSerializer::ReadWString(int length)
{
    return m_buffer->ReadWString(length);
}

char* PacketDataSerializer::ReadString(int length)
{
    return m_buffer->ReadString(length);
}

void PacketDataSerializer::WriteByte(uint8_t value)
{
    m_buffer->WriteByte(value);
}

void PacketDataSerializer::WriteBoolean(bool value)
{
    m_buffer->WriteBoolean(value);
}

void PacketDataSerializer::WriteUnsignedByte(uint8_t value)
{
    m_buffer->WriteUnsignedByte(value);
}

void PacketDataSerializer::WriteShort(short value)
{
    m_buffer->WriteShort(value);
}

void PacketDataSerializer::WriteUnsignedShort(int value)
{
    m_buffer->WriteUnsignedShort(value);
}

void PacketDataSerializer::WriteInt(int value)
{
    m_buffer->WriteInt(value);
}

int PacketDataSerializer::Capacity()
{
    return m_buffer->Capacity();
}

void* PacketDataSerializer::GetData()
{
    return m_buffer->GetData();
}

uint8_t PacketDataSerializer::_GetByte(int index)
{
    return m_buffer->_GetByte(index);
}

short PacketDataSerializer::_GetShort(int index)
{
    return m_buffer->_GetShort(index);
}

int PacketDataSerializer::_GetInt(int index)
{
    return m_buffer->_GetInt(index);
}

ByteBuf* PacketDataSerializer::ReadBytes(int length)
{
    return m_buffer->ReadBytes(length);
}

void PacketDataSerializer::_SetByte(int index, uint8_t value)
{
    m_buffer->_SetByte(index, value);
}

void PacketDataSerializer::_SetShort(int index, short value)
{
    m_buffer->_SetShort(index, value);
}

void PacketDataSerializer::_SetInt(int index, int value)
{
    m_buffer->_SetInt(index, value);
}

void PacketDataSerializer::WriteBytes(void* src, int srcIndex, int length)
{
    m_buffer->WriteBytes(src, srcIndex, length);
}
} // namespace mpp