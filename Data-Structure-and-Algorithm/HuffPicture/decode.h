#pragma once
#include<iostream>
#include <string>

using namespace std;

int decode(string fileName);
int readFile(FILE* in); //读取文件
void dCreateHuffman(); //重建哈夫曼树
void dSelectMin(int now, int& x1, int& x2); //选取最小值
void dReadHuffman(); //读取哈夫曼树数组结构
void dReadHuffmanCode(); //读取哈夫曼树编码表
void dPrintChar(); //打印字符统计表
char* decodeFile(FILE* in); //解压文件
void Byte2Char(char* pBinStr, int pBin); //将字节转为8个一组的字符串
void dWriteFile(string fileName, const char* pBuffer); //写入解压的文件