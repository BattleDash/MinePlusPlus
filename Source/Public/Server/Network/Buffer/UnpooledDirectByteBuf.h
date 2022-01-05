// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Server/Network/Buffer/AbstractByteBuf.h>

namespace mpp
{
class UnpooledDirectByteBuf : public AbstractByteBuf
{
  public:
    MPP_API UnpooledDirectByteBuf(int initialCapacity, int maxCapacity);
    MPP_API ~UnpooledDirectByteBuf();

    MPP_API int Capacity() override;

    MPP_API void* GetData() override;
    MPP_API uint8_t _GetByte(int index) override;
    MPP_API short _GetShort(int index) override;
    MPP_API int _GetInt(int index) override;
    MPP_API ByteBuf* ReadBytes(int length) override;
    MPP_API void WriteBytes(void* src, int srcIndex, int length) override;

    MPP_API void _SetByte(int index, uint8_t value) override;
    MPP_API void _SetShort(int index, short value) override;
    MPP_API void _SetInt(int index, int value) override;

  private:
    uint8_t* m_buffer;
    int m_capacity;
};
} // namespace mpp