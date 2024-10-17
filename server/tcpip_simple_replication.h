#pragma comment(lib, "ws2_32")

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <winsock.h>
#include <mswsock.h>

#define NUM_PORT            7777
#define NUM_MAX_SESSIONS    5
#define SESSION_BUFFER_SIZE 100

/* MinGW 에서 mswsock.h 가 포함이 안되는 경우 하드코딩 */
#ifndef _MSWSOCK_
    #define WSAID_ACCEPTEX      { 0xb5367df1, 0x5b9c, 0x11d1, { 0x96, 0x8b, 0x00, 0xc0, 0x4f, 0x6c, 0xd7, 0x5e } };
    #define WSAID_CONNECTEX     { 0x25a8b5e1, 0x7c13, 0x11d1, { 0x96, 0x8b, 0x00, 0xc0, 0x4f, 0x6c, 0xd7, 0x5e } };
    #define WSAID_DISCONNECTEX   { 0x7e4c81a1, 0x7c13, 0x11d1, { 0x96, 0x8b, 0x00, 0xc0, 0x4f, 0x6c, 0xd7, 0x5e } };

    typedef BOOL (WINAPI *LPFN_CONNECTEX)(
    SOCKET s,
    const struct sockaddr *name,
    int namelen,
    PVOID lpBuffer,
    DWORD dwBufferLen,
    LPDWORD lpdwBytesTransferred,
    LPOVERLAPPED lpOverlapped
    );

    typedef BOOL (WINAPI *LPFN_DISCONNECTEX)(
        SOCKET s,
        LPOVERLAPPED lpOverlapped,
        DWORD dwFlags,
        DWORD dwReserved
    );

    typedef BOOL (WINAPI *LPFN_ACCEPTEX)(
        SOCKET sListenSocket,
        SOCKET sAcceptSocket,
        PVOID pOutputBuffer,
        DWORD dwReceiveDataLength,
        DWORD dwLocalAddressLength,
        DWORD dwRemoteAddressLength,
        LPDWORD lpdwBytesReceived,
        LPOVERLAPPED lpOverlapped
    );
#endif


int InitializeServerService();
int InitializeWinsock(WSADATA* wsaData);
int InitializeIocp(HANDLE* iocpHandle, LPFN_ACCEPTEX acceptEx, LPFN_CONNECTEX connEx, LPFN_DISCONNECTEX disconnEx);
int InitializeListenSocket(SOCKET* socket);
int InitializeSession(ServerService* service);
int AcceptConnection(ServerService* service);


typedef struct SessionContext
{
  OVERLAPPED overlapped;
  SOCKET clientSocket;
  char buffer[SESSION_BUFFER_SIZE];
} SessionContext;

typedef struct ServerService
{
    WSADATA wsaData;
    HANDLE iocpHandle;
    SOCKET listenSocket;
    LPFN_ACCEPTEX acceptEx;
    LPFN_CONNECTEX connectEx;
    LPFN_DISCONNECTEX disconnectEx;
    SessionContext* contextCollection[NUM_MAX_SESSIONS];
} ServerService;
