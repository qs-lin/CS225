/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */

  std::ifstream wordsFile(filename);
  std::string word;
  if (wordsFile.is_open()) {
    while(std::getline(wordsFile,word)){
      build_word(word);
    }
  }
  //std::cout << dict.size() << std::endl;
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */

  for( std::string word : words){
    build_word(word);
/*
    std::string w = word;
    std::sort(word.begin(),word.end());
    auto it = dict.find(word);
    if(it!=dict.end()){
      std::vector<std::string>& v = it->second;
      auto iter = std::find(v.begin(),v.end(),w);
      if(iter!=v.end())
        v.push_back(w);
    }else{
      std::vector<std::string> v;
      v.push_back(w);
      dict[word] = v;
    }
*/

  }
}

void AnagramDict::build_word(std::string word){

    std::string w = word;
    std::sort(word.begin(),word.end());
    auto it = dict.find(word);
    if(it!=dict.end()){
      std::vector<std::string>& v = it->second;
      auto iter = std::find(v.begin(),v.end(),w);
      if(iter==v.end())
        v.push_back(w);
    }else{
      std::vector<std::string> v;
      v.push_back(w);
      dict[word] = v;
    }

}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
  std::string w = word;
  std::sort(w.begin(),w.end());
  auto it = dict.find(w);
  if(it!=dict.end()){
    if(it->second.size()>=2)
      return it->second;

  }   
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
  std::vector<std::vector<std::string>> results;
    for( auto& elem : dict){    
      if(elem.second.size()>=2)
        results.push_back(elem.second);
    }
    //return vector<vector<string>>();
    return results; 
}

void AnagramDict::debug(){

  std::cout << "dict size: " << dict.size() << std::endl;
  std::string test = "god";
  std::sort(test.begin(),test.end());
  std::cout << "god sorted = " << test << std::endl;

  auto it = dict.find(test);
  if(it!=dict.end()){
    for(size_t i=0;i<it->second.size();++i){
      std::cout << "start printing" << std::endl;
      std::cout << it->second[i] << std::endl;
    }
  }
  }


