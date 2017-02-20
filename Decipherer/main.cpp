/*

*/


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "CipherText.h"
#include "Decipher.h"
int main(int argc, char* argv[]) {

	if (argc != 3) {
		std::cout << "Correct usage: Decipherer inputFile outputFile" << std::endl;
		return -1;
	}

	std::string inputText = "";
	std::ifstream inp(argv[1]);
	std::ofstream outp(argv[2]);
	if (!inp) {
		std::cout << "File could not be found" << std::endl;
		return -1;
	}

	getline(inp, inputText);

	CipherText cipher(inputText);

	char userInput = ' ';

	while (userInput != 'q') {
		std::cout << "Enter 1 (Shift), 2 (Substitution), 3 (Vigenere), 4 (Permutation), p (output current plaintext to file), or q (quit) ";
		std::cin >> userInput;

		switch (userInput) {
		case '1':
			Shift_Cipher(cipher);
			outp << cipher.getModifiedText();
			break;
		case '2':
			Substitution_Cipher(cipher);
			outp << cipher.getModifiedText();
			break;
		case '3':
			Vigenere_Cipher(cipher);
			outp << cipher.getModifiedText();
			break;
		case '4':
			Permutation_Cipher(cipher);
			outp << cipher.getModifiedText();
			break;
		case 'p':
			outp << cipher.getModifiedText();
			break;
		}

	}

	outp.close();
	inp.close();

	return 0;
}