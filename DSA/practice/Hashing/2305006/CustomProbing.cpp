#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

int nextPrime(int n) {
    if (n <= 1) return 2;
    while (!isPrime(n)) n++;
    return n;
}

int previousPrime(int n) {
    if (n < 2) return 2; 
    n--; 
    while (n > 2 && !isPrime(n)) n--;
    return n;
}

long long hash1_polynomial(const string &key, int m) {
    long long hashVal = 0;
    int p = 53; 
    long long p_pow = 1;
    for (char c : key) {
        hashVal = (hashVal + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hashVal;
}


long long hash2_fnv(const string &key, int m) {
    long long hashVal = 2166136261u;
    const int FNV_prime = 16777619;
    for (char c : key) {
        hashVal ^= c;
        hashVal *= FNV_prime;
    }
    return abs(hashVal) % m;
}


long long auxHash(const string &key, int m) {
    long long sum = 0;
    for (char c : key) sum += c;
    return 1 + (sum % (m - 1));
}


template <typename HashedObj>
class CustomHashTable
{
  public:
    explicit CustomHashTable( int size = 13, int hashId = 1, int c1 = 1, int c2 = 1 );
    void makeEmpty();
    bool insert( const HashedObj & x );
    bool remove( const HashedObj & x );
    
    long long getNumberOfCollisions() const;
    double getAverageSearchCost( const vector<HashedObj> &testData );

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;
        HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
          : element( e ), info( i ) { }
    };

    vector<HashEntry> array;
    int currentSize; 
    long long totalCollisions;
    int hashFunctionId;
    int C1;
    int C2;
    int initialTableSize;
    int insertionsSinceExpansion;
    int deletionsSinceCompaction;

    bool isActive( int currentPos ) const;
    int findPos( const HashedObj & x ) const;
    void rehash( int newSize );
    int myhash( const HashedObj & x ) const;
};

template <typename HashedObj>
CustomHashTable<HashedObj>::CustomHashTable( int size, int hashId, int c1, int c2 ) 
    : currentSize(0), totalCollisions(0), hashFunctionId(hashId), C1(c1), C2(c2),
      initialTableSize(size), insertionsSinceExpansion(0), deletionsSinceCompaction(0)
{
    array.resize( nextPrime( size ) );
    makeEmpty();
}

template <typename HashedObj>
void CustomHashTable<HashedObj>::makeEmpty( )
{
    currentSize = 0;
    totalCollisions = 0;
    insertionsSinceExpansion = 0;
    deletionsSinceCompaction = 0;
    for( auto & entry : array )
        entry.info = EMPTY;
}

template <typename HashedObj>
int CustomHashTable<HashedObj>::myhash( const HashedObj & x ) const
{
    long long val = (hashFunctionId == 1) ? 
                    hash1_polynomial(x, array.size()) : 
                    hash2_fnv(x, array.size());
    return val % array.size();
}

template <typename HashedObj>
bool CustomHashTable<HashedObj>::isActive( int currentPos ) const
{
    return array[ currentPos ].info == ACTIVE;
}
template <typename HashedObj>
int CustomHashTable<HashedObj>::findPos( const HashedObj & x ) const
{
    int tableSize = array.size();
    long long hashVal = (hashFunctionId == 1) ? 
                        hash1_polynomial(x, tableSize) : 
                        hash2_fnv(x, tableSize);
    
    long long aux = auxHash(x, tableSize);
    int i = 0;
    int currentPos = hashVal % tableSize;

    while( array[ currentPos ].info != EMPTY &&
           array[ currentPos ].element != x )
    {
        i++;
        long long offset = (long long)C1 * i * aux + (long long)C2 * i * i;
        currentPos = (hashVal + offset) % tableSize;
    }
    return currentPos;
}

template <typename HashedObj>
bool CustomHashTable<HashedObj>::insert( const HashedObj & x )
{
    int tableSize = array.size();
    long long hashVal = (hashFunctionId == 1) ? 
                        hash1_polynomial(x, tableSize) : 
                        hash2_fnv(x, tableSize);
    long long aux = auxHash(x, tableSize);

    int i = 0;
    int currentPos = hashVal % tableSize;
    while( array[currentPos].info != EMPTY && array[currentPos].element != x ) {
        totalCollisions++; 
        i++;
        long long offset = (long long)C1 * i * aux + (long long)C2 * i * i;
        currentPos = (hashVal + offset) % tableSize;
    }
    if( array[currentPos].info == ACTIVE && array[currentPos].element == x )
        return false; 
    array[currentPos] = HashEntry(x, ACTIVE);
    currentSize++;
    insertionsSinceExpansion++;
    if( (double)currentSize / array.size() > 0.5 ) {
            rehash( nextPrime( 2 * array.size() ) );
    }
    return true;
}

template <typename HashedObj>
bool CustomHashTable<HashedObj>::remove( const HashedObj & x )
{
    int currentPos = findPos( x );
    if( !isActive( currentPos ) )
        return false;

    array[ currentPos ].info = DELETED;
    --currentSize;
    deletionsSinceCompaction++;
    if( (double)currentSize / array.size() < 0.25 && array.size() > initialTableSize ) {
         
            int target = previousPrime( array.size() / 2 );
            if(target < initialTableSize) target = initialTableSize;
            rehash( target );
         
    }
    return true;
}

template <typename HashedObj>
void CustomHashTable<HashedObj>::rehash( int newSize )
{
    vector<HashEntry> oldArray = array;
    array.resize( newSize );
    
    for( auto & entry : array ) entry.info = EMPTY;
    currentSize = 0;
    insertionsSinceExpansion = 0;
    deletionsSinceCompaction = 0;
    for( auto & entry : oldArray )
        if( entry.info == ACTIVE )
            insert( entry.element );
}

template <typename HashedObj>
long long CustomHashTable<HashedObj>::getNumberOfCollisions() const {
    return totalCollisions;
}

template <typename HashedObj>
double CustomHashTable<HashedObj>::getAverageSearchCost( const vector<HashedObj> &testData ) {
    long long totalHits = 0;
    for( const auto &word : testData ) {
        int hits = 1; 
        int tableSize = array.size();
        long long hashVal = (hashFunctionId == 1) ? 
                            hash1_polynomial(word, tableSize) : 
                            hash2_fnv(word, tableSize);
        long long aux = auxHash(word, tableSize);
        
        int i = 0;
        int currentPos = hashVal % tableSize;

        while( array[ currentPos ].info != EMPTY && 
               array[ currentPos ].element != word )
        {
            hits++;
            i++;
            long long offset = (long long)C1 * i * aux + (long long)C2 * i * i;
            currentPos = (hashVal + offset) % tableSize;
        }
        totalHits += hits;
    }
    return (double)totalHits / testData.size();
}

string generateRandomString(int length) {
    string s = "";
    for(int i = 0; i < length; ++i) s += ('a' + (rand() % 26));
    return s;
}

int main() {
    srand(42); 

    const int TOTAL_WORDS = 10000;
    const int TEST_WORDS_COUNT = 1000;
    const int WORD_LENGTH = 10;
    

    const int C1 = 13;
    const int C2 = 11;

  
    vector<string> dataset;
    set<string> uniqueChecker;
    cout << "Generating " << TOTAL_WORDS << " unique words..." << endl;
    while(dataset.size() < TOTAL_WORDS) {
        string s = generateRandomString(WORD_LENGTH);
        if(uniqueChecker.find(s) == uniqueChecker.end()) {
            uniqueChecker.insert(s);
            dataset.push_back(s);
        }
    }


    vector<string> testSet = dataset;
    random_device rd;
    mt19937 g(rd());
    shuffle(testSet.begin(), testSet.end(), g);
    testSet.resize(TEST_WORDS_COUNT);

    cout << "Testing Custom Probing (Polynomial)..." << endl;
    CustomHashTable<string> ch1(13, 1, C1, C2);
    for(const string &s : dataset) ch1.insert(s);
  
    cout << "Testing Custom Probing (FNV)..." << endl;
    CustomHashTable<string> ch2(13, 2, C1, C2);
    for(const string &s : dataset) ch2.insert(s);

    cout << "\n" << string(60, '-') << endl;
    cout << "Custom Probing Performance Report (C1=" << C1 << ", C2=" << C2 << ")" << endl;
    cout << string(60, '-') << endl;
    
    cout << left << setw(20) << "Metric" 
         << setw(15) << "Hash 1 (Poly)" 
         << setw(15) << "Hash 2 (FNV)" << endl;
    cout << string(60, '-') << endl;

    cout << left << setw(20) << "Collisions" 
         << setw(15) << ch1.getNumberOfCollisions() 
         << setw(15) << ch2.getNumberOfCollisions() << endl;

    cout << left << setw(20) << "Avg Hits/Search" 
         << setw(15) << fixed << setprecision(3) << ch1.getAverageSearchCost(testSet)
         << setw(15) << ch2.getAverageSearchCost(testSet) << endl;

    cout << string(60, '-') << endl;
    cout << "CSV:" << ch1.getNumberOfCollisions() << "," << ch1.getAverageSearchCost(testSet) << "," << ch2.getNumberOfCollisions() << "," <<ch2.getAverageSearchCost(testSet) << endl;
    
    return 0;
}