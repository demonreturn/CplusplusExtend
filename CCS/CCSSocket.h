
#ifndef _CCS_SOCKET_H_
#define _CCS_SOCKET_H_

#include "CCSBase.h"

class  CCCSInetAddress;

namespace CCS_OS
{
	/*
	 * һ�������Զ�����errno������errno�Ĺ�����
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
	 * ��һ��4�ֽڵ�DWORDֵת���ɷ���IPV4�淶�ĵ�ַ
	 */
	extern CCS_API CCSString IPDigitalToString( DWORD dwIP );

	/*
	 * ��һ������IPV4�淶�ĵ�ַת����4�ֽڵ�DWORDֵ
	 */
	extern CCS_API DWORD IPStringToDigital( const char* pstrIP );

	/*
	 * ����socket��I/Oģʽ
	 */
	extern CCS_API int SetIOCtrl(
		CSSOCKET handle,
		int flag,
		void* pparam );

	/*
	 * ��ȡһ���������������󶨵ı��ص�ַ
	 */
	extern CCS_API int GetLocalAddress(
		CSSOCKET handle,
		CCCSInetAddress& localAddress );

	/*
	 * ��ȡһ���������������󶨵ĶԶ˵�ַ
	 */
	extern CCS_API int GetRemoteAddress(
		CSSOCKET handle,
		CCCSInetAddress& remoteAddress );

	/*
	 * ����socket������
	 */
	extern CCS_API int SetSocketOption(
		CSSOCKET handle,
		int iLevel,
		int iOption,
		const void* pOption,
		int iOptionLen );

	/*
	 * ��ȡsocket������
	 */
	extern CCS_API int GetSocketOption(
		CSSOCKET handle,
		int iLevel,
		int iOption,
		void* pOptionValue,
		int* pOptionLen );

	/*
	 * �ر�һ��socket
	 */
	extern CCS_API int CloseSocket(CSSOCKET handle);

	/*
	 * ��������
	 */
	extern CCS_API int Send(
		HANDLE handle,
		const char* pData,
		DWORD dwLength,
		int iFlag = 0 );

	/*
	 * ��������
	 */
	extern CCS_API int SendV(
		HANDLE handle,
		const iovec pszIov[],
		DWORD dwCount );

	/* 
	 * ��ȡ����
	 */
	extern CCS_API int Recv(
		HANDLE handle,
		char* pBuffer,
		DWORD dwLength,
		int iFlag = 0 );

	/*
	 * ��ȡ����
	 */
	extern CCS_API int RecvV(
		HANDLE handle,
		iovec szIov[],
		DWORD dwCount );

	/*
	 * ��������, ������UDP
	 */
	extern CCS_API int SendUdp(
		HANDLE handle,
		const char* pData,
		DWORD dwLength,
		const CCCSInetAddress& peerAddress,
		int iFlag = 0 );

	/*
	 * ��������, ������UDP
	 */
	extern CCS_API int SendUdpV(
		HANDLE handle,
		const iovec pszIov[],
		DWORD dwCount,
		const CCCSInetAddress& peerAddress );

	/*
	 * ��ȡ����, ������UDP
	 */
	extern CCS_API int RedvUDP(
		HANDLE handle,
		char* pBuffer,
		DWORD dwLength,
		CCCSInetAddress& peerAddress,
		int iFlag = 0 );

	/*
	 * Ϊһ��socket�����һ�����ص�ַ
	 */
	extern CCS_API int Bind(
		HANDLE handle,
		const CCCSInetAddress& localAddreess );

	/*
	 * ����ĳ��socket��ĳЩ����
	 */
	extern CCS_API int ShutDown(
		HANDLE handle,
		int iFlag );

	/*
	 * ����
	 */
	extern CCS_API int Connect(
		HANDLE handle,
		const CCCSInetAddress& peerAddress );

	/*
	 * ����
	 */
	extern CCS_API int Listen(
		HANDLE handle,
		const CCCSInetAddress& peerAddress );

	/*
	 * ����
	 */
	extern CCS_API HANDLE Accept(
		HANDLE handle,
		CCCSInetAddress& peerAddress );
}

#endif // _CCS_SOCKET_H_
