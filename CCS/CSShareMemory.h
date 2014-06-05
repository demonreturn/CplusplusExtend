
#ifndef _CCS_SHARE_MEMORY_H_
#define _CCS_SHARE_MEMORY_H_

#include "CCSBase.h"
#include "CSFile.h"

class CCSShareMemory
{
public:
	enum CCS_SHARE_MEMORY_OPEN_MODE
	{
		OM_TRUNCATE				= 1,		// ���ļ�ӳ��Ĺ����ڴ�ʱ�׶��Ѵ��ڵ��ļ�
		OM_MAP_FILE				= 1 << 1,	// �������ڴ�ӳ�䵽�ļ�
		OM_CREATE				= 1 << 2,	// ������������Զ����������ڴ�
	};

	CCSShareMemory();

	~CCSShareMemory();

	int Open(
		const char* pname,
		DWORD dwSize,
		DWORD dwOpenMode = 0,
		const char* pFileDir = NULL );

	char* GetHeadPointer() const;

	int Close();

	int Read(
		char* pBuffer,
		DWORD dwLength,
		DWORD& dwAcutualRead );

	int Write(
		const char* pBuffer,
		DWORD dwLength );

	int Seek(
		long lOffset,
		DWORD nMoveMethod );

	char* GetCurrentPointer() const;

	/*
	* ����˵��: 
	*	��Ҫ��������Linux�в�����ϵͳĿ¼/dev/shm/�µĹ����ڴ��ļ���
	* Windowsƽ̨�²�ִ���κβ�����
	*
	*/
	void UnLink();

	bool Flush();

protected:
	CCSString GenerateFileName(
		const char* pname,
		const char* pdirtory );

	bool CreateMapFile(
		const char* pname,
		DWORD nMode );

private:
	CCSString					m_strName;
	DWORD						m_dwSize;
	char*						m_pHead;
	char*						m_pCurrent;
	HANDLE						m_hFileMap;
	CCSFile						m_fMapping;
};

#endif // _CCS_SHARE_MEMORY_H_