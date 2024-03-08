#pragma once
//Huffman ���ڵ�
typedef struct HTNode
{
	int weight;
	int parent;
	int lchild;
	int rchild;
}*HuffmanTree,HTNode;
typedef char** HuffmanCode;
//����Ȩֵ��С���
int Select(HuffmanTree pHT, int nSize);
//����Huffman��
int CreateHuffmanTree(HuffmanTree pHT, int weight[], int size);

int HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC);

int TestHuffmanTree(HuffmanTree pHT);

void TestHuffmanCode(int root, HuffmanTree pHT, HuffmanCode pHC);