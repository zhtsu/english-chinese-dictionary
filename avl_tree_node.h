#pragma once
#ifndef __AVLTREENODE__H__
#define __AVLTREENODE__H__

#include <iostream>

using namespace std;

//AVL树节点的结构
//除了必要的节点指针外，
//存储 2 个数据：键 key，值 val
//此文件仅供 avl_tree.h 文件调用
struct AvlTreeNode {
	string key;
	string val;
	AvlTreeNode* left;
	AvlTreeNode* right;

	//结构体构造函数
	AvlTreeNode() : left(NULL), right(NULL) { }
	AvlTreeNode(string node_key, string node_val)
		: key(node_key), val(node_val),
		left(NULL), right(NULL) { }
};

#endif // !__AVLTREENODE__H__
