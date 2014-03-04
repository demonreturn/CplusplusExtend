

/*
	ƽ̨���
*/

#ifndef _CCS_PLANTFORM_DEFINES_H_
#define _CCS_PLANTFORM_DEFINES_H_

// operation system check

// windows 
#ifdef WIN32
	#ifndef CCS_WIN32
		#define CCS_WIN32
	#endif
#endif

// linux
#ifdef LINUX
	#ifndef CCS_LINUX
		#define CCS_LINUX
	#endif
#endif

#if ( !defined( CCS_WIN32) && !defined(CCS_LINUX) )
	#error Only support win32 and linux
#endif


/*
 *	��win32�����£���Ҫʹ��winsock2������Ҫ�������win NT 4.0��
 *	����ϵͳ
 */
#ifdef CCS_WIN32
	#ifndef SC_HAS_WINNT_4_0
		#define SC_HAS_WINNT_4_0 1	// Ĭ�ϵ�ǰ����ϵͳΪwin NT 4.0�����ϰ汾
	#endif	// SC_HAS_WINNT_4_0

	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0400
	#endif	// _WIN32_WINNT
#endif

/*
 *	win32���뻷��ǿ��VCϵ�У���֧������Boland C++�ȵ�
 */

#ifdef CCS_WIN32
	#ifndef _MSC_VER
		#error on Win32 platform, ONLY support VC to compile
	#endif	// _MSC_VER

	/* Ҫ����̰߳汾C++���п� */
	#ifndef _MT
		#error on Win32 platform, C Run-Time Libraries of multiple thread version is needed
	#endif

	#pragma warning( disable: 4786 )	// identifier was truncated to '255' characters in the browser information(mainly brought by stl)
	#pragma warning( disable: 4355 )	// disable 'this' used in base member initializer list
	#pragma warning( disable: 4275 )	// deriving exported class from non-exported
	#pragma warning( disable: 4251 )	// using non-exported as public in exported
	#pragma warning( disable: 4005 )	// ���Կ��ܴ����ض���

	#if ( _MSC_VER > 1200 )
		#pragma warning( disable: 6258 )	// ����ʹ��TerminateThread������warning
		#pragma warning( disable: 6326 )
	#endif	// ( _MSC_VER > 1200 )

#endif	// CCS_WIN32

/*
 * �������汾�Ķ���
 */
#ifndef SC_COMPILER_VERSION
	#ifdef CCS_WIN32
		#define SC_COMPILER_VERSION _MSC_VER
		#if (SC_COMPILER_VERSION < 1600)
			#error VC2010 or later version is needed 
		#endif	// (SC_COMPILER_VERSION < 1200)
	#else	// !SC_WIN32
		#define SC_COMPILER_VERSION 1600
	#endif	// SC_WIN32
#endif	// SC_COMPILER_VERSION

/*
 *	��linux�����£���Ҫʹ��epoll������Ҫ��kernel��2.6.x������
 */
#ifdef CCS_LINUX
	#include <linux/version.h>
	#if ( !defined(LINUX_VERSION_CODE) || !defined(KERNEL_VERSION) )
		#error macro LINUX_VERSION_CODE & KERNEL_VERSION are both missed, please check your <linux/version.h>
	#endif	//  ( !defined(LINUX_VERSION_CODE) || !defined(KERNEL_VERSION) )

	#if ( LINUX_VERSION_CODE < KERNEL_VERSION(2, 4, 20) )
		#error kernel 2.6.9 or later version is needed
	#endif	// ( LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 9) )
#endif	// SC_LINUX
#endif	// _CCS_PLANTFORM_DEFINES_H_