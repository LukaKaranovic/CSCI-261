//To multiply two unsigned and signed numbers and return product
//To divide two unsigned numbers and display quotient and remainder

#include <stdio.h>
#include "../include/convert.h"
#include <stdlib.h>
#include <string.h>
#define SIZE_REG 33


// Driver program 
int main() 
{ 
    char choice = '\0';    
    do {     
            printf("Enter your choice \n"
            "'*': To multiply two unsigned integers (binary multiplication) \n"
            "'X': To multiply two signed integers (booth's algorithm)\n"
            "'/': Binary division with restoration\n");
            scanf("%c", &choice);
            
    } while(choice != '*' && choice != 'X' && choice != '/');  
    
    char * tnumber1;
	char * tnumber2;  
        
    if(choice == '*'){   
        //Hold unsigned input from user to be multiplied
        unsigned int udnumber1 = 0, udnumber2 = 0;      

        //Holds binary result of multiplications of two unsigned binary numbers
        char* result = NULL;

        printf("Enter the first unsigned integer \n");
        scanf("%u", &udnumber1);
        printf("Enter the second unsigned integer \n");
        scanf("%u", &udnumber2);
        
        //Convert unsigned number to binary    
        tnumber1 = decimalToBinary(udnumber1);
        tnumber2 = decimalToBinary(udnumber2);
        
        //multiply two 32 (1 extra bit for '\0' so actually 33) length binary numbers 
        //and give result as 64 length string
        result = uMultiplication(tnumber1, tnumber2);

        printf("Binary Multiplication of unsigned numbers\n"
                "%s X %s = %s\n", tnumber1, tnumber2, result);
        
        //convertToDecimal converts a long unsigned number to decimal
        //you can use or calls binaryToDecimal 
        unsigned long product = convertToDecimal(result);
        printf("\nBinary Multiplication of unsigned decimal numbers\n"
        "%u X %u= %ld\n", udnumber1, udnumber2, product); 
        free(result);  
    }       
    else if(choice == 'X'){
        int dnumber1 = 0;
        int dnumber2 = 0;
        printf("Enter the first signed integer \n");
        scanf("%d", &dnumber1);
        printf("Enter the second signed integer \n");
        scanf("%d", &dnumber2);
        
        //Holds binary result of multiplications of two unsigned binary numbers
        char* result = NULL;
        
        //Calls twosComplment toconvert integer to binary even if it is negative 
        tnumber1 = twosComplement(dnumber1);
        tnumber2 = twosComplement(dnumber2);
        
        //multiplies two binary numbers and returns 64 length string 
        result = bootMultiplication(tnumber1, tnumber2);
        printf("Binary Boot Multiplication of signed numbers\n"
                "%s X %s = %s\n", tnumber1, tnumber2, result);

        //64 length string needs a long to store the resulting decimal
        //convertToDecimalSigned converts a 64 length signed string to decimal
        //you can call twosComplement to implement if you want
        long product = convertToDecimalSigned(result);       
        printf("Binary Multiplication (Boot's Algorithm) of signed numbers %d and %d is %ld\n", dnumber1, dnumber2, product);
        free(result);
    }
    else if(choice == '/'){   
        unsigned int udnumber1 = 0, udnumber2 = 0;     
        printf("Enter the first unsigned integer \n");
        scanf("%u", &udnumber1);
        printf("Enter the second unsigned integer \n");
        scanf("%u", &udnumber2);
               
        tnumber1 = twosComplement(udnumber1);
        tnumber2 = twosComplement(udnumber2);
        
        //points to quotient and reaminder
        char* bQuotient = restoredDivisionQ(tnumber1, tnumber2);
        char* bRemainder = restoredDivisionR(tnumber1, tnumber2);
        
        //usnigned version to divide unsigned numbers
        unsigned int quotient = binaryToDecimal(bQuotient);
        unsigned int remainder = binaryToDecimal(bRemainder);
        
        printf("Binary Quotient of Restored Divison between %s and %s is %s\n", tnumber1, tnumber2, bQuotient);
        printf("Decimal Quotient of Restored Divison between %u and %u is %u\n", udnumber1, udnumber2, quotient);
        printf("Binary remainder of Restored Divison between %s and %s is %s\n", tnumber1, tnumber2, bRemainder);
        printf("Decimal Remainder of Restored Divison between %u and %u is %u\n", udnumber1, udnumber2, remainder);      
        free(bQuotient);
        free(bRemainder);
    }       
//Free appropriate memory locations   
    free(tnumber1);
    free(tnumber2);
    return 0;
}
