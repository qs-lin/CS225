#include <iostream>

#include "lphashtable.h"
#include "schashtable.h"
#include "dhhashtable.h"
#include "textfile.h"

using std::string;

int main()
{
    std::cout << "This main file is for you to write and run your own test cases." << std::endl;
    std::cout << "To run the provided test cases, run `./test`" << std::endl;
    // feel free to insert manual test cases here

/*
  SCHashTable<std::string,int> schash(15);
  schash.insert("test1",10);
  schash.insert("test2",11);
  std::cout << schash.find("test1") << std::endl;
  std::cout << schash.find("test2") << std::endl;
  schash.remove("test2");
  std::cout << schash.find("test2") << std::endl;

  schash.test();
*/

/*
  LPHashTable<std::string,int> lphash(15);
  lphash.insert("test1",10);
  lphash.insert("test2",20);
  std::cout << lphash["test1"] << std::endl;
  std::cout << lphash.find("test2") << std::endl;
  std::cout << lphash.find("test3") << std::endl;
  lphash.remove("test1");
  lphash.remove("test2");
  lphash.remove("test3");
*/

/*
    TextFile infile( "tests/textEasy.txt" );
    LPHashTable<string, int> hashTable(100);
    while( infile.good() ) {
        string word = infile.getNextWord();
        hashTable.insert(word, 0);
    }
    std::cout << "insert done" << std::endl;

    hashTable.insert("__SENTINEL__", 0);
    if( !hashTable.keyExists("__SENTINEL__") )
      std::cout << "insert not working" << std::endl;

    hashTable.remove("all");
    std::cout << "remove done" << std::endl;


    if( hashTable.keyExists("all") )
        std::cout << "Did not remove key: 'all'" << std::endl;


    std::cout << "LINE: " << __LINE__ << std::endl;

    hashTable.remove("base");
    std::cout << "remove done" << std::endl;
    if( hashTable.keyExists("base") )
        std::cout << "Did not remove key: 'base'" << std::endl;
*/



/*
    TextFile infile( "tests/textEasy.txt" );
    LPHashTable<string, int> hashTable(100);

    while( infile.good() ) {
        string word = infile.getNextWord();
        hashTable.insert(word, 0);
    }

    hashTable.debug();
*/




/*
    TextFile infile( "tests/textLong.txt" );
    LPHashTable<string, int> hashTable(16);

    int val = 0;
    while( infile.good() ) {
        string word = infile.getNextWord();
        if( !hashTable.keyExists(word) ) {
            val++;
            hashTable.insert(word, val);
        }
    }
*/

    //std::cout << "size: " << hashTable.tableSize() << std::endl;
    //std::cout << "val: " << val << std::endl; 

/*
    REQUIRE(hashTable.tableSize() >= val / 0.7);
    if( hashTable.find("got") != 2 )
        FAIL("Didn't copy over existing lists properly on resize");
    if( hashTable.find("to") != 3 )
        FAIL("Didn't re-hash keys properly");

    REQUIRE(true);
*/


    TextFile infile( "tests/textEasy.txt" );
    DHHashTable<string, int> hashTable(32);
    while( infile.good() ) {
        string word = infile.getNextWord();
        hashTable.insert(word, 0);
    }
  return 0;
}
