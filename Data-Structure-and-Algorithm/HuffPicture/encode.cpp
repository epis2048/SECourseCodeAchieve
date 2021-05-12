#pragma once
#include <iostream>
#include <stdio.h>
#include "encode.h"
#include "base.h"

using namespace std;



HuffmanTree enTree[512];//��������
char* pHC[512];

int enCharWeight[256] = { 0 };//�洢ÿ���ַ���Ƶ��
int enCharLength = 0;//�洢�ַ�����

struct HEAD* shead;

int newSize = 0; //���ļ��ж೤

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
	cout << "ԭ�ļ�����" << enCharLength << "�ֽ�" << endl;
	cout << "���ļ�����" << newSize << "�ֽ�" << endl;
	cout << "ѹ���ʣ�" << (double)newSize / (double)enCharLength * 100 << "%" << endl;

	// Information output end

	if (pBuffer) {
		delete[] pBuffer;
	}
	fclose(file);
	return 0;
}

void readChar(FILE* file) {
	int ch;
	//ѭ����ȡͳ��Ƶ��
	while ((ch = getc(file)) != EOF) {
		enCharWeight[ch] += 1;
		enCharLength += 1;
	}
}

void printChar() {
	cout << "���ַ�����" << enCharLength << endl;
	cout << "�ַ�Ƶ�ȣ�" << endl;
	for (int i = 0; i < 256; i++) {
		cout << i << "\t" << enCharWeight[i] << endl;
	}
}

void createHuffman() {
	//��Ԫ�ڵ㱣��������������
	int n = 256;
	for (int i = 0; i < n; i++) {
		enTree[i + 1].weight = enCharWeight[i];
		enTree[i + 1].parent = 0;
		enTree[i + 1].lchild = 0;
		enTree[i + 1].rchild = 0;
	}
	int x1, x2; //������СԪ��
	for (int i = n + 1; i <= n * 2 - 1; i++)
	{
		selectMin(i - 1, x1, x2); //ѡȡ��С����Ԫ��
		//���������ĸ��ڵ�
		enTree[i].lchild = x1; 
		enTree[i].rchild = x2;
		enTree[i].weight = enTree[x1].weight + enTree[x2].weight;
		enTree[x1].parent = i;
		enTree[x2].parent = i;
	}
}

void selectMin(int now, int&x1, int&x2) {
	int i;
	long long w1;	// ��С��
	long long w2;	// �ڶ�С��
	w1 = w2 = 0xFFFFFFFFFFF;
	for (i = 1; i <= now; i++) { //����Ŀǰ����Ԫ��
		if (enTree[i].parent == 0) { //���û�и�ĸ��δ��ѡ����
			if (enTree[i].weight < w1) { //�������С�Ļ�С
				x2 = x1; //��С�ı���˵ڶ�С��
				x1 = i; //����С�ĸ�ֵ��x1
				w2 = w1; //��С�ı���˵ڶ�С��
				w1 = enTree[i].weight; //����С�ĸ�ֵ��w1
			}
			else if (enTree[i].weight < w2) { //����ȵڶ�С�Ļ�С
				x2 = i; //���ڶ�С�ĸ�ֵ��x2
				w2 = enTree[i].weight; //���ڶ�С�ĸ�ֵ��w2
			}
		}
	}
}

void PreorderTraverse(int root) {
	cout << enTree[root].weight << " ";// ���ʽڵ�
	if (enTree[root].lchild) { // ����
		PreorderTraverse(enTree[root].lchild);
	}
	if (enTree[root].rchild) { // �Һ���
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
	// ��ջ�ǵݹ����Huffman������Huffman����
	char cd[256] = { '\0' }; // ��¼����·��
	int cdlen = 0; // ��¼��ǰ·������
	for (int i = 1; i < 512; i++) {
		enTree[i].weight = 0; // ����Huffman��ʱ�����ڵ��״̬��־
	}
	int p = 511;// ���ڵ�
	while (p != 0){
		if (enTree[p].weight == 0) { // ����
			enTree[p].weight = 1;
			if (enTree[p].lchild != 0) {
				p = enTree[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (enTree[p].rchild == 0) { // �Ǽ�Ҷ�ӽڵ���ַ��ı���
				pHC[p] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(pHC[p], cd);// ���Ʊ���
			}
		}
		else if (enTree[p].weight == 1) { // ����
			enTree[p].weight = 2;
			if (enTree[p].rchild != 0) { // �Һ���ΪҶ�ӽڵ�
				p = enTree[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else {// �˻ظ��ڵ㣬���볤�ȼ�1
			enTree[p].weight = 0;
			p = enTree[p].parent;
			--cdlen;
		}
	}
	return 0;
}

char* encodeFile(FILE* in) {
	//�����ļ���С
	for (int i = 1; i <= 256; i++) {
		newSize += enCharWeight[i - 1] * strlen(pHC[i]);
	}
	newSize = (newSize % 8) ? newSize / 8 + 1 : newSize / 8;
	//���뻺��
	char* pBuffer = new char[newSize + 1];
	if (!pBuffer) {
		cout << "Failed to build a cashe area" << endl;
		return NULL;
	}
	char cd[256] = { 0 };
	int pos = 0;
	int ch;
	//��ȡ�ļ�
	while ((ch = fgetc(in)) != EOF) {
		strcat(cd, pHC[ch + 1]);
		//8���ַ�һ�飬���б���
		while (strlen(cd) >= 8) {
			pBuffer[pos++] = Str2byte(cd);
			//ɾ����8��
			for (int i = 0; i < 256 - 8; i++) {
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd) > 0) { //�������ʣ���
		pBuffer[pos++] = Str2byte(cd);
	}
	return pBuffer;
}

char Str2byte(const char* str) {
	char b = 0x00;
	for (int i = 0; i < 8; i++) {
		/*
		b = b << 1;	//��b���ƣ��ұ�������
		if (pBinStr[i] == '1') {
			b = b | 0x01; //�����һ��ͨ�������㽫���һλ���1
		}*/
		b = b << 1; //��b��2
		if (str[i] - '0') b++; //�����1���ĩβ��1
	}
	return b;
}

int writeFile(const char* pFilename, const char* pBuffer) {
	FILE* out = fopen(pFilename, "wb");
	if (out == NULL) {
		return 1;
	}
	// �����ṹ��
	shead = new struct HEAD;
	shead->enCharLength = enCharLength;
	for (int i = 0; i < 256; i++) {
		shead->enCharWeight[i] = enCharWeight[i];
	}
	//д�ļ�
	fwrite(shead, sizeof(HEAD), 1, out);
	fwrite(pBuffer, newSize, 1, out);
	fclose(out);
	return 0;
}