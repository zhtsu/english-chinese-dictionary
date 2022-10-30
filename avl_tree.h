#pragma once
#ifndef __AVLTREE__H__
#define __AVLTREE__H__

#include <iostream>
#include "avl_tree_node.h"

using namespace std;

//AVL树类，存储待查的单词数据
//提供增删查操作
class AvlTree {
public:
	AvlTree();
	AvlTree(string key_array[], string val_array[], int length);
	~AvlTree();

public:
	//打印树存储的数据
	void PrintData();
	//查找数据
	bool FindVal(string goal_key);
	//得到数据
	string GetVal(string goal_key);
	//插入数据
	void Insert(string key, string val);
	//删除数据
	string Delete(string goal_key);

private:
	//判断字符串是否为英文单词
	bool IsEnglish_(string str);
	//中序遍历输出数据
	void InOrderPrint_(AvlTreeNode* root);
	//键值为英文的中序遍历查找
	string FindByEnglishKey_(AvlTreeNode* root, string goal_key);
	//计算节点高度
	int GetHeight_(AvlTreeNode* root);
	//计算平衡因子
	int GetBalanceFactor_(AvlTreeNode* root);
	//保持树的平衡
	AvlTreeNode* BalanceTree_(AvlTreeNode* root);
	//左旋平衡
	AvlTreeNode* LeftRotate_(AvlTreeNode* root);
	//右旋平衡
	AvlTreeNode* RightRotate_(AvlTreeNode* root);
	//插入节点
	AvlTreeNode* InsertNode_(AvlTreeNode* root, AvlTreeNode node);
	//得到一棵树中的最小键对应的节点
	AvlTreeNode* GetMinNode_(AvlTreeNode* root);
	//删除节点指针指向的节点
	AvlTreeNode* DeleteNode_(AvlTreeNode* node);
	//删除节点
	AvlTreeNode* Delete_(AvlTreeNode* root, string goal_key);
	//释放内存
	void Release_(AvlTreeNode* root);

private:
	//AVL树的根节点
	AvlTreeNode* root_;
	//存储每次被删除的节点值
	string del_val_;
};

#endif // !__AVLTREE__H__
