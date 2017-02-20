#pragma once
//------------------------------------------------------------------------------------------------
//
//
//------------------------------------------------------------------------------------------------

#ifndef DECIPHER_H
#define DECIPHER_H

#include "CipherText.h"

void Shift_Cipher(CipherText cipher);
void Substitution_Cipher(CipherText cipher);
void Permutation_Cipher(CipherText cipher);

#endif