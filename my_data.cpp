#include <iostream>
#include <string>
#include "my_data.h"

using namespace std;

//无参构造
//从文件读取数据构造所有哈希表和树
//并存放到类的数据中
MyData::MyData() {
	string key_array[1000];
	string val_array[1000];
	string file_name;
	int length = 0;
	MyFile file;
	
	char ch = 'a';
	for (int i = 0; i < 26; i++) {
		file_name = "TXT\\";
		file_name += ch;
		file_name += "_.txt";
		
		file.set_file_name(file_name);
		length = file.ReadData(); 
		file.CopyEnglishDataTo(key_array, length);
		file.CopyChineseDataTo(val_array, length); 
		avl_tree_[i] = new AvlTree(key_array, val_array, length);
		my_hash_[i] = new MyHash(key_array, val_array, length);
		ch++;
	}
}

//析构函数
//释放数组中各个类占用的动态内存空间
MyData::~MyData() {
	for (int i = 0; i < 26; i++) {
		delete avl_tree_[i];
		delete my_hash_[i];
	}
}

//调用哈希表的查找
string MyData::MyHashSearch(string english) {
	if (english.empty()) {
		return "NOT_FIND";
	}
	
	char first_ch = *english.begin();
	if (first_ch >= 'A' && first_ch <= 'Z') {
		first_ch += 32;
	}

	int in = first_ch - 97;

	return my_hash_[in]->GetVal(english);
}

//调用AVl树的查找
string MyData::AvlTreeSearch(string english) {
	if (english.empty()) {
		return "NOT_FIND";
	}

	char first_ch = *english.begin();
	if (first_ch >= 'A' && first_ch <= 'Z') {
		first_ch += 32;
	}

	int in = first_ch - 97;

	return avl_tree_[in]->GetVal(english);
}

//增加一个单词数据
string MyData::AddData(string english, string chinese) {
	if (english.empty()) {
		return "EMPTY";
	}

	char first_ch = *english.begin();
	if (first_ch >= 'A' && first_ch <= 'Z') {
		first_ch += 32;
	}

	int in = first_ch - 97;
	my_hash_[in]->Insert(english, chinese);
	avl_tree_[in]->Insert(english, chinese);

	return english;
}

//删除一个单词数据
string MyData::DeleteData(string english) {
	if (english.empty()) {
		return "EMPTY";
	}

	char first_ch = *english.begin();
	if (first_ch >= 'A' && first_ch <= 'Z') {
		first_ch += 32;
	}

	int in = first_ch - 97;
	string del_chinese = my_hash_[in]->Delete(english);
	avl_tree_[in]->Delete(english);

	return del_chinese;
}
