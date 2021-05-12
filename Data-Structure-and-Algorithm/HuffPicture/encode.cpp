#pragma once
#include <iostream>
#include <stdio.h>
#include "encode.h"
#include "base.h"

using namespace std;



HuffmanTree enTree[512];//哈夫曼树
char* pHC[512];

int enCharWeight[256] = { 0 };//存储每个字符的频度
int enCharLength = 0;//存储字符总数

struct HEAD* shead;

int newSize = 0; //新文件有多长

int encode(string fileName) {
	FILE* file;
	file = fopen(fileName.c_str(), "rb");
	if (file == nullptr) {
		cout << "ERROR" << endl;
		return 0;
	}
	readChar(file);
	printChar();
	createHuffman();
	readHuffman();
	//PreorderTraverse(511);
	doHuffmanCoding();
	//readHuffmanCode();
	char* pBuffer = encodeFile(file);
	if (!pBuffer) {
		cout << "ERROR" << endl;
		return 0;
	}
	char* compressFile = new char[fileName.length() + 4];
	strcpy(compressFile, fileName.c_str());
	strcat(compressFile, ".huf");

	writeFile(compressFile, pBuffer);
	cout << "原文件共：" << enCharLength << "字节" << endl;
	cout << "新文件共：" << newSize << "字节" << endl;
	cout << "压缩率：" << (double)newSize / (double)enCharLength * 100 << "%" << endl;

	// Information output end

	if (pBuffer) {
		delete[] pBuffer;
	}
	fclose(file);
	return 0;
}

void readChar(FILE* file) {
	int ch;
	//循环读取统计频度
	while ((ch = getc(file)) != EOF) {
		enCharWeight[ch] += 1;
		enCharLength += 1;
	}
}

void printChar() {
	cout << "总字符数：" << enCharLength << endl;
	cout << "字符频度：" << endl;
	for (int i = 0; i < 256; i++) {
		cout << i << "\t" << enCharWeight[i] << endl;
	}
}

void createHuffman() {
	//将元节点保存至哈夫曼树组
	int n = 256;
	for (int i = 0; i < n; i++) {
		enTree[i + 1].weight = enCharWeight[i];
		enTree[i + 1].parent = 0;
		enTree[i + 1].lchild = 0;
		enTree[i + 1].rchild = 0;
	}
	int x1, x2; //两个最小元素
	for (int i = n + 1; i <= n * 2 - 1; i++)
	{
		selectMin(i - 1, x1, x2); //选取最小的俩元素
		//创建这俩的父节点
		enTree[i].lchild = x1; 
		enTree[i].rchild = x2;
		enTree[i].weight = enTree[x1].weight + enTree[x2].weight;
		enTree[x1].parent = i;
		enTree[x2].parent = i;
	}
}

void selectMin(int now, int&x1, int&x2) {
	int i;
	long long w1;	// 最小的
	long long w2;	// 第二小的
	w1 = w2 = 0xFFFFFFFFFFF;
	for (i = 1; i <= now; i++) { //遍历目前所有元素
		if (enTree[i].parent == 0) { //如果没有父母（未被选过）
			if (enTree[i].weight < w1) { //如果比最小的还小
				x2 = x1; //最小的变成了第二小的
				x1 = i; //将最小的赋值给x1
				w2 = w1; //最小的变成了第二小的
				w1 = enTree[i].weight; //将最小的赋值给w1
			}
			else if (enTree[i].weight < w2) { //如果比第二小的还小
				x2 = i; //将第二小的赋值给x2
				w2 = enTree[i].weight; //将第二小的赋值给w2
			}
		}
	}
}

void PreorderTraverse(int root) {
	cout << enTree[root].weight << " ";// 访问节点
	if (enTree[root].lchild) { // 左孩子
		PreorderTraverse(enTree[root].lchild);
	}
	if (enTree[root].rchild) { // 右孩子
		PreorderTraverse(enTree[root].rchild);
	}
}

void readHuffman() {
	for (int i = 0; i < 512; i++) {
		cout << i << "\t" << enTree[i].weight << "\t" << enTree[i].parent << "\t" << enTree[i].lchild << "\t" << enTree[i].rchild << endl;
	}
}

void readHuffmanCode() {
	for (int i = 0; i < 256; i++) {
		cout << i << "\t" << pHC[i] << endl;
	}
}

int doHuffmanCoding() {
	// 无栈非递归遍历Huffman树，求Huffman编码
	char cd[256] = { '\0' }; // 记录访问路径
	int cdlen = 0; // 记录当前路径长度
	for (int i = 1; i < 512; i++) {
		enTree[i].weight = 0; // 遍历Huffman树时用作节点的状态标志
	}
	int p = 511;// 根节点
	while (p != 0){
		if (enTree[p].weight == 0) { // 向左
			enTree[p].weight = 1;
			if (enTree[p].lchild != 0) {
				p = enTree[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (enTree[p].rchild == 0) { // 登记叶子节点的字符的编码
				pHC[p] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(pHC[p], cd);// 复制编码
			}
		}
		else if (enTree[p].weight == 1) { // 向右
			enTree[p].weight = 2;
			if (enTree[p].rchild != 0) { // 右孩子为叶子节点
				p = enTree[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else {// 退回父节点，编码长度减1
			enTree[p].weight = 0;
			p = enTree[p].parent;
			--cdlen;
		}
	}
	return 0;
}

char* encodeFile(FILE* in) {
	//计算文件大小
	for (int i = 1; i <= 256; i++) {
		newSize += enCharWeight[i - 1] * strlen(pHC[i]);
	}
	newSize = (newSize % 8) ? newSize / 8 + 1 : newSize / 8;
	//申请缓存
	char* pBuffer = new char[newSize + 1];
	if (!pBuffer) {
		cout << "Failed to build a cashe area" << endl;
		return NULL;
	}
	char cd[256] = { 0 };
	int pos = 0;
	int ch;
	//读取文件
	while ((ch = fgetc(in)) != EOF) {
		strcat(cd, pHC[ch + 1]);
		//8个字符一组，进行编码
		while (strlen(cd) >= 8) {
			pBuffer[pos++] = Str2byte(cd);
			//删掉这8个
			for (int i = 0; i < 256 - 8; i++) {
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd) > 0) { //如果还有剩余的
		pBuffer[pos++] = Str2byte(cd);
	}
	return pBuffer;
}

char Str2byte(const char* str) {
	char b = 0x00;
	for (int i = 0; i < 8; i++) {
		/*
		b = b << 1;	//将b左移，右边留出来
		if (pBinStr[i] == '1') {
			b = b | 0x01; //如果是一则通过或运算将最后一位变成1
		}*/
		b = b << 1; //给b乘2
		if (str[i] - '0') b++; //如果是1则把末尾变1
	}
	return b;
}

int writeFile(const char* pFilename, const char* pBuffer) {
	FILE* out = fopen(pFilename, "wb");
	if (out == NULL) {
		return 1;
	}
	// 建立结构体
	shead = new struct HEAD;
	shead->enCharLength = enCharLength;
	for (int i = 0; i < 256; i++) {
		shead->enCharWeight[i] = enCharWeight[i];
	}
	//写文件
	fwrite(shead, sizeof(HEAD), 1, out);
	fwrite(pBuffer, newSize, 1, out);
	fclose(out);
	return 0;
}