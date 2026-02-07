#include<bits/stdc++.h>
using namespace std;

//[cite_start] [cite: 186] Hash function for string objects (Page 13)

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
int computeHash(const string & key, int tableSize)
{
    int hashVal = 0;
    for(int i = 0; i < key.length(); i++)
        hashVal = 37 * hashVal + key[i];
        
    hashVal %= tableSize;
    if(hashVal < 0)
        hashVal += tableSize;
        
    return hashVal;
}

////// [cite: 244-285] Hash Table Class Declaration (Page 18)
template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable( int size = 101 );
    bool contains( const HashedObj & x ) const;
    void makeEmpty( );
    bool insert( const HashedObj & x );
    bool remove( const HashedObj & x );
    void printTable();

  private:
    vector<list<HashedObj> > theLists;   // The array of Lists
    int currentSize;                     // Current #elements in the hashtable

    void rehash( );
    int myhash( const HashedObj & x ) const;
};

template <typename HashedObj>
HashTable<HashedObj>::HashTable( int size ) : currentSize(0)
{
    theLists.resize( nextPrime( size ) );
}

//// [cite: 290-306] Internal Hash Function (Page 19)
template <typename HashedObj>
int HashTable<HashedObj>::myhash( const HashedObj & x ) const
{
    int hashVal = computeHash(x,theLists.size());
    
    hashVal %= theLists.size();
    if( hashVal < 0 )
        hashVal += theLists.size();
        
    return hashVal;
}

//// [cite: 341-348] Make Empty Operation (Page 21)
template <typename HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
    for( int i = 0; i < theLists.size( ); i++ )
        theLists[ i ].clear( );
}

//// [cite: 351-359] Contains/Search Operation (Page 21)
template <typename HashedObj>
bool HashTable<HashedObj>::contains( const HashedObj & x ) const
{
    const list<HashedObj> & whichList = theLists[ myhash( x ) ];
    return find( whichList.begin( ), whichList.end( ), x ) != whichList.end( );
}

//// [cite: 362-385] Remove Operation (Page 21)
template <typename HashedObj>
bool HashTable<HashedObj>::remove( const HashedObj & x )
{
    list<HashedObj> & whichList = theLists[ myhash( x ) ];
    typename list<HashedObj>::iterator itr = find( whichList.begin( ), whichList.end( ), x );

    if( itr == whichList.end( ) )
        return false;

    whichList.erase( itr );
    --currentSize;
    return true;
}

//// [cite: 312-318] Insert Operation (Page 20)
template <typename HashedObj>
bool HashTable<HashedObj>::insert( const HashedObj & x )
{
    list<HashedObj> & whichList = theLists[ myhash( x ) ];
    if( find( whichList.begin( ), whichList.end( ), x ) != whichList.end( ) )
        return false;
        
    whichList.push_back( x );
    
    // Rehash; see Section 5.5
    if( ++currentSize > theLists.size( ) )
        rehash( );
        
    return true;
}

//// [cite: 1048-1086] Rehashing for Separate Chaining (Page 53)
template <typename HashedObj>
void HashTable<HashedObj>::rehash( )
{
    vector<list<HashedObj> > oldLists = theLists;
    
    // Create new double-sized, empty table
    theLists.resize( nextPrime( 2 * theLists.size( ) ) );
    for( int j = 0; j < theLists.size( ); j++ )
        theLists[ j ].clear( );
        
    // Copy table over
    currentSize = 0;
    for( int i = 0; i < oldLists.size( ); i++ )
    {
        typename list<HashedObj>::iterator itr = oldLists[ i ].begin( );
        while( itr != oldLists[ i ].end( ) )
            insert( *itr++ );
    }
}

// Added helper to visualize the chains
template <typename HashedObj>
void HashTable<HashedObj>::printTable() {
    cout << "--- Hash Table Content ---" << endl;
    for(int i = 0; i < theLists.size(); i++) {
        if(!theLists[i].empty()) {
            cout << "Index " << i << ": ";
            // Iterates through the list at this index to show the chain
            for(auto &x : theLists[i]) cout << "[" << x << "] -> ";
            cout << "NULL" << endl;
        }
    }
    cout << "--------------------------" << endl;
}


int main() {
    // 1. Create a HashTable for strings
    // Initial size is 101 by default, but we can set it small (e.g., 7) to force collisions/rehashing easily
    cout << "Creating Hash Table..." << endl;
    HashTable<string> ht(7); 

    // 2. Insert elements
    cout << "Inserting elements: Apple, Banana, Mango, Cherry, Date" << endl;
    ht.insert("Apple");
    ht.insert("Banana");
    ht.insert("Mango");
    ht.insert("Cherry");
    ht.insert("Date");
    
    // 3. Print table to see where they landed (Checking Chaining)
    ht.printTable();

    // 4. Test Contains
    cout << "\nChecking if 'Mango' exists: " << (ht.contains("Mango") ? "Yes" : "No") << endl;
    cout << "Checking if 'Grape' exists: " << (ht.contains("Grape") ? "Yes" : "No") << endl;

    // 5. Test Remove
    cout << "\nRemoving 'Banana'..." << endl;
    if(ht.remove("Banana")) {
        cout << "Banana removed successfully." << endl;
    } else {
        cout << "Banana not found." << endl;
    }

    // 6. Verify Removal
    cout << "Checking if 'Banana' exists: " << (ht.contains("Banana") ? "Yes" : "No") << endl;
    
    ht.printTable();

    return 0;
}