#pragma once
#ifndef __MYHASHNODE__H__
#define __MYHASHNODE__H__

#include <iostream>

using namespace std;

//使用拉链法作为冲突处理的哈希表的节点结构
//除了必要的节点指针外，
//存储 2 个数据：键 key， 值 val
//此文件仅供 my_hash.h 文件调用
struct MyHashNode {
	string key;
	string val;
	MyHashNode* next;

	//结构体构造函数
	MyHashNode() : next(NULL) { }
	MyHashNode(string node_key, string node_val)
		: key(node_key), val(node_val), 
		next(NULL) { }
};

#endif // !__MYHASHNODE__H__
