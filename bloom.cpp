#include "./lib/hashes.cpp" //hashing functions

#include <string>
#include <fstream>
#include <iostream>
#include <bitset>


using namespace std;
bitset<4096> lookup;

//shorten the hashed value
//advice from http://www.burtleburtle.net/bob/c/lookup3.c

int shorten (long hash) {
    return (hash & (1 << 12));
}

int main() {
    char dictionaryPath[] = "/usr/share/dict/words";
    //char t[] = "cat";
    /*string t = "cat";
    int t_hashed_murmur = MurmurHash2(t.c_str(), t.length(), 0);
    long t_hashed_djb2 = djb2(t.data(), t.length());
    printf("hashed value (murmur) is: %d\n", t_hashed_murmur);
    printf("hashed value (djb2) is: %lu\n", t_hashed_djb2);
    printf("shortened value (murmur) is: %d\n", shorten((long)t_hashed_murmur));
    printf("shortened value (djb2) is: %d\n\n", shorten(t_hashed_djb2));*/
    
    ifstream dictionary;
    dictionary.open(dictionaryPath);
    int collCount = 0;
    long max = 0;
    string line;
    while(!dictionary.eof()) {
        getline(dictionary, line);
        //int a,b;
        int a;
        long b;
        //a = shorten(MurmurHash2(line.c_str(), line.length(), 0));
        //a = shorten(djb2(line.c_str(), line.length()));
        a = MurmurHash2(line.c_str(), line.length(), 0);
        b = djb2(line.c_str(), line.length());

        if (a > max) 
            max = a;

        if (b > max)
            max = b;

        if (a == b)
            collCount++;
    }

    printf("There were %d collisions.\n",collCount);
    printf("The max value was %lu.\n",max);
    return 0;
}
