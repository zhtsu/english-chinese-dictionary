#pragma once
#ifndef  __MYFILE__H__
#define __MYFILE__H__

#include <iostream>

using namespace std;

//读取到的数据的最大数量
const int kDataMaxSize = 1000;
//接收文件流的缓冲区大小
const int kBuffLen = 100;

//文件操作类，实现程序对文件的读写操作
class MyFile {
public:
	MyFile();
	MyFile(string file_name);

public:
	//设置操作的文件名
	void set_file_name(string file_name);
	//从文件读取数据
	int ReadData();
	//向文件写入数据
	int WriteDataOf(string array[], int length);
	//拷贝单词数据到指定数组
	void CopyEnglishDataTo(string array[], int length);
	//拷贝汉语数据到指定数组
	void CopyChineseDataTo(string array[], int length);

private:
	//提取单词数据
	string ExtractEnglish_(string str);      
	//提取汉语数据
	string ExtractChinese_(string str);     

private:
	//存储文件名
	string file_name_;
	//记录已读取的数据长度
	int length_;          
	//存储读取到的单词数据
	string english_[kDataMaxSize];
	//存储读取到的汉语数据
	string chinese_[kDataMaxSize];
};

#endif // !__MYFILE__H__
