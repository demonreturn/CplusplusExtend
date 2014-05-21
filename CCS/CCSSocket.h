
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
	extern int SetSocketOption(
		CSSOCKET handle,
		int iLevel,
		int iOption,
		const void* pOption,
		int iOptionLen );
}

#endif // _CCS_SOCKET_H_
