//implement functions defined in convert.h

#include "../include/convert.h"
#include <string.h>
#include <math.h> 
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

// One greater than UQ16.16 / Q15.16 string length, as it is 33 bits with the fixed point (need null temrinator).
#define SIZE_REF 34

// Reused functions from Assignment1-3, for explanations, please refer to past assignments. 

int charToNumber(char x) {
    int number = x;
    if (number >= 48 && number <= 57) {
        return number - 48;
    }
    number = toupper(x) - 'A';
    number += 10; 
    return number;
}

char numberToLetter(int number) {
    char letter;
    if (number <= 9) {
        letter = 48 + number;
    } else {
        letter = 'A' + (number - 10); 
    }
    return letter;
}

char* uextendBinary(char *bin, int size) { 
    char* extendedStr = (char*) calloc(size, sizeof(char));
    for (int i = 0; i < (size-1) - strlen(bin); i++) {
        extendedStr[i] = '0';
    }
    for (int j = 0; j < strlen(bin); j++) {
        extendedStr[j + ((size-1) - strlen(bin))] = bin[j];
    }
    return extendedStr;
}

char* extendBinary(char *bin, int size) { 
    char* extendedStr = (char*) calloc(size, sizeof(char));
    if (charToNumber(bin[0]) == 0) {
        for (int i = 0; i < (size-1) - strlen(bin); i++) {
            extendedStr[i] = '0';
        }
        for (int j = 0; j < strlen(bin); j++) {
            extendedStr[j + ((size-1) - strlen(bin))] = bin[j];
        }
    } else if (charToNumber(bin[0]) == 1) {
        for (int i = 0; i < ((size-1) - strlen(bin)); i++) {
            extendedStr[i] = '1';
        }
        for (int j = 0; j < strlen(bin); j++) {
            extendedStr[j + ((size-1) - strlen(bin))] = bin[j];
        }
    }

    return extendedStr;
}

char* reverse(char* other) { 
    char* reversedString = (char*) calloc(SIZE_REF, sizeof(char));
    for (int i = 0; i < strlen(other); i++) {
        reversedString[i] = other[strlen(other) - i - 1];
    }
    return reversedString;
}

char* decimalToBinary(int dnumber) { 
    char* result = (char*) calloc(SIZE_REF, sizeof(char));
    int i = 0;
    for (i = 0; dnumber > 0; ++i) {
        int remainder = dnumber % 2; 
        result[i] = numberToLetter(remainder); 
        dnumber /= 2;
    }
    result[i] = '\0';
    char* temp = reverse(result);
    free(result);
    return temp;
}

int binaryToDecimal(char *other) {
    int result = 0;
    int power = 0;

    for (int i = strlen(other) - 1; i >= 0; i--) {
        int currentDigit = charToNumber(other[i]);
        result += (currentDigit * pow(2, power));
        power++;
    }

    return result;
}

// Should only have same input size strings.
char* uaddBinary(char* num1, char* num2) {
    int size = strlen(num1);
    char* addNum = (char*) calloc(size+1, sizeof(char));
    int carryIn = 0;
    int carryOut = 0;

    for (int i = size-1; i >= 0; i--) {
        if (num1[i] != '.' && num2[i] != '.') {
            carryIn = carryOut;
            carryOut = 0;

            int x = charToNumber(num1[i]);
            int y = charToNumber(num2[i]);

            int sum = (x + y + carryIn) % 2;
            addNum[i] = numberToLetter(sum);
            carryOut = (x + y + carryIn) / 2;
        } else {
            addNum[i] = '.';
        }
        
    }
    free(num1);

    return addNum;
}

char* onesComplement(int num) {
    char* binary = decimalToBinary(num);
    char* temp = extendBinary(binary, strlen(binary)+1);
        for (int i = 0; i < strlen(temp); i++) {
            if (temp[i] == '0') {
                temp[i] = '1';
            } else {
                temp[i] = '0';
            }
        }
    free(binary);
    return temp;
} 

char* twosComplement(int num) {
    if (num < 0) {
        char* onesComp = onesComplement(abs(num));
        char* one = uextendBinary("1", strlen(onesComp)+1);
        char* twosComp = uaddBinary(onesComp, one); 
        free(one);

        char* result = extendBinary(twosComp, strlen(twosComp)+2);
        result[0] = '1';
        free(twosComp);
        return result;
    }
    char* temp = decimalToBinary(num);

    char* result = extendBinary(temp, strlen(temp)+2);
    result[0] = '0';
    free(temp);
    return result;
}

/** @brief Turns an input string into its two's complement version.
 *
 *  Takes the input string and flips the 1s and 0s, adds 1 at the end.
 *  This function edits the input string directly and ignores the '.', meaning 
 *  the point will be in the same position it was before.
 *  e.g. 10011.1001 -> 01100.0111
 *
 *  @param input The input string to be converted.
 *  @return The new string, two's complement of the original string.
*/

char* twosComplementString(char* input) {
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '1') {
            input[i] = '0';
        } else if (input[i] == '0') {
            input[i] = '1';
        }
    }
    char* one = uextendBinary("1", strlen(input)+1);
    char* twosComp = uaddBinary(input, one);
    free(one);
    return twosComp;
}

/** @brief Converts an unsigned float to a UQ16.16 format binary fixed point number.
 *
 *  First gets the integerPart by integer casting the float number (rounds down).
 *  Then, subtracting the integer part from float number to get the fraction part.
 *  Then stores the integer part as a binary string in temp, and inserts a point ('.') after.
 *  Uses the fraction to binary algorithm on the fraction part for 16 bits. Finally, extends the string to
 *  have 16 bits in front of the first point, making it UQ16.16 format.
 *
 *  @param floatNumber The unsigned float to be converted to UQ16.16 format.
 *  @return The UQ16.16 format binary string equivalent to floatNumber.
*/

char* fixedUnsignedBinary(float floatNumber) {
    int integerPart = (int) floatNumber;
    float fractionPart = floatNumber - integerPart;
    char* temp = decimalToBinary(integerPart);
    temp[strlen(temp)] = '.';
    for (int i = strlen(temp), j = 0; j < 16; i++, j++) {
        fractionPart *= 2;
        if (fractionPart >= 1) {
            temp[i] = '1';
            fractionPart -= 1;
        } else {
            temp[i] = '0';
        }
    }
    char* result = uextendBinary(temp, SIZE_REF);
    free(temp);
    return result;
}

/** @brief Converts a float to a Q15.16 format binary fixed point number.
 *
 *  If the floatNumber is positive, calls fixedUnsignedBinary() and returns it (UQ16.16 format works for positive).
 *  If the floatNumber is negative, calls fixedUnsignedBinary() on the absolute value of floatNumber,
 *  gets the result as a UQ16.16 and then gets the two's complement of that string with twosComplementString().
 *  
 *  fixedUnsignedBinary() algorithm explanation:
 *  First gets the integerPart by integer casting the float number (rounds down).
 *  Then, subtracting the integer part from float number to get the fraction part.
 *  Then stores the integer part as a binary string in temp, and inserts a point ('.') after.
 *  Uses the fraction to binary algorithm on the fraction part for 16 bits. Finally, extends the string to
 *  have 16 bits in front of the first point, making it UQ16.16 format.
 *
 *  @param floatNumber The float to be converted to Q15.16 format.
 *  @return The Q15.16 format binary string equivalent to floatNumber.
*/

char* fixedSignedBinary(float floatNumber) {
    char* result;
    if (floatNumber < 0) {
        char* temp = fixedUnsignedBinary(-1 * floatNumber);
        result = twosComplementString(temp);
    } else {
        result = fixedUnsignedBinary(floatNumber);
    }

    return result;
}

/** @brief Checks if the format of a fixed point input string is UQ16.16/Q15.16 or not.
 *
 *  First does a sanity check on the length of the input string. If the length of the input string isn't
 *  33, then it can't possibly be in UQ16.16/Q15.16 format. 
 *
 *  Then the first 16 bits of the string are checked, if any bit is not '0' or '1', then the string 
 *  isn't a binary string and it is false. 
 *
 *  After 16 bits, checks if the 17th position is where the fixed point is or not, if not, then it has
 *  more than 16 bits before the decimal, and the string is not in the correct format.
 *
 *  For the last 16 bits, does the same as the first 16 bits, checking if each one is not '0' or '1', if
 *  one bit isn't one of those, then the string is not in the correct format.
 *
 *  @param input The input string to be checked for its format.
 *  @return 1 if the input string is in UQ16.16 or Q15.16 format, 0 if it is not.
*/

int isFixedBinary(char *input) {
    if (strlen(input) != 33) {
        return 0;
    }

    for (int i = 0; i < 16; i++) {
        if (input[i] != '0' && input[i] != '1') {
            return 0;
        }
    }

    if (input[16] != '.') {
        return 0;
    }

    for (int i = 17; i < 33; i++) {
        if (input[i] != '0' && input[i] != '1') {
            return 0;
        }
    }

    return 1;
}

/** @brief Takes an input UQ16.16 fixed point binary string and converts it to its unsigned float form.
 *
 *  Starts at the MSB (2^15 spot), and initializes power at 15. Checks each bit from left to right.
 *  
 *  Checks each bit as follows:
 *  If there is a '1' in the bit, adds 2^power to the result (e.g. '1' in the 5th bit would be 1 * 2^11).
 *  If there is a '0' in the bit, doesn't change the valeu fo the string, so just decreases the power and
 *  moves over to the next bit.
 *  Note: if there is a '.', simply ignores it and goes to the next bit without decreasing the power.
 *
 *  Goes until the LSB of the UQ16.16 string (2^-16) spot, checking the same thing.
 *
 *  @param input The UQ16.16 input string to be checked to be converted to an unsigned float.
 *  @return The unsigned float equivalent of the input binary string.
*/

float fixedBinaryToFloat(char *input) {
    float res = 0;
    int power = 15;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '1') {
            res += pow(2, power);
            power--;
        } else if (input[i] == '0') {
            power--;
        }
    }
    return res;
}

/** @brief Takes an input Q15.16 fixed point binary string and converts it to its signed float form.
 *
 *  First checks the sign bit: 
 *  If it is '0', ignores it as it doesn't add to the magnitude and keeps the number positive.
 *  If it is '1', takes the magnitude of the MSB (2^15), and subtracts it from the total, 
 *  then adds the rest of the '1's in the string to get its value, as it is a two's complement number.
 *
 *  Adds the ones the same way as fixedBinaryToFloat():
 *  Starts at the second bit (2^14 spot), and initializes power at 14. Checks each bit from left to right.
 *  
 *  Checks each bit as follows:
 *  If there is a '1' in the bit, adds 2^power to the result (e.g. '1' in the 5th bit would be 1 * 2^11).
 *  If there is a '0' in the bit, doesn't change the valeu fo the string, so just decreases the power and
 *  moves over to the next bit.
 *  Note: if there is a '.', simply ignores it and goes to the next bit without decreasing the power.
 *
 *  Goes until the LSB of the Q15.16 string (2^-16) spot, checking the same thing.
 *
 *  @param input The Q15.16 input string to be checked to be converted to a signed float.
 *  @return The signed float equivalent of the input binary string.
*/

float fixedSignBinaryToFloat(char *input) {
    float res = 0;
    // Check sign bit
    if (input[0] == '1') {
        res -= pow(2, 15);
    }

    // fixedBinaryToFloat() algorithm for the remaining bits
    int power = 14;
    for (int i = 1; i < strlen(input); i++) {
        if (input[i] == '1') {
            res += pow(2, power);
            power--;
        } else if (input[i] == '0') {
            power--;
        }
    }
    return res;
}

/** @brief Takes an input signed float number and converts it to its single-precision IEEE754 floating point equivalent.
 *
 *  Sign bit:
 *  First, checks the sign bit. If the floatNumber is negative, adds a 1 to the sign bit and turns the
 *  floatNumber to positive. If the floatNumber is positive, adds a 0 to the sign bit and moves on.
 *
 *  Exponent:
 *  Next, normalizes the number in base 2 format. If the floatNumber is greater than 2, reduces it to be
 *  greater than 1 and less than 2, calculating its power in the process (each division of 2 adds 1 to power).
 *  If the floatNumber is less than 1, multiplies it by 2 until it's greater than 1 and less than 2 
 *  (each multiplication of 2 subtracts 1 from power).
 *  Next, adds bias constant (127 in this case), and converts the power to an 8-bit binary string, then stores it in the IEEE754 string.
 * 
 *  Mantissa:
 *  After the number has been normalized, we already have the fraction part, which is in floatNumber after we subtract 1 from it
 *  For the remaining 23 bits, does the fraction to binary algorithm over and over, while inserting the results ('0' or '1'), 
 *  into the mantissa part of the string.
 *
 *  @param floatNumber The signed float number to be converted to IEEE754.
 *  @return The IEEE754 floating point equivalent of floatNumber as a 32-bit binary string.
*/

char* floatingToIEEE754Binary(float floatNumber) {
    char* result = (char*) calloc(SIZE_REF-1, sizeof(char));

    // Check sign bit part
    if (floatNumber < 0) {
        result[0] = '1';
        floatNumber *= -1;
    } else {
        result[0] = '0';
    }

    // Normalize number in base 2 format
    int power = 0;
        // For positive powers
    while (floatNumber >= 2) {
        floatNumber /= 2;
        power++;
    }
        // For negative powers
    while (floatNumber < 1) {
       floatNumber *= 2;
       power--;
    }
    floatNumber -= 1;
    power += 127;

    // Getting exponent as part of resultant string.
    char* exponent = decimalToBinary(power);
    char* storedExp = uextendBinary(exponent, 9); // make exponent 8 bits
    free(exponent);
    for (int i = 1; i < 9; i++) {
        result[i] = storedExp[i-1];
    }
    free(storedExp);
    
    // Adding mantissa
    for (int i = 9; i < 32; i++) {
        floatNumber *= 2;
        if (floatNumber >= 1) {
            result[i] = '1';
            floatNumber -= 1;
        } else {
            result[i] = '0';
        }
    }
    return result;
}

/** @brief Takes an input single-precision IEEE754 floating point string and converts it to its equivalent float number.
 *
 *  Calculates the sign bit, exponent, and mantissa, and does the formula at the end:
 *  Formula: (-1)^sign * (1 + fraction) * 2^(actual exponent)
 * 
 *  Sign bit:
 *  First, checks the sign bit. If the first bit is '1', sign is 1. If the first bit is '0', sign is 0.
 *
 *  Exponent:
 *  Next, gets the exponent part of the string into a temporary string, to convert it from binary to decimal.
 *  Since this string was the stored exponent value, we must subtract the bias constant (127 in this case) to
 *  get our result. This is our 'actual exponent' value.
 * 
 *  Mantissa:
 *  For the remaining 23 bits, an algorithm similar to fixedBinaryToFloat()'s is used.
 *  The power starts at -1 (as 2^-1 is first bit for fraction part). 
 *  If the bit is '1', adds 2^power to the fraction and reduces power by 1. 
 *  If the bit is '0', adds nothing and reduces power by 1.
 *
 *  After all of this, does the formula specified at the top of the function description to compute the
 *  float number.
 *
 *  @param input The input single-precision IEEE754 floating point string.
 *  @return The float number equivalent of the input string as a float.
*/

float BinaryIEEE754toFloat(char *input) {
    int sign = 0, expo = 0;
    float fraction = 0;

    // Get sign
    if (input[0] == '1') {
        sign = 1;
    } else {
        sign = 0;
    }

    // Get expo
    char* temp = (char*) calloc(9, sizeof(char));
    for (int i = 0; i < 8; i++) {
        temp[i] = input[i+1];
    }
    expo = binaryToDecimal(temp);
    expo -= 127;
    free(temp);

    // Get fraction
    int power = -1;
    for (int i = 9; i < 32; i++) {
        if (input[i] == '1') {
            fraction += pow(2, power);
        }
        power--;
    }

    float res = pow(-1, sign) * (1 + fraction) * pow(2, expo);
    return res;
}