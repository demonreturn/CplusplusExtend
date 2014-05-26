#include "CCSFile.h"

#ifdef CCS_WIN32
#include <io.h>
#include <sys/stat.h>
#elif defined( CCS_LINUX)		// linux  实现
#include <sys/statfs.h>
#endif



extern CCS_API HANDLE CCS_OS::OpenFile( 
	const char* pFullPath,
	DWORD dwFlags /*= O_RDONLY */,
	DWORD dwMode /*= CCS_DEFAULT_FILE_MODE*/,
	DWORD dwFileAttributes /*= FILE_ATTRIBUTE_NORMAL */,
	LPSECURITY_ATTRIBUTES pSapSecurity /*= NULL */ )
{
	if ( NULL == pFullPath )
	{
		return CCS_INVALID_HANDLE;
	}

#ifdef CCS_WIN32
	DWORD dwAccess = GENERIC_READ;
	DWORD dwShareMode = dwMode;
	DWORD dwCreation = OPEN_EXISTING;
	DWORD dwFlagsAndAttributes = dwFileAttributes;

	//对文件的访问权限标志
	if ( CCS_BIT_ENABLED( dwFlags, O_WRONLY ) )
	{
		dwAccess = GENERIC_WRITE;
	}
	else if ( CCS_BIT_ENABLED( dwFlags, O_RDWR ) )
	{
		dwAccess = GENERIC_READ | GENERIC_WRITE;
	}
	//文件打开/创建标志
	if ( CCS_BIT_CMP_MASK(dwFlags, ( O_CREAT | O_EXCL ), ( O_CREAT | O_EXCL ) ) )
		//if ( (nFlags & (_O_CREAT | _O_EXCL) ) == (_O_CREAT | _O_EXCL) )
	{
		//文件不存在,生成一个新文件
		//文件已存在,创建失败
		dwCreation = CREATE_NEW;
	}
	else if( CCS_BIT_CMP_MASK(dwFlags, ( O_CREAT | O_TRUNC ), ( O_CREAT | O_TRUNC ) ) )
		//else if ( (nFlags & (_O_CREAT | _O_TRUNC) ) == ((_O_CREAT | _O_TRUNC)) )
	{
		//文件已存在,返回成功 文件被清空
		//文件不存在,生成一个新文件
		dwCreation = CREATE_ALWAYS;
	}
	else if ( CCS_BIT_ENABLED (dwFlags, O_CREAT) )
	{
		//文件已存在,返回成功
		//文件不存在,生成一个新文件
		dwCreation = OPEN_ALWAYS;
	}
	else if ( CCS_BIT_ENABLED (dwFlags, O_TRUNC) )
	{
		//文件不存在,返回失败
		dwCreation = TRUNCATE_EXISTING;
	}

	if ( CCS_BIT_ENABLED( dwFlags, O_TEMPORARY ) )
	{
		//临时文件属性
		dwFlagsAndAttributes |= FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE;
	}

	HANDLE handle = ::CreateFileA(
		pFullPath,
		dwAccess,
		dwShareMode,
		pSapSecurity,
		dwCreation,
		dwFlagsAndAttributes,
		NULL );

	if ( INVALID_HANDLE_VALUE == handle )
	{
		return CCS_INVALID_HANDLE;
	}
	else
	{
		if ( CCS_BIT_ENABLED( dwFlags, O_APPEND ))
		{
			::SetFilePointer( handle,
				0,
				0,
				FILE_END );
		}
	}

	return handle;
#elif defined( CCS_LINUX)		// linux  实现
	return (::open(pFullPath,
		dwFlags,
		dwMode ));
#endif
}

extern CCS_API int CCS_OS::ReadFile( 
	HANDLE fileHandle,
	LPVOID pBuffer,
	DWORD dwReadSize,
	LPDWORD dwHaveRead )
{
	if ( NULL == pBuffer )
	{
		return -1;
	}

#ifdef CCS_WIN32
	if ( ::ReadFile( fileHandle,
		pBuffer,
		dwReadSize,
		dwHaveRead,
		NULL ))
	{
		return 0;
	}
#elif defined( CCS_LINUX)		// linux  实现
	ssize_t sz = ::read( fileHandle,
		pBuffer,
		dwReadSize );
	if ( sz >= 0 )
	{
		*dwHaveRead = sz;
		return 0;
	}
#endif
	return -1;
}

