#include "tcpip_simple_replication.h"

void InitializeServer();
void InitializeWinsock(WSADATA* wsaData);
int InitializeIocp(HANDLE* iocpHandle, LPFN_ACCEPTEX acceptEx, LPFN_CONNECTEX connEx, LPFN_DISCONNECTEX disconnEx);
int InitializeListenSocket(SOCKET* socket);
void Accept(unsigned int maxSession);

void InitializeServer()
{

}

void InitializeWinsock(WSADATA* wsaData)
{
  WSAStartup(MAKEWORD(2,2), wsaData);
}

int InitializeIocp( HANDLE* iocpHandle, LPFN_ACCEPTEX acceptEx, LPFN_CONNECTEX connEx, LPFN_DISCONNECTEX disconnEx )
{
  GUID acceptExGuid = GUID_ACCEPTEX;
  GUID connExGuid = GUID_CONNECTEX;
  GUID disconnExGuid = GUID_DISCONNECTEX;

  SOCKET initSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  DWORD bytes;

  WSAIoctl(initSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &acceptExGuid, sizeof(acceptExGuid), acceptEx, sizeof(acceptEx),&bytes, NULL,NULL);
  WSAIoctl(initSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &connExGuid, sizeof(connExGuid), connEx, sizeof(connEx), &bytes, NULL, NULL);
  WSAIoctl(initSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &disconnExGuid, sizeof(disconnExGuid), disconnEx, sizeof(disconnEx), &bytes, NULL, NULL);

  *iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

  closesocket(initSocket);
  WSACleanup();
  return 1;
}

int InitializeListenSocket(SOCKET* listenSocket)
{
  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serveraddr;
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(NUM_PORT);

   if( bind(sock, (struct sockaddr*) &serveraddr, sizeof(serveraddr)) == SOCKET_ERROR )
    return SOCKET_ERROR;

  if( listen(sock, SOMAXCONN) == SOCKET_ERROR )
    return SOCKET_ERROR;

  *listenSocket = sock;

  return 1;
}

int main()
{
  WSADATA wsaData;
  HANDLE iocpHandle;
  SOCKET listenSocket;
  LPFN_ACCEPTEX acceptEx;
  LPFN_CONNECTEX connectEx;
  LPFN_DISCONNECTEX disconnectEx;
  
  InitializeWinsock(&wsaData);
  InitializeIocp(&iocpHandle, acceptEx, connectEx, disconnectEx);
  
  assert ( InitializeListenSocket(&listenSocket) != SOCKET_ERROR );
  
  SessionContext* contextCollection[NUM_MAX_SESSIONS] = {(SessionContext*)malloc(sizeof(SessionContext))};

  for(int i=0; i<NUM_MAX_SESSIONS; i++)
  {
    SessionContext* ctx = contextCollection[i];
    ctx->clientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    
    CreateIoCompletionPort((HANDLE) ctx->clientSocket, iocpHandle, 0, 0);

    acceptEx(
      listenSocket, 
      ctx->clientSocket, 
      ctx->buffer, 
      sizeof(ctx->buffer), 
      sizeof(struct sockaddr_in)+16, 
      sizeof(struct sockaddr_in)+16, 
      NULL, 
      (OVERLAPPED*)&ctx->overlapped
      );
  }

  return 0;
}