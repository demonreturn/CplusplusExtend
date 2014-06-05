
#include "CCSBase.h"

class CCSDataBlock
{
public:
	// DB标志位
	enum DATABLOCK_FLAGS
	{
		DEL_DATA			=	0,		// 数据空间有DB删除
		NO_DEL_DATA			=	1,		// 数据空间不能删除标志位
	};

	// DB与MB关系的枚举类型
	enum MB_RELATIVE
	{
		CUR_READ_DB			=	1,		// DB是MB的当前读指针位置
		CUR_WRITE_DB		=	1<<1	// 当前写DB
	};

public:
	CCSDataBlock(
		DWORD dwSize,
		char* pBase = NULL );

	~CCSDataBlock();

	CCSDataBlock* Duplicate();

	CCSDataBlock* Clone();

	int Read(
		char* pDst,
		DWORD dwBeginPos,
		DWORD dwLength );

	int Write(
		const char* pBuffer,
		DWORD dwBeginPos,
		DWORD dwLength );

	DWORD GetSpace();

	// 传入的参数必须是MB_RELATIVE类型
	DWORD GetLength( DWORD nMBRelativeFlag = 0 );

	DWORD GetSize();

	char* GetBasePtr();

	DWORD GetCurReadPos();

	DWORD GetCurWritePos();

	int SetCurReadPos( DWORD dwPos );

	int SetCurWritePos( DWORD dwPos );

	void Reset();

	int Release();

private:
	char*						m_pBase;
	DWORD						m_size;
	DWORD						m_readPos;
	DWORD						m_writePos;

	DWORD						m_refCount;
	DWORD						m_dwFlag;
};

