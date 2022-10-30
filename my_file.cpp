#include <iostream>
#include <fstream>
#include <string>
#include "my_file.h"

using namespace std;

//无参构造
MyFile::MyFile() {
	file_name_ = "";
	length_ = 0;
}

//构造函数
//指定操作的文件名，将读取的数据长度赋值为 0
MyFile::MyFile(string file_name) {
	file_name_ = file_name;
	length_ = 0;
}

//设置文件名，并重置记录的数据数量
//接下来的文件流都将导入重新设置的文件
void MyFile::set_file_name(string file_name) {
	file_name_ = file_name;
	length_ = 0;
}

//从字符串中提取出英文单词
string MyFile::ExtractEnglish_(string str) {
	int pos = str.find_first_of(" ");
	string goal = str.substr(0, pos);

	return goal;
}

//从字符串中提取出汉语翻译
string MyFile::ExtractChinese_(string str) {
	int pos = str.find_first_of(" ") + 3;
	string goal = str.substr(pos);

	return goal;
}

//将类存储的单词数据拷贝给一个数组
void MyFile::CopyEnglishDataTo(string array[], int length) {
	for (int i = 0; i < length; i++) {
		array[i] = english_[i];
	}
}

//将类存储的汉语数据拷贝给一个数组
void MyFile::CopyChineseDataTo(string array[], int length) {
	for (int i = 0; i < length; i++) {
		array[i] = chinese_[i];
	}
}

//以二进制从文件中按行读取数据，并返回读取到的数据长度
int MyFile::ReadData() {
	ifstream infile(file_name_.c_str(), ios::in|ios::binary);
	
	if (!infile) {
		cerr << "open error!" << endl;
		abort();
	} 

	for (int i = 0; i < kDataMaxSize && infile.peek() != EOF; i++) {
		char buff[kBuffLen];
		//读入一行数据
		infile.getline(buff, kBuffLen);
		//将读入的char型数组转为 string 类型
		string tempStr(buff);
		//存储单词数据
		english_[i] = ExtractEnglish_(tempStr);
		//存储汉语数据
		chinese_[i] = ExtractChinese_(tempStr);
		length_++;
	}

	infile.close();

	return length_;
}

//将一个数组中指定数量的数据写入文件，返回写入的数据的数量
//若文件不为空，会先清空文件内容
int MyFile::WriteDataOf(string array[], int length) {
	ofstream outfile(file_name_.c_str(), ios::out|ios::binary);

	if (!outfile) {
		cerr << "open error!" << endl;
		abort();
	}
	
	int count = 0;
	char ch = '\n';
	for (int i = 0; i < length; i++) {
		//写入数据
		outfile.write(array[i].c_str(), sizeof(array[i]));
		//换行
		outfile.write("\n", sizeof(ch));
		count++;
	}

	outfile.close();

	return count;
}
