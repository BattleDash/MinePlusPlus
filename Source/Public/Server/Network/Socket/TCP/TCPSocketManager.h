// Copyright BattleDash. All Rights Reserved.

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/Network/Socket/TCP/TCPSocketClient.h>
#include <Server/Network/Socket/TCP/TCPSocketServer.h>

#include <vector>
#include <thread>
#include <mutex>
#include <functional>

namespace mpp
{
class TCPSocketManager
{
  public:
    MPP_API TCPSocketManager();
    MPP_API ~TCPSocketManager();

    MPP_API bool Listen(const String& ip, int port);
    MPP_API std::vector<TCPSocketClient*>& Clients();
    MPP_API void ChildHandler(std::function<void(TCPSocketClient*)> childHandler);
    MPP_API void Close();


  private:
    MPP_API void AcceptClients();
    MPP_API void Run();

    std::mutex m_mutex;
    TCPSocketServer* m_socket;
    std::vector<TCPSocketClient*> m_clients;
    bool m_listening;
    std::thread m_acceptThread;
    std::thread m_thread;
    std::function<void(TCPSocketClient*)> m_childHandler;
};
} // namespace mpp