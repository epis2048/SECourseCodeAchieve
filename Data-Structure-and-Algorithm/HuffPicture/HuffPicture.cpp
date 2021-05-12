#include <iostream>
#include "encode.h"
#include "decode.h"
constexpr auto filename = "test.txt";
constexpr auto filenameRec = "test.txt.huf";
using namespace std;


int main() {
	int x;
	char y[50];
	while (1) {
		system("cls");
		cout << "请选择1. 压缩 2.解压缩 0.退出" << endl;
		cin >> x;
		if (x == 1) {
			cout << "请输入文件名：";
			cin >> y;
			encode(filename);
		}
		else if (x == 2) {
			cout << "请输入文件名：";
			cin >> y;
			decode(filenameRec);
		}
		else break;
		system("pause");
	}
	return 0;
}