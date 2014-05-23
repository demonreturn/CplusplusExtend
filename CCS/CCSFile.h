#pragma once

#ifndef	_CCS_FILE_OPERATION_H_
#define _CCS_FILE_OPERATION_H_

#include "CCSBase.h"

namespace CCS_OS
{
	/*
	 * 打开文件
	 */
	extern CCS_API HANDLE OpenFile(
		const char* pFullPath,
		DWORD dwFlags = O_RDONLY ,
		DWORD dwMode = CCS_DEFAULT_FILE_MODE,
		DWORD dwFileAttributes = FILE_ATTRIBUTE_NORMAL ,
		LPSECURITY_ATTRIBUTES pSapSecurity = NULL );

	/*
	 * 读取文件
	 */
	extern CCS_API int ReadFile(
		HANDLE fileHandle,
		LPVOID pBuffer,
		DWORD dwReadSize,
		LPDWORD dwHaveRead );

	/*
	 * 写入文件
	 */
	extern CCS_API int WriteFile(
		HANDLE handle, 
		const LPVOID pBuffer,
		DWORD dwWriteSize,
		LPDWORD dwHaveWrite );

	/*
	 * 文件指针定位
	 */
	extern CCS_API int SeekFile(
		HANDLE handle,
		CCS_OFFSET lDistance,
		DWORD nMoveMethod );

	/*
	 * 文件同步到磁盘
	 */
	extern CCS_API int FlushFile(
		HANDLE handle );

	/*
	 * 关闭文件
	 */
	extern CCS_API int CloseFile(
		HANDLE handle );

	/*
	 * 取文件当前位置 从文件开始的位置
	 */
	extern CCS_API CCS_OFFSET GetFilePosition(
		HANDLE handle );

	/*
	 * 取文件的大小 创建时间 修改时间 属性
	 */
	extern CCS_API int GetFileAddribute(
		const char* pFullPath,
		FileAttribute& fileAttri );

	/*
	 * 文件读锁, 共享锁, 默认锁获取失败时立即返回,不阻塞
	 * 没有读权限时读锁失败
	 */
	extern CCS_API int ReadLockFile(
		HANDLE handle,
		CCS_OFFSET offset,
		LONGLONG llLockSize,
		DWORD dwFlags = LOCKFILE_FAIL_IMMEDIATELY );

	/*
	 * 文件写锁，独占
	 */
	extern CCS_API int WriteLockFile(
		HANDLE handle,
		CCS_OFFSET offset,
		LONGLONG llLockSize,
		DWORD dwFlags = LOCKFILE_EXCLUSIVE_LOCK );

	/*
	 * 解锁
	 */
	extern CCS_API int UnLockFile(
		HANDLE handle,
		CCS_OFFSET offset,
		LONGLONG llLockSize );

	/*
	 * 文件是否存在
	 */
	extern CCS_API bool IsFileExist( const char* pFullPath );

	/*
	 * 删除文件, 删除空目录, 只读文件不能被删, 权限不够
	 */
	extern CCS_API bool DeleteFile( const char* pFullPath );

	/*
	*	取Path所在路径的磁盘剩余空间字节
	* [参数]
	* pPath			:[IN]  文件路径 [ "C:\\", "E:\\" ,"/root/test.txt" , "/" ]
	*/
	extern CCS_API LONGLONG GetDiskFreeSpace( const char* pPath );

	/*
	 * 截断文件, 适用于将文件缩小
	 */
	extern CCS_API int TruncateFile( 
		HANDLE scHandle,
		LONGLONG llSize );

	/*
	 * 复制文件, 从pSourceFile到pDestFile, 可选择是否覆盖DestFile
	 */
	extern CCS_API int CopyFile(
		const char* pSrcFile,
		const char* pDstFile,
		bool bFailIfExist = true );
}

#endif // _CCS_FILE_OPERATION_H_

