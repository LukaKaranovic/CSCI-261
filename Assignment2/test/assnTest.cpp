
#include "../src/convert.c"
#include "gtest/gtest.h"

//Tests binary addition of two unsigned decimal integers 
TEST(addsub, addB) { 
      //278893 + 2344 = 281237  
    ASSERT_STREQ("00000000000001000100101010010101", uaddBinary("1000100000101101101", "100100101000"));
    //1090 + 2981 =4071
    ASSERT_STREQ("00000000000000000000111111100111", uaddBinary("10001000010", "101110100101"));
    }

//Tests binary subtraction of two unsigned decimal integers
TEST(addsub, subB) { 
    //59032 - 10992 = 48041
    ASSERT_STREQ("00000000000000001011101110101000", usubBinary("1110011010011000", "10101011110000"));
    //272821727 - 3455 = 272818272
    ASSERT_STREQ("00010000010000101110000001100000", usubBinary("10000010000101110110111011111", "110101111111"));
    }

//Tests binary addition of two unsigned decimal integers and checks if Carry occured
TEST(addsub, cCarry) { 
    //4294967290 + 100 returns 1 as the sum is more than what could fit 
    //in 32 bit unsigned 4,294,967,295
    ASSERT_EQ(1, uaddCarry("11111111111111111111111111111010", "1100100"));
    //2863311530 + 2000 gives Carry
    ASSERT_EQ(1, uaddCarry("10101010101010101010101010101010", "1110111001101011001010000000000"));
    //278496 + 4177983 fits in 32 bits with no carry
    ASSERT_EQ(0, uaddCarry("1000011111111100000", "1111111100000000111111"));
    }

//Tests binary subtraction of two unsigned decimal integers and tests if Borrow occurs 
//Borrow = Inverse Carry, 0 means borrow occured
 TEST(addsub, cBorrow) { 
        //1223 - 4290772992 Borrow occurs when output is CF is 0
        ASSERT_EQ(0, usubBorrow("10011000111", "11111111110000000000000000000000"));
        //5 - 120
        ASSERT_EQ(0, usubBorrow("101", "1111000"));
        //30 - 5
        ASSERT_EQ(1, usubBorrow("11110", "101"));
     }

//Tests binary subtraction of two signed decimal integers
TEST(ass2C, binarySubTwos) { 
    //-214738647 - -29822
    ASSERT_STREQ("11110011001100111100110110100111", subSignedBinary("11110011001100110101100100101001", "11111111111111111000101110000010"));  
    //19887 - 2000 = 17887
    ASSERT_STREQ("00000000000000000100010111011111", subSignedBinary("00000000000000000100110110101111", "00000000000000000000011111010000"));  
    //-13 - -5 = -5
    ASSERT_STREQ("11111111111111111111111111111011", subSignedBinary("11111111111111111111111111110011", "11111111111111111111111111111000"));  
    //2188923 - -45 = 2188968
    ASSERT_STREQ("00000000001000010110011010101000", subSignedBinary("00000000001000010110011001111011", "11111111111111111111111111010011"));  
    }

//Tests if binary addition of two signed binary numbers lead to overflow
TEST(ass2C, overTestAdd) {
    //2147483647 + 55 gives overflow
    ASSERT_EQ(1, findAddOverflow("01111111111111111111111111111111","00000000000000000000000000110111")); 
     
     //55 + 55 no overflow
     ASSERT_EQ(0, findAddOverflow("00000000000000000000000000110111","00000000000000000000000000110111")); 
     
     //-1719332701 + -1994120014 overflow
     ASSERT_EQ(1, findAddOverflow("10011001100001010001000010100011","10001001001001000010010010110010")); 
     //
}

//Tests if binary subtraction of two signed binary numbers lead to overflow
TEST(ass2C, overTestSub) {
   //567789 - 23445 returns 0
    ASSERT_EQ(0, findSubOverflow("00000000000010001010100111101101","00000000000000000101101110010101")); 
    //2147438645 - -567889 return 1
    ASSERT_EQ(1, findSubOverflow("01111111111111110101000000110101","11111111111101110101010110101111")); 
     // -2147438647 - 2267889 returns 1
    ASSERT_EQ(1, findSubOverflow("10000000000000001010111111001001","00000000000001000001011001110001")); 
}


//Driver function
int main(int argc, char **argv) 
    {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }