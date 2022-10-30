#pragma once
#ifndef __MYHASH__H__
#define __MYHASH__H__

#include <iostream>
#include "my_hash_node.h"

using namespace std;

//开哈希表的桶的最大数量，同时也是哈希函数计算键使用的模
const int kMaxSize = 10;

//开哈希表类，存储待查的单词数据
//仅存储同一字母开头的单词
//根据每个键（英文字符串）的“分值”，使用除留余数法作为哈希函数
//提供增删查操作并且只支持查询英文单词
class MyHash {
public:
	MyHash();
	MyHash(string key_array[], string val_array[], int length);
	~MyHash();

public:
	//打印数据
	void PrintList();
	//查找数据
	bool FindVal(string key);
	//得到数据
	string GetVal(string key);
	//插入一个节点
	void Insert(string english, string chinese);
	//删除一个节点
	string Delete(string key);
	//得到表内数据的总数量
	int get_length();
	//拷贝表内数据
	void CopyDataTo(string array[], string val_array[], int length);

private:
	//检查字符串是否为英文
	bool IsEnglish_(string str);
	//计算一个英文字符串对应哈希表内的桶号
	int GetEnglishKeyIn_(string str);

private:
	//记录数据的数量
	int length_;
	//存储同字母开头的单词的哈希桶
	MyHashNode* buckets_[kMaxSize];
};

#endif // !__MYHASH__H__
