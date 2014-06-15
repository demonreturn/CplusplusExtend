

#ifndef _CCS_TRACE_DEFINE_H_
#define _CCS_TRACE_DEFINE_H_

#include "CCSBase.h"


/* 进程ID */
const DWORD CCS_TRACE_MAX_PROCESS				= 10;

/* 进程名 */
const DWORD CCS_TRACE_MAX_PROCESS_NAME			= 32;

/* 允许打印多少种类型不同的信息, 暂时不会用到, 保留项 */
const DWORD CCS_TRACE_MAX_MODULE				= 20;

/* 允许信息类型的最大值, 暂时不会用到, 保留项 */
const DWORD CCS_TRACE_MAX_MASK					= 32;

/* 信息类型名称的最大长度, 暂时不会用到, 保留项 */
const DWORD CCS_TRACE_MAX_MODULE_NAME			= 32;

/* 允许信息类型最大值的名字的最大长度, 暂时不会用到, 保留项 */
const DWORD CCS_TRACE_MAX_MASK_NAME				= 32;

/* trace内容的最大长度 */
const DWORD CCS_TRACE_MAX_TRACE_LEN				= 1024;

/* trace格式化部分保留长度 */
const DWORD CCS_TRACE_RESERVE_DATA_LEN			= 64;

/* 实际允许trace的最大长度 */
const DWORD CCS_TRACE_AVAILABLE_DATA_LEN		= CCS_TRACE_MAX_TRACE_LEN - CCS_TRACE_RESERVE_DATA_LEN;

/* trace打印多少行时保存, <1>为1行就保存 */
const DWORD CCS_TRACE_DEFAULT_FLUSH_FREQ		= 1;

/* trace一次打印最多产生的日志文件数*/
const DWORD CCS_TRACE_DEFAULT_FILE_NUM			= 10;

/* 字符数组最大长度*/
const DWORD CCS_TRACE_CHAR_MAX_LEN				= 255;

#ifdef CCS_WIN32
const DWORD CCS_TRACE_DEFAULT_TRACE_SIZE		= (20 * 1024 * 1024 );
#elif defined( CCS_LINUX)		// linux  实现
const DWORD CCS_TRACE_DEFAULT_TRACE_SIZE		= (20 * 1024 * 1024 );	
#endif

const char CCS_TRACE_EXT_NAME[]					= ".log";
const char CCS_TRACE_CURRENT_LINE_MARK[]		= "************************* Current trace line *************************\n\n";
const char CCS_TRACE_FORMAT[]					= "[%02d/%02d/%04d %02d:%02d:%02d.%03ld pid=%d tid=%d] %s %s\n";

/*
 *  默认文件夹
 */
#ifdef CCS_WIN32
#define CCS_TRACE_FOLDER_NAME		".\\Log\\"
#elif defined( CCS_LINUX)		// linux  实现
#define CCS_TRACE_FOLDER_NAME		"./Log/"
#endif

#endif	// _CCS_TRACE_DEFINE_H_
