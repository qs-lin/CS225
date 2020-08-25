/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */


  ++elems;
  if(shouldResize()){
    //std::cout << "elems: " << elems << " size: " << size << " need resizing "  << std::endl;
    resizeTable();
  }  
  size_t index = hashes::hash(key,size);
  size_t idx = index;
/*
  while(table[index]!=nullptr){
    ++index;
  }
*/

  for(size_t i=0; i<size; ++i){
    idx = (i+index)%size;
    if(table[idx]==nullptr)
      break;  
  }
  typename std::pair<K,V> new_pair = std::make_pair(key,value);
  table[idx] = new std::pair<K,V>(new_pair); 
  should_probe[idx] = true;

}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{

  int i= findIndex(key);
  if(i==-1) return;

  if(table[i]!=nullptr){
    delete table[i];
    table[i] = nullptr;
    --elems;
  }
  should_probe[i] = false; 
    /**
     * @todo: implement this function
     */
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    
    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */

  size_t index = hashes::hash(key,size);
  size_t idx = index;
  for(size_t i=0; i<size; ++i){
    idx = (index+i)%size;
    if(should_probe[idx]==false) continue;
    if(table[idx]==nullptr) continue;
    if( (*table[idx]).first == key )
      return static_cast<int>(idx); 

  }
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++){
      if(table[i]!=nullptr)
        delete table[i];
    }      
    if(table!=nullptr)
      delete[] table;
    if(should_probe!=nullptr)
      delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{

//this original method will make duplicates and not efficient
/*
  //std::cout << "-------- resizing -------------" << std::endl; 
  size_t oldSize = size;
  size = findPrime(2*size);

  std::pair<K,V>** tmp_table = table; 
  bool* tmp_probe  = should_probe; 

  for(size_t i=0; i<oldSize; ++i){
    tmp_table[i]  = table[i];
    //tmp_probe[i] = should_probe[i];
  }

  table = new std::pair<K,V>*[size];
  should_probe = new bool[size]; 
  for(size_t i=0; i<size; ++i){
    table[i] = nullptr;
    should_probe[i] = false;
  }


  for(size_t i=0; i<oldSize; ++i){
    if(tmp_probe[i]==true){
    //if(tmp_probe[i]==true && table[i]!=nullptr){
      insert(tmp_table[i]->first,tmp_table[i]->second);
    }
  }   


  for(size_t i=0; i<oldSize; ++i){
    if(tmp_table[i]!=nullptr)
      delete tmp_table[i];
  }

  delete[] tmp_table;
  delete[] tmp_probe;
*/

//this new method simply move pointers around

  size_t newSize = findPrime(2*size);
  std::pair<K,V>** tmp = new std::pair<K,V>*[newSize];
  delete[] should_probe;
  should_probe = new bool[newSize];

  for(size_t i=0; i<newSize; ++i){
    tmp[i] = nullptr;
    should_probe[i] = false;
  }

  for(size_t i=0; i<size; ++i){
    if(table[i]==nullptr) continue;
    size_t idx = hashes::hash(table[i]->first,newSize); 

    while(tmp[idx]!=nullptr)
      idx = (idx + 1)%newSize;  

    tmp[idx] = table[i];
    should_probe[idx] = true;
  }

  delete[] table;
  table = tmp;
  size = newSize;


/*
  for(size_t i=0; i<oldSize; ++i){
    if(should_probe[i]==true){
      size_t index = hashes::hash(table[i]->first,size);


    }
  }
*/
    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
}


template <class K, class V>
void LPHashTable<K,V>::debug(){


  std::cout << "orig size: " << size << std::endl;
  resizeTable();
  std::cout << "new size: " << size << std::endl;
  
}
