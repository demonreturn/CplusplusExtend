
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
	extern int SetSocketOption(
		CSSOCKET handle,
		int iLevel,
		int iOption,
		const void* pOption,
		int iOptionLen );
}

#endif // _CCS_SOCKET_H_
