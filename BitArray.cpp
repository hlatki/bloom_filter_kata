#include "BitArray.h"
#include <iostream>

BitArray::BitArray(int size) {
    _size = size;
    _bitArray = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        _bitArray[i] = 0;
    }
}

BitArray::~BitArray() {
    delete[] _bitArray;
}

void BitArray::findBit(int *whichChar, int *bitInChar, int pos) {
    *whichChar =  pos / 8;
    *bitInChar = pos % 8;
}

void BitArray::setBit(int pos) {
    int whichChar, bitInChar;
    findBit(&whichChar, &bitInChar, pos);

    _bitArray[whichChar] = _bitArray[whichChar] | (1 << bitInChar);
}

void BitArray::clearBit(int pos) {
    int whichChar, bitInChar;
    findBit(&whichChar, &bitInChar, pos);  
    
    _bitArray[whichChar] = _bitArray[whichChar] & ~(1 << bitInChar);
}

void BitArray::flipBit(int pos) {
    int whichChar, bitInChar;
    findBit(&whichChar, &bitInChar, pos);

    _bitArray[whichChar] = _bitArray[whichChar] ^ (1 << bitInChar);

}

bool BitArray::getBit(int pos) {
    int whichChar, bitInChar;
    findBit(&whichChar, &bitInChar, pos);

    return _bitArray[whichChar] & (1 << bitInChar);
}

void BitArray::printBitArray() {
    for (int i = 0; i < _size; i++) {
        std::cout << getBit(i);
        if ((i + 1) % 8 == 0) //print space between bytes
            std::cout << " ";
    }
    std::cout << "\n";
}

