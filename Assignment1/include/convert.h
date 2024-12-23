#ifndef INCLUDE_CONVERT_H_
#define INCLUDE_CONVERT_H_

/* 
Parameters -
x: character being checked for its number value.
Function takes a character symbol and converts it to the decimal number that it is supposed
to represent.
letterToNumber('A') returns 10
letterToNumber('D') returns 13
letterToNumber('H') returns 17
*/
int letterToNumber(char x);

/* 
Parameters -
number: number being converted to its letter symbol equivalent.
Function takes a number and converts it to the alphabet symbol that it is supposed
to represent.
numberToLetter(10) returns 'A'
numberToLetter(13) returns 'D'
numberToLetter(17) returns 'H'
*/
char numberToLetter(int number);

/*
Parameters-
radix: radix of the number entered
other: number to be converted to unsigned integer
Function takes the radix and the number to be converted to and converts to decimal
oToDecimal(2, "10001011") return 139
oToDecimal(16,"8B") return 139
oToDecimal(8, "213") return 139
*/
int otherToDecimal(int radix, char *other);

/*
Parameters-
radix: radix to which the number is to be converted
dnumber: unsigned integer number to be converted to radix
Function takes a decimal number and the radix to which it is to be converted
decimalToO(139, 2) return 10001011
decimalToO(139, 16) return 8B
decimalToO(139, 8) return 213
*/
char* decimalToOther(int dnumber, int radix);

/*
Parameter:
other: string to be reversed
Takes a string and reverses it
reverse("10001011") returns "11010001"
reverse("112") returns "211'
reverse("4321B") returns "B1234"
*/
char* reverse(char *other);

/*
Parameters-
radix: radix of the number
other: a number whose radix is to be checked 
Function checks if the string other is of the passed radix
Return 1 if the radix is correct and 0 otherwise
isRadix("1B11110", 2) return 0
isRadix("4571230", 8) returns 1
isRadix("6789334", 8) return 0
isRadix("567829", 10) returns 1
isRadix("678B334", 10) returns 0
isRadix("56H7829", 16) returns 0
isRadix("678B334", 16) returns 1
*/
int isRadix(char *other, int radix);


/*
Parameter:
other: string to be extended to 32 bit
Takes a string and if it is less than 32 bit long, add 0's in the begining
uextendBinary("110111110000111110001011") returns "00000000110111110000111110001011"
For this assignment, extend only positive numbers
*/
char* uextendBinary(char *bin);


/*
Parameters-
dnumber: decimal number to be converted to binary
Function takes a decimal number and converts to binary
decimalToBinary(139) returns 10001011
*/
char* decimalToBinary(int dnumber);


/*
Parameters-
num: a signed decimal number to be converted to binary
Function converts the number to binary, checks if the string num is positive or negative
Extends the number to 32 bit
If negative, it places 1 in first bit to depict the sign bit, else 0 to depict positive.
signMagnitude(12) returns "00000000000000000000000000001100"
signMagnitude(-12) returns "10000000000000000000000000001100"
*/
char* signMagnitude(int num); 

/*
Parameters-
num: a signed decimal number to be converted to binary
Function converts the number to binary
Extends the number to 32 bit
Checks if the string num is positive or negative
If negative, converts it into 1's complement as discussed in class and shared in notes in VIULearn
onesComplement(12) returns "00000000000000000000000000001100"
onesComplement(-12) returns "11111111111111111111111111110011"
*/
char* onesComplement(int num);

/*
Parameters-
num: a signed decimal number to be  converted to binary
Function converts the number to binary
Extends the number to 32 bit
Checks if the string num is positive or negative
If negative, converst it into 2's complement as discussed in class and shared in notes in VIULearn
twosComplement(-12) returns "11111111111111111111111111110100"
twosComplement(12) returns "00000000000000000000000000001100"
*/
char* twosComplement(int num);

/*
Parameters-
num1: a binary number in a character array/ string
num2: a binary number in a character array/ string
Function adds num1 and num2 two binary numbers and returns the added binary number
Used in implementing 2's complement. 
Invert all 1's to 0's and 0's to 1's
Add 1 in 1's complement
*/
char* uaddBinary(char *num1, char *num2);

/*
Parameters-
bNum: a binary number to be converted to signed decimal
Function converts the binary number to decimal, checks bit 0, 
if it is 1 the string is a negative number else it is positive
Converts the binary number to decimal and if bit 0 is 1, places - at the begining.
Converts binary to decimal as sicussed in class
signMagnitudeDecimal("00000000000000000000000000001100") returns 12
signMagnitude("10000000000000000000000000001100") returns -12
*/
int signMagnitudeDecimal(char* bNum); 

/*
Parameters-
bNum: a binary number to be converted to signed decimal
Function converts the binary number to decimal, checks bit 0, 
if it is 1 the string is a negative number else it is positive
Inverts all 0's to 1's and 1's to 0's
Converts binary to decimal as discussed in class
onesComplementDecimal(00000000000000000000000000001100) returns 12
onesComplementDecimal("11111111111111111111111111110011") returns -12
*/
int onesComplementDecimal(char* bNum);

/*
bNum: a binary number to be converted to signed decimal
Function converts the binary number to decimal, checks bit 0, 
if it is 1 the string is a negative number else it is positive
Inverts all 0's to 1's and 1's to 0's and add 1
Converts binary to decimal as sicussed in class
twosComplementDecimal(00000000000000000000000000001100) returns 12
twosComplementDecimal("11111111111111111111111111110100") returns -12
If length of binary two's complement is less than SIE_REF, 
extend the number by add 0's to fill if it is positive
extend the number by add 1's to fill if it is negative
*/
int twosComplementDecimal(char* bNum);


#endif