extern CCS_API int CCS_OS::WriteFile(
	HANDLE handle,
	const LPVOID pBuffer,
	DWORD dwWriteSize,
	LPDWORD dwHaveWrite )
{
	if ( NULL == dwHaveWrite )
	{
		return -1;
	}
#ifdef CCS_WIN32
	if ( ::WriteFile( handle,
		pBuffer,
		dwWriteSize,
		dwHaveWrite,
		NULL ))
	{
		return 0;
	}
#elif defined( CCS_LINUX)		// linux  实现
	ssize_t sz = ::write( handle,
		pBuf,
		dwWriteSize );
	if ( sz >= 0 )
	{
		*dwHaveWrite = sz;
		return 0;
	}
#endif

	return -1;
}

extern CCS_API int CCS_OS::SeekFile( 
	HANDLE handle,
	CCS_OFFSET lDistance,
	DWORD nMoveMethod )
{
#ifdef CCS_WIN32
	LARGE_INTEGER lgDistance;
	lgDistance.QuadPart = lDistance;

	DWORD dwRet = ::SetFilePointer( handle, 
		lgDistance.LowPart,
		&(lgDistance.HighPart),
		nMoveMethod );
	if ( dwRet == INVALID_SET_FILE_POINTER 
		&& GetLastError() != NO_ERROR )
	{
		return -1;
	}

	return 0;
#elif defined( CCS_LINUX)		// linux  实现
	CCS_OFFSET lRet = ::lseek( handle,
		lDistance,
		nMoveMethod );

	if ( -1 != lRet )
	{
		return 0;
	}
#endif

	return -1;
}

extern CCS_API int CCS_OS::FlushFile( HANDLE handle )
{
#ifdef CCS_WIN32
	if ( ::FlushFileBuffers( handle ))
	{
		return 0;
	}

	return -1;
#elif defined( CCS_LINUX)		// linux  实现
	return ::fsync( handle );
#endif

	return -1;
}

extern CCS_API int CCS_OS::CloseFile( HANDLE handle )
{
#ifdef CCS_WIN32
	if ( ::CloseHandle( handle ))
	{
		return 0;
	}

	return -1;
#elif defined( CCS_LINUX)		// linux  实现
	return ::close(handle);
#endif

	return -1;
}

extern CCS_API CCS_OFFSET CCS_OS::GetFilePosition( 
	HANDLE handle )
{
#ifdef CCS_WIN32
	LARGE_INTEGER lgIn;
	LARGE_INTEGER lgOut;
	lgIn.QuadPart = 0;

	BOOL bRet = ::SetFilePointerEx( 
		handle,
		lgIn, 
		&lgOut, 
		FILE_CURRENT );

	if ( bRet)
	{
		return lgOut.QuadPart;
	}

	return -1;
#elif defined( CCS_LINUX)		// linux  实现
	return ::lseek( handle, 0, SEEK_CUR );
#endif

	return -1;
}

extern CCS_API int CCS_OS::GetFileAddribute( 
	const char* pFullPath,
	FileAttribute& fileAttri )
{
	if ( NULL == pFullPath )
	{
		return -1;
	}

#ifdef CCS_WIN32
	struct __stat64 fileStat;
	int iRet = ::_stat64( pFullPath,
		&fileStat );

	if ( 0 != iRet )
	{
		return -1;
	}

	fileAttri.llCreateTime = fileStat.st_ctime;
	fileAttri.llFlesize = fileStat.st_size;
	fileAttri.llModifyTime = fileStat.st_mtime;
#elif defined( CCS_LINUX)		// linux  实现
	struct stat fileStat;

	int iRet = ::stat( pFullPath, 
		&fileStat );
	if ( 0 == iRet )
	{
		fileAttri.llCreateTime = fileStat.st_ctime;
		fileAttri.llFlesize = fileStat.st_size;
		fileAttri.llModifyTime = fileStat.st_mtime;
	}

	return -1;
#endif
	
	return -1;
}

