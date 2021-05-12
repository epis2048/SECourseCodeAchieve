#pragma once
#include <iostream>
#include <stdio.h>
#include "decode.h"
#include "base.h"

struct HEAD* dhead;

HuffmanTree deTree[512];//哈夫曼树
char* dpHC[512];
int oldSize = 0;



int decode(string fileName) {
	FILE* file;
	file = fopen(fileName.c_str(), "rb");
	if (file == nullptr) {
		cout << "ERROR" << endl;
		return 0;
	}
	readFile(file);
	//dPrintChar();
	dCreateHuffman();
	//dReadHuffman();

	oldSize = dhead->enCharLength;
	char* pBuffer = decodeFile(file);
	dWriteFile(fileName + ".png", pBuffer);

	fclose(file);
	cout << "解压完成！" << endl;
}

int readFile(FILE* in) {
	
	// 建立结构体
	dhead = new struct HEAD;
	//读文件
	fread(dhead, sizeof(HEAD), 1, in);
	for (int i = 0; i < 256; i++) {
		deTree[i + 1].weight = dhead->enCharWeight[i];
		deTree[i + 1].parent = 0;
		deTree[i + 1].lchild = 0;
		deTree[i + 1].rchild = 0;
	}
	return 0;
}


void dCreateHuffman() {
	//将元节点保存至哈夫曼树组
	int n = 256;
	for (int i = 0; i < n; i++) {
		deTree[i + 1].weight = dhead->enCharWeight[i];
		deTree[i + 1].parent = 0;
		deTree[i + 1].lchild = 0;
		deTree[i + 1].rchild = 0;
	}
	int x1, x2; //两个最小元素
	for (int i = n + 1; i <= n * 2 - 1; i++)
	{
		dSelectMin(i - 1, x1, x2); //选取最小的俩元素
		//创建这俩的父节点
		deTree[i].lchild = x1;
		deTree[i].rchild = x2;
		deTree[i].weight = deTree[x1].weight + deTree[x2].weight;
		deTree[x1].parent = i;
		deTree[x2].parent = i;
	}
}

void dSelectMin(int now, int& x1, int& x2) {
	int i;
	long long w1;	// 最小的
	long long w2;	// 第二小的
	w1 = w2 = 0xFFFFFFFFFFF;
	for (i = 1; i <= now; i++) { //遍历目前所有元素
		if (deTree[i].parent == 0) { //如果没有父母（未被选过）
			if (deTree[i].weight < w1) { //如果比最小的还小
				x2 = x1; //最小的变成了第二小的
				x1 = i; //将最小的赋值给x1
				w2 = w1; //最小的变成了第二小的
				w1 = deTree[i].weight; //将最小的赋值给w1
			}
			else if (deTree[i].weight < w2) { //如果比第二小的还小
				x2 = i; //将第二小的赋值给x2
				w2 = deTree[i].weight; //将第二小的赋值给w2
			}
		}
	}
}

void dReadHuffman() {
	for (int i = 0; i < 512; i++) {
		cout << i << "\t" << deTree[i].weight << "\t" << deTree[i].parent << "\t" << deTree[i].lchild << "\t" << deTree[i].rchild << endl;
	}
}

void dReadHuffmanCode() {
	for (int i = 0; i < 256; i++) {
		cout << i << "\t" << dpHC[i] << endl;
	}
}

void dPrintChar() {
	cout << "总字符数：" << dhead->enCharLength << endl;
	cout << "字符频度：" << endl;
	for (int i = 0; i < 256; i++) {
		cout << i << "\t" << dhead->enCharWeight[i] << endl;
	}
}


char* decodeFile(FILE* in) {
	//申请缓存
	char* pBuffer = new char[oldSize + 1];
	if (!pBuffer) {
		cout << "ERROR" << endl;
		return NULL;
	}
	char cd[256 * 2] = { 0 };
	char mid[256];
	int pos = 0;
	int ch;
	int byte;
	fseek(in, sizeof(HEAD), 0);
	//读文件，使用编码解压
	while ((ch = fgetc(in)) != EOF) {
		Byte2Char(mid, ch);
		strcat(cd, mid);
		while (strlen(cd) >= 256){
			int move = 0, root = 256 * 2 - 1;
			while (deTree[root].lchild != 0 && deTree[root].rchild != 0) {
				if (cd[move] == '0') {
					root = deTree[root].lchild;
				}
				else {
					root = deTree[root].rchild;
				}
				move++;
			}
			byte = root - 1;
			//向左移动8个字符
			pBuffer[pos++] = byte;
			for (int i = 0; i < 256 * 2 - move; i++) {
				cd[i] = cd[i + move];
			}
		}
	}
	if (strlen(cd) > 0) {
		int move = 0, root = 256 * 2 - 1;
		while (deTree[root].lchild != 0 && deTree[root].rchild != 0) {
			if (cd[move] == '0') {
				root = deTree[root].lchild;
			}
			else {
				root = deTree[root].rchild;
			}
			move++;
		}
		byte = root - 1;
		//左移8个字符
		pBuffer[pos++] = byte;
	}
	pBuffer[pos] = '\0';
	fclose(in);
	return pBuffer;
}

void Byte2Char(char* pBinStr, int pBin) {
	for (int i = 0; i < 8; i++) {
		if (pBin % 2 == 1) {
			pBinStr[7 - i] = '1';
		}
		else
		{
			pBinStr[7 - i] = '0';
		}
		pBin = pBin >> 1;	// move right 1
	}
	pBinStr[8] = '\0';
}

void dWriteFile(string fileName, const char* pBuffer) {
	FILE* out = fopen(fileName.c_str(), "wb");
	if (out == NULL) {
		cout << "ERROR" << endl;
		return ;
	}

	fwrite(pBuffer, oldSize, 1, out);
	fclose(out);
}