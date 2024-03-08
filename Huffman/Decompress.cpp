#include "Decompress.h"

using namespace std;

int Decompress(const char* filename) {
	ifstream file(filename);

	if (file.is_open()) {
		HEAD sHead;

		file.read(reinterpret_cast<char*>(&sHead), sizeof(HEAD));

		char ch;
		char* pBuffer = new char[sHead.length];
		memset(pBuffer, 0, (sHead.length) * sizeof(char));

		int n = 256;
		int m = 2 * n - 1;
		HuffmanTree pHT = new HTNode[m + 1];
		CreateHuffmanTree(pHT, sHead.weight, n);

		TestHuffmanTree(pHT);

		Decode(pHT, pBuffer, file);

		file.close();

		WriteFile(filename, pBuffer, sHead.length);

		delete pBuffer;
	}

	return 1;
}

int Decode(const HuffmanTree pHT, char* pBuffer, ifstream& file) {
	char cd[256] = { 0 };
	int pos = 0; char ch;

	while (file.get(ch)) {
		char* c = Byte2str(ch);
		/*printf("%s ",c);*/
		strcat(cd, c); delete[] c;
		while (strlen(cd) >= 64) {
			HuffmanDecode(cd, pHT, pBuffer, pos);
		}
	}
	if (strlen(cd) > 0)
		HuffmanDecode(cd, pHT, pBuffer, pos);
	return 1;
}

char* Byte2str(const char& ch) {
	char* binaryString = new char[9];
	binaryString[8] = '\0';
	for (int i = 7; i >= 0; --i) {
		binaryString[7 - i] = ((ch & (1 << i)) ? '1' : '0');
	}
	return binaryString;
}

int WriteFile(const char* pFilename, const char* pBuffer, const int nSize) {
	char filename[256] = { 0 };
	strcpy(filename, pFilename);
	strcat(filename, ".bmp");

	FILE* out = fopen(filename, "wb");

	fwrite(pBuffer, sizeof(char), nSize, out);

	fclose(out);
	out = NULL;

	cout << "生成原文件：" << filename << endl;

	return nSize;
}

int HuffmanDecode(char* cd, const HuffmanTree pHT, char* pBuffer, int& pos) {
	int temp = 511;
	int len = strlen(cd);
	int move = 0;
	for (int i = 0; i < len; i++) {
		if (pHT[temp].lchild == 0 && pHT[temp].rchild == 0) {
			pBuffer[pos++] = temp - 1;
			temp = 511;
			move = i;
			i--;
			continue;
		}
		if (cd[i] == '0') {
			temp = pHT[temp].lchild;
		}
		else if (cd[i] == '1') {
			temp = pHT[temp].rchild;
		}
	}
	int j;
	for (j = 0; j < len - move; j++)
		cd[j] = cd[j + move];
	for (int k = j; k < len; k++)
		cd[k] = '\0';
	return 1;
}