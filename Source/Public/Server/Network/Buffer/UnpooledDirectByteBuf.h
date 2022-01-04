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
    MPP_API uint8_t _GetByte(int index) override;

  private:
    uint8_t* m_buffer;
    int m_capacity;
};
} // namespace mpp