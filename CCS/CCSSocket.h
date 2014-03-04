
#ifndef _CCS_SOCKET_H_
#define _CCS_SOCKET_H_

#include "CCSBase.h"

namespace CCS_OS
{
	class CCCSSocket
	{
	public:
		CCCSSocket();
		~CCCSSocket();
	};

	extern CCS_API CCSString IPDigitalToString( DWORD dwIP );

	extern CCS_API DWORD IPStringToDigital( const char* pstrIP );

	extern CCS_API int SetIOCtrl(
		CSSOCKET handle,
		int flag,
		void* pparam );

	extern CCS_API GetLocalAddress(
		CCS_HANDLE handle,
		)
}

#endif // _CCS_SOCKET_H_
