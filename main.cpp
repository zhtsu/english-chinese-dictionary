#include <iostream>
#include <string>
#include "my_data.h"

using namespace std;

int main() {
	MyData tool;

	cout << "****************************************" << endl;
	cout << "english-chinese-dictionary --version 1.0" << endl;
	cout << "to provide you with translation services" << endl;
	cout << "you can get help by 'help'" << endl;
	cout << "****************************************" << endl;
	
	bool is_open = true;
	while (is_open) {
		cout << ">";

		string key_str, key, str;
		getline(cin, key_str);
		if (key_str.find(" ") != key_str.npos) {
			int pos = key_str.find_first_of(" ") + 1;
			key = key_str.substr(0, pos - 1);
			str = key_str.substr(pos);
		}

		if (key_str.empty()) {

		}
		else if (key_str == "help") {
			cout << "可用的命令：" << endl;
			cout << "\tfind\t查找一个单词的汉语翻译" << endl;
			cout << "\tadd\t增加一个单词数据" << endl;
			cout << "\tdelete\t删除一个单词的数据" << endl;
			cout << "\tquit\t退出程序" << endl;
			cout << "\thelp\t获取帮助" << endl;
		}
		else if (key_str == "quit") {
			is_open = false;
			cout << "Bye ! Have a good day." << endl;
		}
		else if (key_str == "add" || key_str == "a") {
			string english, chinese;
			cout << "english:";
			cin >> english;
			cout << "chinese:";
			cin >> chinese;
			if (tool.AddData(english, chinese) == "EMPTY") {
				cout << "错误：插入空数据" << endl;
			}
			else {
				cout << endl;
			}
		}
		else if (key == "find" || key == "f") {
			cout << tool.MyHashSearch(str) << endl;
		}
		else if (key == "delete" || key == "d") {
			string res = tool.DeleteData(str);
			if (res == "EMPTY") {
				cout << "错误：删除空数据" << endl;
			}
			else if (res == "NOT_FIND"){
				cout << "错误：数据不存在" << endl;
			}
			else {
				cout << endl;
			}
		}
		else {
			cout << "错误：无效命令。" << endl;
			cout << "请使用 help 查看帮助信息。" << endl;
		}
	}

	return 0;
}
