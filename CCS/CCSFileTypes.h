

#ifndef _CCS_FILE_TYPES_H_
#define _CCS_FILE_TYPES_H_

enum CCS_FILE_TYPES
{
	FILE_TYPES_REGULAR_FILE				= 0,	// 普通文件
	FILE_TYPES_OVERLAPIO_FILE			= 1,	// 异步io
	FILE_TYPES_NETFILE					= 2,	// 分布式网络文件
};
#endif	// _CCS_FILE_TYPES_H_