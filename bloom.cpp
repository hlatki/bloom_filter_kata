#include "./lib/hashes.cpp" //hashing functions

#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <set>
#include <map>
#include <cmath>

// there are 235887 in the dictionary on the mac
#define BUCKETS (235887 * 12)
#define RUN_METRICS 1 

using namespace std;

void printHashStats(map<int,int> hashes) {
    int sum = 0;
    float avg = 0.0; 
    long diffSum = 0;
    float diffAvg = 0;
    float standardDev = 0;
    map<int, int> bucketCount; 
    int hashSize = hashes.size();
    
    for(map<int, int>::iterator it = hashes.begin(); it != hashes.end(); ++it) {
        sum += it->second;
        bucketCount[it->second]++;
    }
    for(map<int,int>::iterator it = bucketCount.begin(); it != bucketCount.end(); ++it) {
        float percent = ((float) it->second / (float) hashSize) * 100;
        printf("Buckets with %d item(s): %d (%f%%)\n", (int)it->first, (int)it->second, percent); 
    }

    avg = (float) sum / (float) hashSize;

    for(map<int, int>::iterator it = hashes.begin(); it != hashes.end(); ++it) {
       diffSum += pow((double)(avg - it->second), 2.0); 
    }
    diffAvg = (float) diffSum / (float) hashSize;
    standardDev = sqrt(diffAvg);


    cout << "\tAverage bucket contains: " << avg;
    cout << "\n\tWith standard deviation: " << standardDev;
}

int main() {

    bitset<BUCKETS> lookup;
    char dictionaryPath[] = "/usr/share/dict/words";

    for (int i = 0; i < lookup.size(); i++){
        lookup.set(i,0);
    }

    #if RUN_METRICS 
    //vars for doing metrics
    set<long> wordHashes;
    int collCount = 0;
    int wordCount = 0;
    #endif
    
   

    ifstream dictionary;
    dictionary.open(dictionaryPath);
    string line;

    map<int, int> murmurMap;
    map<int, int> djb2Map;
    while(!dictionary.eof()) {
        getline(dictionary, line);
        int a;
        long b;
        a = MurmurHash2(line.c_str(), line.length(), 0) % BUCKETS;
        b = djb2(line.c_str(), line.length()) % BUCKETS;
        lookup[a] = 1;
        lookup[b] = 1;

        //for metrics
        #if RUN_METRICS
        wordCount++;
        wordHashes.insert(a);
        wordHashes.insert(b);
        murmurMap[a] += 1;
        djb2Map[b] += 1;
        if (a == b) {
            collCount++;
            cout << line << "\n";
        }
        #endif
    }
    
    #if RUN_METRICS
    //formula from http://pages.cs.wisc.edu/~cao/papers/summary-cache/node8.html
    //(1 - e^(-kn/m))^k
    //where k is the number of hashing functions, n is number of keys inserted
    //and m is size of bitset
    float falsePositive = pow((1.0 - exp( -2.0 * wordCount / BUCKETS)),2.0) * 100.0;
    //Output stats
    cout << "Hash distribution: \n";
    cout << "For Murmur: \n"; 
    printHashStats(murmurMap);
    cout << "\n";
    cout << "For djb2: \n"; 
    printHashStats(djb2Map);
    cout << "\n\n";
    cout << "Bucket Size: " << BUCKETS << "\n";
    printf("There were %d collisions.\n",collCount);
    printf("%d words in dictionary.\n",wordCount);
    cout << wordHashes.size() << " items in set of hashes.\n";
    printf("Probability of false positive: %f", falsePositive);
    cout << "\n\n";
    #endif

    while(1) {
        string input;
        cout << "Enter string to test: ";
        getline(cin,input);
        int t1 =  MurmurHash2(input.c_str(), input.length(), 0) % BUCKETS;
        int t2 =  djb2(input.c_str(), input.length()) % BUCKETS;

        //cout << "t1 is: " << lookup[t1] << " & t2 is " << lookup[t2] << "\n";
        if (lookup[t1] && lookup[t2]) {
            cout << "String found in lookup\n"; 
        } else {
            cout << "Not found\n";
        }
    }



    return 0;
}
