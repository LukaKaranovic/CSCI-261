#ifndef CONVERT_FUNCS 
#define CONVERT_FUNCS 

#include "../include/convert.h"
#include <string.h>
#include <math.h> 
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#define SIZE_REF 33
#define SIZE_RES 65



// Reused functions from Assignment1/Assignment2, for explanations, please refer to past assignments. 

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

// Changed so it extends properly for any size, not just to 32 bits.

char* uextendBinary(char *bin, int size) {
    char* extendedStr = (char*) calloc(size, sizeof(char));
    for (int i = 0; i < ((size-1) - strlen(bin)); i++) {
        extendedStr[i] = '0';
    }
    for (int j = 0; j < strlen(bin); j++) {
        extendedStr[j + ((size-1) - strlen(bin))] = bin[j];
    }
    return extendedStr;
}

// Changed so it extends properly for any size, not just to 32 bits.

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

// Changed so it works for any size, as long as the two input strings are the same length.

char* uaddBinary(char* num1, char* num2) {
    int size = strlen(num1);
    char* addNum = (char*) calloc(size+1, sizeof(char));
    int carryIn = 0;
    int carryOut = 0;

    for (int i = size-1; i >= 0; i--) {
        carryIn = carryOut;
        carryOut = 0;

        int x = charToNumber(num1[i]);
        int y = charToNumber(num2[i]);

        int sum = (x + y + carryIn) % 2;
        addNum[i] = numberToLetter(sum);
        carryOut = (x + y + carryIn) / 2;
    }

    free(num1);

    return addNum;
}

// Changed so it works for any size, as long as the two input strings are the same length.

char* addSignedBinary(char* bNum1, char* bNum2) {
    int size = strlen(bNum1);

    char* addNum = (char*) calloc(size+1, sizeof(char));
    int carryIn = 0;
    int carryOut = 0;

    for (int i = size-1; i >= 0; i--) {
        carryIn = carryOut;
        carryOut = 0;

        int x = charToNumber(bNum1[i]);
        int y = charToNumber(bNum2[i]);

        int sum = (x + y + carryIn) % 2;
        addNum[i] = numberToLetter(sum);
        carryOut = (x + y + carryIn) / 2;
    }

    free(bNum1);

    return addNum;
}

/* Changed so it works for any size, as long as the two input strings are the same length. This means extend binary has to be called to 
ensure both inputs are same length for addSignedBinary call */

char *subSignedBinary(char *binaryNumber1, char *binaryNumber2) {
    int num2 = twosComplementDecimal(binaryNumber2) * -1;
    char* temp = twosComplement(num2);
    char* negNum2 = extendBinary(temp, strlen(binaryNumber1)+1);
    free(temp);
    char* result = addSignedBinary(binaryNumber1, negNum2);
    free(negNum2);
    return result;
}

char* reverse(char* other) { 
    char* reversedString = (char*) calloc(strlen(other) + 1, sizeof(char));
    for (int i = 0; i < strlen(other); i++) {
        reversedString[i] = other[strlen(other) - i - 1];
    }
    return reversedString;
}

