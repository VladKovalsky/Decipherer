#include "Decipher.h"
#include <algorithm>
void Shift_Cipher(CipherText cipher)
{
	char userInput = ' ';
	int shiftAmount = 0;
	int recShift = 0;
	int i = 0;
	std::vector<SubText> orderMono = cipher.getOrderedMonograms();
	while (userInput != 'q') {
		std::cout << "Enter s (shift), f (monogram frequencies), or q (quit) ";
		std::cin >> userInput;
		switch (userInput)
		{
		case 's':
		{
			recShift = orderMono[0].getString()[0] - 'E';
			if (recShift < 0) recShift = -26 + recShift;
			std::cout << "Recomended shift is " << recShift << " based on the frequency of the cipher and english E" << std::endl;
			std::cout << "Enter shift amount (0-25) ";
			std::cin >> shiftAmount;
			if (shiftAmount >= 0 && shiftAmount < 26) {
				for (i = 0; i < 26 - shiftAmount; i++) {
					if (i + shiftAmount > 25) shiftAmount = -26 + shiftAmount;
					cipher.swapLetters(i, (i + shiftAmount));
				}
				cipher.buildModifiedText(); // int 1 means monograms
			}
			break;

		}
		case 'f':
		{
			cipher.printMonogramFrequency();
			std::cout << std::endl;
		}
		default:
			break;
		}
	}
}
void Substitution_Cipher(CipherText cipher) {
	char userInput = ' ';
	int shiftAmount = 0;
	int recShift = 0;
	int i = 0;
	char quit = NULL;
	char FROM, FROM2, FROM3 = NULL;
	char TO, TO2, TO3 = NULL;
	std::string input = cipher.getOriginalText();
	std::cout << input << std::endl;
	//	std::vector<SubText> orderMono = cipher.getOrderedMonograms();
	//	std::vector<SubText> orderMono = cipher.getOrderedMonograms();
	while (userInput != 'q') {
		std::cout << "Enter m (monogram frequencies), b (bigram frequencies), t (trigram frequencies) or q (quit) ";
		std::cin >> userInput;
		switch (userInput)
		{
		case 'm':
		{
			cipher.printMonogramFrequency(); std::cout << std::endl;
			std::cout << "Type in 1 letter and switch from ";
			std::cin >> FROM;
			std::cout << "to ";
			std::cin >> TO;
			replace(input.begin(), input.end(), FROM, TO);
			std::cout << input << std::endl;
			break;
		}
		case 'b':
		{
			cipher.printBigramFrequency(); std::cout << std::endl;
			std::cout << "Type in 2 letters and switch from ";
			std::cin >> FROM >> FROM2;
			std::cout << "type in 2 letters and to ";
			std::cin >> TO >> TO2;
			replace(input.begin(), input.end(), FROM, TO);
			replace(input.begin(), input.end(), FROM2, TO2);
			std::cout << input << std::endl;
			break;
		}
		case 't':
		{
			cipher.printTrigramFrequency(); std::cout << std::endl;
			std::cout << "Type in 3 letters and switch from ";
			std::cin >> FROM >> FROM2 >> FROM3;
			std::cout << "type in 2 letters and to ";
			std::cin >> TO >> TO2 >> TO3;
			replace(input.begin(), input.end(), FROM, TO);
			replace(input.begin(), input.end(), FROM2, TO2);
			replace(input.begin(), input.end(), FROM3, TO3);
			std::cout << input << std::endl;
			break;
		}
		default:
			break;
		}
	}




}
