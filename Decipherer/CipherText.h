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
	
	std::vector<SubText*> textComp;

	std::vector<SubText> orderedMonograms;

	void createComponents();
	void setFrequencies();
	void order();
public:
	CipherText() {};
	CipherText(std::string text);
	void buildModifiedText();
	void swapLetters(int loc1, int loc2);
	void printMonogramFrequency();
	std::vector<SubText> getOrderedMonograms() { return orderedMonograms; };
	std::vector<SubText> getMonograms() { return monograms; };

};
#endif

//------------------------------------------------------------------------------------------------


