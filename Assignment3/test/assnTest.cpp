#include "../src/convert.c"
#include "gtest/gtest.h"

//To test unsigned multiplication of two binary numbers
TEST(mul, binMul) 
    { 
        //4567 * 345 = 1575615
    ASSERT_STREQ("0000000000000000000000000000000000000000000110000000101010111111", uMultiplication("01000111010111", "00101011001"));  
    //88945 * 1000 = 88945000
    ASSERT_STREQ("0000000000000000000000000000000000000101010011010011000101101000", uMultiplication("0010101101101110001", "00000001111101000"));  
    
    //2111111111 * 2111111111 = 4456790122987654144
    ASSERT_STREQ("0011110111011001101100110000000011110111001001100000110010110001", uMultiplication("1111101110101001111111111000111", "1111101110101001111111111000111"));    

    }

//To test signed multiplication of two binary numbers
TEST(mul, binMulBoot) 
    { 
        //17 X 33 = 561
    ASSERT_STREQ("0000000000000000000000000000000000000000000000000000001000110001", bootMultiplication("00000000000000000000000000010001","00000000000000000000000000100001"));  
    //-2089  X 33 = -68937
    ASSERT_STREQ("1111111111111111111111111111111111111111111111101111001010110111", bootMultiplication("11111111111111111111011111010111", "00000000000000000000000000100001")); 
    // -2089 X -33 
    ASSERT_STREQ("0000000000000000000000000000000000000000000000010000110101001001", bootMultiplication("11111111111111111111011111010111", "11111111111111111111111111011111")); 

    //2111111111 * 2111111111 = 4456790122987654144
    ASSERT_STREQ("0011110111011001101100110000000011110111001001100000110010110001", bootMultiplication("01111101110101001111111111000111", "01111101110101001111111111000111"));  

    //-2111111111 * 2111111111 = -4456790122987654144
    ASSERT_STREQ("1100001000100110010011001111111100001000110110011111001101001111", bootMultiplication("10000010001010110000000000111001", "01111101110101001111111111000111"));  

    //-2111111111 * -2111111111 = 4456790122987654144
    ASSERT_STREQ("0011110111011001101100110000000011110111001001100000110010110001", bootMultiplication("10000010001010110000000000111001", "10000010001010110000000000111001"));  
    }

//To test quotient of unsigned division of two binary numbers
TEST(div, binResQ) 
    { 
        // 4567 / 345 = 13
    ASSERT_STREQ("00000000000000000000000000001101", restoredDivisionQ("00000000000000000001000111010111", "00000000000000000000000101011001"));  

    // 10000000 / 100 = 100000    
    ASSERT_STREQ("00000000000000011000011010100000", restoredDivisionQ("00000000100110001001011010000000", "00000000000000000000000001100100"));  
    }

//To test remainder of unsigned division of two binary numbers
TEST(div, binResR) 
    { 
        // 4567 % 345 = 82
    ASSERT_STREQ("00000000000000000000000001010010", restoredDivisionR("00000000000000000001000111010111", "00000000000000000000000101011001"));  
    // 10000000 / 100 = 100000
    
    ASSERT_STREQ("00000000000000000000000000000000", restoredDivisionR("00000000100110001001011010000000", "00000000000000000000000001100100"));  
    }
    

//Driver Program
int main(int argc, char **argv) 
    {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }