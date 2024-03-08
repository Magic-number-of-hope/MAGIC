#include "Huffman.h"
#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;
int Select(HuffmanTree pHT, int nSize) {
	int minValue = 0x7FFFFFFF;
	int min = 0;

	for (int i = 1; i <= nSize; i++) {
		if (pHT[i].parent == 0 && pHT[i].weight < minValue){
			minValue = pHT[i].weight;
			min = i;
		}
	}
	return min;
}
int CreateHuffmanTree(HuffmanTree pHT, int weight[], int size) {
	int m = 2 * size - 1;

	for (int i = 1; i <= size; i++) {
		pHT[i].weight = weight[i - 1];
		pHT[i].lchild = 0;
		pHT[i].rchild = 0;
		pHT[i].parent = 0;
	}
	for (int i = size + 1; i <= m; i++) {
		pHT[i].parent = 0;
		pHT[i].lchild = 0;
		pHT[i].rchild = 0;
		pHT[i].weight = 0;
	}

	for (int i = size + 1; i <= m; i++) {
		int min;
		min = Select(pHT, i - 1);
		pHT[min].parent = i;
		pHT[i].lchild = min;
		pHT[i].weight += pHT[min].weight;
		min = Select(pHT, i - 1);
		pHT[min].parent = i;
		pHT[i].rchild = min;
		pHT[i].weight += pHT[min].weight;
	}
	return 1;
}
int HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC) {
	char cd[256] = { '\0' };//记录访问路径
	int cdlen = 0;//记录当前路径长度
	//将用不上的权重选项置零，用于记录已走路径
	for (int i = 1; i < 512; i++)
		pHT[i].weight = 0;
	//从根节点出发
	int p = 511;
	while (p != 0) {
		//向左子树移动并记录
		if (pHT[p].weight == 0) {
			pHT[p].weight = 1;
			if (pHT[p].lchild != 0) {
				p = pHT[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (pHT[p].rchild == 0) {
				pHC[p-1] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(pHC[p-1], cd);
			}
		}
		//向右子树移动并记录
		else if (pHT[p].weight == 1) {
			pHT[p].weight = 2;
			if (pHT[p].rchild != 0) {
				p = pHT[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		//向双亲结点移动并记录
		else {
			pHT[p].weight = 0;
			p = pHT[p].parent;
			cdlen--;
		}
	}
	return 1;
}
int TestHuffmanTree(HuffmanTree pHT) {
	cout << "Huffman树的每个结点信息为：" << endl;
	cout << "Byte\t\tWeight\tParent\tLchild\tRchild" << endl;
	for (int i = 1; i < 512; i++) {
		if (i <= 99)
			cout << "pHT[" << i << "]\t\t" << pHT[i].weight << "\t" << pHT[i].parent << "\t" << pHT[i].lchild << "\t" << pHT[i].rchild << endl;
		else
			cout<< "pHT[" << i << "]\t" << pHT[i].weight << "\t" << pHT[i].parent << "\t" << pHT[i].lchild << "\t" << pHT[i].rchild << endl;
	}
	cout << endl;
	return 1;
}

void TestHuffmanCode(int root, HuffmanTree pHT, HuffmanCode pHC) {
	if (pHT[root].lchild == 0 && pHT[root].rchild == 0)
		printf("0x%02X\t%s\n", root - 1, pHC[root - 1]);
	if (pHT[root].lchild)
		TestHuffmanCode(pHT[root].lchild, pHT, pHC);
	if (pHT[root].rchild)
		TestHuffmanCode(pHT[root].rchild, pHT, pHC);
}