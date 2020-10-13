// ConsoleApplication57.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

char Base64Char(unsigned char b) {
	b &= 0x3F;
	/*	char Base64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	return Base64Alphabet[b];
	*/
	if (b < 26) return 'A' + b;
	if (b < 52) return 'a' + (b - 26);
	if (b < 62) return '0' + (b - 52);
	if (b == 62) return '+';
	if (b == 63) return '/';
	return ' ';
}

int Base64Encode(char *inStr, int Len, char *outStr) {
	
	int i = 0, j = 0; 
	unsigned char a1, a2, a3;
	unsigned char b1, b2, b3, b4;

	for (i = 0; i < Len; i += 4) {
		a1 = a2 = a3 = 0;
		b1 = b2 = b3 = b4 = 0;
		
		
		b1 = inStr[i];
		if (i + 1 < Len) b2 = inStr[i + 1];
		if (i + 2 < Len) b3 = inStr[i + 2];
		if (i + 3 < Len) b4 = inStr[i + 3];

		/*b1 = a1 >> 2;
		b2 = ((a1 & 0x3) << 4) | (a2 >> 4);
		b3 = ((a2 & 0xF) << 2) | (a3 >> 6);
		b4 = a3 & 0x3F;*/
		
		a1 = (b1 << 2) | (b2 >> 6);
		a2 = (b2 << 4) | (b3 >> 2);
		a3 = (b3 << 6) | b4;

		outStr[j++] = Base64Char(a1);
		outStr[j++] = (i + 1 < Len) ? Base64Char(a2) : ' ';
		outStr[j++] = (i + 2 < Len) ? Base64Char(a3) : ' ';
	}

	return j;
}

int main()
{
	char inputFileName[1024];
	char outputFileName[1024];
	std::cout << "Input source file name: ";
	std::cin.getline(inputFileName, 1024);
	std::cout << "Input destination file name: ";
	std::cin.getline(outputFileName, 1024);



	std::ifstream fin(inputFileName);
	char ch; char in[1024]; char out[1024];
	int s = 0; 
	
	std::ofstream fout(outputFileName);
	while (fin.peek() != EOF) {
		fin.read(in, 1024);
		s = fin.gcount();
		s = Base64Encode(in, s, out);
		fout.write(out, s);
		fout << std::endl;
	}

    std::cout << std::endl;
	fin.close();
}

