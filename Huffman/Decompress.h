#pragma once
#include<iostream>
#include<fstream>
#include"Huffman.h"
#include"common.h"
using namespace std;

int Decompress(const char* filename);

int Decode(const HuffmanTree pHT, char* pBuffer, ifstream& file);

char* Byte2str(const char& pBuffer);

int WriteFile(const char* pFilename, const char* pBuffer, const int nSize);

int HuffmanDecode(char* cd, const HuffmanTree pHT, char* pBuffer, int& pos);