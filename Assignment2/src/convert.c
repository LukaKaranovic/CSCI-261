#include <string.h>
#include <math.h> 
#include <stdlib.h>
#include <ctype.h>
#include "../include/convert.h"
#include <stdio.h>
#define SIZE_REF 33


// Reused functions from Assignment1, for explanations, please refer to Assignment1/src/convert.c

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

char* reverse(char* other) { 
    char* reversedString = (char*) calloc(strlen(other) + 1, sizeof(char));
    reversedString[strlen(other)] = '\0';
    for (int i = 0; i < strlen(other); i++) {
        reversedString[i] = other[strlen(other) - i - 1];
    }
    return reversedString;
}

int isRadix(char *other, int radix) {
    for (int i = 0; i < strlen(other); i++) {
        if (charToNumber(other[i]) >= radix) {
            return 0;
        }
    }
    return 1;
}

// Extends unsigned binary numbers to 32 bits.
char* uextendBinary(char *bin) {
    char* extendedStr = (char*) calloc(SIZE_REF, sizeof(char));
    extendedStr[32] = '\0';
    for (int i = 0; i < (32 - strlen(bin)); i++) {
        extendedStr[i] = '0';
    }
    for (int j = 0; j < strlen(bin); j++) {
        extendedStr[j + (32 - strlen(bin))] = bin[j];
    }
    return extendedStr;
}

char* twosComplement(int num) {
    char* result = onesComplement(num);
    if (num < 0) {
        char* twosComp = uaddBinary(result, "1"); 
        free(result);
        return twosComp;
    } 
    return result;
}

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
    free(binary);
    return temp;
}   

/** @brief Converts a given unsigned binary string to its decimal equivalent.
 *
 *  Uses charToNumber to calculate the value of the current digit. The value is multiplied 
 *  by the current n-digit value 2^n, and is added to the result.
 *  Note, if the digit value is 0, the value added is 0 * 2^n, meaning 0's won't be added.
 *
 *  @param other The string of the passed number.
 *  @return The unsigned decimal value of the given unsigned binary string.
*/

int binaryToDecimal(char *other) {
    // Sanity check to see if other is within valid radix.
    if (isRadix(other, 2) == 0) {
        printf("The number uses symbols that are not in the inputted radix.");
        return -1;
    }

    int result = 0;
    int power = 0;

    for (int i = strlen(other) - 1; i >= 0; i--) {
        int currentDigit = charToNumber(other[i]);
        result += (currentDigit * pow(2, power));
        power++;
    }

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
        result = binaryToDecimal(temp);
        char* onesComp = onesComplement(result);
        result = binaryToDecimal(onesComp);
        result += (-1 * pow(2, strlen(bNum)-1)); // Flips it to negative and the correct decimal.
        free(onesComp);
    } else {
        result = binaryToDecimal(bNum);
    }
    free(temp);
    return result;
}

/** @brief Adds two unsigned 32-bit binary strings together, returning their sum as an unsigned 32-bit binary string.
 *
 *  Starting from the least significant bit (end of the binary string), the numbers are added bit by bit. 
 *  Each bit addition keeps track of the carryIn and carryOut numbers. The sum is calculated by
 *  summing the current bit values x and y with the carryIn number, and finding the remainder (modulo 2).
 *  The sum bit is added to the resultant string addNum. The carryOut is 1 if the sum was greater than or equal to 2, 
 *  and 0 otherwise. The carryOut becomes the new carryIn for the next bit.
 *
 *  If non 32-bit binary strings are passed, the function will extend both strings to 32 bits.
 *
 *  @param num1 The first binary string to be added.
 *  @param num2 The second binary string to be added.
 *  @return The resulting binary string as a sum of num1 and num2.
*/   

char* uaddBinary(char* num1, char* num2) {
    // Extending strings incase improper binary string lengths are used.
    char* bNum1 = uextendBinary(num1);
    char* bNum2 = uextendBinary(num2);
    
    char* addNum = (char*) calloc(SIZE_REF, sizeof(char));
    addNum[32] = '\0';
    int carryIn = 0;
    int carryOut = 0;

    for (int i = 31; i >= 0; i--) {
        // Maintain carryIn and carryOut
        carryIn = carryOut;
        carryOut = 0;

        // Find values for current bit (0 or 1)
        int x = charToNumber(bNum1[i]);
        int y = charToNumber(bNum2[i]);

        // Calculate sum and carryOut
        int sum = (x + y + carryIn) % 2;
        addNum[i] = numberToLetter(sum);
        carryOut = (x + y + carryIn) / 2;
    }

    free(bNum1);
    free(bNum2);

    return addNum;
}

