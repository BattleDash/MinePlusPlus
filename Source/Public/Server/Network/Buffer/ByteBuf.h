// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>

#include <cstdint>

namespace mpp
{
class ByteBuf
{
  public:
    MPP_API virtual bool IsReadOnly() = 0;
    MPP_API virtual ByteBuf* AsReadOnly() = 0;
    MPP_API virtual int Capacity() = 0;
    MPP_API virtual int MaxCapacity() = 0;
    MPP_API virtual void MaxCapacity(int maxCapacity) = 0;
    MPP_API virtual int ReaderIndex() = 0;
    MPP_API virtual ByteBuf& ReaderIndex(int readerIndex) = 0;
    MPP_API virtual int WriterIndex() = 0;
    MPP_API virtual ByteBuf& WriterIndex(int writerIndex) = 0;
    MPP_API virtual ByteBuf& SetIndex(int readerIndex, int writerIndex) = 0;
    MPP_API virtual ByteBuf& Clear() = 0;
    MPP_API virtual bool IsReadable() = 0;
    MPP_API virtual bool IsReadable(int numBytes) = 0;
    MPP_API virtual bool IsWritable() = 0;
    MPP_API virtual bool IsWritable(int numBytes) = 0;
    MPP_API virtual int ReadableBytes() = 0;
    MPP_API virtual int WritableBytes() = 0;
    MPP_API virtual int MaxWritableBytes() = 0;
    MPP_API virtual ByteBuf& MarkReaderIndex() = 0;
    MPP_API virtual ByteBuf& ResetReaderIndex() = 0;
    MPP_API virtual ByteBuf& MarkWriterIndex() = 0;
    MPP_API virtual ByteBuf& ResetWriterIndex() = 0;

    MPP_API virtual void* GetData() = 0;
    MPP_API virtual uint8_t GetByte(int index) = 0;
    MPP_API virtual uint8_t _GetByte(int index) = 0;
    MPP_API virtual short _GetShort(int index) = 0;
    MPP_API virtual int _GetInt(int index) = 0;

    MPP_API virtual uint8_t ReadByte() = 0;
    MPP_API virtual bool ReadBoolean() = 0;
    MPP_API virtual uint8_t ReadUnsignedByte() = 0;
    MPP_API virtual short ReadShort() = 0;
    MPP_API virtual int ReadUnsignedShort() = 0;
    MPP_API virtual int ReadInt() = 0;
    MPP_API virtual wchar_t ReadWChar() = 0;
    MPP_API virtual wchar_t* ReadWString(int length) = 0;

    MPP_API virtual void _SetByte(int index, uint8_t value) = 0;
    MPP_API virtual void _SetShort(int index, short value) = 0;
    MPP_API virtual void _SetInt(int index, int value) = 0;

    MPP_API virtual void WriteByte(uint8_t value) = 0;
    MPP_API virtual void WriteBoolean(bool value) = 0;
    MPP_API virtual void WriteUnsignedByte(uint8_t value) = 0;
    MPP_API virtual void WriteShort(short value) = 0;
    MPP_API virtual void WriteUnsignedShort(int value) = 0;
    MPP_API virtual void WriteInt(int value) = 0;

    MPP_API virtual ByteBuf* ReadBytes(int length) = 0;
    MPP_API virtual void WriteBytes(void* src, int srcIndex, int length) = 0;
};
} // namespace mpp