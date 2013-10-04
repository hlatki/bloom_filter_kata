#ifndef __BITARRAY_H
#define __BITARRAY_H

class BitArray {
    private:
        int _size;
        unsigned char* _bitArray;
        void findBit(int *whichChar, int *bitInChar, int pos); 
    public:
        BitArray(int size);
        ~BitArray();
        void setBit(int pos);
        void clearBit(int pos);
        void flipBit(int pos);
        bool getBit(int pos);
        void printBitArray();

};
#endif 
