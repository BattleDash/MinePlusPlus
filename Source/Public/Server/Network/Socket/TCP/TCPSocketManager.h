// Copyright BattleDash. All Rights Reserved.

#include <Base/Platform.h>
#include <Base/String.h>

namespace mpp
{
class TCPSocketManager
{
  public:
    TCPSocketManager();
    ~TCPSocketManager();

    TCPSocket& Accept();
    void Close();

    bool IsListening() const;

  private:
    bool m_connected;
    bool m_listening;
    int m_socket;
};
} // namespace mpp