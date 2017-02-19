#include "Decipher.h"

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
				cipher.buildModifiedText();
			}

		}
		default:
			break;
		}
	}
}
