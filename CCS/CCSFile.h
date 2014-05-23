#pragma once

#ifndef	_CCS_FILE_OPERATION_H_
#define _CCS_FILE_OPERATION_H_

#include "CCSBase.h"

namespace CCS_OS
{
	/*
	 * ���ļ�
	 */
	extern CCS_API HANDLE OpenFile(
		const char* pFullPath,
		DWORD dwFlags = O_RDONLY ,
		DWORD dwMode = CCS_DEFAULT_FILE_MODE,
		DWORD dwFileAttributes = FILE_ATTRIBUTE_NORMAL ,
		LPSECURITY_ATTRIBUTES pSapSecurity = NULL );

	/*
	 * ��ȡ�ļ�
	 */
	extern CCS_API int ReadFile(
		HANDLE fileHandle,
		LPVOID pBuffer,
		DWORD dwReadSize,
		LPDWORD dwHaveRead );

	/*
	 * д���ļ�
	 */
	extern CCS_API int WriteFile(
		HANDLE handle, 
		const LPVOID pBuffer,
		DWORD dwWriteSize,
		LPDWORD dwHaveWrite );

	/*
	 * �ļ�ָ�붨λ
	 */
	extern CCS_API int SeekFile(
		HANDLE handle,
		CCS_OFFSET lDistance,
		DWORD nMoveMethod );

	/*
	 * �ļ�ͬ��������
	 */
	extern CCS_API int FlushFile(
		HANDLE handle );

	/*
	 * �ر��ļ�
	 */
	extern CCS_API int CloseFile(
		HANDLE handle );

	/*
	 * ȡ�ļ���ǰλ�� ���ļ���ʼ��λ��
	 */
	extern CCS_API CCS_OFFSET GetFilePosition(
		HANDLE handle );

	/*
	 * ȡ�ļ��Ĵ�С ����ʱ�� �޸�ʱ�� ����
	 */
	extern CCS_API int GetFileAddribute(
		const char* pFullPath,
		FileAttribute& fileAttri );

	/*
	 * �ļ�����, ������, Ĭ������ȡʧ��ʱ��������,������
	 * û�ж�Ȩ��ʱ����ʧ��
	 */
	extern CCS_API int ReadLockFile(
		HANDLE handle,
		CCS_OFFSET offset,
		LONGLONG llLockSize,
		DWORD dwFlags = LOCKFILE_FAIL_IMMEDIATELY );

	/*
	 * �ļ�д������ռ
	 */
	extern CCS_API int WriteLockFile(
		HANDLE handle,
		CCS_OFFSET offset,
		LONGLONG llLockSize,
		DWORD dwFlags = LOCKFILE_EXCLUSIVE_LOCK );

	/*
	 * ����
	 */
	extern CCS_API int UnLockFile(
		HANDLE handle,
		CCS_OFFSET offset,
		LONGLONG llLockSize );

	/*
	 * �ļ��Ƿ����
	 */
	extern CCS_API bool IsFileExist( const char* pFullPath );

	/*
	 * ɾ���ļ�, ɾ����Ŀ¼, ֻ���ļ����ܱ�ɾ, Ȩ�޲���
	 */
	extern CCS_API bool DeleteFile( const char* pFullPath );

	/*
	*	ȡPath����·���Ĵ���ʣ��ռ��ֽ�
	* [����]
	* pPath			:[IN]  �ļ�·�� [ "C:\\", "E:\\" ,"/root/test.txt" , "/" ]
	*/
	extern CCS_API LONGLONG GetDiskFreeSpace( const char* pPath );

	/*
	 * �ض��ļ�, �����ڽ��ļ���С
	 */
	extern CCS_API int TruncateFile( 
		HANDLE scHandle,
		LONGLONG llSize );

	/*
	 * �����ļ�, ��pSourceFile��pDestFile, ��ѡ���Ƿ񸲸�DestFile
	 */
	extern CCS_API int CopyFile(
		const char* pSrcFile,
		const char* pDstFile,
		bool bFailIfExist = true );
}

#endif // _CCS_FILE_OPERATION_H_

