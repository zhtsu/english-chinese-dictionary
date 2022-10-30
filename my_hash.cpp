#include <iostream>
#include <algorithm>
#include <string>
#include "my_hash.h"

using namespace std;

//通过字符串首字母判断字符串是否为英文单词
bool MyHash::IsEnglish_(string str) {
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

//根据单词中不同的英文字母的个数计算单词在表中对应的桶号
int MyHash::GetEnglishKeyIn_(string str) {
	//去重
	for (int i = 0; i < str.size() - 1; i++) {
		for (int j = i  + 1; j < str.size(); j++) {
			if (str[j] == str[i]) {
				str.erase(j, 1);
				j--;
			}
		}
	}

	return str.size();
}

//返回表内数据的总数量
int MyHash::get_length() {
	return length_;
}

//根据键值，向哈希表中插入一个节点
void MyHash::Insert(string english, string chinese) {
	int in = GetEnglishKeyIn_(english) % kMaxSize;

	MyHashNode* new_node = new MyHashNode(english, chinese);
	MyHashNode* p = buckets_[in];
	while (p->next != NULL && p->next->key < new_node->key) {
		p = p->next;
	}
	new_node->next = p->next;
	p->next = new_node;
}

//无参构造
MyHash::MyHash() {
	length_ = 0;
	for (int i = 0; i < kMaxSize; i++) {
		buckets_[i] = new MyHashNode;
	}
}

//构造函数
//给链表头指针数组（桶）赋初值
//将分别存储键和值的数组存储到链表中
MyHash::MyHash(string key_array[], string val_array[], int length) {
	length_ = length;
	for (int i = 0; i < kMaxSize; i++) {
		buckets_[i] = new MyHashNode;
	}

	for (int i = 0; i < length; i++) {
		Insert(key_array[i], val_array[i]);
	}
}

//析构函数
//释放哈希表的链表占用的动态内存空间
MyHash::~MyHash() {
	for (int i = 0; i < kMaxSize; i++) {
		MyHashNode* new_head = NULL;
		for (MyHashNode* p = buckets_[i]; p != NULL; p = new_head) {
			new_head = p->next;
			delete p;
		}
	}
}

//打印出哈希表内存储的数据
void MyHash::PrintList() {
	for (int i = 0; i < kMaxSize; i++) {
		cout << i << endl;
		for (MyHashNode* p = buckets_[i]->next; p != NULL; p = p->next) {
			cout << "key:" << p->key << endl;
			cout << "val:" << p->val << endl;
		}
	}
}

//查找表中是否存在匹配的键
bool MyHash::FindVal(string goal_key) {
	if (goal_key.empty()) {
		return false;
	}
	else if (IsEnglish_(goal_key) == false) {
		return false;
	}

	bool is_find = false;

	int in = GetEnglishKeyIn_(goal_key) % kMaxSize;
	MyHashNode* p = buckets_[in]->next;
	while (p != NULL && p->key != goal_key) {
		p = p->next;
	}

	if (p != NULL) {
		is_find = true;
	}

	return is_find;
}

//从表中返回对应键 key 的值
//若未在表中找到对应的 key
//返回一个“NOT_FIND”字符串
//若查找的单词不为英文，则返回一个 "NOT_SUPPORT_OTHER" 字符串
string MyHash::GetVal(string goal_key) {
	if (goal_key.empty()) {
		return "NOT_FIND";
	}
	else if (IsEnglish_(goal_key) == false) {
		return "NOT_SUPPORT_OTHER";
	}

	string res = "NOT_FIND";
	int in = GetEnglishKeyIn_(goal_key) % kMaxSize;
	MyHashNode* p = buckets_[in]->next;
	while (p != NULL && p->key != goal_key) {
		p = p->next;
	}

	if (p != NULL) {
		res = p->val;
	}

	return res;
}

//根据键删除表中对应的节点
//返回被删除节点的值
//若节点不存在表中，返回一个 "NOT_FIND" 字符串
string MyHash::Delete(string key) {
	string del_val = "NOT_FIND";

	int in = GetEnglishKeyIn_(key) % kMaxSize;
	MyHashNode* p = buckets_[in]->next;
	while (p != NULL && p->next != NULL && p->next->key != key) {
		p = p->next;
	}
	if (p != NULL && p->next != NULL) {
		MyHashNode* del_node = p->next;
		del_val = del_node->val;
		p->next = p->next->next;
		delete del_node;
	}

	return del_val;
}

//将表内指定数量的数据拷贝到 2 个数组中
//拷贝后会对数据进行升序排序
void MyHash::CopyDataTo(string key_array[], string val_array[], int length) {
	int pos = 0;

	for (int i = 0; i < kMaxSize; i++) {
		MyHashNode* p = buckets_[i]->next;
		while (p != NULL) {
			key_array[pos] = p->key;
			val_array[pos] = p->val;
			pos++;
			p = p->next;
		}
	}

	//排序
	sort(key_array, key_array + length);
	sort(val_array, val_array + length);
}