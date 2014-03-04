

#ifndef _CCS_PROCESS_H_
#define _CCS_PROCESS_H_

#include "CCSBase.h"

namespace CCS_OS
{
	const unsigned long OS_MAX_PROCESS_CMD_LEN = 1024;

	long GetProcessID()
	{
#ifdef CCS_WIN32
		return ::GetCurrentProcessId();
#elif defined( CCS_LINUX)		// linux  ʵ��
		return getpid();
#endif
	}

	const char* GetExecName()
	{
		static char s_szCmd[ OS_MAX_PROCESS_CMD_LEN ] = { 0 };

		static char* s_pszCmd = NULL;

#ifdef CCS_WIN32
		if ( NULL == s_pszCmd )
		{
			::GetModuleFileNameA(
				NULL,
				s_szCmd,
				sizeof( s_szCmd ) );

			s_pszCmd = s_szCmd;
		}
#elif defined( CCS_LINUX)		// linux  ʵ��
		char szPidFile[OS_MAX_PROCESS_CMD_LEN];
		memset( szPidFile, 0, sizeof(szPidFile) );

		if ( NULL == s_pszCmd )
		{
			FILE* pPipe = NULL;

			// ���ý�������proc·��
			::sprintf(
				szPidFile, 
				"/proc/%d", 
				getpid() );    
			char szCurrentPath[256]={0};
			char* pPath = ::getcwd( szCurrentPath, 256 );
			if( pPath == NULL )
			{
				//error
			}

			// ����ǰ·����Ϊ����·��
			if( -1 != ::chdir(szPidFile) ) 
			{
				memset( szPidFile, 0, sizeof(szPidFile) );

				//      ��1   ��2  ��3  ��4  ��5  ��6  ��7   ��8   ��9 ��10        ��11
				// lrwxrwxrwx  1  root  root  0   10��  26  16:35  exe  ->   /sbin/dhclient

				// ��shell����ִ�н���� "��11" ��ӡ����, ������ʾ, ��������"/sbin/dhclient\n"
				::snprintf(
					szPidFile,
					OS_MAX_PROCESS_CMD_LEN, 
					"ls -l | grep exe | awk '{print $11}'" );

				// �򿪳����Ӧ��pipe
				pPipe = ::popen(
					szPidFile,
					"r" );

				if( NULL == pPipe ) 
				{
					::chdir(szCurrentPath);
					return NULL; 
				}

				//��ȡshell����ִ�н�����ַ���<s_szCmdName>�� 
				if( NULL == fgets(s_szCmd, OS_MAX_PROCESS_CMD_LEN, pPipe) ) 
				{ 
					::pclose( pPipe );
					::chdir(szCurrentPath);
					return NULL;
				}

				::pclose( pPipe );     //popen������fd����Ҫpclose�ر� 

				// ��'\n'��<s_szCmdName>��ȥ��
				DWORD dwLen = ::strnlen(s_szCmd, OS_MAX_PROCESS_CMD_LEN);

				if (  dwLen > 0 && s_szCmd[ dwLen - 1 ] == 0x0A )
				{
					s_szCmd[ dwLen - 1 ] = 0x00;
				}					
				//SC_ZERO( 
				//	s_szCmdName + ::strnlen(s_szCmdName, SC_OS_PROCESS_CMD_BUF_LEN), 
				//	SC_OS_PROCESS_CMD_BUF_LEN - ::strnlen(s_szCmdName, SC_OS_PROCESS_CMD_BUF_LEN) );

				s_pszCmd = s_szCmd;
				::chdir(szCurrentPath);
			}
		}
#endif

		return s_pszCmd;
	}

	const char* GetProcessName()
	{
		const char* pExeName = GetExecName();
		if ( NULL != pExeName )
		{
			const char* pchFind = pExeName + ::strnlen(pExeName, OS_MAX_PROCESS_CMD_LEN );

			while( (pchFind > pExeName) && 
				('\\' != *pchFind) )
			{
				pchFind--;
			}

			if( '\\' == *pchFind )
			{
				pchFind++;
			}

			return pchFind;
		}
		else
		{
			return "UnknowProcess";
		}
	}

	const char* GetExecDir()
	{
		static char s_exExecDir[OS_MAX_PROCESS_CMD_LEN] = { 0 };
		static char* s_pexExecDir = NULL;

		if ( NULL != s_pexExecDir )
		{
			const char* pszExecCmdName = GetExecName();
			const char* pszProcessName = GetProcessName();

			const char* poffset = ::strstr( pszExecCmdName, pszProcessName );

			::strncpy( s_exExecDir, pszExecCmdName, poffset - pszExecCmdName );

			s_pexExecDir = s_exExecDir;
		}

		return s_pexExecDir;
	}

	int SetProcessPriority( CCS_HANDLE prohandle, DWORD dwPriority )
	{
#ifdef CCS_WIN32
		BOOL bRet = ::SetPriorityClass( prohandle, dwPriority );

		return bRet ? 0 : -1;

#elif defined( CCS_LINUX)		// linux  ʵ��
		return -1;
#endif
	}

	DWORD GetProcessPriority( CCS_HANDLE prohandle )
	{
#ifdef CCS_WIN32
		return ::GetPriorityClass( prohandle );
#elif defined( CCS_LINUX)		// linux  ʵ��
		return 0;
#endif
	}
}

#endif //_CCS_PROCESS_H_

