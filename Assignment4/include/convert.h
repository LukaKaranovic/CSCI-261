#ifndef CONVERT_FUNCS
#define CONVERT_FUNCS

/* Helper functions from past assignments, for comments on how they work,
please refer to the past assignments.
*/ 
int charToNumber(char x);
char numberToLetter(int number);
char* extendBinary(char *bin, int size);
char* reverse(char *other);
char* decimalToBinary(int dnumber);
int binaryToDecimal(char *other);
char* uaddBinary(char* num1, char* num2);
char* onesComplement(int num);
char* twosComplement(int num);

// Turns an input string into its two's complement version.
char* twosComplementString(char* input);


/*
Fixed Pont Binary Unsigned Conversion
Paramters:
floatNumber: Unsigned float to be converted to fixed point binary
Return a fixed point binary string in the format 16.16
16 bits before the decimal, decimal point, 16 bits
For floatNumber = 3.141593
returns 0000000000000011.0010010000111111
*/
char* fixedUnsignedBinary(float floatNumber);


/*
Fixed Point Binary signed Conversion
Paramters:
floatNumber: Signed float to be converted to fixed point binary
Return a fixed point binary string in the format 16.16
Sign bit, 15 bits before the decimal, decimal point, 16 bits
For floatNumber = -3.141593
returns 1111111111111100.1101101111000001
*/
char* fixedSignedBinary(float floatNumber);

/*
Checks the format of a fixed point input
Paramters:
input: fixed point binary number
Returns 1 if the input is n the format 16 bits, decimal, 16 bits
For input = 1100110011001100.1111001100110011
1

For input = 11011001100.11E01100110011
returns 0
*/
int isFixedBinary(char *input);

/*
Converts  binary fixed point format input to a unsigned float
Paramters:
input: fixed point binary number
Returns an unsigned float number corresponding to fixed number input
For input = 0000000000000011.0010010000111111
returns
3.141586
*/
float fixedBinaryToFloat(char *input);


/*
Converts  binary fixed point format input to a signed float
Paramters:
input: fixed point binary number
Returns a signed float number corresponding to fixed number input
For input = 1111111111111100.1101101111000001
returns
-3.141586
*/
float fixedSignBinaryToFloat(char *input);


/*
IEEE754 Floating Point Single Precision Binary signed Conversion
Paramters:
floatNumber: Signed float to be converted to fixed point binary
Return a floating point binary string in the format 
1 Sign bit, 8 bit Exponent, 23 bits mentissa 
For floatNumber = 14.5
returns 01000001011010000000000000000000
*/
char* floatingToIEEE754Binary(float floatNumber);


/*
Converts  binary IEEE754 Single precision floating point input to a signed float
Paramters:
input: floating point binary number
Returns a signed float number corresponding to floating point binary input
For input = 00101011101010001110001010001110
returns
0.0000000000012
*/

float BinaryIEEE754toFloat(char *input);


#endif