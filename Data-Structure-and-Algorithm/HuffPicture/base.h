#pragma once
struct HEAD {
	int enCharWeight[256] = { 0 };
	int enCharLength = 0;
};

// Huffman树节点
struct HTNode {
	int weight;// 权值
	int parent;// 父节点
	int lchild;// 左孩子
	int rchild;// 右孩子
};


// Huffman树
typedef HTNode HuffmanTree;// 动态分配数组存储Huffman树