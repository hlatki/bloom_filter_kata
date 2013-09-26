#include "./lib/hashes.cpp" //hashing functions

#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <set>
#include <map>
#include <cmath>


#define BUCKETS 2358870

using namespace std;

void printHashStats(map<int,int> hashes) {
    map<int, int>::iterator it;
    int sum = 0;
    float avg = 0.0; 
    long diffSum = 0;
    float diffAvg = 0;
    float standardDev = 0;


    for(map<int, int>::iterator it = hashes.begin(); it != hashes.end(); ++it) {
        sum += it->second;
    }
    avg = (float) sum / (float) hashes.size();

    for(map<int, int>::iterator it = hashes.begin(); it != hashes.end(); ++it) {
       diffSum += pow((double)(avg - it->second), 2.0); 
    }
    diffAvg = (float) diffSum / (float) hashes.size();
    standardDev = sqrt(diffAvg);


    cout << "\tAverage bucket contains: " << avg;
    cout << "\n\tWith standard deviation: " << standardDev;
}

int main() {

    bitset<BUCKETS> lookup;

    for (int i = 0; i < lookup.size(); i++){
        lookup.set(i,0);
    }


    
    char dictionaryPath[] = "/usr/share/dict/words";
   
    set<long> wordHashes;

    ifstream dictionary;
    dictionary.open(dictionaryPath);
    int collCount = 0;
    string line;
    int buckets = BUCKETS;
    int wordCount = 0;

    map<int, int> murmurMap;
    map<int, int> djb2Map;
    while(!dictionary.eof()) {
        getline(dictionary, line);
        wordCount++;
        //int a,b;
        int a;
        long b;
        //a = shorten(MurmurHash2(line.c_str(), line.length(), 0));
        //a = shorten(djb2(line.c_str(), line.length()));
        a = MurmurHash2(line.c_str(), line.length(), 0) % buckets;
        b = djb2(line.c_str(), line.length()) % buckets;
        lookup[a] = 1;
        lookup[b] = 1;
        wordHashes.insert(a);
        wordHashes.insert(b);

        murmurMap[a] += 1;
        djb2Map[b] += 1;
        if (a == b) {
            collCount++;
            cout << line << "\n";
        }
    }
    cout << "Bucket Size: " << BUCKETS << "\n";
    printf("There were %d collisions.\n",collCount);
    printf("%d words in dictionary.\n",wordCount);
    cout << wordHashes.size() << " items in set of hashes.\n";
    cout << "\n\n";
    cout << "Hash distribution: \n";
    cout << "For Murmur: \n"; 
    printHashStats(murmurMap);
    cout << "\n";
    cout << "For djb2: \n"; 
    printHashStats(djb2Map);
    cout << "\n";

    while(1) {
        string input;
        cout << "Enter string to test: ";
        getline(cin,input);
        int t1 =  MurmurHash2(input.c_str(), input.length(), 0) % buckets;
        int t2 =  djb2(input.c_str(), input.length()) % buckets;

        cout << "t1 is: " << lookup[t1] << " & t2 is " << lookup[t2] << "\n";
        if (lookup[t1] && lookup[t2]) {
            cout << "String found in lookup\n"; 
        } else {
            cout << "Not found\n";
        }
    }



    return 0;
}
