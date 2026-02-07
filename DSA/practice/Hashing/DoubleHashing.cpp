#include <bits/stdc++.h>
using namespace std;

// =========================================================
//                  HELPER FUNCTIONS
// =========================================================

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

// =========================================================
//                  HASH FUNCTIONS
// =========================================================

// Primary Hash 1: Polynomial Rolling Hash
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

// Primary Hash 2: FNV-1a
long long hash2_fnv(const string &key, int m) {
    long long hashVal = 2166136261u;
    const int FNV_prime = 16777619;
    for (char c : key) {
        hashVal ^= c;
        hashVal *= FNV_prime;
    }
    return abs(hashVal) % m;
}

// Auxiliary Hash Function
long long auxHash(const string &key, int m) {
    long long sum = 0;
    for (char c : key) sum += c;
    return 1 + (sum % (m - 1));
}

// =========================================================
//            CLASS: DOUBLE HASHING HASH TABLE
// =========================================================

template <typename HashedObj>
class DoubleHashTable
{
  public:
    explicit DoubleHashTable( int size = 13, int hashId = 1 );
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
    
    int initialTableSize;
    int insertionsSinceExpansion;
    int deletionsSinceCompaction;

    bool isActive( int currentPos ) const;
    int findPos( const HashedObj & x ) const;
    void rehash( int newSize );
    int myhash( const HashedObj & x ) const;
};

// ---------------- Implementation ----------------

template <typename HashedObj>
DoubleHashTable<HashedObj>::DoubleHashTable( int size, int hashId ) 
    : currentSize(0), totalCollisions(0), hashFunctionId(hashId), 
      initialTableSize(size), insertionsSinceExpansion(0), deletionsSinceCompaction(0)
{
    array.resize( nextPrime( size ) );
    makeEmpty();
}

template <typename HashedObj>
void DoubleHashTable<HashedObj>::makeEmpty( )
{
    currentSize = 0;
    totalCollisions = 0;
    insertionsSinceExpansion = 0;
    deletionsSinceCompaction = 0;
    for( auto & entry : array )
        entry.info = EMPTY;
}

template <typename HashedObj>
int DoubleHashTable<HashedObj>::myhash( const HashedObj & x ) const
{
    long long val = (hashFunctionId == 1) ? 
                    hash1_polynomial(x, array.size()) : 
                    hash2_fnv(x, array.size());
    return val % array.size();
}

template <typename HashedObj>
bool DoubleHashTable<HashedObj>::isActive( int currentPos ) const
{
    return array[ currentPos ].info == ACTIVE;
}

// Used for remove/contains (does NOT count collisions)
template <typename HashedObj>
int DoubleHashTable<HashedObj>::findPos( const HashedObj & x ) const
{
    int currentPos = myhash( x );
    int offset = (int)auxHash( x, array.size() ); 
    
    while( array[ currentPos ].info != EMPTY &&
           array[ currentPos ].element != x )
    {
        currentPos += offset;  
        if( currentPos >= array.size() )
            currentPos -= array.size(); 
    }
    return currentPos;
}

// --- UPDATED INSERT TO COUNT EVERY PROBE ---
template <typename HashedObj>
bool DoubleHashTable<HashedObj>::insert( const HashedObj & x )
{
    // // 1. Calculate Initial Positions [cite: 49]
    int currentPos = myhash(x);
    int offset = (int)auxHash(x, array.size());

    // 2. Probe Loop
    // We loop as long as the spot is occupied (NOT EMPTY) and NOT the item we want.
    // Every time the loop runs, it means we "collided" or "skipped" a spot.
    while( array[currentPos].info != EMPTY && array[currentPos].element != x ) {
        
        totalCollisions++; // // <--- UPDATED: Counts every iteration [cite: 64]
        
        currentPos += offset;
        if(currentPos >= array.size()) currentPos -= array.size();
    }

    // 3. Check Duplicate
    if( array[currentPos].info == ACTIVE && array[currentPos].element == x )
        return false; 

    // 4. Insert
    // Note: If we stopped on a DELETED spot with the same value, we just overwrite/reactivate it.
    // If we stopped on EMPTY, we fill it.
    array[currentPos] = HashEntry(x, ACTIVE);
    currentSize++;
    insertionsSinceExpansion++;

    // 5. Resize Check
    if( (double)currentSize / array.size() > 0.5 ) {
         if ( insertionsSinceExpansion >= (currentSize / 2) )
            rehash( nextPrime( 2 * array.size() ) );
    }
    return true;
}

