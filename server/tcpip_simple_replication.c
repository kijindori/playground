#include "tcpip_simple_replication.h"

/***************** 
  간단한 IOCP 서버 
*******************/



int InitializeServerService( ServerService* service )
{
  assert( InitializeWinsock(&service->wsaData) == 0 ) ;
  assert( InitializeIocp(&service->iocpHandle, service->acceptEx, service->connectEx, service->disconnectEx) == 0 );
  assert( InitializeListenSocket(&service->listenSocket) != SOCKET_ERROR );
  assert( InitializeSession(service) == 0 );
  
  return 0;
}

/* 최대 세션 개수만큼 생성, IOCP를 위한 소켓으로 초기화 */
int InitializeSession(ServerService* service)
{
  for(int i =0; i<NUM_MAX_SESSIONS ; i++)
  {
    service->contextCollection[i] = (SessionContext*)malloc(sizeof(SessionContext));
    SessionContext* ctx = service->contextCollection[i];
    ctx->clientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    assert( CreateIoCompletionPort((HANDLE) ctx->clientSocket, service->iocpHandle, 0, 0) != NULL );
  }

  return 0;
}

int InitializeWinsock(WSADATA* wsaData)
{
  return WSAStartup(MAKEWORD(2,2), wsaData);
}

int InitializeIocp( HANDLE* iocpHandle, LPFN_ACCEPTEX acceptEx, LPFN_CONNECTEX connEx, LPFN_DISCONNECTEX disconnEx )
{
  GUID acceptExGuid = WSAID_ACCEPTEX;
  GUID connExGuid = WSAID_CONNECTEX;
  GUID disconnExGuid = WSAID_DISCONNECTEX;

  SOCKET initSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  DWORD bytes;

  assert( WSAIoctl(initSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &acceptExGuid, sizeof(acceptExGuid), acceptEx, sizeof(acceptEx),&bytes, NULL,NULL) != SOCKET_ERROR);
  assert( WSAIoctl(initSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &connExGuid, sizeof(connExGuid), connEx, sizeof(connEx), &bytes, NULL, NULL) != SOCKET_ERROR);
  assert( WSAIoctl(initSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &disconnExGuid, sizeof(disconnExGuid), disconnEx, sizeof(disconnEx), &bytes, NULL, NULL) != SOCKET_ERROR);

  *iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

  closesocket(initSocket);
  WSACleanup();
  return 0;
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

  return 0;
}

int AcceptConnection(ServerService* service)
{
  for(int i=0; i<NUM_MAX_SESSIONS ; i++)
  {
    SessionContext* ctx = service->contextCollection[i];

    // Proactor accept 호출
    service->acceptEx(
      service->listenSocket, 
      ctx->clientSocket, 
      ctx->buffer, 
      sizeof(ctx->buffer), 
      sizeof(struct sockaddr_in)+16, 
      sizeof(struct sockaddr_in)+16, 
      NULL, 
      (OVERLAPPED*)&ctx->overlapped
      );
  }
}


int main()
{
  ServerService service;
  InitializeServerService(&service);
  AcceptConnection(&service);
  
  //TODO: 세션 관리자 (최대 개수보다 초과한 경우, 연결 유지하는 중인지 확인 등..)
  while(1)
  {
    DWORD numBytes;
    ULONG completionKey;
    SessionContext* context;
    DWORD timeout = INFINITE; 

    int result = GetQueuedCompletionStatus(service.iocpHandle, &numBytes, (PULONG_PTR)&completionKey,(struct _OVERLAPPED**) &context, timeout);
    assert( result == 0 );

    if(GetLastError() == WAIT_TIMEOUT)
      continue;
    
    // TODO: 에러 처리

    // 연결 요청 처리
    struct sockaddr_in clientAddr;
    int addrLen = sizeof(clientAddr);
    char clientIp[16];

    getpeername(context->clientSocket, (struct sockaddr*)&clientAddr, &addrLen);
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIp, sizeof(clientIp));

    printf("클라이언트가 접속했습니다. IP: %s \n", clientIp);
  }
  

  return 0;
}