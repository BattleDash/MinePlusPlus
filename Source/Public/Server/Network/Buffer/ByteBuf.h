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

    MPP_API virtual uint8_t GetByte(int index) = 0;
    MPP_API virtual uint8_t _GetByte(int index) = 0;

    MPP_API virtual uint8_t ReadByte() = 0;
    MPP_API virtual bool ReadBoolean() = 0;
    MPP_API virtual uint8_t ReadUnsignedByte() = 0;
};
} // namespace mpp