template <typename HashedObj>
bool DoubleHashTable<HashedObj>::remove( const HashedObj & x )
{
    int currentPos = findPos( x );
    if( !isActive( currentPos ) )
        return false;

    array[ currentPos ].info = DELETED;
    --currentSize;
    deletionsSinceCompaction++;

    if( (double)currentSize / array.size() < 0.25 && array.size() > initialTableSize ) {
         if( deletionsSinceCompaction >= (currentSize / 2) ) {
            int target = previousPrime( array.size() / 2 );
            if(target < initialTableSize) target = initialTableSize;
            rehash( target );
         }
    }
    return true;
}

template <typename HashedObj>
void DoubleHashTable<HashedObj>::rehash( int newSize )
{
    vector<HashEntry> oldArray = array;
    array.resize( newSize );
    
    for( auto & entry : array ) entry.info = EMPTY;
    currentSize = 0;
    
    // Reset metrics after rehash
    insertionsSinceExpansion = 0;
    deletionsSinceCompaction = 0;
    
    // Note: Re-inserting will increment totalCollisions again based on the new layout.
    // This is generally correct as rehashing is an expensive operation that involves collision resolution.
    for( auto & entry : oldArray )
        if( entry.info == ACTIVE )
            insert( entry.element );
}

template <typename HashedObj>
long long DoubleHashTable<HashedObj>::getNumberOfCollisions() const {
    return totalCollisions;
}

template <typename HashedObj>
double DoubleHashTable<HashedObj>::getAverageSearchCost( const vector<HashedObj> &testData ) {
    long long totalHits = 0;
    for( const auto &word : testData ) {
        int hits = 1; 
        
        int currentPos = myhash( word );
        int offset = (int)auxHash( word, array.size() );

        while( array[ currentPos ].info != EMPTY && 
               array[ currentPos ].element != word )
        {
            hits++;
            currentPos += offset;
            if( currentPos >= array.size() )
                currentPos -= array.size();
        }
        totalHits += hits;
    }
    return (double)totalHits / testData.size();
}

// =========================================================
//                     MAIN (TEST DRIVER)
// =========================================================

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

    // 1. Generate Data
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

    // 2. Prepare Test Set
    vector<string> testSet = dataset;
    random_device rd;
    mt19937 g(rd());
    shuffle(testSet.begin(), testSet.end(), g);
    testSet.resize(TEST_WORDS_COUNT);

    // 3. Test Double Hashing with Hash1 (Polynomial)
    cout << "Testing Double Hashing (Polynomial)..." << endl;
    DoubleHashTable<string> dh1(13, 1);
    for(const string &s : dataset) dh1.insert(s);
    
    // 4. Test Double Hashing with Hash2 (FNV)
    cout << "Testing Double Hashing (FNV)..." << endl;
    DoubleHashTable<string> dh2(13, 2);
    for(const string &s : dataset) dh2.insert(s);

    // 5. Report
    cout << "\n" << string(60, '-') << endl;
    cout << "Double Hashing Performance Report" << endl;
    cout << string(60, '-') << endl;
    
    cout << left << setw(20) << "Metric" 
         << setw(15) << "Hash 1 (Poly)" 
         << setw(15) << "Hash 2 (FNV)" << endl;
    cout << string(60, '-') << endl;

    cout << left << setw(20) << "Collisions" 
         << setw(15) << dh1.getNumberOfCollisions() 
         << setw(15) << dh2.getNumberOfCollisions() << endl;

    cout << left << setw(20) << "Avg Hits/Search" 
         << setw(15) << fixed << setprecision(3) << dh1.getAverageSearchCost(testSet)
         << setw(15) << dh2.getAverageSearchCost(testSet) << endl;

    cout << string(60, '-') << endl;
     cout << "CSV:" << dh1.getNumberOfCollisions() << "," << dh1.getAverageSearchCost(testSet) << "," << dh2.getNumberOfCollisions() << "," << dh2.getAverageSearchCost(testSet) << endl;

    return 0;
}