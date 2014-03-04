

/*
	������붨��
*/

#ifndef _CCS_ERROR_DEFINES_H_
#define _CCS_ERROR_DEFINES_H_

#define ERROR_BASE					10000
#define ERROR_NETWORK_BASE			20000
#define ERROR_OPERATOR_BASE			30000

enum enum_CCS_ERROR
{
	// �ɹ�
	CCS_OK							= (long)0,

	// ʧ��
	CCS_ERROR_FAILURE				= (long)(ERROR_BASE + 1 ),

	// û�г�ʼ��
	CCS_ERROR_NOT_INIT				= (long)(ERROR_BASE + 2 ),

	// �Ѿ���ʼ��
	CCS_ERROR_ALREADY_INIT			= (long)(ERROR_BASE + 3 ),

	// û��ʵ��
	CCS_ERROR_NOT_IMPLEMENTED			= (long)(ERROR_BASE + 4 ),

	// ��ָ��
	CCS_ERROR_NULL_POINTER			= (long)(ERROR_BASE + 5 ),

	// �ڴ治��
	CCS_ERROR_OUT_OF_MEMORY			= (long)(ERROR_BASE + 6 ),

	// ��������
	CCS_ERROR_INVALID_PARAM			= (long)(ERROR_BASE + 7 ),

	// ����������
	CCS_ERROR_OPER_NOT_ALLOWED		= (long)(ERROR_BASE + 8 ),

	// ������
	CCS_ERROR_NOT_FOUND				= (long)(ERROR_BASE + 9 ),

	// �Ѿ�����
	CCS_ERROR_ALREADY_EXISTS		= (long)(ERROR_BASE + 10 ),

	// ���ݲ�����
	CCS_ERROR_PARTIAL_DATA			= (long)(ERROR_BASE + 11 ),

	// ��ʱ
	CCS_ERROR_TIMEOUT				= (long)(ERROR_BASE + 12 ),
};

#endif	//_CCS_ERROR_DEFINES_H_