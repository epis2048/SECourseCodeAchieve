#pragma once
struct HEAD {
	int enCharWeight[256] = { 0 };
	int enCharLength = 0;
};

// Huffman���ڵ�
struct HTNode {
	int weight;// Ȩֵ
	int parent;// ���ڵ�
	int lchild;// ����
	int rchild;// �Һ���
};


// Huffman��
typedef HTNode HuffmanTree;// ��̬��������洢Huffman��