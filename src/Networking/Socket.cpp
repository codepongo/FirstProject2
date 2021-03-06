#include "stdafx.h"
#include "LFC/LFC.h"
#include "Socket.h"

#if AMIGA

typedef long long quad_t;
typedef unsigned long long u_quad_t;

#include "../amiga_header.h"

extern "C"
{
#include <bsdsocket.h>
#include <netdb.h>

inline int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exeptfds,
	 struct timeval *timeout)
{
  /* call WaitSelect with NULL signal mask pointer */
  return WaitSelect(nfds, readfds, writefds, exeptfds, timeout, NULL);
}

inline char * inet_ntoa(struct in_addr addr) 
{
  return Inet_NtoA(addr.s_addr);
}

}

#endif

#define WAIT_TIME	40	// seconds

#if WIN32

//#include "../include/windows_header.h"
#define PASCAL      __stdcall
//typedef uint8 BYTE;
//typedef uint16 WORD;
//typedef int * LPINT;
//typedef int BOOL;

//#define Array winArray

/*
namespace System
{
namespace MSWindows
{


//#include <WinSock.h>
}
}

//#undef _INC_WINDOWS
#include <windows.h>
*/
#include <WinSock.h>

//#undef Array
//#undef DefWindowProc
#endif

#if AMIGA

struct Library* SocketBase;

#endif

#if WIN32
#include "LFC/MSWindows.h"

#pragma comment(lib, "ws2_32.lib")

#endif

#include "Socket.h"

namespace System
{
namespace Net
{

using namespace std;
//using namespace MSWindows;

void AsyncSocket::SocketWindow::Create()
{
//	RECT rect;
//	SetRectEmpty(&rect);
	windowBase::Create(NULL, gm::RectI(), NULL, WS_POPUP);
}

bool AsyncSocket::SocketWindow::ProcessWindowMessage(MSWindows::Hwnd hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, DWORD dwMsgMapID*/ )
{
	ASSERT(IsWindow(m_hWnd));

	if (uMsg == WM_USER+101)
	{
		bool bHandled = true;
		lResult = OnMessage(uMsg, wParam, lParam, bHandled);
		return bHandled;
	}
	return false;
}

AsyncSocket::AsyncSocket()
{
#if WIN32
//	if (pSocketWindow == NULL)
	{
		pSocketWindow = new SocketWindow;
		pSocketWindow->Create();
	}
#endif

#if AMIGA
	if (SocketBase == NULL)
	{
		SocketBase = execOpenLibrary(*(ExecBase**)4, "bsdsocket.library", 0);
	}
#endif
}

AsyncSocket::~AsyncSocket()
{
	Close();
}

#if WIN32
WSADATA wsadata;
#endif

void AsyncSocket::OnAccept(int nErrorCode)
{
}

void AsyncSocket::OnConnect(int nErrorCode)
{
}

void AsyncSocket::OnClose(int nErrorCode)
{
}

void AsyncSocket::OnReceive(int nErrorCode)
{
}

void AsyncSocket::OnSend(int nErrorCode)
{
}

bool bSocketStarted = false;


bool AsyncSocket::Socket(int nSocketType, int protocol)
{
	if (!bSocketStarted)
	{
#if WIN32
		int err = WSAStartup(MAKEWORD(2,2), &wsadata);
#endif
		bSocketStarted = true;
	}

	// create socket
	m_socket = socket(AF_INET, nSocketType, protocol);
	if (m_socket == INVALID_SOCKET)
	{
		return false;
	}
#if WIN32
	pSocketWindow->m_sockets.insert(SocketWindow::tysocketmap::value_type(m_socket, this));

	int err;
	err = WSAAsyncSelect(m_socket, pSocketWindow->m_hWnd, WM_USER+101, FD_ACCEPT | FD_READ | FD_WRITE | FD_CONNECT | FD_CLOSE | FD_OOB);
	if (err != 0)
	{
		VERIFY(0);
	}
#endif

//	TRACE("socket = %d\n", m_socket);
	DebugTrace("socket =" << m_socket);

	return true;
}

bool AsyncSocket::Create(UINT nSocketPort, int nSocketType, LPCSTR lpszSocketAddress)
{
	if (!Socket(nSocketType))
		return false;

	if (Bind(nSocketPort,lpszSocketAddress))
		return true;

	return true;
}

/*
bool AsyncSocket::CreateBlocking(int nSocketType, int protocol)
{
	if (!create(nSocketType, protocol))
		return false;

	pSocketWindow->m_sockets.insert(SocketWindow::tysocketmap::value_type(m_socket, this));

	return true;
}
*/

void AsyncSocket::Close()
{
//	OnClose(0);	// ??

	if (m_socket != INVALID_SOCKET)
	{
		//shutdown(m_socket, 0);
#if WIN32
		closesocket(m_socket);
#else
		CloseSocket(m_socket);
#endif
#if 0
		pSocketWindow->m_sockets.erase(pSocketWindow->m_sockets.find(m_socket));
#endif
		m_socket = INVALID_SOCKET;
	}
}

bool AsyncSocket::Bind(UINT nSocketPort, const char* lpszSocketAddress)
{
	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));

