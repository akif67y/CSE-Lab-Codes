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

// --- HASH FUNCTIONS ---

// Primary 1: Polynomial Rolling Hash
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

// Primary 2: FNV-1a
long long hash2_fnv(const string &key, int m) {
    long long hashVal = 2166136261u;
    const int FNV_prime = 16777619;
    for (char c : key) {
        hashVal ^= c;
        hashVal *= FNV_prime;
    }
    return abs(hashVal) % m;
}

// Auxiliary Hash for Double Hashing
// Must be non-zero and relatively prime to Table Size (which is prime).
// A simple strategy: 1 + (Sum of chars) % (M - 1) is often sufficient,
// or a smaller prime calculation.
long long auxHash(const string &key, int m) {
    long long sum = 0;
    for (char c : key) sum += c;
    // Ensure result is never 0. Return value between 1 and m-1.
    long long val = 1 + (sum % (m - 1));
    return val;
}

// =========================================================
//            CLASS 1: CHAINING HASH TABLE
// =========================================================

template <typename HashedObj>
class ChainingHashTable
{
  public:
    explicit ChainingHashTable( int size = 13, int hashId = 1 );
    void makeEmpty();
    bool insert( const HashedObj & x );
    bool remove( const HashedObj & x );
    long long getNumberOfCollisions() const;
    double getAverageSearchCost( const vector<HashedObj> &testData );

  private:
    vector<list<HashedObj> > theLists;   
    int currentSize;                     
    long long totalCollisions;           
    int hashFunctionId; 
    int initialTableSize;
    int insertionsSinceExpansion;
    int deletionsSinceCompaction;

    void rehash( int newSize );
    int myhash( const HashedObj & x ) const;
};

// --- Chaining Implementation ---

template <typename HashedObj>
ChainingHashTable<HashedObj>::ChainingHashTable( int size, int hashId ) 
  : currentSize(0), totalCollisions(0), hashFunctionId(hashId), 
    initialTableSize(size), insertionsSinceExpansion(0), deletionsSinceCompaction(0)
{
    theLists.resize( nextPrime( size ) );
}

template <typename HashedObj>
int ChainingHashTable<HashedObj>::myhash( const HashedObj & x ) const
{
    long long val = (hashFunctionId == 1) ? 
                    hash1_polynomial(x, theLists.size()) : 
                    hash2_fnv(x, theLists.size());
    return val % theLists.size();
}

template <typename HashedObj>
void ChainingHashTable<HashedObj>::makeEmpty( )
{
    for( auto & thisList : theLists ) thisList.clear( );
    currentSize = 0; totalCollisions = 0; 
    insertionsSinceExpansion = 0; deletionsSinceCompaction = 0;
}

template <typename HashedObj>
bool ChainingHashTable<HashedObj>::insert( const HashedObj & x )
{
    int index = myhash(x);
    if( !theLists[index].empty() ) totalCollisions++; // Collision!

    list<HashedObj> & whichList = theLists[ index ];
    if( find( whichList.begin( ), whichList.end( ), x ) != whichList.end( ) )
        return false;
        
    whichList.push_back( x );
    ++currentSize;
    insertionsSinceExpansion++;

    if( (double)currentSize / theLists.size() > 0.5 ) {
        if ( insertionsSinceExpansion >= (currentSize / 2) )
            rehash( nextPrime( 2 * theLists.size() ) );
    }
    return true;
}

template <typename HashedObj>
bool ChainingHashTable<HashedObj>::remove( const HashedObj & x )
{
    list<HashedObj> & whichList = theLists[ myhash( x ) ];
    auto itr = find( whichList.begin( ), whichList.end( ), x );
    if( itr == whichList.end( ) ) return false;

    whichList.erase( itr );
    --currentSize;
    deletionsSinceCompaction++;

    if( (double)currentSize / theLists.size() < 0.25 && theLists.size() > initialTableSize ) {
        if( deletionsSinceCompaction >= (currentSize / 2) ) {
            int target = previousPrime( theLists.size() / 2 );
            if(target < initialTableSize) target = initialTableSize;
            rehash( target );
        }
    }
    return true;
}

