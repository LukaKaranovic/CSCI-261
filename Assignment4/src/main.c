/* Convert from unsigned decimal to Fixedpoint binary UQ16.16,
 signed decimal to Fixed Point binary number Q16.16
 Convert  unsigned Fixed Point Binary to decimal
 Convert  signed Fixed Point Binary to signed decimal
 Convert Decimal float number to IEEE754 single point precison floating point number
 Convert IEEE754 single point precison floating point number to Decimal float number
 */


#define MAIN_FUNCS
#define SIZE_REF 33

#include <stdio.h>
#include "../include/convert.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Driver program 
int main() 
{ 
	float fnumber = 0;
    char choice;
    char *tnumber;
    while(1)
        {     
            printf("Enter your choice \n"
            "'1' : To Convert from unsigned integer decimal to Fixed Point binary \n"
            "'2' : To Convert from signed integer decimal to fixed point binary\n"
            "'3' : To convert unsigned Fixed Point binary to decimal\n"
            "'4' : To convert signed Fixed Point binary to decimal\n"
            "'5' :To Convert from a decimal float to IEEE754 Single PrecisionFloating Point binary \n"
            "'6' :To Convert from IEEE754Single precision Floating Point binary to a float decimal number\n");
            scanf("%c", &choice);
            if(choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5' || choice == '6')
                break;
        }
    if(choice == '1') {          
        printf("Enter the unsigned foating point number\n");
        scanf("%f", &fnumber);
        //fixedUnsignedBinary converts float to fixed point binary UQ16.16 format
        tnumber = fixedUnsignedBinary(fnumber);
        printf("Fixed Point unsigned representation of %f is %s\n", fnumber, tnumber);
        free(tnumber);
    }       
    else if(choice == '2'){
         //U15.16+1=32 for sign
        printf("Enter the signed floating point number \n");
        scanf("%f", &fnumber);
        //fixedSignedBinary converts float to fixed point binary
        tnumber = fixedSignedBinary(fnumber);
        //displays number in 1/0Q15.16 format
        printf("Fixed Point Signed representation of %f is %s\n", fnumber, tnumber);
        free(tnumber);
    }
    else if(choice == '3') {
        //Sign bit + 15 bit before decimal + 1 decimal + 16 bits after decimal + '\0' = 34 bits 
        //SIZE_REF is 33, so32 bit number 1 for '\0' and 1 to decimal totalling to SIZE_REF + 1
        char *fixedbinary = (char *) calloc(SIZE_REF+1, sizeof(char));
        while(1) {
            printf("Enter the Binary number in unsigned Fixed point format 16 bit before and 16 bit after the decimal point\n");
            scanf("%s", fixedbinary);
        /*
        Check if the number entered is binary,
        isFixedBinary returns true if the nuber entered has only 0s, 1s and a decimal
        after 16 bits
        */
            if(isFixedBinary(fixedbinary))
                break;
        }
        //Convert fixed Binary to decimal unisgned
        float binaryFloat = fixedBinaryToFloat(fixedbinary);
        printf("The decimal equalivalet of %s is %f\n", fixedbinary, binaryFloat);      
        free(fixedbinary);
    }
    else if(choice == '4') {
        char *fixbinary = (char *) calloc(SIZE_REF+1, sizeof(char));
        while(1) {
            printf("Enter the Binary number in Fixed pont format sign bit, 15 bit before and 16 bit after the decimal with sign bit as MSB\n");
            scanf("%s", fixbinary);
            //Check if the input is binry with 16 bits of 0's and 1's, decimal point and 16 bits
            if(isFixedBinary(fixbinary))
                break;
        }
        float binaryFloat = fixedSignBinaryToFloat(fixbinary);
        printf("The decimal equalivalet of %s is %e\n", fixbinary, binaryFloat);      
        free(fixbinary);
    }        
else if(choice == '5')  {          
        printf("Enter the decimal integer \n");
        scanf("%f", &fnumber);
        /*
        Converts a floating point number to binary IEEE754 single precision form
        */
        char *floatIEEE754 = floatingToIEEE754Binary(fnumber);
        //Note use of %e to print floating point as exponent
        printf("IEEE754 Single precision Floating point representation of %e is %s\n",fnumber, floatIEEE754);  
        free(floatIEEE754);

    }       
    else if(choice == '6')  {
        printf("Enter the floating point binary in IEEE754 Single Precision\n"
        "as 32 bit number 1 sign 2-9 exponent added bias 10-32 fraction\n");
        char *floatIEEE754 = (char *)calloc(SIZE_REF, sizeof(char));
        scanf("%s", floatIEEE754);
        //Converts IEEE754 single precision form to decimal float
        fnumber = BinaryIEEE754toFloat(floatIEEE754);
        printf("IEEE754 Single precision Floating point %s to decimal float is %e and %f \n",floatIEEE754, fnumber, fnumber);
        free(floatIEEE754);
    }
        return 0;
}
