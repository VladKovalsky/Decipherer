/*

*/


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "CipherText.h"
#include "Decipher.h"
int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Correct usage: Decipherer inputFile" << std::endl;
		return -1;
	}

	std::string inputText = "";
	std::ifstream inp(argv[1]);
	if (!inp) {
		std::cout << "File could not be found" << std::endl;
		return -1;
	}

	getline(inp, inputText);

	CipherText cipher(inputText);
	cipher.createBigrams();
	cipher.createTrigrams();

	char userInput = ' ';

	while (userInput != 'q') {
		std::cout << "Enter 1 (Shift), 2 (Substitution), 3 (Vigenere), 4 (Permutation), or q (quit) ";
		std::cin >> userInput;

		switch (userInput) {
		case '1':
			Shift_Cipher(cipher);
			break;
		case '2':
			Substitution_Cipher(cipher);
			break;
		case '3':
			Vigenere_Cipher(cipher);
			break;
		case '4':
			Permutation_Cipher(cipher);
			break;

		}
	}
	inp.close();

	return 0;
}