#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include "Shift_Cipher.h"
using namespace std;

void ShiftCipher() {
	ifstream inp;
	inp.open("cipher1.txt");
	ofstream outp;
	outp.open("output.txt");
	string data;
	int Num = 1;
	while (getline(inp, data)) {
		cout << data << endl;
	}
	while (Num <= 26) {
		outp << "------------------------" << Num << "-------------------------------------" << endl << endl << endl;


		//outp << "-----------!!!!!!!!!!!!!!!!!!!!!!!---------------------------------------------------------------------------------------------------" << endl << endl << endl;
		for (unsigned int i = 0; i < unsigned(data.length()); i++)
		{
			if (isalpha(data[i]))												// check if the letter is alphabet
				if (islower(data[i]))											// check if the letter is lower case
				{
					data[i] = (data[i] - Num) - 97;					 //char value + shift key and - minumum range of lower case
					data[i] = ((data[i] + 26) % 26) + 97;							//divide 26 letters  then add 26 letters in to prevent negative numbers and add the minimum range of lower case back
				}
				else if (isupper(data[i]))										// check if the letter is lower case
				{
					data[i] = data[i] - Num - 65;						//char value + shift key and - minumum range of upper case
					data[i] = ((data[i] + 26) % 26) + 65;								//divide 26 letters  then add 26 letters in to prevent negative numbers and add the minimum range of upper case back
				}


			outp << data[i];
			//[i] 
			//X    Y    Z    ??   A   B     c
			//88   89   90		  97

		}
		outp << endl;
		Num++;

	}
	inp.close();
	outp.close();
}


