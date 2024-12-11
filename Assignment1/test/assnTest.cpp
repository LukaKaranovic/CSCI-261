/*
cpp file used to perform unit testing

*/
#include "../src/convert.c"
#include "gtest/gtest.h"

//test for conversion from unsigned ineteger to any other radix 
TEST(conversion, dtob) { 
    //unisigned integer 139 to radix 2(binary) results in 10001011
    ASSERT_STREQ("10001011", decimalToOther(139, 2)); 

    //unisigned integer 139 to radix 16(hexadecimal) results in 8B
    ASSERT_STREQ("8B", decimalToOther(139, 16));

    //unisigned integer 139 to radix 8(octal) results in 213
    ASSERT_STREQ("213", decimalToOther(139, 8));    

    //unisigned integer 280 to radix 8(octal) results in 430
    ASSERT_STREQ("430", decimalToOther(280, 8));

    //unisigned integer 280 to radix 16 results in 118
    ASSERT_STREQ("118", decimalToOther(280, 16));

    //unisigned integer 280 to radix 2 results in 100011000
    ASSERT_STREQ("100011000", decimalToOther(280, 2));
}
 

 //test for conversion from one radix to unsigned ineteger
TEST(conversion, btod) { 
    //10001011 Binary 2 radix to unisigned integer is 139 
    ASSERT_EQ(139, otherToDecimal(2, "10001011"));

    //8B hexadecimal 16 radix to unisigned integer is 139
    ASSERT_EQ(139, otherToDecimal(16,"8B"));

    //214 Octal 8 radix to unisigned integer is 139
    ASSERT_EQ(139, otherToDecimal(8, "213"));

    //430 Octal 8 radix to unisigned integer is 280
    ASSERT_EQ(280, otherToDecimal(8, "430"));

    //118 hexadecimal 16 radix to unisigned integer is 280
    ASSERT_EQ(280, otherToDecimal(16, "118"));

    //100011000 Binary 2 radix to unisigned integer is 280
    ASSERT_EQ(280, otherToDecimal(2, "100011000"));
}


//test for reverse of a string    
TEST(conversion, reversenum) { 
    //revese of binary 10001011 gives 11010001
    ASSERT_STREQ("11010001", reverse("10001011"));

    //reverse of 112 gives 211
    ASSERT_STREQ("211", reverse("112"));

    //reverse of 4321B gives B1234
    ASSERT_STREQ("B1234", reverse("4321B"));   
}
    
//tests if the function isRadix is correctly testing 
//that the radix of the number entered as second parameter       
TEST(conversion, checkradix) { 
    // tests if the radix of 1011110 is 2 is true and returns 1
    ASSERT_EQ(isRadix("1011110", 2), 1);

    // tests if the radix of 1B11110 is 2 is false and returns 0
    ASSERT_EQ(0, isRadix("1B11110", 2));

    // tests if the radix of 1511110 is 2 is false and returns 0
    ASSERT_EQ(0, isRadix("1511110", 2));

    // tests if the radix of 4571230 is 8 is true and returns 1
    ASSERT_EQ(1, isRadix("4571230", 8));

    // tests if the radix of 6789334 is 8 is false and returns 0
    ASSERT_EQ(0, isRadix("6789334", 8));

    // tests if the radix of 6789C34 is 8 is false and returns 0
     ASSERT_EQ(0, isRadix("6789C34", 8));

     // tests if the radix of 567829 is 10 is true and returns 1
     ASSERT_EQ(1, isRadix("567829", 10));

     // tests if the radix of 678B334 is 10 is false and returns 0
     ASSERT_EQ(0, isRadix("678B334", 10));

     // tests if the radix of 56H7829 is 16 is false and returns 0
     ASSERT_EQ(0, isRadix("56H7829", 16));

     // tests if the radix of 678B334 is 16 is true and returns 1
     ASSERT_EQ(1, isRadix("678B334", 16));
}

//tests the integer conversion to signed magnitude binary
TEST(negativeNum, signM){ 
    //signed magnitude conversion of 12 is 00000000000000000000000000001100
    ASSERT_STREQ("00000000000000000000000000001100", signMagnitude(12));

    //signed magnitude conversion of -12 is 10000000000000000000000000001100
    ASSERT_STREQ("10000000000000000000000000001100", signMagnitude(-12));

    //signed magnitude conversion of 523 is 00000000000000000000001000001011
    ASSERT_STREQ("00000000000000000000001000001011", signMagnitude(523));

    //signed magnitude conversion of -523 is 10000000000000000000001000001011
    ASSERT_STREQ("10000000000000000000001000001011", signMagnitude(-523));   
}
 