/** @brief Subtracts two unsigned 32-bit binary strings from each other, returning their difference as an unsigned 32-bit binary string.
 *
 *  Starting from the least significant bit (end of the binary string), the numbers are subtracted bit by bit. 
 *  Each bit subtraction keeps track of the borrow and difference numbers. The difference is calculated by
 *  subtracting the current bit values x and y with the current borrow. If the difference is negative, that means that
 *  borrowing is required, so the difference increases by 2 and borrow gets set to 1 to simulate borrowing from the next bit (from the left).
 *  The difference, now 0 or 1 (after borrow if needed), is added to the correct bit of the resultant string subNum.
 *  If no borrowing occured for the current bit subtraction, the borrow is set back to 0.
 *
 *  If non 32-bit binary strings are passed, the function will extend both strings to 32 bits.
 *
 *  @param num1 The first binary string as the minuend.
 *  @param num2 The second binary string as the subtractend.
 *  @return The resulting binary string as a difference of num1 and num2.
*/   

char* usubBinary(char* num1, char* num2) {
    char* subNum = (char*) calloc(SIZE_REF, sizeof(char));
    subNum[32] = '\0';
    char* bNum1 = uextendBinary(num1);
    char* bNum2 = uextendBinary(num2);
    int difference;
    int borrow = 0;

    for (int i = 31; i >= 0; i--) {
        // Find values for current bit (0 or 1)
        int x = charToNumber(bNum1[i]);
        int y = charToNumber(bNum2[i]);

        // Calculate difference
        difference = x - y - borrow;

        // Does borrowing for specific bit if needed
        if (difference < 0) {
            difference += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        subNum[i] = numberToLetter(difference);
    }

    free(bNum1);
    free(bNum2);
    return subNum;
}

/** @brief Adds two unsigned 32-bit binary strings together, returning the carry flag.
 *
 *
 *  Starting from the least significant bit (end of the binary string), the numbers are added bit by bit. 
 *  Each bit addition keeps track of the carryIn and carryOut numbers. The sum is calculated by
 *  summing the current bit values x and y with the carryIn number, and finding the remainder (modulo 2).
 *  The sum bit is added to the resultant string addNum. The carryOut is 1 if the sum was greater than or equal to 2, 
 *  and 0 otherwise. The carryOut becomes the new carryIn for the next bit.
 *
 *  The carry flag should return the carryOut value at the end of the addition as if the final carryOut value is 1, that means the result crosses the range of 32-bit
 *  numbers (0 and 2^32 - 1). If the final carryOut is 0, that means there is no carry value that goes past the range of 32-bit binary numbers.
 *
 *  If non 32-bit binary strings are passed, the function will extend both strings to 32 bits.
 *
 *  @param num1 The first binary string to be added.
 *  @param num2 The second binary string to be added.
 *  @return The carry flag value after the addition of num1 and num2.
*/   

int uaddCarry(char* num1, char* num2) {
    // Same logic as uaddBinary, but return the final carryOut value.    
    char* bNum1 = uextendBinary(num1);
    char* bNum2 = uextendBinary(num2);
    
    char* addNum = (char*) calloc(SIZE_REF, sizeof(char));
    addNum[32] = '\0';
    int carryIn = 0;
    int carryOut = 0;

    for (int i = 31; i >= 0; i--) {
        carryIn = carryOut;
        carryOut = 0;

        int x = charToNumber(bNum1[i]);
        int y = charToNumber(bNum2[i]);

        int sum = (x + y + carryIn) % 2;
        addNum[i] = numberToLetter(sum);
        carryOut = (x + y + carryIn) / 2;
    }

    free(bNum1);
    free(bNum2);
    free(addNum);

    // If carryOut is 1, it has crossed the bit boundary, meaning overflow
    return carryOut;
}

/** @brief Subtracts two unsigned 32-bit binary strings from each other, returning the carry flag.
 *
 *  Starting from the least significant bit (end of the binary string), the numbers are subtracted bit by bit. 
 *  Each bit subtraction keeps track of the borrow and difference numbers. The difference is calculated by
 *  subtracting the current bit values x and y with the current borrow. If the difference is negative, that means that
 *  borrowing is required, so the difference increases by 2 and borrow gets set to 1 to simulate borrowing from the next bit (from the left).
 *  The difference, now 0 or 1 (after borrow if needed), is added to the correct bit of the resultant string subNum.
 *  If no borrowing occured for the current bit subtraction, the borrow is set back to 0.
 *  
 *  The carry flag should return 0 if borrowing has occured on the last bit of subtraction (borrowing from out of bit range) because the result is negative 
 *  (because unsigned subtraction can't have negative result). The carry flag returns 1 if there was no borrowing from outside of the bit range, 
 *  meaning the result is unsigned and positive.
 *
 *  If non 32-bit binary strings are passed, the function will extend both strings to 32 bits.
 *
 *  @param binaryNumber1 The first binary string as the minuend.
 *  @param binaryNumber2 The second binary string as the subtractend.
 *  @return The carry flag value after the subtraction of num2 from num1.
*/   

int usubBorrow(char *binaryNumber1, char *binaryNumber2) {
    // Same logic as usubBinary, but return the carry flag corresponding to the borrow value.    
    char* subNum = (char*) calloc(SIZE_REF, sizeof(char));
    subNum[32] = '\0';
    char* bNum1 = uextendBinary(binaryNumber1);
    char* bNum2 = uextendBinary(binaryNumber2);
    int difference;
    int borrow = 0;

    for (int i = 31; i >= 0; i--) {

        int x = charToNumber(bNum1[i]);
        int y = charToNumber(bNum2[i]);

        difference = x - y - borrow;

        if (difference < 0) {
            difference += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        subNum[i] = numberToLetter(difference);
    }

    free(bNum1);
    free(bNum2);
    free(subNum);

    // If no borrowing from outside bit range occured, carry flag is 1
    if (borrow == 0) {
        return 1;
    } 
    // Borrowing from outside bit range occured, carry flag is 0
    return 0;
}

/** @brief Subtracts two signed 32-bit binary strings from each other, returning their difference as an unsigned 32-bit binary string.
 *
 *  First, the function multiplies the second number by -1 and returns its two's complement equivalent. This is like converting an equation A - B to A + (-B).
 *  Then the function extends both strings appropriately and performs addition on A and -B, returning what would be the same as subtracting B from A (A - B).
 *
 *  Signed addition logic (to do A + (-B)):
 *  Starting from the least significant bit (end of the binary string), the numbers are added bit by bit. 
 *  Each bit addition keeps track of the carryIn and carryOut numbers. The sum is calculated by
 *  summing the current bit values x and y with the carryIn number, and finding the remainder (modulo 2).
 *  The sum bit is added to the resultant string addNum. The carryOut is 1 if the sum was greater than or equal to 2, 
 *  and 0 otherwise. The carryOut becomes the new carryIn for the next
 *
 *  If non 32-bit binary strings are passed, the function will extend both strings to 32 bits.
 *
 *  @param binaryNumber1 The first binary string as the minuend.
 *  @param binaryNumber2 The second binary string as the subtractend.
 *  @return The resulting binary string as a difference of binaryNumber1 and binaryNumber2.
*/   

char *subSignedBinary(char *binaryNumber1, char *binaryNumber2) {
    // Converts second number to negative version
    int num2 = twosComplementDecimal(binaryNumber2) * -1;
    char* temp = twosComplement(num2);

    // extendBinary helper function works for both pos and neg numbers (see function below).
    char* bNum1 = extendBinary(binaryNumber1);
    char* bNum2 = extendBinary(temp);

    free(temp);
    char* result = addSignedBinary(bNum1, bNum2);
    free(bNum1);
    free(bNum2);
    return result;
}

/** @brief Converts a given unsigned decimal number to an equivalent unsigned binary string.  
 *
 *  Uses numberToLetter to find the symbol of the current digit. The symbol is added
 *  to the end of the string. The string is then reversed as the last symbols inserted are the biggest digits
 *  (because of repeated division).
 *
 *  @param dnumber The decimal number to be converted.
 *  @return The unsigned binary string of the converted number value.
*/

char* udecimalToBinary(unsigned int dnumber) {

    char* result = (char*) calloc(SIZE_REF, sizeof(char));
    int i = 0;

    // Algorithm like our division table we use to convert on paper.
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

/** @brief Extends a signed binary string that is less than 32 bits to 32 bits.
 *
 *  If the number is positive (sign bit is 0): 
 *  Adds 0s until the actual binary number starts, then copies it from the passed binary string 'bin'.
 *  Adding the actual number at the end ensures it is the same value as before, as the 0s before will not change
 *  the numerical value of the binary string.
 *
 *  If the number is negative (sign bit is 1): 
 *  Adds 1s until the actual binary number starts, then copies it from the passed binary string 'bin'.
 *  Adding the actual number at the end ensures it is the same value as before, as the 1s before will not change
 *  the numerical value of the binary string (in two's complement).
 *
 *  @param bin The binary string of the passed number.
 *  @return The binary string of the passed number extended to 32 bits.
*/

char* extendBinary(char *bin) { 
    char* extendedStr = (char*) calloc(SIZE_REF, sizeof(char));
    extendedStr[32] = '\0';

    // Extension if number is positive.
    if (charToNumber(bin[0]) == 0) {
        for (int i = 0; i < (32 - strlen(bin)); i++) {
            extendedStr[i] = '0';
        }
        for (int j = 0; j < strlen(bin); j++) {
            extendedStr[j + (32 - strlen(bin))] = bin[j];
        }
    // Extension if number is negative.
    } else if (charToNumber(bin[0]) == 1) {
        for (int i = 0; i < (32 - strlen(bin)); i++) {
            extendedStr[i] = '1';
        }
        for (int j = 0; j < strlen(bin); j++) {
            extendedStr[j + (32 - strlen(bin))] = bin[j];
        }
    }

    return extendedStr;
}

/** @brief Adds two signed 32-bit binary strings together, returning their sum as a signed 32-bit binary string.
 *
 *  Starting from the least significant bit (end of the binary string), the numbers are added bit by bit. 
 *  Each bit addition keeps track of the carryIn and carryOut numbers. The sum is calculated by
 *  summing the current bit values x and y with the carryIn number, and finding the remainder (modulo 2).
 *  The sum bit is added to the resultant string addNum. The carryOut is 1 if the sum was greater than or equal to 2, 
 *  and 0 otherwise. The carryOut becomes the new carryIn for the next bit.
 *
 *  If non 32-bit binary strings are passed, the function will extend both strings to 32 bits.
 *
 *  @param binaryNumber1 The first binary string to be added.
 *  @param binaryNumber2 The second binary string to be added.
 *  @return The resulting binary string as a sum of binaryNumber1 and binaryNumber2.
*/   

char* addSignedBinary(char* binaryNumber1, char* binaryNumber2) {
    // Extending strings incase improper binary string lengths are used.
    char* bNum1 = extendBinary(binaryNumber1);
    char* bNum2 = extendBinary(binaryNumber2);

    
    char* addNum = (char*) calloc(SIZE_REF, sizeof(char));
    addNum[32] = '\0';
    int carryIn = 0;
    int carryOut = 0;

    for (int i = 31; i >= 0; i--) {
        // Maintain carryIn and carryOut
        carryIn = carryOut;
        carryOut = 0;

        // Find values for current bit (0 or 1)
        int x = charToNumber(bNum1[i]);
        int y = charToNumber(bNum2[i]);

        // Calculate sum and carryOut
        int sum = (x + y + carryIn) % 2;
        addNum[i] = numberToLetter(sum);
        carryOut = (x + y + carryIn) / 2;
    }

    free(bNum1);
    free(bNum2);

    return addNum;
}

/** @brief Adds two signed 32-bit binary strings together, returning the overflow flag value from adding them.
 *
 *  Starting from the least significant bit (end of the binary string), the numbers are added bit by bit. 
 *  Each bit addition keeps track of the carryIn and carryOut numbers. The sum is calculated by
 *  summing the current bit values x and y with the carryIn number, and finding the remainder (modulo 2).
 *  The sum bit is added to the resultant string addNum. The carryOut is 1 if the sum was greater than or equal to 2, 
 *  and 0 otherwise. The carryOut becomes the new carryIn for the next bit.
 *
 *  The overflow flag returns 1 if the carryIn and carryOut values differ on the sign bit. If the carryIn and carryOut on the sign bit 
 *  equal each other, no overflow has occured. This is because carryIn is the carry value going into the sign bit, and carryOut is the carry value 
 *  going out of the sign bit.
 *
 *  If non 32-bit binary strings are passed, the function will extend both strings to 32 bits.
 *
 *  @param num1 The first binary string to be added.
 *  @param num1 The second binary string to be added.
 *  @return The overflow flag from summing num1 and num2.
*/   

int findAddOverflow(char *num1, char *num2) {
    char* bNum1 = extendBinary(num1);
    char* bNum2 = extendBinary(num2);
    
    char* addNum = (char*) calloc(SIZE_REF, sizeof(char));
    addNum[32] = '\0';
    int carryIn = 0;
    int carryOut = 0;

    for (int i = 31; i >= 0; i--) {
        carryIn = carryOut;
        carryOut = 0;

        int x = charToNumber(bNum1[i]);
        int y = charToNumber(bNum2[i]);

        int sum = (x + y + carryIn) % 2;
        addNum[i] = numberToLetter(sum);
        carryOut = (x + y + carryIn) / 2;
    }

    free(bNum1);
    free(bNum2);
    free(addNum);

    // Carry value changes in sign bit.
    if (carryIn != carryOut) {
        return 1;
    }
    // Carry value doesn't change in sign bit.
    return 0;
}

/** @brief Subtracts two signed 32-bit binary from each other, returning the overflow flag value from subtracting them.
 *
 *  First, the function multiplies the second number by -1 and returns its two's complement equivalent. This is like converting an equation A - B to A + (-B).
 *  Then the function extends both strings appropriately and performs addition on A and -B, returning what would be the same as subtracting B from A (A - B).
 *
 *  Signed addition logic (to do A + (-B)):
 *  Starting from the least significant bit (end of the binary string), the numbers are added bit by bit. 
 *  Each bit addition keeps track of the carryIn and carryOut numbers. The sum is calculated by
 *  summing the current bit values x and y with the carryIn number, and finding the remainder (modulo 2).
 *  The sum bit is added to the resultant string addNum. The carryOut is 1 if the sum was greater than or equal to 2, 
 *  and 0 otherwise. The carryOut becomes the new carryIn for the next
 *
 *  First, if num1 or num2 is 0, then there is no overflow that occured from subtraction, since both input integers should be in range already. To find the overflow, we 
 *  calculate three values: the sign of num1, the sign of num2, and the sign of the result. If num1 is positive, num2 is negative, and result is negative, then overflow has 
 *  occured as the result should be positive. If num1 is negative, num2 is positive, and result is positive, then overflow has occured as the result should be negative. The 
 *  overflow flag is set to 1 for these cases. Otherwise, overflow flag is 0 as no overflow occured.
 *
 *  If non 32-bit binary strings are passed, the function will extend both strings to 32 bits.
 *
 *  @param num1 The first binary string to be added.
 *  @param num1 The second binary string to be added.
 *  @return The overflow flag from subtracting num2 from num1.
*/   

int findSubOverflow(char *num1, char *num2) {
    // If there is a 0 in the equation there shouldn't be subtraction overflow unless an invalid integer value (not in range) is passed.
    if (binaryToDecimal(num1) == 0 || binaryToDecimal(num2) == 0) {
        return 0;
    }

    char* bNum1 = extendBinary(num1);
    int dnum2 = twosComplementDecimal(num2) * -1;
    char* temp = twosComplement(dnum2);
    char* bNum2 = extendBinary(temp);
    free(temp);
    char* result = addSignedBinary(bNum1, bNum2);

    int sign = charToNumber(result[0]);
    int n1sign = charToNumber(num1[0]);
    int n2sign = charToNumber(num2[0]);

    free(bNum1);
    free(bNum2);
    free(result);


    // If num1 is pos and num2 is neg, then result must be pos if no overflow.
    if (n1sign == 0 && n2sign == 1) {
        if (sign == 1) {
            return 1;
        }
        return 0;
    // If num1 is neg and num2 is pos, then result must be neg if no overflow.
    } else if (n1sign == 1 && n2sign == 0) {
        if (sign == 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}