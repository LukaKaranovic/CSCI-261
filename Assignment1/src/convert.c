/** 
 * @file convert.c
 * @author Luka Karanovic, 665778833, F24N01, CSCI 261, VIU
 * @version 1.0.0
 * @date September 12, 2024
*/

#ifndef CONVERT_FUNCS_H
#define CONVERT_FUNCS_H

#include "../include/convert.h"
#include <string.h>
#include <math.h> 
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#define SIZE_REF 33

/** @brief Converts a given character symbol (number or letter) to its decimal number value.
 *
 *  Uses ASCII table values to convert a character to its proper int value. For digits 0-9, we subtract 48 
 *  because that is the ASCII value of '0'. For letters, we subtract the ASCII value of 'A' and add 10.
 *
 *  @param x The character symbol to be converted to an integer.
 *  @return The decimal number value the symbol represents.
*/

int charToNumber(char x) {
    int number = x;
    if (number >= 48 && number <= 57) {
        return number - 48;
    }
    number = toupper(x) - 'A';
    number += 10; 
    return number;
}

/** @brief Converts a given decimal number to its character symbol (number or letter) value.
 *
 *  Uses ASCII table values to convert a number to its proper character symbol. For digits 0-9, we add 48 
 *  because that is the ASCII value of '0'. For letters, we add the ASCII value of 'A' and subtract 10.
 *
 *  @param number The integer to be converted to a character symbol.
 *  @return The character symbol that represents the number.
*/

char numberToLetter(int number) {
    char letter;
    if (number <= 9) {
        letter = 48 + number;
    } else {
        letter = 'A' + (number - 10); 
    }
    return letter;
}

/** @brief Converts a given number of any radix to its decimal equivalent.
 *
 *  Uses charToNumber to calculate the value of the current digit. The value is multiplied 
 *  by the current n-digit value radix^n, and is added to the result.
 *
 *  @param radix The radix of the passed number other.
 *  @param other The string of the passed number.
 *  @return The decimal value of any number of any radix.
*/

int otherToDecimal(int radix, char *other) {
    // Sanity check to see if other is within valid radix.
    if (isRadix(other, radix) == 0) {
        printf("The number uses symbols that are not in the inputted radix.");
        return -1;
    }

    int result = 0;
    int power = 0;

    for (int i = strlen(other) - 1; i >= 0; i--) {
        int currentDigit = charToNumber(other[i]);
        result += (currentDigit * pow(radix, power));
        power++;
    }

    return result;
}

/** @brief Converts a given decimal number to a number of another radix.       
 *
 *  Uses numberToLetter to find the symbol of the current digit. The symbol is added
 *  to the end of the string. The string is then reversed as the last symbols inserted are the biggest digits
 *  (because of repeated division).
 *
 *  @param radix The radix of the passed number dnumber.
 *  @param dnumber The decimal number to be converted.
 *  @return The string of the converted number value with the target radix.
*/

char* decimalToOther(int dnumber, int radix) { 
    char* result = (char*) calloc(SIZE_REF, sizeof(char));
    int i = 0;

    // Algorithm like our division table we use to convert on paper.
    for (i = 0; dnumber > 0; ++i) {
        int remainder = dnumber % radix; 
        result[i] = numberToLetter(remainder); 
        dnumber /= radix;
    }
    result[i] = '\0';

    char* temp = reverse(result);
    free(result);
    return temp;
}

/** @brief Reverses a given string,
 *
 *  @param other The string to be reversed.
 *  @return The new reversed string.
*/

char* reverse(char* other) { 
    char* reversedString = (char*) calloc(strlen(other) + 1, sizeof(char));
    
    reversedString[strlen(other)] = '\0';

    for (int i = 0; i < strlen(other); i++) {
        reversedString[i] = other[strlen(other) - i - 1];
    }
   
    return reversedString;

}

/** @brief Checks if a given number is within a certain radix.
 *
 *  Uses charToNumber to calculate the value of the current digit. Compares this digit with the radix,
 *  if it is greater than or equal to the radix, then the symbol is not used within the passed radix and isRadix is not true.
 *
 *  @param radix The radix of the passed number other.
 *  @param other The string of the passed number.
 *  @return 0 if the number isn't under the passed radix and 1 if the number is within the passed radix.
*/

int isRadix(char *other, int radix) {
    for (int i = 0; i < strlen(other); i++) {
        if (charToNumber(other[i]) >= radix) {
            return 0;
        }
    }

    return 1;
}

/** @brief Extends a string that is less than 32 bits to 32 bits.
 *
 *  Adds 0s until the actual binary number starts, then copies it from the passed binary string 'bin'.
 *  Adding the actual number at the end ensures it is the same value as before, as the 0s before will not change
 *  the numerical value of the binary string.
 *
 *  @param bin The string of the passed number.
 *  @return The string of the passed number extended to 32 bits.
*/

char* uextendBinary(char *bin) {

    char* extendedStr = (char*) calloc(SIZE_REF, sizeof(char));
    extendedStr[32] = '\0';

    for (int i = 0; i < (32 - strlen(bin)); i++) {
        extendedStr[i] = '0';
    }

    for (int j = 0; j < strlen(bin); j++) {
        extendedStr[j + (32 - strlen(bin))] = bin[j];
    }

    free(bin);
    return extendedStr;
}

/** @brief Converts a given decimal number to its equivalent number in binary.
 *
 *  Calls the decimalToOther function with radix 2.
 *
 *  @param dnumber The decimal number to be converted.
 *  @return The binary string of the passed number value.
*/

char* decimalToBinary(int dnumber) {
    return decimalToOther(dnumber, 2);
}

/** @brief Converts a given decimal number to its equivalent number in binary using the signed magnitude system.
 *
 *  Calls the decimalToBinary function on the absolute value of the number. This is because decimalToOther doesn't work with negative numbers.
 *  The string is then extended to 32 bits as specific and if the original number was negative, the first bit is changed to a '1' to ensure it is
 *  the correct sign magnitude.
 *
 *  @param num The decimal number to be converted.
 *  @return The signed magnitude binary string of the passed number value.
*/

char* signMagnitude(int num) {
    char* result = uextendBinary(decimalToBinary(abs(num)));
    if (num < 0) {
        result[0] = '1';
    }
    
    return result;
}

/** @brief Converts a given decimal number to its equivalent number in binary using the ones complement system.
 *
 *  Calls the decimalToBinary function on the absolute value of the number. This is because decimalToOther doesn't work with negative numbers.
 *  The string is then extended to 32 bits as specific and if the original number was negative, every bit's value is flipped (0 to 1 and 1 to 0).
 *
 *  @param num The decimal number to be converted.
 *  @return The ones complement binary string of the passed number value.
*/

char* onesComplement(int num) {
    char* binary = decimalToBinary(abs(num));
    char* temp = uextendBinary(binary);
    if (num < 0) {
        for (int i = 0; i < strlen(temp); i++) {
            if (temp[i] == '0') {
                temp[i] = '1';
            } else {
                temp[i] = '0';
            }
        }
    }
    return temp;
}   

/** @brief Converts a given decimal number to its equivalent number in binary using the twos complement system.
 *
 *  Calls the decimalToBinary function on the absolute value of the number. This is because decimalToOther doesn't work with negative numbers.
 *  The string is then extended to 32 bits as specific and if the original number was negative, every bit's value is flipped (0 to 1 and 1 to 0) with the
 *  ones complement function. To ensure the binary string is in twos complement, we add a 1 using our uaddBinary function to add two binary strings together.
 *
 *  @param num The decimal number to be converted.
 *  @return The twos complement binary string of the passed number value.
*/    
    
char* twosComplement(int num) {
    char* result = onesComplement(num);

    if (num < 0) {
        // Making a custom 32-bit binary string of value 1 to add.
        char* one = (char*) calloc(SIZE_REF, sizeof(char));
        one[32] = '\0';
        for (int i = 0; i < 31; i++) {
            one[i] = '0';
        }
        one[31] = '1';

        result = uaddBinary(result, one); 
        free(one);
    } 
    return result;
}

/** @brief Adds two 32-bit binary strings together, returning their sum as a 32-bit binary string.
 *
 *  Starting from the least significant bit (end of the binary string), the numbers are added. There are three main cases defined in the main if-else statement.
 *  1) num1 and num2 both hold a 1 in the same index.
 *  2) exactly 1 of num1 or num2 hold a 1 in the same index.
 *  3) num1 and num2 both hold a 0 in the same index.
 *  Each of these cases depend on the already existing carry value (whether it is 0 or 1), which is handled in the nested if-else statements.
 *  If non 32-bit binary strings are passed, the function will return a null string and prompt the user with an error message.
 *
 *  @param num1 The first binary string to be added.
 *  @param num2 The second binary string to be added.
 *  @return The resulting binary string as a sum of num1 and num2.
*/   

