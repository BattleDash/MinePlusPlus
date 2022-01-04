// Copyright BattleDash. All Rights Reserved.

#include <Base/Platform.h>
#include <Base/String.h>

#include <Server/Network/Socket/TCP/TCPSocketClient.h>

namespace mpp
{
class TCPSocketManager
{
  public:
    MPP_API TCPSocketManager();
    MPP_API ~TCPSocketManager();

    MPP_API TCPSocketClient& Accept();
    MPP_API void Close();

    MPP_API bool IsListening() const;

  private:
    bool m_connected;
    bool m_listening;
    int m_socket;
};
} // namespace mpp