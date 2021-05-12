#pragma once
#include<iostream>
#include <string>

using namespace std;

int encode(string fileName);
void readChar(FILE* file); //读取并保存字符统计表
void printChar(); //打印字符统计表
void createHuffman(); //创建哈夫曼树
void selectMin(int now, int& x1, int& x2); //获取最小的两个元素
void readHuffman(); //读取哈夫曼树数组结构
void PreorderTraverse(int root); //前序遍历哈夫曼树
int doHuffmanCoding(); //进行哈夫曼编码
void readHuffmanCode(); //读取哈夫曼编码表
char* encodeFile(FILE* in); //对文件编码
char Str2byte(const char* pBinStr); //将8个字符一组的字符串转为字节
int writeFile(const char* pFilename, const char* pBuffer); //写入文件