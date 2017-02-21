#pragma once

#include "CipherText.h"


CipherText::CipherText(std::string text) {
	this->originalText = text;
	this->modifiedText = "";

	createMonograms();

	buildModifiedText();

	//Index of Coincidence calculation (does not need to be in a function?)
	int i = 0;
	for (i = 0; i < 26; i++) {
	IC = IC + (monograms[i].getFreq() * (monograms[i].getFreq() - 1));
	}
	IC = IC / (originalText.length() * (originalText.length() - 1));

}

void CipherText::createMonograms() {
	//Create monogram data
	int i = 0;
	monograms.clear();
	for (i = 0; i < 26; i++) {
		SubText newLetter(std::string(1, char(65 + i)));
		monograms.push_back(newLetter);
	}

	//Get frequencies of monograms
	for (i = 0; i < originalText.size(); i++) {
		monograms.at(originalText.at(i) - 65).incFreq();
	}
	
	//Order by frequency
	int loc = 0;
	std::vector<SubText> temp = this->monograms;
	orderedMonograms.clear();
	while (temp.size() > 0 && orderedMonograms.size() < 26) {
		loc = 0;
		SubText max = temp[0];
		for (i = 1; i < temp.size(); i++) {
			if (max.getFreq() < temp[i].getFreq()) {
				max = temp[i];
				loc = i;
			}
		}
		this->orderedMonograms.push_back(max);
		temp.erase(temp.begin() + loc);
	}
}

void CipherText::createBigrams() {
	//Create bigram data
	int i = 0;
	bigrams.clear();
	for (i = 0; i < 26 * 26; i++) {
		std::string temp = "";
		temp.push_back(i / 26 + 65);
		temp.push_back(i % 26 + 65);
		SubText newSub(temp);
		bigrams.push_back(newSub);
	}

	//Set frequencies
	int loc = 0;
	std::string substr = "";
	bool foundSub = false;
	for (i = 0; i < originalText.size(); i++) {
		loc = 0;
		//bigrams
		if (i < originalText.size() - 1) {
			substr = originalText.substr(i, 2);
			loc = (substr[0] - 65) * 26 + (substr[1] - 65);
			bigrams[loc].incFreq();
		}
	}
	
	//Order
	std::vector<SubText> temp = this->bigrams;
	orderedBigrams.clear();
	while (temp.size() > 0 && orderedBigrams.size() < 20) {
		loc = 0;
		SubText max = temp[0];
		for (i = 1; i < temp.size(); i++) {
			if (max.getFreq() < temp[i].getFreq()) {
				max = temp[i];
				loc = i;
			}
		}
		this->orderedBigrams.push_back(max);
		temp.erase(temp.begin() + loc);
	}
}

void CipherText::createTrigrams() {
	int i = 0;
	//Setting up AAA-ZZZ trigrams
	trigrams.clear();
	for (i = 0; i < 26 * 26 * 26; i++) {
		std::string temp = "";
		temp.push_back(i / 26 / 26 + 65);
		temp.push_back(i / 26 % 26 + 65);
		temp.push_back(i % 26 + 65);
		SubText newSub(temp);
		trigrams.push_back(newSub);
	}

	//Setting frequencies
	int loc = 0;
	std::string substr = "";
	bool foundSub = false;
	for (i = 0; i < originalText.size(); i++) {
		loc = 0;

		//trigrams
		if (i < originalText.size() - 2) {
			substr = originalText.substr(i, 3);
			loc = (substr[0] - 65) * 26 * 26 + (substr[1] - 65) * 26 + substr[2] - 65;
			trigrams[loc].incFreq();
		}
	}
	std::vector<SubText> temp = this->trigrams;
	orderedTrigrams.clear();
	while (temp.size() > 0 && orderedTrigrams.size() < 20) {
		loc = 0;
		SubText max = temp[0];
		for (i = 1; i < temp.size(); i++) {
			if (max.getFreq() < temp[i].getFreq()) {
				max = temp[i];
				loc = i;
			}
		}
		this->orderedTrigrams.push_back(max);
		temp.erase(temp.begin() + loc);
	}

}

void CipherText::buildModifiedText() {
	int i = 0;

	this->modifiedText = "";

		for (i = 0; i < originalText.size(); i++) {
			modifiedText.push_back(monograms[originalText[i] - 65].getString()[0]);
		}
}

void CipherText::buildModifiedText(std::string key) {
	int i = 0;

	this->modifiedText = "";

	int shiftAmm = 0;

	for (i = 0; i < originalText.size(); i++) {
		shiftAmm = key[i%key.size()] - 65;
		if ((originalText[i] - 65 - shiftAmm) < 0) shiftAmm = shiftAmm - 26;
		modifiedText.push_back(originalText[i] - shiftAmm);
	}
}


void CipherText::swapLetters(int loc1, int loc2) {
	std::string temp(this->monograms[loc1].getString());
	this->monograms[loc1].setString(this->monograms[loc2].getString());
	this->monograms[loc2].setString(temp);
	std::cout << "Swapped " << this->monograms[loc2].getString() << " with " << this->monograms[loc1].getString() << ":" << std::endl;
}

void CipherText::printMonogramFrequency()
{
	int i = 0;
	std::cout << "Monogram frequencies: " << std::endl;
	for (i = 0; i < orderedMonograms.size(); i++) {
		std::cout << orderedMonograms[i].getString() << " " << orderedMonograms[i].getFreq() << " |";
	}
}
void CipherText::printBigramFrequency()
{
	int i = 0;
	std::cout << "Bigram frequencies: " << std::endl;
	for (i = 0; i < orderedBigrams.size(); i++) {
		std::cout << orderedBigrams[i].getString() << " " << orderedBigrams[i].getFreq() << " |";
	}
}
void CipherText::printTrigramFrequency()
{
	int i = 0;
	std::cout << "Trigram frequencies: " << std::endl;
	for (i = 0; i < orderedTrigrams.size(); i++) {
		std::cout << orderedTrigrams[i].getString() << " " << orderedTrigrams[i].getFreq() << " |";
	}
}

std::string CipherText::getOriginalText() {return this->originalText;}

void CipherText::permuteData(int key) {
	std::string permuteData = this->originalText;
	std::vector<std::vector<char>> TwoDVector;
	int i, j ,k = 0;
	int flag = 0;
	for (i = 0; k < permuteData.size(); i++) {
		std::vector<char>temp;
		for (j = 0; j < key; j++) {
			if (flag == 1) {
				break;
			}
			if (permuteData[k] == NULL) {
				flag = 1;
				temp.push_back ('-');
			}
			else {
				temp.push_back(permuteData[k]);
				k++;
			}
		}
		TwoDVector.push_back(temp);
	}
	for (i = 0; i < TwoDVector.size(); i++) {
		for (j = 0; j < key; j++) {
			if (TwoDVector[i][j] == '-') {
				break;
			}
			else{
				std::cout << TwoDVector[i][j];
			}
		}
		std::cout << std::endl;
	}
}