	addr.sin_family=AF_INET;
	addr.sin_port=htons(nSocketPort);

	if (lpszSocketAddress == NULL)
	{
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
#if WIN32
		DWORD lResult = inet_addr(lpszSocketAddress);
#else
		DWORD lResult = inet_addr((const unsigned char*)lpszSocketAddress);
#endif
		if (lResult == INADDR_NONE)
		{
#if WIN32
			WSASetLastError(WSAEINVAL);
#endif
			return false;
		}
		addr.sin_addr.s_addr = lResult;
	}

	return Bind((SOCKADDR*)&addr, sizeof(addr));

	/*
	ret = bind(m_socket, (sockaddr*)&addr, sizeof(addr));
	if (ret != 0)
	{
		int error = WSAGetLastError ();
		TRACE("bind error %x\n", error);
		return false;
	}
	else
	{
		ret = WSAAsyncSelect(m_socket, pSocketWindow->m_hWnd, WM_USER+101, FD_READ | FD_WRITE);
		if (ret != 0)
		{
			int error = WSAGetLastError ();
			TRACE("WSAAsyncSelect error %x\n", error);
			return false;
		}
	}
	*/
	return true;
}

bool AsyncSocket::Bind(const SOCKADDR* lpSockAddr, int nSockAddrLen)
{
	/*
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr= htonl(INADDR_ANY);

	int ret;
	
	  */
	int ret = bind(m_socket, (/*MSWindows::*/sockaddr*)lpSockAddr, nSockAddrLen);
	if (ret == 0)
	{
		return true;
	}
	else
	{
#if WIN32
		int error = WSAGetLastError ();
	//	TRACE("bind error %x\n", error);
#endif
		return false;
	}
}

int AsyncSocket::Listen(/*int port,*/ int nConnectionBacklog)
{
	int ret = listen(m_socket, nConnectionBacklog);
	if (ret != 0)
	{
#if WIN32
		int error = WSAGetLastError ();
	//	TRACE("listen error %x\n", error);
#endif
	}
	return ret;

#if 0
	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));

	/*
	char name[256];
	gethostname(name, 256);

	hostent* hp;
	unsigned int temp2 = inet_addr(name);
	if (temp2 == INADDR_NONE)
	{
		hp = gethostbyname(name);
	}
	else
	{
	//	unsigned int temp2 = inet_addr(server);
		hp = gethostbyaddr((char*)&temp2,sizeof(temp2),AF_INET);
	}
	*/

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//addr.sin_addr.s_addr = *(unsigned long*)hp->h_addr;//htonl(INADDR_ANY);

	int ret;
	
	ret = bind(m_socket, (sockaddr*)&addr, sizeof(addr));

	if (ret != 0)
	{
		int error = WSAGetLastError ();
		TRACE("bind error %x\n", error);
	}
	else
	{
		ret = WSAAsyncSelect(m_socket, pSocketWindow->m_hWnd, WM_USER+101, FD_ACCEPT | FD_READ | FD_WRITE | FD_CONNECT | FD_CLOSE);
		if (ret != 0)
		{
			int error = WSAGetLastError ();
			TRACE("WSAAsyncSelect error %x\n", error);
		}
		else
		{
			ret = listen(m_socket, nConnectionBacklog);
			if (ret != 0)
			{
				int error = WSAGetLastError ();
				TRACE("listen error %x\n", error);
			}

			/*
			{
				int namelen = sizeof(addr);
				ret = getsockname (m_socket, (sockaddr*)&addr, &namelen);

			}
			*/
		}
	}
#endif
}

bool AsyncSocket::Connect(DWORD address, int port)
{
	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));

	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=htonl(address);

