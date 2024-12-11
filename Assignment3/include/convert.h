// Functions from assignments 1 and 2.
int charToNumber(char x);

char numberToLetter(int number);

char* uextendBinary(char *bin, int size);

char* extendBinary(char *bin, int size);

char* uaddBinary(char *num1, char *num2);

char* addSignedBinary(char* bNum1, char* bNum2);

char *subSignedBinary(char *binaryNumber1, char *binaryNumber2);

char* reverse(char *other);

char* decimalToBinary(unsigned int dnumber);

char* onesComplement(int num);

char *twosComplement(int num);\

int twosComplementDecimal(char* bNum); 

int uaddCarry(char* num1, char* num2);

//Any other function as per your requirement or from previous assignements

//convert a 65 (including '\0') length string to unsigned long
// you can use/upgrade your implemnetation of binaryToDecimal from Assignemnt1 or 2 
unsigned long convertToDecimal(char *result);

//convert a 65 (including '\0') length string to a signed long
// you can use/upgrade your implemnetation of binaryToDecimal from Assignemnt1 or 2 
long convertToDecimalSigned(char *bNum);

//converts a binary number to unsigned,
// you can use your imlemnetation from Assignemnt1 or 2 
unsigned int binaryToDecimal(char *other);

/*
Parameters-
multiplicand : a signed binary representation of multiplicand
multiplier : a signed binary representation of multiplier
Function multiplies two signed binary numbers using Booth's algorithms 
and returns product in binary
bootMultiplication("01000111010111", "00101011001") 
returns "0000000000000000000000000000000000000000000110000000101010111111"
Note: The returned string is 65 bit, 64 bits for the product and 1 bit for '\0'

bootMultiplication("11111111111111111111011111010111", "00000000000000000000000000100001")
returns "1111111111111111111111111111111111111111111111101111001010110111"
*/
char* bootMultiplication(char *multiplicand, char *multiplier);


/*
Parameters-
dividend : an unsigned binary representation of dividend
divisor : an unsigned binary representation of divisor
Function divides binary dividend by divisor 
and returns quotient in binary using restoration algorithm

restoredDivisionQ("00000000000000000001000111010111", "00000000000000000000000101011001")
returns "00000000000000000000000000001101"
*/
char* restoredDivisionQ(char *dividend, char *divisor);

/*
Parameters-
dividend : an unsigned binary representation of dividend
divisor : an unsigned binary representation of divisor
Function divides binary dividend by divisor 
and returns remainder in binary using restoration algorithm

restoredDivisionR("00000000000000000001000111010111", "00000000000000000000000101011001")
returns "00000000000000000000000001010010"
 */
char* restoredDivisionR(char *dividend, char *divisor);

/*
Parameters-
multiplicand : an unsigned binary representation of multiplicand
multiplier : an unsigned binary representation of multiplier
Function multiplies two unsigned binary numbers and returns product in binary
uMultiplication("01000111010111", "00101011001") 
returns "0000000000000000000000000000000000000000000110000000101010111111"
Note: The returned string is 65 bit, 64 bits for the product and 1 bit for '\0'
*/
char* uMultiplication(char *multiplicand, char *multiplier);

//Write declarations for
//arithmeticshiftRight to be used in bootMultiplication
//shiftRight to be used in uMultiplication
//shiftLeft to be used in restoredDivisionQ, restoredDivisionR

void shiftLeft(char* A, char* Q);

void shiftRight(char* C, char* A, char* Q);

void arithmeticShiftRight(char* A, char* Q, char* Q1);