

/*
	错误编码定义
*/

#ifndef _CCS_ERROR_DEFINES_H_
#define _CCS_ERROR_DEFINES_H_

#define ERROR_BASE					10000
#define ERROR_NETWORK_BASE			20000
#define ERROR_OPERATOR_BASE			30000

enum enum_CCS_ERROR
{
	// 成功
	CCS_OK							= (long)0,

	// 失败
	CCS_ERROR_FAILURE				= (long)(ERROR_BASE + 1 ),

	// 没有初始化
	CCS_ERROR_NOT_INIT				= (long)(ERROR_BASE + 2 ),

	// 已经初始化
	CCS_ERROR_ALREADY_INIT			= (long)(ERROR_BASE + 3 ),

	// 没有实现
	CCS_ERROR_NOT_IMPLEMENTED			= (long)(ERROR_BASE + 4 ),

	// 空指针
	CCS_ERROR_NULL_POINTER			= (long)(ERROR_BASE + 5 ),

	// 内存不足
	CCS_ERROR_OUT_OF_MEMORY			= (long)(ERROR_BASE + 6 ),

	// 参数错误
	CCS_ERROR_INVALID_PARAM			= (long)(ERROR_BASE + 7 ),

	// 操作不允许
	CCS_ERROR_OPER_NOT_ALLOWED		= (long)(ERROR_BASE + 8 ),

	// 不存在
	CCS_ERROR_NOT_FOUND				= (long)(ERROR_BASE + 9 ),

	// 已经存在
	CCS_ERROR_ALREADY_EXISTS		= (long)(ERROR_BASE + 10 ),

	// 数据不完整
	CCS_ERROR_PARTIAL_DATA			= (long)(ERROR_BASE + 11 ),

	// 超时
	CCS_ERROR_TIMEOUT				= (long)(ERROR_BASE + 12 ),
};

#endif	//_CCS_ERROR_DEFINES_H_