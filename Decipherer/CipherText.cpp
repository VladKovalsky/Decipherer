#pragma once

#include "CipherText.h"

CipherText::CipherText(std::string text) {
	this->originalText = text;
	this->modifiedText = "";

	createComponents();

	order();
	buildModifiedText();

	//Index of Coincidence calculation (does not need to be in a function?)
	int i = 0;
	for (i = 0; i < 26; i++) {
	IC = IC + (monograms[i].getFreq() * (monograms[i].getFreq() - 1));
	}
	IC = IC / (originalText.length() * (originalText.length() - 1));

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

void CipherText::createComponents() {
	int i = 0;
	//Setting up A-Z monograms
	for (i = 0; i < 26; i++) {
		SubText newLetter(std::string(1, char(65 + i)));
		monograms.push_back(newLetter);
	}
	//Setting up AA-ZZ bigrams
	for (i = 0; i < 26 * 26; i++) {
		std::string temp = "";
		temp.push_back(i / 26 + 65);
		temp.push_back(i % 26 + 65);
		SubText newSub(temp);
		bigrams.push_back(newSub);
	}
	//Setting up AAA-ZZZ trigrams
	for (i = 0; i < 26 * 26 * 26; i++) {
		std::string temp = "";
		temp.push_back(i / 26 / 26 + 65);
		temp.push_back(i / 26 % 26 + 65);
		temp.push_back(i % 26 + 65);
		SubText newSub(temp);
		trigrams.push_back(newSub);
	}

	setFrequencies();
}

void CipherText::setFrequencies() {
	int i = 0;
	int j = 0;
	int locNum = 0;
	std::string substr = "";
	bool foundSub = false;
	for (i = 0; i < originalText.size(); i++) {
		locNum = 0;
		monograms.at(originalText.at(i) - 65).incFreq();
		//bigrams
		if (i < originalText.size() - 1) {
			substr = originalText.substr(i, 2);
			locNum = (substr[0] - 65) * 26 + (substr[1] - 65);
			bigrams[locNum].incFreq();
		}

		//trigrams
		if (i < originalText.size() - 2) {
			substr = originalText.substr(i, 3);
			locNum = (substr[0] - 65) * 26 * 26 + (substr[1] - 65) * 26 + substr[2] - 65;
			trigrams[locNum].incFreq();
		}
	}
}

void CipherText::order()
{
	int i = 0;
	int loc = 0;
	std::vector<SubText> temp = this->monograms;
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
	temp = this->bigrams;
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
	temp = this->trigrams;
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

std::string CipherText::getOriginalText() {
	return this->originalText;
}