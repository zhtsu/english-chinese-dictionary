#include <iostream>
#include <string>
#include <algorithm>
#include "avl_tree.h"

using namespace std;

//通过字符串末尾字母判断字符串是否为英文单词
bool AvlTree::IsEnglish_(string str) {
	bool res;
	char first_ch = *str.begin();
	if (first_ch >= 'a' && first_ch <= 'z' || first_ch >= 'A' && first_ch <= 'Z') {
		res = true;
	}
	else {
		res = false;
	}

	return res;
}

//递归获取节点的高度
int AvlTree::GetHeight_(AvlTreeNode* root) {
	if (root == NULL) {
		return 0;
	}

	int left_height = GetHeight_(root->left) + 1;
	int right_height = GetHeight_(root->right) + 1;

	return max(left_height, right_height);
}

//根据节点的高度属性计算平衡因子
int AvlTree::GetBalanceFactor_(AvlTreeNode* root) {
	if (root == NULL) {
		return 0;
	}

	return GetHeight_(root->left) - GetHeight_(root->right);
}

//左旋一棵二叉树使其成为平衡树，更新高度后返回新的根节点
AvlTreeNode* AvlTree::LeftRotate_(AvlTreeNode* root) {
	AvlTreeNode* new_root = root->right;
	AvlTreeNode* new_son_right = new_root->left;

	root->right = new_son_right;
	new_root->left = root;

	return new_root;
}

//右旋一棵二叉树使其成为平衡树，更新高度后返回新的根节点
AvlTreeNode* AvlTree::RightRotate_(AvlTreeNode* root) {
	AvlTreeNode* new_root = root->left;
	AvlTreeNode* new_son_left = new_root->right;

	root->left = new_son_left;
	new_root->right = root;

	return new_root;
}

//调整一颗树使其保持平衡，返回调整后树的根节点
AvlTreeNode* AvlTree::BalanceTree_(AvlTreeNode* root) {
	int balance_factor = GetBalanceFactor_(root);
	//左旋的情况
	if (balance_factor < -1 && GetBalanceFactor_(root->right) < 0) {
		return LeftRotate_(root);
	}
	//右旋的情况
	if (balance_factor > 1 && GetBalanceFactor_(root->left) > 0) {
		return RightRotate_(root);
	}
	//先右旋再左旋的情况
	if (balance_factor < -1 && GetBalanceFactor_(root->right) > 0) {
		root->right = RightRotate_(root->right);
		return LeftRotate_(root);
	}
	//先左旋再右旋的情况
	if (balance_factor > 1 && GetBalanceFactor_(root->left) < 0) {
		root->left = LeftRotate_(root->left);
		return RightRotate_(root);
	}

	return root;
}

//向平衡二叉树中插入一个节点并保持平衡，供类构造函数调用
//根据键的大小寻找插入位置。左小右大
//找到位置，递归结束，插入节点并返回平衡后的树的根节点
AvlTreeNode* AvlTree::InsertNode_(AvlTreeNode* root, AvlTreeNode node) {
	if (root == NULL) {
		AvlTreeNode* new_node = new AvlTreeNode(node.key, node.val);
		return new_node;
	}
	if (node.key <= root->key) {
		root->left = InsertNode_(root->left, node);
	}
	else {
		root->right = InsertNode_(root->right, node);
	}

	return BalanceTree_(root);
}

//递归释放树占用的动态内存空间
void AvlTree::Release_(AvlTreeNode* root) {
	if (root == NULL) {
		return ;
	}

	Release_(root->left);
	Release_(root->right);
	delete root;
}

//无参构造
AvlTree::AvlTree() {
	root_ = NULL;
	del_val_ = "NOT_FIND";
}

//构造函数
//初始化成员变量
//并将分别存储键数据和值数据的数组存入 AVL 树中
AvlTree::AvlTree(string key_array[], string val_array[], int length) {
	root_ = NULL;
	del_val_ = "NOT_FIND";
	AvlTreeNode temp_node;
	for (int i = 0; i < length; i++) {
		temp_node.key = key_array[i]; 
		temp_node.val = val_array[i];
		root_ = InsertNode_(root_, temp_node);
	}
}

