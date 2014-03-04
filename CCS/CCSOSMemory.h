

#ifndef _CCS_OS_MEMORY_H_
#define _CCS_OS_MEMORY_H_

#include "CCSBase.h"

namespace CCS_OS
{
	inline void* OSMemset(
		void* pdst,
		int value,
		unsigned int len )
	{
		return ::memset(
			pdst, value, len );
	}

	inline int OSMemcpy(
		void* pdst,
		unsigned int dstlen,
		void* psrc,
		unsigned int srclen )
	{
		return ::memcpy_s(
			pdst, dstlen, psrc, srclen );
	}

	inline int OSMemcmp(
		void* pbuf1,
		void* pbuf2,
		unsigned int len )
	{
		return ::memcmp( pbuf1, pbuf2, len );
	}

	inline unsigned int OSStrlen( const char* pstr )
	{
		return ::strlen( pstr );
	}

	inline unsigned int OSStrlen( const char* pstr, DWORD dwBufSize )
	{
		return ::strnlen_s( pstr, dwBufSize );
	}

	inline int OSPrintf(
		FILE* stream,
		const char* pformat,
		... )
	{
		va_list argp;
		va_start( argp, pformat );

		int ret = ::_vfprintf_s_l(
			stream, pformat, NULL, argp );

		va_end( argp );

		return ret;
	}

	inline int OSSnprintf(
		char* pbuf,
		size_t bufSize,
		size_t count,
		const char* pformat,
		... )
	{
		va_list argp;
		va_start( argp, pformat );

		int ret = ::_vsnprintf_s_l(
			pbuf,
			bufSize,
			count,
			pformat,
			NULL,
			argp );

		va_end( argp );

		return ret;
	}

	inline int OSSprintf(
		char* pbuf,
		size_t bufSize,
		const char* pformat,
		... )
	{
		va_list argp;
		va_start( argp, pformat );

		int ret = ::_vsprintf_s_l(
			pbuf,
			bufSize,
			pformat,
			NULL,
			argp );

		va_end( argp );

		return ret;
	}
}

#endif // _CCS_OS_MEMORY_H_