template <typename HashedObj>
void ChainingHashTable<HashedObj>::rehash( int newSize )
{
    vector<list<HashedObj> > oldLists = theLists;
    theLists.resize( newSize );
    for( auto & thisList : theLists ) thisList.clear( );
    
    currentSize = 0;
    insertionsSinceExpansion = 0;
    deletionsSinceCompaction = 0;
    
    for( auto & list : oldLists )
        for( auto & x : list ) insert( x );
}

template <typename HashedObj>
long long ChainingHashTable<HashedObj>::getNumberOfCollisions() const {
    return totalCollisions;
}

template <typename HashedObj>
double ChainingHashTable<HashedObj>::getAverageSearchCost( const vector<HashedObj> &testData ) {
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

// =========================================================
//          CLASS 2: PROBING HASH TABLE (Double Hashing)
// =========================================================

template <typename HashedObj>
class ProbingHashTable
{
  public:
    explicit ProbingHashTable( int size = 13, int hashId = 1 );
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

// --- Probing Implementation ---

template <typename HashedObj>
ProbingHashTable<HashedObj>::ProbingHashTable( int size, int hashId ) 
    : currentSize(0), totalCollisions(0), hashFunctionId(hashId), 
      initialTableSize(size), insertionsSinceExpansion(0), deletionsSinceCompaction(0)
{
    array.resize( nextPrime( size ) );
    makeEmpty();
}

template <typename HashedObj>
void ProbingHashTable<HashedObj>::makeEmpty( )
{
    currentSize = 0;
    totalCollisions = 0;
    insertionsSinceExpansion = 0;
    deletionsSinceCompaction = 0;
    for( auto & entry : array )
        entry.info = EMPTY;
}

template <typename HashedObj>
bool ProbingHashTable<HashedObj>::isActive( int currentPos ) const
{
    return array[ currentPos ].info == ACTIVE;
}

// PRIMARY HASH WRAPPER
template <typename HashedObj>
int ProbingHashTable<HashedObj>::myhash( const HashedObj & x ) const
{
    long long val = (hashFunctionId == 1) ? 
                    hash1_polynomial(x, array.size()) : 
                    hash2_fnv(x, array.size());
    return val % array.size();
}

// DOUBLE HASHING FIND POSITION
template <typename HashedObj>
int ProbingHashTable<HashedObj>::findPos( const HashedObj & x ) const
{
    int currentPos = myhash( x );
    
    // Auxiliary Hash: auxHash(k)
    // Note: We cast to int for calculations, assuming table size fits in int
    int offset = (int)auxHash( x, array.size() ); 
    
    // Double Hashing Loop: (Hash(k) + i * auxHash(k)) % N
    // We already have 'currentPos' (which is Hash(k)). 
    // We add 'offset' repeatedly.
    while( array[ currentPos ].info != EMPTY &&
           array[ currentPos ].element != x )
    {
        currentPos += offset;  // The + i*auxHash step
        if( currentPos >= array.size() )
            currentPos -= array.size(); // Modulo arithmetic optimization
            
        // Note: We loop until we find the element OR an EMPTY spot.
        // DELETED spots are skipped over during search.
    }
    return currentPos;
}

template <typename HashedObj>
bool ProbingHashTable<HashedObj>::insert( const HashedObj & x )
{
    // Collision Counting Logic:
    // If the immediate primary hash index is occupied by a different element, it's a collision.
    int primaryIndex = myhash(x);
    if( array[primaryIndex].info == ACTIVE && array[primaryIndex].element != x ) {
        totalCollisions++;
    }

    int currentPos = findPos( x );
    if( isActive( currentPos ) )
        return false; // Already exists

    array[ currentPos ] = HashEntry( x, ACTIVE );
    ++currentSize;
    insertionsSinceExpansion++;

    // Load Factor > 0.5
    if( (double)currentSize / array.size() > 0.5 ) {
         if ( insertionsSinceExpansion >= (currentSize / 2) )
            rehash( nextPrime( 2 * array.size() ) );
    }
    return true;
}

template <typename HashedObj>
bool ProbingHashTable<HashedObj>::remove( const HashedObj & x )
{
    int currentPos = findPos( x );
    if( !isActive( currentPos ) )
        return false;

    array[ currentPos ].info = DELETED;
    // We don't decrement currentSize immediately in some lazy implementations,
    // but the assignment implies resizing based on N (elements present).
    // So we will decrement.
    --currentSize;
    deletionsSinceCompaction++;

    // Load Factor < 0.25
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
void ProbingHashTable<HashedObj>::rehash( int newSize )
{
    vector<HashEntry> oldArray = array;
    array.resize( newSize );
    for( auto & entry : array )
        entry.info = EMPTY;

    currentSize = 0;
    insertionsSinceExpansion = 0;
    deletionsSinceCompaction = 0;

    for( auto & entry : oldArray )
        if( entry.info == ACTIVE )
            insert( entry.element );
}

template <typename HashedObj>
long long ProbingHashTable<HashedObj>::getNumberOfCollisions() const {
    return totalCollisions;
}

template <typename HashedObj>
double ProbingHashTable<HashedObj>::getAverageSearchCost( const vector<HashedObj> &testData ) {
    long long totalHits = 0;
    for( const auto &word : testData ) {
        int hits = 1; // Initial access counts as 1
        int currentPos = myhash( word );
        int offset = (int)auxHash( word, array.size() );

        // Simulate the search loop to count hits
        while( array[ currentPos ].info != EMPTY && 
               array[ currentPos ].element != word )
        {
            hits++;
            currentPos += offset;
            if( currentPos >= array.size() )
                currentPos -= array.size();
        }
        // If found or not found, we add the hits
        totalHits += hits;
    }
    return (double)totalHits / testData.size();
}

// =========================================================
//                     MAIN FUNCTION
// =========================================================

string generateRandomString(int length) {
    string s = "";
    for(int i = 0; i < length; ++i) s += ('a' + (rand() % 26));
    return s;
}

int main() {
    srand(time(0)); 

    const int TOTAL_WORDS = 10000;
    const int TEST_WORDS_COUNT = 1000;
    const int WORD_LENGTH = 10; // n=10 as per specification

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

    // --- TEST 1: Chaining ---
    ChainingHashTable<string> chain1(13, 1);
    ChainingHashTable<string> chain2(13, 2);
    
    for(const string &s : dataset) { chain1.insert(s); chain2.insert(s); }
    
    long long c1_col = chain1.getNumberOfCollisions();
    double c1_hits = chain1.getAverageSearchCost(testSet);
    long long c2_col = chain2.getNumberOfCollisions();
    double c2_hits = chain2.getAverageSearchCost(testSet);

    // --- TEST 2: Double Hashing ---
    ProbingHashTable<string> double1(13, 1);
    ProbingHashTable<string> double2(13, 2);

    for(const string &s : dataset) { double1.insert(s); double2.insert(s); }

    long long d1_col = double1.getNumberOfCollisions();
    double d1_hits = double1.getAverageSearchCost(testSet);
    long long d2_col = double2.getNumberOfCollisions();
    double d2_hits = double2.getAverageSearchCost(testSet);

    // --- REPORT ---
    cout << "\n" << string(70, '-') << endl;
    cout << "Performance Comparison: Chaining vs Double Hashing" << endl;
    cout << string(70, '-') << endl;
    
    cout << left << setw(20) << "Collision Method" 
         << setw(16) << "Hash 1 Coll." << setw(10) << "Hits"
         << setw(16) << "Hash 2 Coll." << setw(10) << "Hits" << endl;
    
    cout << string(70, '-') << endl;

    cout << left << setw(20) << "Chaining" 
         << setw(16) << c1_col << setw(10) << fixed << setprecision(3) << c1_hits
         << setw(16) << c2_col << setw(10) << c2_hits << endl;

    cout << left << setw(20) << "Double Hashing" 
         << setw(16) << d1_col << setw(10) << fixed << setprecision(3) << d1_hits
         << setw(16) << d2_col << setw(10) << d2_hits << endl;

    cout << string(70, '-') << endl;
    
    return 0;
}