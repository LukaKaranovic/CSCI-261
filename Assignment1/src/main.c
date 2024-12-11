
/* 
NUMBER CONVERSION
Convert any radix input to unisgned integer or unsgned ineteger to any other radix chosen by
the user
Convert signed integer to binary using
signed magnitude
One's Complement
Two's Complement

@ author Kawal Jeet
*/

#include <stdio.h> 
#include "../include/convert.h"
#include <stdlib.h>
#define SIZE_REF 33 //Assuming 32 bit registers and hence integer


// Driver program 
int main() 
{ 
	int dnumber = 0; //dnumber to hold integer during conversion
    int radix = 0; //keep track of radix of the number
    //to keep track of the choice of what do ou want to do
    int choice = 0; 
    char *num = NULL; //pointer to characater array holding number of any radix
    char bNum[SIZE_REF]; //To keep the binary number

    do{     
            printf("1 :Convert unsigned integer to any Other Radix (binary 2, Octal 8, Hexadecimal 16).\n"
                    "2 :Convert From any Radix (binary 2, Octal 8, Hexadecimal 16) to unsigned integer number.\n"
                    "3 :To convert signed integer to sign magnitude binary number \n"
                    "4 :To convert sign magnitude binary number to signed integer number\n"
                    "5 :To convert signed integer number to ones complement binary number \n"
                    "6 :To convert ones complement binary number to signed integer number\n"
                    "7 :To convert signed integer number to twos complement binary number \n"
                    "8 :To convert twos complement binary number to signed integer number\n");
                    
            scanf("%d", &choice);
        }while(choice < 1 || choice > 8);
            
    switch(choice){
        
        case 1:
            printf("Enter the unsigned integer number to be converted\n");
            scanf("%d", &dnumber);
            printf("Enter the radix converted to:\t");
            scanf("%d",&radix);
            printf("\n");
            //to convert decimal input dnumber to radix
            num = decimalToOther(dnumber, radix);
            printf("Unsigned integer %d to radix %d is %s\n", dnumber, radix, num); 
        break;

        case 2:
            printf("Enter the number to be converted to unsigned integer from other radix\n");
            scanf("%s", bNum); //number to be converted to decimal
      
            do{
                printf("Enter the radix of the number you are converting from:\t");
                //For the current assignment, use radix only decimal, octal, bnary and hexadecimal
                scanf("%d",&radix); //radix of the number to be converetd to decimal
                printf("\n");
            }while(!isRadix(bNum, radix));
            //check if the input is of correct required radix, binary, octal or hexadecimal in this assignment
            printf("radix %d conversion of %s to unsigned integer is %d\n", radix, bNum, otherToDecimal(radix, bNum));          
            break; 

        case 3:
            printf("Enter the integer to be converted \n");
            scanf("%d", &dnumber);         
            num = signMagnitude(dnumber); //convert ineteger to signed magnitude binary representation
            printf("Signed Magnitude representation of %d is %s", dnumber, num); 
            break;

        case 4:
            do{
                printf("Enter the sign magnitude number to be converted to integer\n");
                //you can scan binary of any size, it will check MSB to check if it is positve or negative
                scanf("%s", bNum); 
            }while(!isRadix(bNum, 2));//check if the number is atleast binary

            //Convert binary number to integer assuming the number is in signed  magnitude binary
            dnumber = signMagnitudeDecimal(bNum);
            printf("Decimal conversion of sign magniude representation of %s is %d", bNum, dnumber); 
            break;

        case 5:             
            printf("Enter the integer to be converted \n");
            scanf("%d", &dnumber);
            num = onesComplement(dnumber); //convert integer to one's complement
            printf("Ones Complement of a number %d is %s", dnumber, num); 
            break;

        case 6:
         do{
                 printf("Enter the ones complement number to be converted to integer\n");
        //you can scan binary of any size, it will check MSB to check if it is positve or negative
                scanf("%s", bNum);
            }while(!isRadix(bNum, 2));//check if the number is atleast binary

        //Convert binary number to integer assuming the number is in one's complement binary
            dnumber = onesComplementDecimal(bNum); 
            printf("Decimal conversion of ones complement representation of %s is %d", bNum, dnumber); 
            break;

        case 7: 
            printf("Enter the integer to be converted \n");
            scanf("%d", &dnumber);
            num = twosComplement(dnumber); //convert integer to two's complement
            printf("Twos Complement of a number %d is %s", dnumber, num); 
            break;
    
        case 8:
            do{
                printf("Enter the twos complement number to be converted to integer\n");
                //Make sure to put 0 in front of a positive integer two's complement number
                //you can scan binary of any size, it will check MSB to check if it is positve or negative
                scanf("%s", bNum);
            }while(!isRadix(bNum, 2));//check if the number is atleast binary

        //Convert binary number to integer assuming the number is in two's complement binary
            dnumber = twosComplementDecimal(bNum);
            printf("Decimal conversion of twos complement representation of %s is %d", bNum, dnumber); 
            break; 
    
    }          
    free (num);   
    return 0;
}
