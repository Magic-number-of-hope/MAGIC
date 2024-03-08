#pragma once
#include"Huffman.h"
#include"common.h"

int Compress(const char* pFilename);

int InitHead(const char* pFilename, HEAD& sHead);

int Encode(const char* pFilename, const HuffmanCode pHC, char* pBuffer, const int nSize);

char Str2byte(const char* pBinStr);

int WriteFile(const char* pFilename, const HEAD sHead, const char* pBuffer, const int nSize);