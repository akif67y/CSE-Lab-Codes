#include <bits/stdc++.h>
using namespace std;
double minload = 0.25;
double maxload = 0.5;
int initalsize = 13;
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
    if (n <= 2) return 2; 
    n--; 
    while (n > 2 && !isPrime(n)) {
        n--;
    }
    return n;
}


long long  hash1_polynomial(const string &key, int m) {
    long long hashVal = 0;
    const int p = 53; 
    const int M = 1e9 + 9; 
    long long p_pow = 1;

    for (char c : key) {
        hashVal = (hashVal + (c - 'a' + 1) * p_pow) % M;
        p_pow = (p_pow * p) % M;
    }
    
  
    return (hashVal % m + m) % m;
}


long long hash2_fnv(const string &key, int m) {
    
    unsigned int hashVal = 2166136261u; 
    
 
    const unsigned int FNV_prime = 16777619u; 

    for (char c : key) {
        hashVal ^= c;           
        hashVal *= FNV_prime;   
    }
    return (long long)hashVal % m;
}



template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable( int size = initalsize, int hashId = 1 ); 
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
void HashTable<HashedObj>::makeEmpty()
{
    for( int i = 0; i < theLists.size(); i++ )
        theLists[i].clear();
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

    
    double loadFactor = (double)currentSize / theLists.size();
    if( loadFactor < minload && theLists.size() > initialTableSize ) {
      
            int targetSize = previousPrime( theLists.size() / 2 );
            if (targetSize < initialTableSize) targetSize = initialTableSize;
            rehash( targetSize );
        
    }
    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert( const HashedObj & x )
{
    int index = myhash(x);
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
    if( (double)currentSize / theLists.size() > maxload ) {
            rehash( nextPrime( 2 * theLists.size() ) );
        
    }
    return true;
}

template <typename HashedObj>
void HashTable<HashedObj>::rehash( int newSize )
{
    vector<list<HashedObj> > oldLists = theLists;
    theLists.resize( newSize );
    for( int j = 0; j < theLists.size(); j++ )
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
    const int WORD_LENGTH = 10; 


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


    HashTable<string> ht1(13, 1);
    cout << "Running Hash1 (Polynomial)..." << endl;
    for(const string &s : dataset) ht1.insert(s);
    long long collisions1 = ht1.getNumberOfCollisions();
    double avgHits1 = ht1.getAverageSearchCost(testSet);

    
    HashTable<string> ht2(13, 2); 
    cout << "Running Hash2 (FNV)..." << endl;
    for(const string &s : dataset) ht2.insert(s);
    long long collisions2 = ht2.getNumberOfCollisions();
    double avgHits2 = ht2.getAverageSearchCost(testSet);

    cout << "\n" << string(65, '-') << endl;
    cout << "Performance Comparison Report" << endl;
    cout << string(65, '-') << endl;
    cout << left << setw(20) << "Collision Method" 
         << setw(20) << "Metric"
         << setw(12) << "Hash 1" 
         << setw(12) << "Hash 2" << endl;
    
    cout << string(65, '-') << endl;

    cout << left << setw(20) << "Chaining" 
         << setw(20) << "# Collisions"
         << setw(12) << collisions1 
         << setw(12) << collisions2 << endl;

    
    cout << left << setw(20) << "" 
         << setw(20) << "Avg Hits"
         << setw(12) << fixed << setprecision(3) << avgHits1 
         << setw(12) << avgHits2 << endl;

    cout << string(65, '-') << endl;
    cout << "CSV:" << collisions1 << "," << avgHits1 << "," << collisions2 << "," << avgHits2 << endl;
    return 0;
}