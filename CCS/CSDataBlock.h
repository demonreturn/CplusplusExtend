
#include "CCSBase.h"

class CCSDataBlock
{
public:
	// DB��־λ
	enum DATABLOCK_FLAGS
	{
		DEL_DATA			=	0,		// ���ݿռ���DBɾ��
		NO_DEL_DATA			=	1,		// ���ݿռ䲻��ɾ����־λ
	};

	// DB��MB��ϵ��ö������
	enum MB_RELATIVE
	{
		CUR_READ_DB			=	1,		// DB��MB�ĵ�ǰ��ָ��λ��
		CUR_WRITE_DB		=	1<<1	// ��ǰдDB
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

	// ����Ĳ���������MB_RELATIVE����
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

