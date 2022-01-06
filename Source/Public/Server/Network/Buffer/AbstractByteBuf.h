// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Server/Network/Buffer/ByteBuf.h>

namespace mpp
{
class AbstractByteBuf : public ByteBuf
{
  public:
    MPP_API AbstractByteBuf(int maxCapacity);
    MPP_API ~AbstractByteBuf();

    MPP_API bool IsReadOnly() override;
    MPP_API ByteBuf* AsReadOnly() override;
    MPP_API int MaxCapacity() override;
    MPP_API void MaxCapacity(int maxCapacity) override;
    MPP_API int ReaderIndex() override;
    MPP_API static void CheckIndexBounds(int readerIndex, int writerIndex, int capacity);
    MPP_API void CheckReadableBytes(int minimumReadableBytes);
    MPP_API ByteBuf& ReaderIndex(int readerIndex) override;
    MPP_API int WriterIndex() override;
    MPP_API ByteBuf& WriterIndex(int writerIndex) override;
    MPP_API ByteBuf& SetIndex(int readerIndex, int writerIndex) override;
    MPP_API ByteBuf& Clear() override;
    MPP_API bool IsReadable() override;
    MPP_API bool IsReadable(int numBytes) override;
    MPP_API bool IsWritable() override;
    MPP_API bool IsWritable(int numBytes) override;
    MPP_API int ReadableBytes() override;
    MPP_API int WritableBytes() override;
    MPP_API int MaxWritableBytes() override;
    MPP_API ByteBuf& MarkReaderIndex() override;
    MPP_API ByteBuf& ResetReaderIndex() override;
    MPP_API ByteBuf& MarkWriterIndex() override;
    MPP_API ByteBuf& ResetWriterIndex() override;

    MPP_API uint8_t GetByte(int index) override;

    MPP_API uint8_t ReadByte() override;
    MPP_API bool ReadBoolean() override;
    MPP_API uint8_t ReadUnsignedByte() override;
    MPP_API short ReadShort() override;
    MPP_API int ReadUnsignedShort() override;
    MPP_API int ReadInt() override;
    MPP_API int64_t ReadLong() override;
    MPP_API wchar_t ReadWChar() override;
    MPP_API wchar_t* ReadWString(int length) override;
    MPP_API char ReadChar() override;
    MPP_API char* ReadString(int length) override;

    MPP_API void WriteByte(uint8_t value) override;
    MPP_API void WriteBoolean(bool value) override;
    MPP_API void WriteUnsignedByte(uint8_t value) override;
    MPP_API void WriteShort(short value) override;
    MPP_API void WriteUnsignedShort(int value) override;
    MPP_API void WriteInt(int value) override;
    MPP_API void WriteLong(int64_t value) override;

  protected:
    int m_readerIndex;
    int m_writerIndex;

  private:
    int m_markedReaderIndex;
    int m_markedWriterIndex;
    int m_maxCapacity;
};
} // namespace mpp