char* decimalToBinary(unsigned int dnumber) { 
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

// Changed it so it takes any length string and extends length by 1 to add sign bit appropriately.

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

// Changed logic for handling negative numbers to not use pow function.

int twosComplementDecimal(char* bNum) { 
    int result;
    if (bNum[0] == '1') {
        char* temp = extendBinary(bNum, strlen(bNum)+1);
        for (int i = 0; i < strlen(temp); i++) {
            if (temp[i] == '0') {
                temp[i] = '1';
            } else {
                temp[i] = '0';
            }
        }
        char* one = uextendBinary("1", strlen(temp)+1);
        char* twosComp = uaddBinary(temp, one); 
        free(one);
        result = binaryToDecimal(twosComp) * -1;
        free(twosComp);
    } else {
        result = binaryToDecimal(bNum);
    }
    return result;
}

// Changed so it works for any size, as long as the two input strings are the same length.

int uaddCarry(char* num1, char* num2) {
    char* bNum1 = uextendBinary(num1, strlen(num1)+1);
    char* bNum2 = uextendBinary(num2, strlen(num2)+1);
    int size = strlen(num2);
    char* addNum = (char*) calloc(size+1, sizeof(char));
    addNum[size-1] = '\0';
    int carryIn = 0;
    int carryOut = 0;

    for (int i = size-2; i >= 0; i--) {
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

    return carryOut;
}


/** @brief Converts a given unsigned long binary string to its unsigned long decimal equivalent.
 *
 *  Starts at least significant bit and checks each bit for a 1. Each bit iteration increases the power (j) from 1 starting from 0.
 *  If a 1 is found, an unsigned long of value 1 is shifted to the left with the bitwise shift operator j bits, giving it the appropriate decimal value 
 *  for that bit. Works for up to 64-bit numbers.
 *
 *  @param result The string of the passed number.
 *  @return The unsigned long decimal value of the given unsigned binary string.
*/

unsigned long convertToDecimal(char *result) {  
    unsigned long res = 0;
    int length = strlen(result);
    int j = 0;
    for (int i = length-1; i >= 0; i--) {
        if (result[i] == '1') {
            res += 1UL << j;
        }
        j++;
    }


    return res;
}

/** @brief Converts a given signed long binary string to its signed long decimal equivalent.
 *
 *  For positive numbers:
 *  Starts at least significant bit and checks each bit for a 1. Each bit iteration increases the power (j) from 1 starting from 0.
 *  If a 1 is found, a long int of value 1 is shifted to the left with the bitwise shift operator j bits, giving it the appropriate decimal value 
 *  for that bit. Works for up to 64-bit numbers.
 *
 *  For negative numbers:
 *  Since sign bit is negative, it gets the twos complement of the negative number to get the positive equivalent. Then it follows the same logic 
 *  for positive numbers, and multiplies the result by -1 at the end (as number was originally negative).
 *
 *  @param bNum The string of the passed number.
 *  @return The signed long decimal value of the given signed long binary string.
*/

long convertToDecimalSigned(char *bNum) {
    long res = 0;
    int length = strlen(bNum);
    int j = 0;
    if (bNum[0] == '0') {
        // Can do sign bit here as it is 0 so it won't change value.
        for (int i = length-1; i >= 0; i--) {
            if (bNum[i] == '1') {
                res += 1L << j;
            }
        j++;
        }
    } else {
        char* temp = (char*) calloc(strlen(bNum)+1, sizeof(char));
        // Get twos comp of bNum
        for (int i = 0; i < strlen(bNum); i++) {
            if (bNum[i] == '0') {
                temp[i] = '1';
            } else {
                temp[i] = '0';
            }
        }
        char* one = uextendBinary("1", strlen(temp)+1);
        temp = uaddBinary(temp, one); 
        free(one);

        // Do all but sign bit.
        for (int i = length-1; i > 0; i--) {
            if (temp[i] == '1') {
                res += 1L << j;
            }
            j++;
        }
        res *= -1;
        free(temp);
    }
    return res;
}

/** @brief Converts a given unsigned binary string to its unsigned decimal equivalent.
 *
 *  Starts at least significant bit and checks each bit for a 1. Each bit iteration increases the power (j) from 1 starting from 0.
 *  If a 1 is found, an unsigned long of value 1 is shifted to the left with the bitwise shift operator j bits, giving it the appropriate decimal value 
 *  for that bit. Works for up to 32-bit numbers.
 *
 *  @param other The string of the passed number.
 *  @return The unsigned decimal value of the given unsigned binary string.
*/

unsigned int binaryToDecimal(char *other) {
    unsigned int res = 0;
    int length = strlen(other);
    int j = 0; // Keeps track of power
    for (int i = length-1; i >= 0; i--) {
        if (other[i] == '1') {
            // Unsigned long 1, shifted j bits left and converted to decimal.
            res += 1UL << j;
        }
        j++;
    }
    return res;
}

/** @brief Performs binary multiplication of two signed binary numbers using Booth's Algorithm.
 *
 *  A, Q, and M are 32-bit registers. Q1 is a 1-bit register. M is the multiplicand, Q is the multiplier,
 *  and A and Q1 are both set to 0. At the end of the loop, A and Q are concatenated to form the 64-bit product.
 *  A holds the most significant 32 bits and Q holds the least significant 32 bits.
 *
 *  @param multiplicand The binary string of the multiplicand of the operation.
 *  @param multiplier The binary string of the multiplier of the operation.
 *  @return The resultant as a 64-bit signed binary string.
*/

char* bootMultiplication(char *multiplicand, char *multiplier) {
    char* M = extendBinary(multiplicand, SIZE_REF);
    char* Q = extendBinary(multiplier, SIZE_REF);

    // Same as Q_-1 register
    char* Q1 = (char*) calloc(2, sizeof(char));
    Q1[0] = '0';
    Q1[1] = '\0';
    char* A = uextendBinary("0", strlen(M)+1);
    // Set both A (length of M) and Q1 to 0.

    int count = strlen(Q);
    while (count != 0) {
        if (Q[strlen(Q)-1] == '1' && Q1[0] == '0') {
            // A = A-M
            A = subSignedBinary(A, M);
        } else if (Q[strlen(Q)-1] == '0' && Q1[0] == '1') {
            A = addSignedBinary(A, M);
        } 
        // Performs shift every iteration.
        arithmeticShiftRight(A, Q, Q1);
        count--;
    }

    // Print A and Q registers to result
    char* result = (char*) calloc(SIZE_RES, sizeof(char));
    for (int i = 0; i < strlen(A); i++) {
        result[i] = A[i];
    }
    for (int j = 0; j < strlen(Q); j++) {
        result[strlen(A) + j] = Q[j];
    }
    free(Q);
    free(M);
    free(Q1);
    free(A);
    return result;
}

/** @brief Performs binary division of two unsigned binary numbers using the restoration method.
 *
 *  A, Q, and M are 32-bit registers. M is the divisor, Q is the dividend, and A is set to 0.  
 *  At the end of the loop, the Q register contains the quotient as a 32-bit binary string.
 *
 *  @param dividend The binary string of the dividend of the operation.
 *  @param divisor The binary string of the divisor of the operation.
 *  @return The quotient result of the division as a 32-bit unsigned binary string.
*/

char* restoredDivisionQ(char *dividend, char *divisor) {
    // Since using two functions with same parameters for division, have to make local copy to properly free memory and return results.
    char* Q = uextendBinary(dividend, SIZE_REF);
    char* M = uextendBinary(divisor, SIZE_REF);

    // Set A equal to 0 and length of Q.
    char* A = uextendBinary("0", strlen(Q)+1);

    int count = strlen(Q);
    while (count != 0) {

        // Performs shift every iteration
        shiftLeft(A, Q);
        // A = A-M
        A = subSignedBinary(A, M);

        if (twosComplementDecimal(A) < 0) {
            Q[strlen(Q)-1] = '0';
            // Undo A = A-M
            A = addSignedBinary(A, M);
        } else {
            Q[strlen(Q)-1] = '1';
        }
        count--;
    }
    free(A);
    free(M);
    // Q register is quotient
    return Q;
}

/** @brief Performs binary division of two unsigned binary numbers using the restoration method.
 *
 *  A, Q, and M are 32-bit registers. M is the divisor, Q is the dividend, and A is set to 0.  
 *  At the end of the loop, the A register contains the remainder as a 32-bit binary string.
 *
 *  @param dividend The binary string of the dividend of the operation.
 *  @param divisor The binary string of the divisor of the operation.
 *  @return The remainder result of the division as a 32-bit unsigned binary string.
*/

char* restoredDivisionR(char *dividend, char *divisor) {
    // Since using two functions with same parameters for division, have to make local copy to properly free memory and return results.
    char* Q = uextendBinary(dividend, SIZE_REF);
    char* M = uextendBinary(divisor, SIZE_REF);

    // Set A equal to 0 and length of Q.
    char* A = uextendBinary("0", strlen(Q)+1);

    int count = strlen(Q);
    while (count != 0) {

        // Performs shift every iteration
        shiftLeft(A, Q);
        // A = A-M
        A = subSignedBinary(A, M);

        if (twosComplementDecimal(A) < 0) {
            Q[strlen(Q)-1] = '0';
            // Undo A = A-M
            A = addSignedBinary(A, M);
        } else {
            Q[strlen(Q)-1] = '1';
        }
        count--;
    }
    free(M);
    free(Q);
    // A register is remainder
    return A;
}

/** @brief Performs binary multiplication of two unsigned binary numbers using the partial sums method.
 *
 *  A, Q, and M are 32-bit registers. C is a 1-bit register. M is the multiplicand, Q is the multiplier,
 *  and A and C are both set to 0. At the end of the loop, A and Q are concatenated to form the 64-bit product.
 *  A holds the most significant 32 bits and Q holds the least significant 32 bits.
 *
 *  @param multiplicand The binary string of the multiplicand of the operation.
 *  @param multiplier The binary string of the multiplier of the operation.
 *  @return The resultant as a 64-bit unsigned binary string.
*/

char* uMultiplication(char *multiplicand, char *multiplier) {
    char* M = uextendBinary(multiplicand, SIZE_REF);
    char* Q = uextendBinary(multiplier, SIZE_REF);

    char* C = (char*) calloc(2, sizeof(char));
    C[0] = '0';
    C[1] = '\0';
    char* A = uextendBinary("0", strlen(M)+1);
    // Set A (length of M) and C equal to 0

    int count = strlen(Q);
    while (count != 0) {
        if (Q[strlen(Q)-1] == '1') {
            int carry = uaddCarry(A, M);
            C[0] = numberToLetter(carry);
            A = uaddBinary(A, M);
        }

        // Performs shift every iteration
        shiftRight(C, A, Q);        
        count--;
    }

    // Print A and Q registers to result
    char* result = (char*) calloc(SIZE_RES, sizeof(char));
    for (int i = 0; i < strlen(A); i++) {
        result[i] = A[i];
    }
    for (int j = 0; j < strlen(Q); j++) {
        result[strlen(A) + j] = Q[j];
    }
    free(Q);
    free(M);
    free(C);
    free(A);
    return result;
}

/** @brief Performs a logical left shift on the two registers involved in binary division.
 *
 *  A and Q are the two 32-bit registers in binary division. Shifts all elements one bit to the left and fills the right-most bit with a 0.
 *
 *  @param A 32-bit register containing remainder of division.
 *  @param Q 32-bit register containing quotient of division.
 *  @return Void.
*/

void shiftLeft(char* A, char* Q) {
    for (int i = 1; i <= strlen(A)-1; i++) {
        A[i-1] = A[i];
    }
    A[strlen(A)-1] = Q[0];
    for (int j = 1; j <= strlen(Q)-1; j++) {
        Q[j-1] = Q[j];
    }
    // Right-most bit becomes filled with a 0
    Q[strlen(Q)-1] = '0';
}

/** @brief Performs a logical right shift on the three registers involved in unsigned binary multiplication.
 *
 *  C, A, and Q are the tree registers in unsigned binary multiplication. Shifts all elements one bit to the right and fills the left-most bit with a 0.
 *
 *  @param A 32-bit register used in unsigned binary multiplication.
 *  @param Q 32-bit register used in unsigned binary multiplication. 
 *  @param C 1-bit register used in unsigned binary multiplication.
 *  @return Void.
*/

void shiftRight(char* C, char* A, char* Q) {  
    for (int i = strlen(Q)-1; i > 0; i--) {
        Q[i] = Q[i-1];
    }
    Q[0] = A[strlen(A)-1];
    for (int j = strlen(A)-1; j > 0; j--) {
        A[j] = A[j-1];
    }
    A[0] = C[0];
    // Left-most bit becomes filled with a 0
    C[0] = '0';
}

/** @brief Performs an arithmetic right shift on the three registers involved in Booth's algorithm binary multiplication.
 *
 *  A, Q and Q1 are the tree registers in unsigned binary multiplication. Shifts all elements one bit to the right and the left-most bit stays the same.
 *
 *  @param A 32-bit register used in Booth's algorithm binary multiplication.
 *  @param Q 32-bit register used in Booth's algorithm binary multiplication. 
 *  @param Q1 1-bit register used in Booth's algorithm binary multiplication.
 *  @return Void.
*/

void arithmeticShiftRight(char* A, char* Q, char* Q1) {
    Q1[0] = Q[strlen(Q)-1];
    for (int i = strlen(Q)-1; i > 0; i--) {
        Q[i] = Q[i-1];
    }
    Q[0] = A[strlen(A)-1];
    for (int j = strlen(A)-1; j > 0; j--) {
        A[j] = A[j-1];
    }
    // The last bit, A[0], stays the same.
}










#endif