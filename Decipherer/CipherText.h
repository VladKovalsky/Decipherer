#pragma once
//------------------------------------------------------------------------------------------------
//
//
//------------------------------------------------------------------------------------------------

#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include <string>
#include <iostream>
#include <vector>
#include "SubText.h"

class CipherText {
private:
	std::string originalText;
	std::string modifiedText;


	std::vector<SubText> monograms;
	std::vector<SubText> bigrams;
	std::vector<SubText> trigrams;

	std::vector<SubText> orderedMonograms;
	std::vector<SubText> orderedBigrams;
	std::vector<SubText> orderedTrigrams;

	int IC;

	void createComponents();
	void setFrequencies();
	void order();
public:
	CipherText() {};
	CipherText(std::string text);
	void buildModifiedText();
	void swapLetters(int loc1, int loc2);
	void printMonogramFrequency();
	void printBigramFrequency();
	void printTrigramFrequency();
	void permuteData(int key);
	std::string getOriginalText();
	std::string getModifiedText();
	std::vector<SubText> getOrderedMonograms() { return orderedMonograms; };
	std::vector<SubText> getMonograms() { return monograms; };
	std::vector<SubText> getOrderedBigrams() { return orderedBigrams; };
	std::vector<SubText> getBigrams() { return bigrams; };
	std::vector<SubText> getOrderedTrigrams() { return orderedTrigrams; };
	std::vector<SubText> getTrigrams() { return trigrams; };
};
#endif

//------------------------------------------------------------------------------------------------