//	ULONG b = 1;	// non-blocking
//	ioctlsocket(m_socket, FIONBIO, &b);

	int err;
//	err = WSAAsyncSelect(m_socket, pSocketWindow->m_hWnd, WM_USER+101, FD_READ | FD_WRITE | FD_CONNECT | FD_CLOSE);

	if (connect(m_socket, (sockaddr*)&addr, sizeof(addr)) == 0)
	{
		return true;
	}
	else
	{
#if WIN32
		err = WSAGetLastError();
		if (err == WSAEWOULDBLOCK)
		{
		//WSAEINPROGRESS
			return true;
		}
		else
		{
//			TRACE("Failed to connect to socket\n");
			return false;
		}
#else
		err = Errno();
		// TODO

		return false;
#endif
	}
}

bool AsyncSocket::Connect(const char* server, int port)
{
	hostent* hp;
#if WIN32
	unsigned int temp2 = inet_addr(server);
#else
	unsigned int temp2 = inet_addr((const unsigned char*)server);
#endif
	if (temp2 == INADDR_NONE)
	{
#if WIN32
		hp = gethostbyname(server);
#else
		hp = gethostbyname((const unsigned char*)server);
#endif
	}
	else
	{
	//	unsigned int temp2 = inet_addr(server);
#if WIN32
		hp = gethostbyaddr((char*)&temp2,sizeof(temp2),AF_INET);
#else
		hp = gethostbyaddr((unsigned char*)&temp2,sizeof(temp2),AF_INET);
#endif
	}

	if (hp)
	{
#if WIN32
		return Connect(ntohl(*((unsigned long*)hp->h_addr)), port);
#else
		ASSERT(0);
#endif
#if 0
		sockaddr_in addr;
		memset(&addr, 0, sizeof(sockaddr_in));

		addr.sin_family=AF_INET;
		addr.sin_port=htons(port);
		addr.sin_addr.s_addr=*((unsigned long*)hp->h_addr);

	//	ULONG b = 1;	// non-blocking
	//	ioctlsocket(m_socket, FIONBIO, &b);

		int err;
		err = WSAAsyncSelect(m_socket, pSocketWindow->m_hWnd, WM_USER+101, FD_READ | FD_WRITE | FD_CONNECT | FD_CLOSE);

		if (connect(m_socket, (sockaddr*)&addr, sizeof(sockaddr_in)) == 0)
		{
			return true;
		}
		else
		{
			err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK)
			{
			//WSAEINPROGRESS
				return true;
			}
			else
			{
				TRACE("Failed to connect to socket\n");
			}
		}
#endif
	}

	return false;
}

bool AsyncSocket::Accept(AsyncSocket* pSocket)
{
	pSocket->m_socket = accept(m_socket, NULL, NULL);
	if (pSocket->m_socket != INVALID_SOCKET)
	{
#if WIN32
	//	WSAAsyncSelect(pSocket->m_socket, pSocketWindow->m_hWnd, WM_USER+101, FD_READ | FD_WRITE | FD_CONNECT | FD_CLOSE);
		pSocketWindow->m_sockets.insert(SocketWindow::tysocketmap::value_type(pSocket->m_socket, pSocket));
#endif
		return true;
	}
	else
		return false;
}

bool AsyncSocket::GetPeerName(SOCKADDR* lpSockAddr, int* lpSockAddrLen)
{
#if WIN32
	return getpeername(m_socket, (/*MSWindows::*/sockaddr*)lpSockAddr,lpSockAddrLen) == 0;
#else
	return getpeername(m_socket,lpSockAddr,(long*)lpSockAddrLen) == 0;
#endif
}

bool AsyncSocket::GetPeerName(StringVariant& rPeerAddress, UINT& rPeerPort)
{
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));

	int nSockAddrLen = sizeof(sockAddr);
	bool bResult = GetPeerName((SOCKADDR*)&sockAddr, &nSockAddrLen);
	if (bResult)
	{
		rPeerPort = ntohs(sockAddr.sin_port);
		rPeerAddress = inet_ntoa(sockAddr.sin_addr);
	}
	return bResult;
}

#if 0
bool AsyncSocket::GetSockName(std::string& rSocketAddress, UINT& rSocketPort)
{
	SOCKADDR_IN sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));

	int nSockAddrLen = sizeof(sockAddr);
	bool bResult = GetSockName((SOCKADDR*)&sockAddr, &nSockAddrLen);
	if (bResult)
	{
		rSocketPort = ntohs(sockAddr.sin_port);
		rSocketAddress = inet_ntoa(sockAddr.sin_addr);
	}
	return bResult;
}
#endif

