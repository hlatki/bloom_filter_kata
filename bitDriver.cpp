#include <iostream>
#include "BitArray.h"

int main() {
    std::printf("Setting 14 and 15\n");
    BitArray b(16);
    b.setBit(15);
    b.setBit(14);
    b.printBitArray();
    std::printf("Clear 14\n");
    b.clearBit(14);
    b.printBitArray();
    std::printf("Clear 14 again\n");
    b.clearBit(14);
    b.printBitArray();
    std::printf("Set 8\n");
    b.setBit(8);
    b.printBitArray();
    std::printf("Flip 0\n");
    b.flipBit(0);
    b.printBitArray();
    std::printf("Flip 8\n");
    b.flipBit(8);
    b.printBitArray();

    return 0;
}
