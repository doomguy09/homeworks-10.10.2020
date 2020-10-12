// ConsoleApplication56.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

int Base64Char2(unsigned char b) {
	//b &= 0x3F;
		char Base64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		int j = 0;
		for (int i = 0; i < 64; ++i) {
			if (Base64Alphabet[i] == b) break;
			++j;
		}
		return j;
}

char Base64Char(unsigned char b) {
	b &= 0x3F;
	if (b < 26) return 'A' + b;
	if (b < 52) return 'a' + (b - 26);
	if (b < 62) return '0' + (b - 52);
	if (b == 62) return '+';
	return '/';
}



int main()
{
	const int row = 20; const int col = 64;
	char matrix[row][col];
	char ch;
	int count[col]; int x = 1;
	for (int i = 0; i < col; ++i) count[i] = 0;
	std::ifstream fin("readme.txt");
	while (fin.peek()!=EOF) {
		fin.get(ch);
		count[Base64Char2(ch)] += x;
	}
	for (int i = row - 2; i >= 0; --i) {
		for (int j = 0; j < col; ++j) {
			if (count[j] > 0) {
				matrix[i][j] = '*'; count[j] += -1;
			}
			else {
				matrix[i][j] = ' ';
			}
		}
	}
	for (int j = 0; j < col; ++j) {
		matrix[row-1][j] = Base64Char(j);
	}

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			std::cout << "  " << matrix[i][j];
		}
		std::cout<<std::endl;
	}
	fin.close(); 
	std::cout << std::endl;
	
}

