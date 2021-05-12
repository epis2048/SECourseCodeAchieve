#pragma once
#include <iostream>
#include <stdio.h>
#include "decode.h"
#include "base.h"

struct HEAD* dhead;

HuffmanTree deTree[512];//��������
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
	cout << "��ѹ��ɣ�" << endl;
}

int readFile(FILE* in) {
	
	// �����ṹ��
	dhead = new struct HEAD;
	//���ļ�
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
	//��Ԫ�ڵ㱣��������������
	int n = 256;
	for (int i = 0; i < n; i++) {
		deTree[i + 1].weight = dhead->enCharWeight[i];
		deTree[i + 1].parent = 0;
		deTree[i + 1].lchild = 0;
		deTree[i + 1].rchild = 0;
	}
	int x1, x2; //������СԪ��
	for (int i = n + 1; i <= n * 2 - 1; i++)
	{
		dSelectMin(i - 1, x1, x2); //ѡȡ��С����Ԫ��
		//���������ĸ��ڵ�
		deTree[i].lchild = x1;
		deTree[i].rchild = x2;
		deTree[i].weight = deTree[x1].weight + deTree[x2].weight;
		deTree[x1].parent = i;
		deTree[x2].parent = i;
	}
}

void dSelectMin(int now, int& x1, int& x2) {
	int i;
	long long w1;	// ��С��
	long long w2;	// �ڶ�С��
	w1 = w2 = 0xFFFFFFFFFFF;
	for (i = 1; i <= now; i++) { //����Ŀǰ����Ԫ��
		if (deTree[i].parent == 0) { //���û�и�ĸ��δ��ѡ����
			if (deTree[i].weight < w1) { //�������С�Ļ�С
				x2 = x1; //��С�ı���˵ڶ�С��
				x1 = i; //����С�ĸ�ֵ��x1
				w2 = w1; //��С�ı���˵ڶ�С��
				w1 = deTree[i].weight; //����С�ĸ�ֵ��w1
			}
			else if (deTree[i].weight < w2) { //����ȵڶ�С�Ļ�С
				x2 = i; //���ڶ�С�ĸ�ֵ��x2
				w2 = deTree[i].weight; //���ڶ�С�ĸ�ֵ��w2
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
	cout << "���ַ�����" << dhead->enCharLength << endl;
	cout << "�ַ�Ƶ�ȣ�" << endl;
	for (int i = 0; i < 256; i++) {
		cout << i << "\t" << dhead->enCharWeight[i] << endl;
	}
}


char* decodeFile(FILE* in) {
	//���뻺��
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
	//���ļ���ʹ�ñ����ѹ
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
			//�����ƶ�8���ַ�
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
		//����8���ַ�
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