extern CCS_API int CCS_OS::ReadLockFile( 
	HANDLE handle,
	CCS_OFFSET offset,
	LONGLONG llLockSize,
	DWORD dwFlags /*= LOCKFILE_FAIL_IMMEDIATELY */ )
{
#ifdef CCS_WIN32
	LARGE_INTEGER lg;
	lg.QuadPart = llLockSize;

	OVERLAPPED overLapp;
	lg.QuadPart = offset;
	overLapp.hEvent=NULL;
	overLapp.Internal = NULL;
	overLapp.InternalHigh = NULL;
	overLapp.Offset = lg.LowPart;
	overLapp.OffsetHigh = lg.HighPart;

	BOOL bRet = ::LockFileEx( handle,
		dwFlags,
		0,
		lg.LowPart,
		lg.HighPart,
		&overLapp );

	return bRet ? 0 : -1;

#elif defined( CCS_LINUX)		// linux  实现
	struct flock fileLock;
	fileLock.l_type = F_RDLCK;
	fileLock.l_whence = SEEK_SET;
	fileLock.l_start = offset;
	fileLock.l_len = llLockSize;

	int iRet = ::fcntl( 
		handle, 
		F_SETLK, 
		&fileLock );

	return iRet != 0 ? -1 : 0;
#endif
}

extern CCS_API int CCS_OS::WriteLockFile( 
	HANDLE handle,
	CCS_OFFSET offset,
	LONGLONG llLockSize,
	DWORD dwFlags /*= LOCKFILE_EXCLUSIVE_LOCK */ )
{
#ifdef CCS_WIN32
	LARGE_INTEGER lg;
	lg.QuadPart = llLockSize;

	OVERLAPPED overLapp;
	lg.QuadPart = offset;
	overLapp.Offset = lg.LowPart;
	overLapp.OffsetHigh = lg.HighPart;

	DWORD dwWriteFlag = dwFlags | LOCKFILE_EXCLUSIVE_LOCK;

	BOOL bRet = ::LockFileEx( handle,
		dwWriteFlag,
		0,
		lg.LowPart,
		lg.HighPart,
		&overLapp );

	return bRet ? 0 : -1;
#elif defined( CCS_LINUX)		// linux  实现
	struct flock fileLock;
	fileLock.l_type = F_WRLCK;
	fileLock.l_whence = SEEK_SET;
	fileLock.l_start = offset;
	fileLock.l_len = llLockSize;

	int iRet = ::fcntl( 
		handle, 
		F_SETLK, 
		&fileLock );

	return iRet != 0 ? -1 : 0;
#endif
}

extern CCS_API int CCS_OS::UnLockFile(
	HANDLE handle,
	CCS_OFFSET offset,
	LONGLONG llLockSize )
{
#ifdef CCS_WIN32
	LARGE_INTEGER lg;
	lg.QuadPart = llLockSize;

	OVERLAPPED overLapp;
	lg.QuadPart = offset;
	overLapp.Offset = lg.LowPart;
	overLapp.OffsetHigh = lg.HighPart;

	BOOL bRet = ::UnlockFileEx( 
		handle, 
		0, 
		lg.LowPart,
		lg.HighPart, 
		&overLapp );

	return bRet ? 0 : -1;
#elif defined( CCS_LINUX)		// linux  实现
	struct flock fileLock;
	fileLock.l_type = F_UNLCK;
	fileLock.l_whence = SEEK_SET;
	fileLock.l_start = offset;
	fileLock.l_len = llLockSize;

	int iRet = ::fcntl( 
		handle, 
		F_SETLK, 
		&fileLock );

	return (iRet == 0) ? 0 : -1;
#endif
}

extern CCS_API bool CCS_OS::IsFileExist( 
	const char* pFullPath )
{
	if ( NULL == pFullPath )
	{
		return false;
	}

#ifdef CCS_WIN32
	int iRet = ::_access( pFullPath, 0 );

	return (iRet == -1) ? false : true;
#elif defined( CCS_LINUX)		// linux  实现
	int iRet = ::access( pFullPath, F_OK );

	return (iRet == -1) ? false : true;
#endif
}

extern CCS_API bool CCS_OS::DeleteFile( 
	const char* pFullPath )
{
	if ( NULL == pFullPath )
	{
		return false;
	}

#ifdef CCS_WIN32
	return ::DeleteFileA( pFullPath );
#elif defined( CCS_LINUX)		// linux  实现
	int iRet = ::remove( pFullPath );

	return (0 == iRet) ? true : false;
#endif
}