int AsyncSocket::Read(void* pv, int size)
{
	int sofar = 0;
	while (sofar < size)
	{
#if 1
		fd_set fd = {1, m_socket};
		timeval tv = {WAIT_TIME,0};
		if (select(0, &fd, NULL, NULL, &tv) == 0)
			break;
#endif

	//	if (!FD_ISSET(m_socket, &fd))
	//		break;

		int left = size - sofar;

#if WIN32
		int nread = recv(m_socket, (char*)pv+sofar, left, 0);
#else
		int nread = recv(m_socket, (unsigned char*)pv+sofar, left, 0);
#endif
		if (nread <= 0)
			break;

		sofar += nread;
	}

	return sofar;
}

int AsyncSocket::Write(const void* pv, int size)
{
	int sofar = 0;
	while (sofar < size)
	{
#if 1
		fd_set fd = {1, m_socket};
		timeval tv = {WAIT_TIME, 0};
		if (select(0, NULL, &fd, NULL, &tv) == 0)
			break;
#endif

		int left = size - sofar;

#if WIN32
		int nwritten = send(m_socket, (const char*)pv+sofar, left, 0);
#else
		int nwritten = send(m_socket, (const unsigned char*)pv+sofar, left, 0);
#endif
		if (nwritten == -1)
			break;

		sofar += nwritten;
	}

	return sofar;
}

int AsyncSocket::Send(const void* pv, int size, int nFlags)
{
#if WIN32
	return send(m_socket, (const char*)pv, size, nFlags);
#else
	return send(m_socket, (const unsigned char*)pv, size, nFlags);
#endif
}

int AsyncSocket::Receive(void* pv, int size, int nFlags)
{
#if WIN32
	return recv(m_socket, (char*)pv, size, nFlags);
#else
	return recv(m_socket, (unsigned char*)pv, size, nFlags);
#endif
}

int AsyncSocket::ReceiveFrom(void* pv, int size, SOCKADDR* lpSockAddr, int* lpSockAddrLen)
{
#if WIN32
	return recvfrom(m_socket, (char*)pv, size, 0, (/*MSWindows::*/sockaddr*)lpSockAddr, lpSockAddrLen);
#else
	return recvfrom(m_socket, (unsigned char*)pv, size, 0, lpSockAddr, (long*)lpSockAddrLen);
#endif
}

int AsyncSocket::IOCtl( long lCommand, DWORD* lpArgument )
{
#if WIN32
	return ioctlsocket(m_socket, lCommand, lpArgument);
#else
	return IoctlSocket(m_socket, lCommand, (char*)lpArgument);
#endif
}

inline uint16 WSAGetSelectError(DWORD lParam)
{
	return HIWORD(lParam);
}

inline uint16 WSAGetSelectEvent(DWORD lParam)
{
	return LOWORD(lParam);
}

#if WIN32
LRESULT AsyncSocket::SocketWindow::OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	SOCKET socket = (SOCKET)wParam;
	tysocketmap::iterator it = m_sockets.find(socket);
	if (it != m_sockets.end())
	{
		AsyncSocket* pSocket = (*it).second;

		WORD nErrorCode = WSAGetSelectError(lParam);

		switch (WSAGetSelectEvent(lParam))
		{
		case FD_ACCEPT:
			pSocket->OnAccept(nErrorCode);
			break;

		case FD_CONNECT:
			pSocket->OnConnect(nErrorCode);
			break;

		case FD_CLOSE:
			pSocket->OnClose(nErrorCode);
			break;

		case FD_READ:
			{
				DWORD nBytes;
				if (pSocket->IOCtl(FIONREAD, &nBytes) != 0)
					nErrorCode = WSAGetLastError();
				if (nBytes != 0 || nErrorCode != 0)
					pSocket->OnReceive(nErrorCode);
				//(*it).second->OnRead();
			}
			break;

		case FD_WRITE:
			pSocket->OnSend(nErrorCode);
			break;

	case FD_OOB:
		ASSERT(0);
	//	pSocket->OnOutOfBandData(nErrorCode);
		break;

		default:
			ASSERT(0);
		}
	}
	else
	{
		MessageBeep(-1);
	}

	return 0;
}

#endif

}
}
