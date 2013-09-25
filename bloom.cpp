#include "./lib/hashes.cpp" //hashing functions

#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <set>


using namespace std;


int main() {

    bitset<2358870> lookup;

    for (int i = 0; i < lookup.size(); i++){
        lookup.set(i,0);
    }
    char dictionaryPath[] = "/usr/share/dict/words";
    //char t[] = "cat";
    /*string t = "cat";
    int t_hashed_murmur = MurmurHash2(t.c_str(), t.length(), 0);
    long t_hashed_djb2 = djb2(t.data(), t.length());
    printf("hashed value (murmur) is: %d\n", t_hashed_murmur);
    printf("hashed value (djb2) is: %lu\n", t_hashed_djb2);
    printf("shortened value (murmur) is: %d\n", shorten((long)t_hashed_murmur));
    printf("shortened value (djb2) is: %d\n\n", shorten(t_hashed_djb2));*/
   
    set<long> wordHashes;

    ifstream dictionary;
    dictionary.open(dictionaryPath);
    int collCount = 0;
    string line;
    int boxes = 2358870;
    int wordCount = 0;
    while(!dictionary.eof()) {
        getline(dictionary, line);
        wordCount++;
        //int a,b;
        int a;
        long b;
        //a = shorten(MurmurHash2(line.c_str(), line.length(), 0));
        //a = shorten(djb2(line.c_str(), line.length()));
        a = MurmurHash2(line.c_str(), line.length(), 0) % boxes;
        b = djb2(line.c_str(), line.length()) % boxes;
        lookup[a] = 1;
        lookup[b] = 1;
        wordHashes.insert(a);
        wordHashes.insert(b);
        if (a == b) {
            collCount++;
            cout << line << "\n";
        }



    }
    
    printf("There were %d collisions.\n",collCount);
    printf("%d words in dictionary.\n",wordCount);
    cout << wordHashes.size() << " items in set of hashes.\n";

    while(1) {
        string input;
        cout << "Enter string to test: ";
        getline(cin,input);
        int t1 =  MurmurHash2(input.c_str(), input.length(), 0) % boxes;
        int t2 =  djb2(input.c_str(), input.length()) % boxes;

        cout << "t1 is: " << lookup[t1] << " & t2 is " << lookup[t2] << "\n";
        if (lookup[t1] && lookup[t2]) {
            cout << "String found in lookup\n"; 
        } else {
            cout << "Not found\n";
        }
    }



    return 0;
}