extern CCS_API LONGLONG CCS_OS::GetDiskFreeSpace( 
	const char* pPath )
{
#ifdef CCS_WIN32
	ULARGE_INTEGER lgFreeBytesAvailable;
	ULARGE_INTEGER lgTotalBytes;
	ULARGE_INTEGER lgFreeTotalBytes;

	BOOL bRet = ::GetDiskFreeSpaceExA( pPath, 
		&lgFreeBytesAvailable, 
		&lgTotalBytes, 
		&lgFreeTotalBytes );
	return lgFreeBytesAvailable.QuadPart;

#elif defined( CCS_LINUX)		// linux  实现
	struct statfs fsInfo;
	int iRet = ::statfs( pPath, 
		&fsInfo );
	//f_bsize : block大小
	//f_bfree : blcok数
	LONGLONG llFreeBytes = fsInfo.f_bsize * fsInfo.f_bfree ;

	return llFreeBytes;
#endif
}

extern CCS_API int CCS_OS::TruncateFile( 
	HANDLE handle,
	LONGLONG llSize )
{
#ifdef CCS_WIN32
	int iRet = ::CCS_OS::SeekFile(
		handle, llSize, CCS_SEEK_BEGIN );

	if ( iRet != 0 )
	{
		return -1;
	}

	BOOL bRet = ::SetEndOfFile( handle );

	return bRet ? 0 : -1;
#elif defined( CCS_LINUX)		// linux  实现
	return ::ftruncate( 
		handle, 
		llSize );
#endif
}

extern CCS_API int CCS_OS::CopyFile( 
	const char* pSrcFile,
	const char* pDstFile,
	bool bFailIfExist /*= true */ )
{
	if ( NULL == pSrcFile || NULL == pDstFile )
	{
		return -1;
	}
#ifdef CCS_WIN32
	bool bRet = ::CopyFileA(
		pSrcFile,
		pDstFile,
		bFailIfExist );

	return bRet ? 0 : -1;
#elif defined( CCS_LINUX)		// linux  实现
	
	if ( bFailIfExist && IsFileExist( pDstFile ))
	{
		return -;
	}

	FileAttribute fileAttri;
	LONGLONG llFileSize = -1;

	if ( 0 == CCS_OS::GetFileAddribute( pSrcFile, fileAttri) )
	{
		llFileSize = fileAttri.llFlesize;
	}
	else
	{
		return -1;
	}

	HANDLE hSrcHandle = CCS_OS::OpenFile( pSrcFile );
	HANDLE hDstHandle = CCS_OS::OpenFile( pDstFile,
		O_CREAT | O_WRONLY | O_TRUNC );

	if ( CCS_INVALID_HANDLE == hSrcHandle 
		|| CCS_INVALID_HANDLE == hDstHandle )
	{
		CCS_OS::CloseFile( pSrcFile );
		CCS_OS::CloseFile( pDstFile );
		return -1;
	}

	if ( -1 ==  CCS_OS::ReadLockFile( hSrcHandle,
		0, llFileSize) )
	{
		CCS_OS::CloseFile( pSrcFile );
		CCS_OS::CloseFile( pDstFile );
		return -1;
	}

	//目标文件加写锁
	if ( -1 == CCS_OS::WriteLockFile( hDstHandle,
		0, llFileSize) )
	{
		CCS_OS::UnLockFile( hSrcHandle,
			0, llFileSize );

		CCS_OS::CloseFile( pSrcFile );
		CCS_OS::CloseFile( pDstFile );
		return -1;
	}

	char tempBuffer[1024];
	DWORD dwHaveRead = 0;
	DWORD dwhaveWrite = 0;
	int iRet = 0;
	bool bFailed = false;

	while ( true )
	{
		dwHaveRead = 0;
		iRet = CCS_OS::ReadFile( hSrcHandle,
			tempBuffer,
			sizeof( tempBuffer),
			&dwHaveRead );

		if ( -1 == iRet 
			|| 0 == dwHaveRead )
		{
			
			bFailed = ((0 == dwHaveRead) ? false : true);

			break;
		}

		dwhaveWrite = 0;
		iRet = ::CCS_OS::WriteFile( hDstHandle, tempBuffer, dwHaveRead, &dwhaveWrite );
		if ( -1 == iRet )
		{
			bFailed = true;
			break;
		}
	}

	CCS_OS::UnLockFile( hSrcHandle, 0, llFileSize );
	CCS_OS::UnLockFile( hDstHandle, 0, llFileSize );

	CCS_OS::CloseFile( hSrcHandle );
	CCS_OS::CloseFile( hDstHandle );

	if ( bFailed )
	{
		CCS_OS::DeleteFile( pDstFile );
	}

	return 0;
#endif

	return -1;
}
