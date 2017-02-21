#include "Decipher.h"
void Shift_Cipher(CipherText cipher)
{
	char userInput = ' ';
	int shiftAmount = 0;
	int recShift = 0;
	int i = 0;
	std::vector<SubText> orderMono = cipher.getOrderedMonograms();
	while (userInput != 'q') {
		std::cout << "Enter s (shift), f (monogram frequencies), p (print plaintext to shift.txt), or q (quit) ";
		std::cin >> userInput;
		switch (userInput)
		{
		case 's':
		{
			recShift = orderMono[0].getString()[0] - 'E';
			if (recShift < 0) recShift = 26 + recShift;
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

		case 'p': {
			std::ofstream outp("shift.txt");
			outp << cipher.getModifiedText();
			outp.close();

			std::cout << "Plaintext printed to shift.txt in the root project directory" << std::endl;

			break;
		}

		case 'f':
		{
			cipher.printMonogramFrequency();
			std::cout << std::endl;
			break;
		}
		default:
			break;
		}
	}
}
void Substitution_Cipher(CipherText cipher) {
	char userInput = ' ';
	std::string FROM;
	std::string TO;
	std::vector<int> temp;
	std::string modified = cipher.getModifiedText();
	std::string original = cipher.getOriginalText();
	std::cout << original << std::endl;
	while (userInput != 'q') {
		std::cout << "Enter f(Show frequency of monograms,bigrams, and trigrams), p (print plaintext to substitution.txt)" << std::endl;
		std::cout << "k (if you know the keys) ,or q(quit) ";
		std::cin >> userInput;
		switch (userInput)
		{
		case 'f':
		{
			cipher.printMonogramFrequency(); std::cout << std::endl;
			cipher.printBigramFrequency(); std::cout << std::endl;
			cipher.printTrigramFrequency(); std::cout << std::endl;
			std::cout << "Type in the letters of the cipher text that you want to change: " << std::endl;
			std::cin >> FROM;
			std::cout << "Type in the letters that you want to change to:" << std::endl;
			std::cin >> TO;

			if (FROM.length() == TO.length()) {

				for (int i = 0; i < FROM.size(); i++) {
					for (int j = 0; j < original.size(); j++) { //make sure the modified text does not mix with the original text
						if (FROM[i] == original[j]) {
							modified[j] = TO[i];
						}
					}
				}
				std::cout << modified << std::endl;
				cipher.setModifiedText(modified);
			}
			else std::cout << "Entered lengths are not the same" << std::endl;
			break;
		}
		case 'p': {
			std::ofstream outp("substitution.txt");
			outp << cipher.getModifiedText();
			outp.close();

			std::cout << "Plaintext printed to substitution.txt in the root project directory" << std::endl;

			break;
		}

		default:
			break;
		}
	}
}

void Vigenere_Cipher(CipherText cipher){

	char userInput = ' ';
	int i = 0;
	std::vector<SubText> orderMono = cipher.getOrderedMonograms();
	std::vector<SubText> orderBi = cipher.getOrderedBigrams();
	std::vector<key> keys;
	std::vector<key> temp;
	int loc = -1;
	int j = 0;
	bool foundLength = false;
	int userLength = 0;
	int recShift = 0;
	std::string userString = "";
	std::string subStr = "";
	while (userInput != 'q') {
		std::cout << "Enter k (key length guess), s (non shifted key (and guess) based on key length), d (decrypt with key), f (monogram frequencies), b (bigram frequencies), p (print plaintext to vigenere.txt), or q (quit) ";
		std::cin >> userInput;
		switch (userInput)
		{
		case 'k':
		{
			keys.clear();
			temp.clear();

			//Get max key length from user
			std::cout << "Enter a maximum key length ";
			std::cin >> userLength;

			//Cycle through possible key lengths, create sub cipher texts, and calcualte IC value for storing them in keyLengthICs vector
			for (i = 0; i < userLength; i++) {
				subStr = "";
				for (j = 0; j < cipher.getOriginalText().length() - i; j = j + i + 1)
					subStr.push_back(cipher.getOriginalText()[j]);
				CipherText subCipher(subStr); //We are treating each subtext as its own cipher text (for functions)

				//Sort search for where to place key length and IC
				loc = keys.size();
				for (j = 0; j < keys.size() && loc == keys.size(); j++) {
					if (subCipher.getIC() > keys[j].IC) loc = j;
				}

				key newKey;
				newKey.IC = subCipher.getIC();
				newKey.length = i + 1;

				keys.insert(keys.begin() + loc, newKey);
			}

			std::cout << "(Length / IC)" << std::endl;
			for (i = 0; i < keys.size(); i++) {
				std::cout << "(" << keys[i].length << " / " << keys[i].IC << ") | ";
			}
			std::cout << std::endl;

			break;

		}

		case 's':
		{
			std::cout << "Enter a test key length N ";
			std::cin >> userLength;

			//Create strings of size key length N  sub strings
			std::vector<std::string> keySplitStrings;
			for (i = 0; i < userLength; i++) {
				std::string temp = "";
				keySplitStrings.push_back(temp);
			}

			//fill those substrings according to the position of each character in original text
			for (i = 0; i < cipher.getOriginalText().length(); i++) {
				keySplitStrings[i%userLength].push_back(cipher.getOriginalText()[i]);
			}

			//Now create ciphers with the strings (to use pre-built functions)
			std::vector<CipherText> keySplitSubTexts;
			for (i = 0; i < keySplitStrings.size(); i++) keySplitSubTexts.push_back(CipherText(keySplitStrings[i]));
			
			//Print the most common letter in each substring
			std::cout << "Most common letter in each substring" << std::endl;
			for (i = 0; i < keySplitSubTexts.size(); i++) std::cout << keySplitSubTexts[i].getOrderedMonograms()[0].getString();
			std::cout << std::endl;

			//Give possible shifted key against E
			std::cout << "Possible key if shifted against E" << std::endl;
			for (i = 0; i < keySplitSubTexts.size(); i++) {
				recShift = keySplitSubTexts[i].getOrderedMonograms()[0].getString()[0] - 'E';
				if (recShift < 0) recShift = 26 + recShift;
				std::cout << char('A' + recShift);
			}
			std::cout << std::endl;
			break;
		}

		case 'd':
		{
			std::cout << "Enter key to decrypt the message with ";
			std::cin >> userString;

			cipher.buildModifiedText(userString);

			std::cout << cipher.getModifiedText() << std::endl;
			break;
		}

		case 'p': {
			std::ofstream outp("vigenere.txt");
			outp << cipher.getModifiedText();
			outp.close();

			std::cout << "Plaintext printed to vigenere.txt in the root project directory" << std::endl;

			break;
		}

		case 'f':
		{
			cipher.printMonogramFrequency();
			std::cout << std::endl;
			break;
		}
		case 'b':
		{
			cipher.printBigramFrequency();
			std::cout << std::endl;
			break;
		}
		default:
			break;
		}
	}
}
void Permutation_Cipher(CipherText cipher) {
	char userInput = ' ';
	int keyLen = 0;
	std::vector<SubText> orderPermu = cipher.getOrderedMonograms();
	while (userInput != 'q') {
		std::cout << "Enter f(frequency analysis), p (print plaintext to permutation.txt), or q (quit) ";
		std::cin >> userInput;
		switch (userInput)
		{
		case 'f':
		{
			cipher.printMonogramFrequency(); std::cout << std::endl;
			cipher.printBigramFrequency(); std::cout << std::endl;
			cipher.printTrigramFrequency(); std::cout << std::endl;
			std::cout << "Propose key length:"; std::cin >> keyLen;
			cipher.permuteData(keyLen);
			break;
		}
		case 'p': {
			std::ofstream outp("permutation.txt");
			outp << cipher.getModifiedText();
			outp.close();

			std::cout << "Plaintext printed to permutation.txt in the root project directory" << std::endl;

			break;
		}
		default:
			break;
		}
	}

}
