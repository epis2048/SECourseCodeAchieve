#pragma once
#include<iostream>
#include <string>

using namespace std;

int encode(string fileName);
void readChar(FILE* file); //��ȡ�������ַ�ͳ�Ʊ�
void printChar(); //��ӡ�ַ�ͳ�Ʊ�
void createHuffman(); //������������
void selectMin(int now, int& x1, int& x2); //��ȡ��С������Ԫ��
void readHuffman(); //��ȡ������������ṹ
void PreorderTraverse(int root); //ǰ�������������
int doHuffmanCoding(); //���й���������
void readHuffmanCode(); //��ȡ�����������
char* encodeFile(FILE* in); //���ļ�����
char Str2byte(const char* pBinStr); //��8���ַ�һ����ַ���תΪ�ֽ�
int writeFile(const char* pFilename, const char* pBuffer); //д���ļ