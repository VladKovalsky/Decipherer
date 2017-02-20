/*

*/


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "CipherText.h"
#include "Decipher.h"
int main(int argc, char* argv[]) {

	std::cout << argc;
	if (argc != 3) {
		std::cout << "Correct usage: Decipherer inputFile outputFile" << std::endl;
		return -1;
	}

	std::string inputText = "";
	std::ifstream inp(argv[1]);
	if (!inp) {
		std::cout << "File could not be found" << std::endl;
		return -1;
	}

	getline(inp, inputText);

	//	CipherText cipher(inputText);

	char userInput = ' ';

	while (userInput != 'q') {
		std::cout << "Enter 1 (Shift), 2 (Substitution), or q (quit) ";
		std::cin >> userInput;

		switch (userInput) {
		case '1':
		{
			CipherText cipher(inputText, 1);
			Shift_Cipher(cipher);
			break;
		}
		case '2': {
			Substitution_Cipher(inputText);
			break;
		}
		}

	}

	inp.close();

	return 0;
}