//析构函数
//通过调用 Release_ 函数释放树占用的动态内存空间
AvlTree::~AvlTree() {
	Release_(root_);
}

//中序遍历输出
void AvlTree::InOrderPrint_(AvlTreeNode* root) {
	if (root == NULL) {
		return ;
	}

	InOrderPrint_(root->left);
	cout << "key: " << root->key << endl;
	cout << "val: " << root->val << endl;
	InOrderPrint_(root->right);
}

//打印树内的所有数据
void AvlTree::PrintData() {
	InOrderPrint_(root_);
}

//键为英文时的查找情况
//递归实现
//供 FindVal 函数和 GetVal 函数调用
string AvlTree::FindByEnglishKey_(AvlTreeNode* root, string goal_key) {
	if (root == NULL) {
		return "NOT_FIND";
	}
	else if (root->key < goal_key) {
		return FindByEnglishKey_(root->right, goal_key);
	}
	else if (root->key > goal_key) {
		return FindByEnglishKey_(root->left, goal_key);
	}
	else {
		return root->val;
	}
}

//查找树中是否存在匹配的键
bool AvlTree::FindVal(string goal_key) {
	if (goal_key.empty()) {
		return false;
	}
	else if (IsEnglish_(goal_key) == false) {
		return false;
	}

	bool res;
	string goal_val = FindByEnglishKey_(root_, goal_key);

	if (goal_val == "NOT_FIND") {
		res = false;
	}
	else {
		res = true;
	}

	return res;
}

//得到键匹配的数据
string AvlTree::GetVal(string goal_key) {
	if (goal_key.empty()) {
		return "NOT_FIND";
	}
	else if (IsEnglish_(goal_key) == false) {
		return "NOT_SUPPORT_OTHER";
	}

	string goal_val = FindByEnglishKey_(root_, goal_key);

	return goal_val;
}

//调用 InsertNode_ 增加一个节点
void AvlTree::Insert(string key, string val) {
	AvlTreeNode node(key, val);
	InsertNode_(root_, node);
}

//不停的递归左树
//找到平衡树中的最小键对应的节点
//返回这个节点指针
AvlTreeNode* AvlTree::GetMinNode_(AvlTreeNode* root) {
	if (root->left == NULL) {
		return root;
	}

	return GetMinNode_(root->left);
}

//删除指定的节点
AvlTreeNode* AvlTree::DeleteNode_(AvlTreeNode* node) {
	del_val_ = node->val;
	//为叶子节点的情况
	if (node->left == NULL && node->right == NULL) {
		delete node;
		return NULL;
	}
	//左子树为空的情况
	else if (node->left == NULL) {
		AvlTreeNode* root = node->right;
		delete node;
		return root;
	} 
	//右子树为空的情况
	else if (node->right == NULL) {
		AvlTreeNode* root = node->left;
		delete node;
		return root;
	}
	//左右子树皆非空
	else {
		AvlTreeNode* right_min_node = GetMinNode_(node->right);
		swap(node->key, right_min_node->key);
		swap(node->val, right_min_node->val);
		node->right = Delete_(node->right, right_min_node->key);
		return node;
	}
}

//删除树中对应键的节点
//供公共接口调用
AvlTreeNode* AvlTree::Delete_(AvlTreeNode* root, string goal_key) {
	if (root == NULL) {
		return NULL;
	} 

	if (root->key > goal_key) {
		root->left = Delete_(root->left, goal_key);
		return root;
	}
	else if (root->key < goal_key) {
		root->right = Delete_(root->right, goal_key);
		return root;
	}
	else {
		root = DeleteNode_(root);
	}

	return BalanceTree_(root);
}

//删除对应键的节点，返回被删除节点的值
string AvlTree::Delete(string goal_key) {
	root_ = Delete_(root_, goal_key);

	return del_val_;
}
