#pragma once
#ifndef SUBTEXT_H
#define SUBTEXT_H

#include <string>
#include <vector>

class SubText {
private:
	std::string subString;
	int freq;
public:
	SubText();
	SubText(std::string name) {
		subString = name;
		freq = 0;
	}
	void incFreq() { freq++; };
	int getFreq() { return freq; };
	std::string getString() { return subString; };
	void setString(std::string chngTo) { this->subString = chngTo; };
};
#endif