


#include <iostream>
#include <assert.h>
#include <utility>
#include <string>
#include "BoolVector.h"



int main() {

    BoolVector bv1("11010100");
    std::cout << "Vector created: " << bv1 << std::endl;

 
    bv1.setBitValue(3, true);
    std::cout << "Bit set: " << bv1 << std::endl;

    bv1.setBitValue(5, true);
    std::cout << "Second bit set: " << bv1 << std::endl;

  
    bv1.setBitValue(3, false);
    std::cout << "Bit reset: " << bv1 << std::endl;

    
    bv1.invert(5);
    std::cout << "Bits inverted: " << bv1 << std::endl;

    
    bv1.setBits(0, 4, true);
    std::cout << "Multiple bits set: " << bv1 << std::endl;


    bv1.invert();
    std::cout << "All bits inverted: " << bv1 << std::endl;

    
    BoolVector bv2(bv1);
    std::cout << "Copy check: " << bv2 << std::endl;

    
    const char* bitString = "11001000";
    BoolVector bv3(bitString);
    std::cout << "Initialized from string: " << bv3 << std::endl;


    BoolVector bv4(bv3);
    std::cout << "Vector bv4 created: " << bv4 << std::endl;

    bv4 = bv1;
    std::cout << "Operator = : " << bv4 << std::endl;

    bv4& bv1;
    std::cout << "Operator & : " << bv4 << std::endl;
    bv4&= bv1;
    std::cout << "Operator &= : " << bv4 << std::endl;
    bv4 | bv1;
    std::cout << "Operator | : " << bv4 << std::endl;
    bv4 |= bv1;
    std::cout << "Operator |= : " << bv4 << std::endl;
    bv4 ^ bv1; 
    std::cout << "Operator ^ : " << bv4 << std::endl;
    ~bv4;
    std::cout << "Operator ^= : " << bv4 << std::endl;
    bv4 << 4;
    std::cout << "Operator << : " << bv4 << std::endl;
    bv4 <<= 4;
    std::cout << "Operator <<= : " << bv4 << std::endl;
    bv4 >> 4;
    std::cout << "Operator >> : " << bv4 << std::endl;
    bv4 >>= 4;
    std::cout << "Operator >>= : " << bv4 << std::endl;

    std::cout << "All tests completed" << std::endl;

}