char* uaddBinary(char *num1, char *num2) {
    // Error handling incase improper binary string lengths are used.
    if (strlen(num1) != 32 || strlen(num2) != 32) {
        printf("Binary strings are not of the appropriate length (32 bits).");
        return "00000000000000000000000000000000"; // Returns 0
    }
    
    char* addNum = (char*) calloc(SIZE_REF, sizeof(char));
    addNum[32] = '\0';
    int carry = 0;


    for (int i = 31; i >= 0; i--) {
        // Case 1: num1 and num2 both hold a 1 in the same index
        if (num1[i] == '1' && num2[i] == '1') {
            if (carry == 0) {
                addNum[i] = '0';
                carry = 1; 
            } else if (carry == 1) {
                addNum[i] = '1';
            }
        // Case 2: exactly 1 of num1 or num2 hold a 1 in the same index
        } else if ((num1[i] == '1' && num2[i] == '0') || (num1[i] == '0' && num2[i] == '1')) {
            if (carry == 1) {
                addNum[i] = '0';
            } else if (carry == 0) {
                addNum[i] = '1';
            }
        // Case 3: num1 and num2 both hold a 0 in the same index
        } else if (num1[i] == '0' && num2[i] == '0') {
            if (carry == 0) {
                addNum[i] = '0';
            } else if (carry == 1) {
                addNum[i] = '1';
                carry = 0;
            }
        }
    }
    free(num1);

    return addNum;
}

/** @brief Converts a binary string using the signed magnitude system into its equivalent decimal value.
 *
 *  Initially copies the passed string bNum to a temporary string. The first bit of the binary string is analyzed to see
 *  the sign of the number (positive or negative). If the string is negative, sign gets set to -1 and the first bit is then set to 0 (positive).
 *  The new positive temporary string is converted to its decimal value and then is multipled by its sign.
 *
 *  @param bNum The binary string to be converted.
 *  @return The decimal value of the signed magnitude binary string.
*/  

int signMagnitudeDecimal(char* bNum) {  
    char* temp = (char*) calloc(strlen(bNum)+1, sizeof(char));
    temp[strlen(bNum)] = '\0';
    strcpy(temp, bNum);

    int sign = 1;
    int result = otherToDecimal(2, temp);

    // Flips sign to negative if the first bit is a 1.
    if (temp[0] == '1') {
        sign = -1;
        temp[0] = '0';
        result = otherToDecimal(2, temp) * sign; 
    }
    free(temp);
    return result;
}

/** @brief Converts a binary string using the ones complement system into its equivalent decimal value.
 *
 *  Initially copies the passed string bNum to a temporary string. The first bit of the binary string is skipped in the copying process.
 *  The temporary string is then converted into its decimal equivalent. However, if bNum's first bit is 1, the ones complement of temp is taken and then is converted
 *  to decimal (high postiive value). Then, -1 * 2^(length-1) is added to the decimal value, and a 1 is added to ensure the correct value is returned (because there is no -0). 
 *  This algorithm works for all ones complement system numbers.
 *
 *  @param bNum The binary string to be converted.
 *  @return The decimal value of the ones complement binary string.
*/  

int onesComplementDecimal(char* bNum) {
    int result;
    char* temp = (char*) calloc(SIZE_REF, sizeof(char));
    temp[32] = '\0';
    for (int i = 0; i < (strlen(bNum) - 1); i++) {
        temp[i] = bNum[i+1]; // Intentionally not copying first bit of bNum.
    }

    if (bNum[0] == '1') {
        result = otherToDecimal(2, temp);
        char* onesComp = onesComplement(result);
        result = otherToDecimal(2, onesComp);
        free(onesComp);
        // Most significant bit is turned negative and added to the decimal number.
        // A 1 is added because there is no -0, so negative numbers need this adjustment.
        result += (-1 * pow(2, strlen(bNum)-1)) + 1; 
    } else {
        result = otherToDecimal(2, bNum);
    }
    free(temp);
    return result;
}

/** @brief Converts a binary string using the twos complement system into its equivalent decimal value.
 *
 *  Initially copies the passed string bNum to a temporary string. The first bit of the binary string is skipped in the copying process.
 *  The temporary string is then converted into its decimal equivalent. However, if bNum's first bit is 1, the ones complement of temp is taken and then is converted
 *  to decimal (high postiive value). Then, -1 * 2^(length-1) is added to the decimal value. Because twos complement has no -0, we don't need to add 1 
 *  to adjust the decimal value. This algorithm works for all twos complement system numbers.
 *
 *  @param bNum The binary string to be converted.
 *  @return The decimal value of the twos complement binary string.
*/  

int twosComplementDecimal(char* bNum) { 
    char* temp = (char*) calloc(SIZE_REF, sizeof(char));
    temp[32] = '\0';
    // Intentionally not copying first bit of bNum.
    for (int i = 0; i < (strlen(bNum) - 1); i++) {
        temp[i] = bNum[i+1]; 
    }

    int result;
    if (bNum[0] == '1') {
        result = otherToDecimal(2, temp);
        char* onesComp = onesComplement(result);
        result = otherToDecimal(2, onesComp);
        result += (-1 * pow(2, strlen(bNum)-1)); // Flips it to negative and the correct decimal.
        free(onesComp);
    } else {
        result = otherToDecimal(2, bNum);
    }
    free(temp);
    return result;
}

#endif

