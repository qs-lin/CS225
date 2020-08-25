/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"
#include <iostream> 
 
template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{

  ++elems;
  if (shouldResize())
    resizeTable();

  unsigned int index = hashes::hash(key,size);
  std::pair<K,V> new_pair = std::make_pair(key,value);
  table[index].push_back(new_pair);
    /**
     * @todo Implement this function.
     *
     */
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo Implement this function.
     *
     * Please read the note in the lab spec about list iterators and the
     * erase() function on std::list!
     */

  typename std::list<std::pair<K,V>>::iterator it;
  unsigned int index = hashes::hash(key,size);
  for(it = table[index].begin(); it!=table[index].end(); ++it){
    if((*it).first==key){
      table[index].erase(it);
      break;  
      --elems;
    }
  }
  

}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{

    /**
     * @todo: Implement this function.
     */

  typename std::list<std::pair<K,V>>::iterator it;
  unsigned int index = hashes::hash(key,size);
  for(it = table[index].begin(); it!=table[index].end(); ++it){
    if((*it).first==key)
      return (*it).second;
  }


  return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it


    //we are doing this because we cannot simply return V()
    //since this function returns a reference to data in our map
    //whereas V() is only a tmp variable on stack
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;


}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
  //we need this typename 
  //iterator is a type since it's before it
  //the scope before iterator will imply it's a member of list (not a type), so we add typename
  typename std::list<std::pair<K, V>>::iterator it;
  size_t oldSize = size;
  size = findPrime(size * 2);
  //std::list<std::pair<K,V>>* tmp = new std::list<std::pair<K, V>>[oldSize]; 
  std::list<std::pair<K,V>>* tmp = table; 
  
  //reHashing
  table = new std::list<std::pair<K,V>>[size];
  for(size_t i=0; i<oldSize; ++i){
    for( const typename std::pair<K,V>& mypair : tmp[i] ){
      insert(mypair.first, mypair.second);           
    }
  }

  delete[] tmp;
    
    /**
     * @todo Implement this function.
     *
     * Please read the note in the spec about list iterators!
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
}

template <class K, class V>
void SCHashTable<K,V>::test(){


  //std::cout << findPrime(800) << std::endl;
  resizeTable(); 

/*
  size_t oldSize = size;
  std::list<std::pair<K,V>>* tmp = new std::list<std::pair<K, V>>[oldSize];

  tmp = table;
  for(unsigned i=0; i<oldSize; ++i){
    tmp[i] = table[i];
  }

  delete[] tmp;
*/
}
