#include <bits/stdc++.h>
using namespace std;

// --- Helper Functions ---

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
    while (n > 2 && !isPrime(n)) {
        n--;
    }
    return n;
}

// --- Hash Functions ---

// Hash1: Polynomial Rolling Hash (Your original)
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

// Hash2: FNV-1a Hash
// A standard non-cryptographic hash function known for good dispersion
long long hash2_fnv(const string &key, int m) {
    long long hashVal = 2166136261u; // FNV Offset Basis
    const int FNV_prime = 16777619;  // FNV Prime

    for (char c : key) {
        hashVal ^= c;
        hashVal *= FNV_prime;
        // We do not mod here to keep the 32-bit property active 
        // until the very end, but for this implementation we just 
        // need a raw integer to mod later.
    }
    // Return absolute value to ensure positive index
    return abs(hashVal) % m;
}

// --- HashTable Class ---

template <typename HashedObj>
class HashTable
{
  public:
    // whichHash: 1 for Polynomial, 2 for FNV
    explicit HashTable( int size = 13, int hashId = 1 ); 
    bool contains( const HashedObj & x ) const;
    void makeEmpty( );
    bool insert( const HashedObj & x );
    bool remove( const HashedObj & x );

    long long getNumberOfCollisions() const;
    double getAverageSearchCost( const vector<HashedObj> &testData );

  private:
    vector<list<HashedObj> > theLists;   
    int currentSize;                     
    long long totalCollisions;           
    int hashFunctionId; // 1 or 2

    // Resizing constraints
    int initialTableSize;
    int insertionsSinceExpansion;
    int deletionsSinceCompaction;

    void rehash( int newSize );
    int myhash( const HashedObj & x ) const;
};

template <typename HashedObj>
HashTable<HashedObj>::HashTable( int size, int hashId ) 
  : currentSize(0), totalCollisions(0), hashFunctionId(hashId), 
    initialTableSize(size), insertionsSinceExpansion(0), deletionsSinceCompaction(0)
{
    theLists.resize( nextPrime( size ) );
}

template <typename HashedObj>
int HashTable<HashedObj>::myhash( const HashedObj & x ) const
{
    long long hashVal;
    if (hashFunctionId == 1) {
        hashVal = hash1_polynomial(x, theLists.size());
    } else {
        hashVal = hash2_fnv(x, theLists.size());
    }
    
    int index = hashVal % theLists.size();
    if( index < 0 ) index += theLists.size();
        
    return index;
}

template <typename HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
    for( int i = 0; i < theLists.size( ); i++ )
        theLists[ i ].clear( );
    currentSize = 0;
    totalCollisions = 0; 
    insertionsSinceExpansion = 0;
    deletionsSinceCompaction = 0;
}

template <typename HashedObj>
bool HashTable<HashedObj>::contains( const HashedObj & x ) const
{
    const list<HashedObj> & whichList = theLists[ myhash( x ) ];
    return find( whichList.begin( ), whichList.end( ), x ) != whichList.end( );
}

