#include<iostream>
#include<stdlib.h>
#include"Decompress.h"
#include"Compress.h"
#include"Huffman.h"
using namespace std;
int main() {
	//输入文件
	cout << "==========Huffman 文件（解）压缩 ==========" << endl;
	
	cout << "1.压缩" << endl << "2.解压缩" << endl << "请输入要执行的操作序号：";
	//读取文件
	int choice;
	cin >> choice;

	if (choice == 1) {
		cout << "请输入文件名：";
		char filename[256];
		cin >> filename;
		Compress(filename);
	}
	else if (choice == 2) {
		cout << "请输入文件名：";
		char filename[256];
		cin >> filename;
		Decompress(filename);
	}
	else
		cout << "错误！" << endl;
	return 0;
}