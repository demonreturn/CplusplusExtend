

#ifndef _CCS_TRACE_DEFINE_H_
#define _CCS_TRACE_DEFINE_H_

#include "CCSBase.h"


/* ����ID */
const DWORD CCS_TRACE_MAX_PROCESS				= 10;

/* ������ */
const DWORD CCS_TRACE_MAX_PROCESS_NAME			= 32;

/* �����ӡ���������Ͳ�ͬ����Ϣ, ��ʱ�����õ�, ������ */
const DWORD CCS_TRACE_MAX_MODULE				= 20;

/* ������Ϣ���͵����ֵ, ��ʱ�����õ�, ������ */
const DWORD CCS_TRACE_MAX_MASK					= 32;

/* ��Ϣ�������Ƶ���󳤶�, ��ʱ�����õ�, ������ */
const DWORD CCS_TRACE_MAX_MODULE_NAME			= 32;

/* ������Ϣ�������ֵ�����ֵ���󳤶�, ��ʱ�����õ�, ������ */
const DWORD CCS_TRACE_MAX_MASK_NAME				= 32;

/* trace���ݵ���󳤶� */
const DWORD CCS_TRACE_MAX_TRACE_LEN				= 1024;

/* trace��ʽ�����ֱ������� */
const DWORD CCS_TRACE_RESERVE_DATA_LEN			= 64;

/* ʵ������trace����󳤶� */
const DWORD CCS_TRACE_AVAILABLE_DATA_LEN		= CCS_TRACE_MAX_TRACE_LEN - CCS_TRACE_RESERVE_DATA_LEN;

/* trace��ӡ������ʱ����, <1>Ϊ1�оͱ��� */
const DWORD CCS_TRACE_DEFAULT_FLUSH_FREQ		= 1;

/* traceһ�δ�ӡ����������־�ļ���*/
const DWORD CCS_TRACE_DEFAULT_FILE_NUM			= 10;

/* �ַ�������󳤶�*/
const DWORD CCS_TRACE_CHAR_MAX_LEN				= 255;

#ifdef CCS_WIN32
const DWORD CCS_TRACE_DEFAULT_TRACE_SIZE		= (20 * 1024 * 1024 );
#elif defined( CCS_LINUX)		// linux  ʵ��
const DWORD CCS_TRACE_DEFAULT_TRACE_SIZE		= (20 * 1024 * 1024 );	
#endif

const char CCS_TRACE_EXT_NAME[]					= ".log";
const char CCS_TRACE_CURRENT_LINE_MARK[]		= "************************* Current trace line *************************\n\n";
const char CCS_TRACE_FORMAT[]					= "[%02d/%02d/%04d %02d:%02d:%02d.%03ld pid=%d tid=%d] %s %s\n";

/*
 *  Ĭ���ļ���
 */
#ifdef CCS_WIN32
#define CCS_TRACE_FOLDER_NAME		".\\Log\\"
#elif defined( CCS_LINUX)		// linux  ʵ��
#define CCS_TRACE_FOLDER_NAME		"./Log/"
#endif

#endif	// _CCS_TRACE_DEFINE_H_
