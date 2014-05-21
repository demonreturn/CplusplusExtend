
#ifndef _CCS_SOCKET_H_
#define _CCS_SOCKET_H_

#include "CCSBase.h"

class  CCCSInetAddress;

namespace CCS_OS
{
	/*
	 * 一个用于自动保存errno和重置errno的工具类
	 */

	class CCSSocketErrorAutoSave
	{
	public: 
		CCSSocketErrorAutoSave();
		~CCSSocketErrorAutoSave();

	public:
		int GetLastError();

	private:
		int						m_iLastError;
	};
	
	/*
	 * 把一个4字节的DWORD值转换成符合IPV4规范的地址
	 */
	extern CCS_API CCSString IPDigitalToString( DWORD dwIP );

	/*
	 * 把一个符合IPV4规范的地址转换成4字节的DWORD值
	 */
	extern CCS_API DWORD IPStringToDigital( const char* pstrIP );

	/*
	 * 设置socket的I/O模式
	 */
	extern CCS_API int SetIOCtrl(
		CSSOCKET handle,
		int flag,
		void* pparam );

	/*
	 * 获取一个已有连接中所绑定的本地地址
	 */
	extern CCS_API int GetLocalAddress(
		CSSOCKET handle,
		CCCSInetAddress& localAddress );

	/*
	 * 获取一个已有连接中所绑定的对端地址
	 */
	extern CCS_API int GetRemoteAddress(
		CSSOCKET handle,
		CCCSInetAddress& remoteAddress );

	/*
	 * 设置socket的属性
	 */
	extern CCS_API int SetSocketOption(
		CSSOCKET handle,
		int iLevel,
		int iOption,
		const void* pOption,
		int iOptionLen );

	/*
	 * 获取socket的属性
	 */
	extern CCS_API int GetSocketOption(
		CSSOCKET handle,
		int iLevel,
		int iOption,
		void* pOptionValue,
		int* pOptionLen );

	/*
	 * 关闭一个socket
	 */
	extern CCS_API int CloseSocket(CSSOCKET handle);

	/*
	 * 发送数据
	 */
	extern CCS_API int Send(
		HANDLE handle,
		const char* pData,
		DWORD dwLength,
		int iFlag = 0 );

	/*
	 * 发送数据
	 */
	extern CCS_API int SendV(
		HANDLE handle,
		const iovec pszIov[],
		DWORD dwCount );

	/* 
	 * 收取数据
	 */
	extern CCS_API int Recv(
		HANDLE handle,
		char* pBuffer,
		DWORD dwLength,
		int iFlag = 0 );

	/*
	 * 收取数据
	 */
	extern CCS_API int RecvV(
		HANDLE handle,
		iovec szIov[],
		DWORD dwCount );

	/*
	 * 发送数据, 仅用于UDP
	 */
	extern CCS_API int SendUdp(
		HANDLE handle,
		const char* pData,
		DWORD dwLength,
		const CCCSInetAddress& peerAddress,
		int iFlag = 0 );

	/*
	 * 发送数据, 仅用于UDP
	 */
	extern CCS_API int SendUdpV(
		HANDLE handle,
		const iovec pszIov[],
		DWORD dwCount,
		const CCCSInetAddress& peerAddress );

	/*
	 * 收取数据, 仅用于UDP
	 */
	extern CCS_API int RedvUDP(
		HANDLE handle,
		char* pBuffer,
		DWORD dwLength,
		CCCSInetAddress& peerAddress,
		int iFlag = 0 );

	/*
	 * 为一个socket句柄绑定一个本地地址
	 */
	extern CCS_API int Bind(
		HANDLE handle,
		const CCCSInetAddress& localAddreess );

	/*
	 * 屏蔽某个socket的某些功能
	 */
	extern CCS_API int ShutDown(
		HANDLE handle,
		int iFlag );

	/*
	 * 连接
	 */
	extern CCS_API int Connect(
		HANDLE handle,
		const CCCSInetAddress& peerAddress );

	/*
	 * 监听
	 */
	extern CCS_API int Listen(
		HANDLE handle,
		const CCCSInetAddress& peerAddress );

	/*
	 * 监听
	 */
	extern CCS_API HANDLE Accept(
		HANDLE handle,
		CCCSInetAddress& peerAddress );
}

#endif // _CCS_SOCKET_H_
