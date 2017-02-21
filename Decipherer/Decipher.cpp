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

	std::string userString = "";
	int loc = -1;
	int j = 0;
	bool foundLength = false;
	int userLength = 0;
	int recShift = 0;
	while (userInput != 'q') {
		std::cout << "Enter l (key length guess), s (substring based on key length), d (decrypt with key), f (monogram frequencies), b (bigram frequencies), p (print plaintext to vigenere.txt), or q (quit) ";
		std::cin >> userInput;
		switch (userInput)
		{
		case 'l':
		{
			std::vector<key_length> keys;
			std::vector<key_length> temp;

			std::cout << "Enter a bigram to use to check possible key lengths ";
			std::cin >> userString;
			loc = -1;
			for (i = 0; i < cipher.getOriginalText().length() - 1; i++) {
				if (userString == cipher.getOriginalText().substr(i, 2)) {
					if (loc == -1) {
						loc = i;
					}
					else {
						j = 0;
						foundLength = false;
						for (j = 0; j < keys.size(); j++) {
							if (keys[j].length == (i - loc)) {
								keys[j].freq++;
								foundLength = true;
							}
						}
						if (!foundLength) {
							key_length newKey;
							newKey.freq = 1;
							newKey.length = (i - loc);
							keys.push_back(newKey);
						}

						loc = i;
					}
				}
			}
			temp = keys;
			keys.clear();
			int maxLoc = 0;
			while(temp.size() > 0) {
				key_length tempKey;
				tempKey.length = 0;
				tempKey.freq = 0;
				maxLoc = 0;
				for(i = 0; i < temp.size(); i++) {
					if (temp[i].freq >= temp[maxLoc].freq) {
						maxLoc = i;
					}
				}
				tempKey.length = temp[maxLoc].length;
				tempKey.freq = temp[maxLoc].freq;
				keys.push_back(tempKey);
				temp.erase(temp.begin() + maxLoc);
			}
			
			std::cout << "(Length / Frequency)" << std::endl;
			for (i = 0; (i < keys.size() || i < 20); i++) {
				std::cout << "(" << keys[i].length << " / " << keys[i].freq << ") | ";
			}
			std::cout << std::endl;
			
			keys.clear();
			temp.clear();

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
		std::cout << "Enter m (monogram frequencies), b (bigram frequencies), t (trigram frequencies), p (print plaintext to permutation.txt), or q (quit) ";
		std::cin >> userInput;
		switch (userInput)
		{
		case 'm':
		{
			cipher.printMonogramFrequency(); std::cout << std::endl;
			std::cout << "Propose key length:"; std::cin >> keyLen;
			cipher.permuteData(keyLen);
			break;
		}
		case 'b':
		{
			cipher.printBigramFrequency(); std::cout << std::endl;
			std::cout << "Propose key length:"; std::cin >> keyLen;

			break;
		}

		case 'p': {
			std::ofstream outp("permutation.txt");
			outp << cipher.getModifiedText();
			outp.close();

			std::cout << "Plaintext printed to permutation.txt in the root project directory" << std::endl;

			break;
		}

		case 't':
		{
			cipher.printTrigramFrequency(); std::cout << std::endl;
			std::cout << "Propose key length:"; std::cin >> keyLen;
			break;
		}
		default:
			break;
		}
	}

}
