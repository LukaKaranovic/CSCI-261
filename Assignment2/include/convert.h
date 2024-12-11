/*
Some of the functions are already implmeneted in Assignment1,
You can directly use them without much expalnation in Assignment2  
*/
char* uextendBinary(char *bin);
char* reverse(char *other);
char* decimalToBinary(int dnumber);
char* twosComplement(int num);

// Additional ones from Assignment1 needed to implement the functions above:
int charToNumber(char x);
char numberToLetter(int number);
int isRadix(char *other, int radix);
char* onesComplement(int num);

/*
unsigned binary to decimal assuming the binary is unsigned
Returns unsigned decimal number
*/
int binaryToDecimal(char* other);

/*
Parameter: Binary number in two's complemnt
Checks MSB and performs two's complement if it is negative number
Returns a decimal equivalent of the binary number 
*/
int twosComplementDecimal(char* bNum);


/*
Unsigned Binary Addition
Paramters:
binaryNumber1: First unsigned binary number to added, character string
binaryNumber2 : Second unsigned binary number to be added, character string
Returns a pointer to memory location holding binary sum of 
binaryNumber1 and binaryNumber2
Extend binaryNumber1 and binaryNumber2 if required before adding
Take care of Carry in and carry out as discussed in class
*/
char* uaddBinary(char* num1, char* num2);

/*
Unsigned Binary Subtraction
Parameters:
binaryNumber1: First unsigned binary number to minuend, character string
binaryNumber2 : Second unsigned binary number to be subtracted, character string
Returns a pointer to memory location holding binary difference of 
binaryNumber1 and binaryNumber2
Extend binaryNumber1 and binaryNumber2 if required before adding
Take care of Borrow as discussed in class
*/
char* usubBinary(char *num1, char *num2);

/*
Unsigned Binary Addition and Check Carry
Parameters:
binaryNumber1: First unsigned binary number minuend, character string
binaryNumber2 : Second unsigned binary number to be subtracted, character string
Binary addition binaryNumber1 + binaryNumber1
Returns 1 if carry occured in unsigned numbers addition.
Extend binaryNumber1 and binaryNumber2 if required before adding
*/
int uaddCarry(char* num1, char* num2);

/*
Unsigned Binary Subtraction and Check Borrow
Paramters:
binaryNumber1: First unsigned binary number to minuend, character string
binaryNumber2 : Second unsigned binary number to be subtracted, character string
Binary Subtract binaryNumber1 - binaryNumber1
Returns 1 if no borrow occured in the end and 0 otherwise for borrow.
In ARM processor, if borrow occurs Carry Flag is 0
Extend binaryNumber1 and binaryNumber2 if required before adding
*/
int usubBorrow(char *binaryNumber1, char *binaryNumber2);

/*
Signed Binary Subtraction
Parameters:
binaryNumber1: First signed binary number minuend, character string
binaryNumber2 : Second signed binary number to be subtracted, character string
Returns a pointer to memory location holding binary difference of 
binaryNumber1 and binaryNumber2
Extend binaryNumber1 and binaryNumber2 if required before adding
You can use twos complement
*/
char *subSignedBinary(char *binaryNumber1, char *binaryNumber2);

/*
unsigned decimal to binary
Decimal to Binary Conversion of unsigned number.
Works similar to binaryToDecimal, paramter passed is unsigned, 
Most Significant Bit is magnitude and not sign 
Returns binary converted string
*/
char* udecimalToBinary(unsigned int dnumber);

/*
Helper functrion: Signed Binary Extension
Parameters:
bin: Input binary string to be extended
Extends both positive and negative numbers to 32 bits. If negative, extends it with 1s instead of 0s.
*/
char* extendBinary(char *bin);

/*
Signed Binary Addition
Paramters:
binaryNumber1: First binary number (Two's complement if negative) to added
binaryNumber2 : Second binary number (Two's complement if negative) to be added
Returns a pointer to memory location holding binary sum of 
binaryNumber1 and binaryNumber2
Extend binaryNumber1 and binaryNumber2 if required before adding
Take care of Carry
*/
char* addSignedBinary(char* binaryNumber1, char* binaryNumber2);

/*
Signed Binary Addition and check if overflow occured
Paramters:
binaryNumber1: First binary number (Two's complement if negative) to added
binaryNumber2 : Second binary number (Two's complement if negative) to be added
Returns a 1 if adding binaryNumber1 and binarNumber2 leads to overflow 
If last carry in and carry out are of same sign then no overflow as discussed in class
*/
int findAddOverflow(char *num1, char *num2);

/*
Signed Binary Subtraction and check if overflow occured
Paramters:
binaryNumber1: First binary number (Two's complement if negative) to added
binaryNumber2 : Second binary number (Two's complement if negative) to be added
Returns a 1 if subtracting binaryNumber1 and binarNumber2 leads to overflow 
You can use two'c complenet for subtraction
*/
int findSubOverflow(char *num1, char *num2);