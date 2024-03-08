#pragma once
//Huffman 树节点
typedef struct HTNode
{
	int weight;
	int parent;
	int lchild;
	int rchild;
}*HuffmanTree,HTNode;
typedef char** HuffmanCode;
//查找权值最小结点
int Select(HuffmanTree pHT, int nSize);
//生成Huffman树
int CreateHuffmanTree(HuffmanTree pHT, int weight[], int size);

int HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC);

int TestHuffmanTree(HuffmanTree pHT);

void TestHuffmanCode(int root, HuffmanTree pHT, HuffmanCode pHC);