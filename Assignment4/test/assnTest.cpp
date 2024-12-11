#include "../src/convert.c"
#include "gtest/gtest.h"

//Tests if a binary string eneterd is in 16bit.16bit format 
TEST(fltfix, checkB){
    ASSERT_EQ(1, isFixedBinary("1100110011001100.1111001100110011"));
    ASSERT_EQ(0, isFixedBinary("1100E10011001100.1111001100110011"));
    ASSERT_EQ(0, isFixedBinary("110011001100.1111100110011"));
}

//tests the conversion of unsigned number to fixed point format UQ16.16
TEST(fltfix, binUnsign)  { 
    ASSERT_STREQ("0000000000000011.0010010000111111", fixedUnsignedBinary(3.141593));  
    ASSERT_STREQ("1111111111111110.1110010000000000", fixedUnsignedBinary(65534.8906257)); 
    ASSERT_STREQ("0000000000000001.1111110101110000", fixedUnsignedBinary(1.99)); 
    }

//tests the conversion of signed number to fixed point format Q15.16 (sign bit 15 bits.16 bits) 
TEST(fltfix, binsign)  { 
    ASSERT_STREQ("1111111111111100.1101101111000001", fixedSignedBinary(-3.141593));
    ASSERT_STREQ("1000000000100001.0011110100000000", fixedSignedBinary(-32734.76223));
    ASSERT_STREQ("0111111111011110.1100001100000000", fixedSignedBinary(32734.76223));
    }

//tests the conversion of a fixed point format Q15.16 to a decimal float
//difference of 0.001 between actual and cacluated value is admissible
TEST(fix, decUsign) { 
    ASSERT_NEAR(3.141586, fixedBinaryToFloat("0000000000000011.0010010000111111"), 0.001);  
    ASSERT_NEAR(52428.949219, fixedBinaryToFloat("1100110011001100.1111001100110011"), 0.001);
    ASSERT_NEAR(65535.601562, fixedBinaryToFloat("1111111111111111.1001101000000000"), 0.0001);  
    }

//tests the conversion of a fixed point format Q15.16 (sign bit 15 bits.16 bits) to signed float.
//noise of 0.001 is admissible
TEST(fix, decSign)  { 
    ASSERT_NEAR(3.141586, fixedSignBinaryToFloat("0000000000000011.0010010000111111"), 0.001);  
   ASSERT_NEAR(-3.141586, fixedSignBinaryToFloat("1111111111111100.1101101111000001"), 0.001);
   ASSERT_NEAR(-3854.100098, fixedSignBinaryToFloat("1111000011110001.1110011000100000"), 0.001);  
   }
   
//tests the conversion of a 32 bit binary number in the form of IEEE754 Single point precison 
//to a float. Noise of 0.001 is admissible  
TEST(fltfix, binFloat) 
    { 
    ASSERT_NEAR(14.5, BinaryIEEE754toFloat("01000001011010000000000000000000"), 0.001);  
    ASSERT_NEAR(-31.875, BinaryIEEE754toFloat("11000001111111110000000000000000"), 0.01);  
    ASSERT_NEAR(0.000021, BinaryIEEE754toFloat("00110111101100000010100100101000"), 0.01);  
   ASSERT_NEAR(0.0000000000012, BinaryIEEE754toFloat("00101011101010001110001010001110"), 0.01);  
    ASSERT_NEAR(-0.0000000000012, BinaryIEEE754toFloat("10101011101010001110001010001110"), 0.01);  
    }

//tests the conversion of a float to 32 bit binary number in the form of IEEE754 Single point precison 
//Noise of 0.001 is admissible
TEST(fltfix, floatBin) { 
    ASSERT_STREQ("01000001011010000000000000000000", floatingToIEEE754Binary(14.5));
    ASSERT_STREQ("01011001001001001100110001001000", floatingToIEEE754Binary(2899156690888224.112488997));      
    ASSERT_STREQ("00110111101100000010100100101000", floatingToIEEE754Binary(0.000021)); 
    ASSERT_STREQ("00101011101010001110001010001110", floatingToIEEE754Binary(0.0000000000012)); 
     ASSERT_STREQ("10101011101010001110001010001110", floatingToIEEE754Binary(-0.0000000000012));     
    }

int main(int argc, char **argv) 
    {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }