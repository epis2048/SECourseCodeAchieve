#pragma once
#include<iostream>
#include <string>

using namespace std;

int decode(string fileName);
int readFile(FILE* in); //��ȡ�ļ�
void dCreateHuffman(); //�ؽ���������
void dSelectMin(int now, int& x1, int& x2); //ѡȡ��Сֵ
void dReadHuffman(); //��ȡ������������ṹ
void dReadHuffmanCode(); //��ȡ�������������
void dPrintChar(); //��ӡ�ַ�ͳ�Ʊ�
char* decodeFile(FILE* in); //��ѹ�ļ�
void Byte2Char(char* pBinStr, int pBin); //���ֽ�תΪ8��һ����ַ���
void dWriteFile(string fileName, const char* pBuffer); //д���ѹ���ļ