template <typename HashedObj>
bool HashTable<HashedObj>::remove( const HashedObj & x )
{
    list<HashedObj> & whichList = theLists[ myhash( x ) ];
    typename list<HashedObj>::iterator itr = find( whichList.begin( ), whichList.end( ), x );

    if( itr == whichList.end( ) )
        return false;

    whichList.erase( itr );
    --currentSize;
    deletionsSinceCompaction++;

    // Downsizing Logic
    double loadFactor = (double)currentSize / theLists.size();
    if( loadFactor < 0.25 && theLists.size() > initialTableSize ) {
        if( deletionsSinceCompaction >= (currentSize / 2) ) {
            int targetSize = previousPrime( theLists.size() / 2 );
            if (targetSize < initialTableSize) targetSize = initialTableSize;
            rehash( targetSize );
        }
    }
    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert( const HashedObj & x )
{
    int index = myhash(x);
    
    // Collision: List is not empty = existing keys mapped here
    if( !theLists[index].empty() ) {
        totalCollisions++; 
    }

    list<HashedObj> & whichList = theLists[ index ];
    if( find( whichList.begin( ), whichList.end( ), x ) != whichList.end( ) )
        return false;
        
    whichList.push_back( x );
    ++currentSize;
    insertionsSinceExpansion++;

    // Upsizing Logic
    if( (double)currentSize / theLists.size() > 0.5 ) {
        if ( insertionsSinceExpansion >= (currentSize / 2) ) {
            rehash( nextPrime( 2 * theLists.size() ) );
        }
    }
    return true;
}

template <typename HashedObj>
void HashTable<HashedObj>::rehash( int newSize )
{
    vector<list<HashedObj> > oldLists = theLists;
    theLists.resize( newSize );
    for( int j = 0; j < theLists.size( ); j++ )
        theLists[ j ].clear( );
        
    currentSize = 0;
    insertionsSinceExpansion = 0;
    deletionsSinceCompaction = 0;
    
    for( int i = 0; i < oldLists.size( ); i++ )
    {
        typename list<HashedObj>::iterator itr = oldLists[ i ].begin( );
        while( itr != oldLists[ i ].end( ) )
            insert( *itr++ );
    }
}

template <typename HashedObj>
long long HashTable<HashedObj>::getNumberOfCollisions() const {
    return totalCollisions;
}

// Helper to run search test on a batch of words
template <typename HashedObj>
double HashTable<HashedObj>::getAverageSearchCost( const vector<HashedObj> &testData ) {
    long long totalHits = 0;
    for( const auto &word : testData ) {
        int hits = 0;
        const list<HashedObj> & whichList = theLists[ myhash( word ) ];
        for( const auto & entry : whichList ) {
            hits++; 
            if( entry == word ) break;
        }
        totalHits += hits;
    }
    return (double)totalHits / testData.size();
}

// --- MAIN FUNCTION ---

string generateRandomString(int length) {
    string s = "";
    for(int i = 0; i < length; ++i) {
        s += ('a' + (rand() % 26));
    }
    return s;
}

int main() {
    srand(42); 

    const int TOTAL_WORDS = 10000;
    const int TEST_WORDS_COUNT = 1000;
    const int WORD_LENGTH = 7; // Use 7 or 10 as per preference

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

    // 2. Prepare Test Set (1000 random words from dataset)
    vector<string> testSet = dataset;
    random_device rd;
    mt19937 g(rd());
    shuffle(testSet.begin(), testSet.end(), g);
    testSet.resize(TEST_WORDS_COUNT);

    // --- TEST 1: Hash1 (Polynomial) ---
    HashTable<string> ht1(13, 1); // ID 1 = Polynomial
    cout << "Running Hash1 (Polynomial)..." << endl;
    for(const string &s : dataset) ht1.insert(s);
    long long collisions1 = ht1.getNumberOfCollisions();
    double avgHits1 = ht1.getAverageSearchCost(testSet);

    // --- TEST 2: Hash2 (FNV) ---
    HashTable<string> ht2(13, 2); // ID 2 = FNV
    cout << "Running Hash2 (FNV)..." << endl;
    for(const string &s : dataset) ht2.insert(s);
    long long collisions2 = ht2.getNumberOfCollisions();
    double avgHits2 = ht2.getAverageSearchCost(testSet);

    // --- REPORT GENERATION ---
    // Format based on the assignment table
    cout << "\n" << string(65, '-') << endl;
    cout << "Performance Comparison Report" << endl;
    cout << string(65, '-') << endl;
    
    // Header
    cout << left << setw(20) << "Collision Method" 
         << setw(20) << "Metric"
         << setw(12) << "Hash 1" 
         << setw(12) << "Hash 2" << endl;
    
    cout << string(65, '-') << endl;

    // Row 1: Number of Collisions
    cout << left << setw(20) << "Chaining" 
         << setw(20) << "# Collisions"
         << setw(12) << collisions1 
         << setw(12) << collisions2 << endl;

    // Row 2: Average Hits
    cout << left << setw(20) << "" 
         << setw(20) << "Avg Hits"
         << setw(12) << fixed << setprecision(3) << avgHits1 
         << setw(12) << avgHits2 << endl;

    cout << string(65, '-') << endl;
    // Add this before return 0;
    cout << "CSV:" << collisions1 << "," << avgHits1 << "," << collisions2 << "," << avgHits2 << endl;
    return 0;
}