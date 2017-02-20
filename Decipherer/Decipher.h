#pragma once
//------------------------------------------------------------------------------------------------
//
//
//------------------------------------------------------------------------------------------------

#ifndef DECIPHER_H
#define DECIPHER_H

#include "CipherText.h"
#include <algorithm>
#include <fstream>

void Shift_Cipher(CipherText cipher);
void Substitution_Cipher(CipherText cipher);
void Vigenere_Cipher(CipherText cipher);
void Permutation_Cipher(CipherText cipher);

struct key_length {
	int length;
	int freq;
};
#endif