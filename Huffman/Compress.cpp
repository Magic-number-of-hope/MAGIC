#include "Compress.h"
#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;
int Compress(const char* pFilename) {
	cout << "正在读取文件......" << endl << endl;
	int weight[256] = { 0 };
	FILE* in = fopen(pFilename, "rb");

	int tempch;

	while ((tempch = getc(in)) != EOF)
		weight[tempch]++;

	cout << "文件读取完毕" << endl;
	cout << "原文件字节出现情况为：" << endl;
	cout << "Byte\t" << "Weight\t" << endl;
	for (int i = 0; i < 256; i++)
		printf("0x%02X\t%d\n", i, weight[i]);
	cout << endl << endl;
	fclose(in);

	int n = 256;
	int m = 2 * n - 1;
	HuffmanTree pHT = new HTNode[m + 1];
	CreateHuffmanTree(pHT, weight, n);

	TestHuffmanTree(pHT);
	
	char** pHC = new char* [n + 1];
	for (int i = 1; i <= n; i++)
		pHT[i].weight = weight[i - 1];
	HuffmanCoding(pHT, pHC);
	cout << "Huffman树的编码信息为：" << endl;
	cout << "Byte\tHuffmanCode" << endl;
	TestHuffmanCode(511, pHT, pHC);

	int nSize = 0;
	for (int i = 0; i < 256; i++)
		nSize += weight[i] * strlen(pHC[i]);
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;

	char* pBuffer = NULL;
	pBuffer = new char[nSize];
	memset(pBuffer, 0, (nSize) * sizeof(char));
	Encode(pFilename, pHC, pBuffer, nSize);
	if (!pBuffer)
		return 0;

	HEAD sHead;
	InitHead(pFilename, sHead);
	cout << "原文件大小为：" << sHead.length << "字节" << endl;
	int afterlen = WriteFile(pFilename, sHead, pBuffer, nSize);
	cout << "压缩后文件大小：" << afterlen << "字节" << endl;
	cout << "压缩比例：" << (double)afterlen * 100 / sHead.length << "%" << endl;

	delete pHT; delete[]pHC; delete pBuffer;

	return 1;
}

int InitHead(const char* pFilename, HEAD& sHead) {
	strcpy(sHead.type, "HUF");
	sHead.length = 0;
	for (int i = 0; i < 256; i++)
		sHead.weight[i] = 0;

	FILE* in = fopen(pFilename, "rb");

	int ch;
	while ((ch = fgetc(in)) != EOF) {
		sHead.weight[ch]++;
		sHead.length++;
	}
	fclose(in);
	in = NULL;
	return 1;
}

//文件压缩编码
int Encode(const char* pFilename, const HuffmanCode pHC, char* pBuffer, const int nSize) {
	FILE* in = fopen(pFilename, "rb");
	/*pBuffer = (char*)malloc(nSize * sizeof(char));
	if (!pBuffer)
		cout << "开辟缓存区失败!" << endl;*/

	char cd[256] = { 0 };

	int pos = 0; int ch;
	while ((ch = fgetc(in)) != EOF) {
		strcat(cd, pHC[ch]);
		/*printf("%s ", cd);*/
		while (strlen(cd) >= 8) {
			pBuffer[pos++] = Str2byte(cd);
			for (int i = 0; i < 256 - 8; i++)
				cd[i] = cd[i + 8];
		}
	}
	if (strlen(cd) > 0)
		pBuffer[pos++] = Str2byte(cd);
	fclose(in);

	return 1;
}

char Str2byte(const char* pBinStr) {
	char b = 0x00;
	for (int i = 0; i < 8; i++) {
		b = b << 1;
		if (pBinStr[i] == '1') {
			b = b | 0x01;
		}
	}
	return b;
}

int WriteFile(const char* pFilename, const HEAD sHead, const char* pBuffer, const int nSize) {
	char filename[256] = { 0 };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");

	FILE* out = fopen(filename, "wb");

	fwrite(&sHead, sizeof(HEAD), 1, out);
	fwrite(pBuffer, sizeof(char), nSize, out);

	fclose(out);
	out = NULL;

	cout << "生成压缩文件：" << filename << endl;
	int len = sizeof(HEAD) +  nSize;

	return len;
}