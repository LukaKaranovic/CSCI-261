/*
Two add and subtract to unsigned numbers and take care of carry and borrow
Two add and subtract to signed numbers and take care of overflow
PLEASE PUT YOUR STUDENT NAME AND STUDENT NUMBER
Student Number: 
Student Name:   


*/
#include <stdio.h> 
#include "../include/convert.h"
#include <stdlib.h>
#include<string.h>
#define SIZE_REF 33 //Assuming 32 bit registers, last bit to store '\0' end of string


// Driver program 
int main() 
{ 

    int choice;

    do{     
            printf("Enter your choice \n"
            "1 :To enter two unsigned integer numbers and add after converting"
             "to binary, check if Carry occured \n"
            "2 :To enter two unsigned integer numbers and subtract after"
             "converting to binary, check Borrow occured\n"
            "3 :To enter two signed integer numbers add after "
            "converting to binary numbers and check overflow\n"
            "4 :To enter two signed integer numbers subtract after"
             "converting to binary numbers and check overflow\n");
            
            scanf("%d", &choice);
        }while(choice < 1 || choice > 4);
  
    char *result;
    char * binaryNumber1;
    char * binaryNumber2;
    
    if(choice == 1) {
        //unsigned addition
        unsigned int digitalNumber1 = 0; 
        unsigned int digitalNumber2 = 0;
       
        do{
            printf("Enter the first unsigned integer addend\n");
            scanf("%u", &digitalNumber1);
            printf("Enter the second unsigned integer addend\n");
            scanf("%u", &digitalNumber2);  
        }while(digitalNumber1 < 0 || digitalNumber2 < 0);

        //Convert unsigned/magnitude of decimal number to binary
        binaryNumber1 = udecimalToBinary(digitalNumber1);
        binaryNumber2 = udecimalToBinary(digitalNumber2);
    
        //add two binary unsigned numbers by calling uaddBinary function
        result =  uaddBinary(binaryNumber1, binaryNumber2);         

        //print binary addition 
        printf("In Binary unsigned addition %s + %s = %s \n", binaryNumber1, binaryNumber2, result);
        
        //Convert resulting binary to decimal to display result in decimal
        printf("In Decimal unsigned addition %u + %u = %u\n", digitalNumber1, digitalNumber2, binaryToDecimal(result)) ;
        
        //Check if adding two unsigned binary numbers results in a Carry
        if(uaddCarry(binaryNumber1, binaryNumber2) == 1)
                printf("Carry Occured\n");
    }                    
    else if(choice == 2) {
        //unsigned subtraction
            unsigned int digitalNumber1 = 0;
            unsigned int digitalNumber2 = 0;
            
            do{
            printf("Enter the first unsigned integer minuend\n");
            scanf("%u", &digitalNumber1);
            printf("Enter the second unsigned integer subtrehend\n");
            scanf("%u", &digitalNumber2);  
        }while(digitalNumber1 < 0 || digitalNumber2 < 0);

            //Convert unsigned/magnitude of decimal number to binary
            binaryNumber1 = udecimalToBinary(digitalNumber1);
            binaryNumber2 = udecimalToBinary(digitalNumber2);
            
            //subtract two binary unsigned numbers by calling usubBinary function
            result =  usubBinary(binaryNumber1, binaryNumber2);         
            
            //print binary subtraction 
            printf("In binary unsigned subtraction %s - %s = %s\n", binaryNumber1, binaryNumber2, result);     
            
            //Convert resulting binary to decimal to display result in decimal
            printf("In Decimal unsigned subtraction %u - %u = %u\n", digitalNumber1, digitalNumber2, binaryToDecimal(result)) ;
            
            //Check if subtracting two unsigned binary numbers results in a Borrow
            if(usubBorrow(binaryNumber1, binaryNumber2) == 0)
                printf("Borrow Occured\n");
          }   
    else if(choice == 3) {        
            int digitalNumber1 = 0;
            int digitalNumber2 = 0;
            
            printf("Enter the first integer addend\n");
            scanf("%d", &digitalNumber1);
            printf("Enter the second integer addend\n");
            scanf("%d", &digitalNumber2);     
           
            //Convert unsigned/magnitude of decimal number to binary   
            binaryNumber1 = twosComplement(digitalNumber1);
            binaryNumber2 = twosComplement(digitalNumber2); 

            result = addSignedBinary(binaryNumber1, binaryNumber2);
            
            printf("In Binary Signed Addition %s + %s = %s\n", binaryNumber1, binaryNumber2, result);
            
            //Convert resulting binary to decimal to display result in decimal
            printf("In Decimal Signed Addition %d + %d = %d\n", digitalNumber1, digitalNumber2, twosComplementDecimal(result)) ;
            
            //Checks if adding two signed binary numbers leads to overflow
            if(findAddOverflow(binaryNumber1, binaryNumber2) == 1)
                printf("Overflow Occured\n");
            }       
    else if(choice == 4)   {
            int digitalNumber1 = 0;
            int digitalNumber2 = 0;
            
            printf("Enter the first integer minuend\n");
            scanf("%d", &digitalNumber1);
            printf("Enter the second integer subtrehend\n");
            scanf("%d", &digitalNumber2);     
            
            //Convert unsigned/magnitude of decimal number to binary   
            binaryNumber1 = twosComplement(digitalNumber1);
            binaryNumber2 = twosComplement(digitalNumber2); 
   
            result = subSignedBinary(binaryNumber1, binaryNumber2);
            printf("In Binary Signed Subtraction  %s - %s = %s\n", binaryNumber1, binaryNumber2, result);
            printf("In Decimal Signed Subtraction %d - %d = %d\n", digitalNumber1, digitalNumber2, twosComplementDecimal(result)) ;
            
            //Checks if subtracting two signed binary numbers leads to overflow
            if(findSubOverflow(binaryNumber1, binaryNumber2) == 1)
                printf("Overflow Occured\n");
            
    }        
    free(binaryNumber1);
    free(binaryNumber2);
    free(result);
    return 0;
}