//tests the integer conversion to one's complement binary 
TEST(negativeNum, onesC){ 
    //One's Complement conversion of 12 is 00000000000000000000000000001100
    ASSERT_STREQ("00000000000000000000000000001100", onesComplement(12));
    
    //One's Complement conversion of -12 is 11111111111111111111111111110011
    ASSERT_STREQ("11111111111111111111111111110011", onesComplement(-12));

    //One's Complement conversion of 523 is 00000000000000000000001000001011
    ASSERT_STREQ("00000000000000000000001000001011", onesComplement(523));

    //One's Complement conversion of -523 is 11111111111111111111110111110100
    ASSERT_STREQ("11111111111111111111110111110100", onesComplement(-523));

    //One's Complement conversion of -32 is 11111111111111111111111111011111
    ASSERT_STREQ("11111111111111111111111111011111", onesComplement(-32));  
}

//tests the integer conversion to two's complement binary
TEST(negativeNum, twosC){ 
    //Twos Complement conversion of -12 is 11111111111111111111111111110100
     ASSERT_STREQ("11111111111111111111111111110100", twosComplement(-12));

     //Twos Complement conversion of 12 is 00000000000000000000000000001100
     ASSERT_STREQ("00000000000000000000000000001100", twosComplement(12));

     //Twos Complement conversion of 523 is 00000000000000000000001000001011
     ASSERT_STREQ("00000000000000000000001000001011", twosComplement(523));

     //Twos Complement conversion of -523 is 11111111111111111111110111110101
     ASSERT_STREQ("11111111111111111111110111110101", twosComplement(-523));

     //Twos Complement conversion of -32 is 11111111111111111111111111100000
     ASSERT_STREQ("11111111111111111111111111100000", twosComplement(-32));

     //Twos Complement conversion of 2147483647 is 01111111111111111111111111111111
     ASSERT_STREQ("01111111111111111111111111111111", twosComplement(2147483647));

     //Twos Complement conversion of -2147483647 is 10000000000000000000000000000001
     ASSERT_STREQ("10000000000000000000000000000001", twosComplement(-2147483647));
}

//tests the conversion from signed magnitude to signed integer
TEST(negativeNum, signMagD){
     //Conversion of 00000000000000000000000000001100 signed magnitude binary number to signed integer is 12
    ASSERT_EQ(12, signMagnitudeDecimal("00000000000000000000000000001100"));

    //Conversion of 10000000000000000000000000001100 signed magnitude binary number to signed integer is -12
    ASSERT_EQ(-12, signMagnitudeDecimal("10000000000000000000000000001100"));

    //Conversion of 00000000000000000000001000001011 signed magnitude binary number to signed integer is 523
    ASSERT_EQ(523, signMagnitudeDecimal("00000000000000000000001000001011"));

    //Conversion of 10000000000000000000001000001011 signed magnitude binary number to signed integer is -523
    ASSERT_EQ(-523, signMagnitudeDecimal("10000000000000000000001000001011"));   
} 

//tests the conversion from ones complement to signed integer
TEST(negativeNum, OnesCompD){
    //Conversion of 00000000000000000000000000001100 one's complement binary number to signed integer is 12
    ASSERT_EQ(12, onesComplementDecimal("00000000000000000000000000001100"));

    //Conversion of 11111111111111111111111111110011 one's complement binary number to signed integer is -12
    ASSERT_EQ(-12, onesComplementDecimal("11111111111111111111111111110011"));

    //Conversion of 00000000000000000000001000001011 one's complement binary number to signed integer is 523
    ASSERT_EQ(523, onesComplementDecimal("00000000000000000000001000001011"));

    //Conversion of 11111111111111111111110111110100 one's complement binary number to signed integer is -523
    ASSERT_EQ(-523, onesComplementDecimal("11111111111111111111110111110100"));   
}

//tests the conversion from two's complement to signed integer
TEST(negativeNum, twosCompD){
    //Conversion of 00000000000000000000000000001100 two's complement binary number to signed integer is 12
    ASSERT_EQ(12, twosComplementDecimal("00000000000000000000000000001100"));

    //Conversion of 11111111111111111111111111110100 two's complement binary number to signed integer is -12
    ASSERT_EQ(-12, twosComplementDecimal("11111111111111111111111111110100"));
    
    //Conversion of 00000000000000000000001000001011 two's complement binary number to signed integer is 523
    ASSERT_EQ(523, twosComplementDecimal("00000000000000000000001000001011"));

    //Conversion of 11111111111111111111110111110101 two's complement binary number to signed integer is -523
    ASSERT_EQ(-523, twosComplementDecimal("11111111111111111111110111110101"));   
}

//Driver function launching the tests 
int main(int argc, char **argv) 
    {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }