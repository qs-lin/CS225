/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());
    file_word_maps.clear();

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        std::map<std::string,unsigned int> map;
        vector<string> words = file_to_vector(filenames[i]);
        for( const string& w : words ){
          //std::map<std::string,unsigned int>::iterator it = map.find(w);
          map[w]++;
        }
        /* Your code goes here! */
    file_word_maps.push_back(map);
/*
    //std::cout << "map size: " << map.size() << std::endl;

    for( auto& elem : map)
      std::cout << "word: " << elem.first << " freq: " << elem.second << std::endl;
    }
  
    std::cout << "last step: " << file_word_maps.size() << std::endl;
    std::cout << "filenames size: " << filenames.size() << std::endl;
*/
  }
}

void CommonWords::init_common()
{
    /* Your code goes here! */

  size_t index = 0;
  size_t min = file_word_maps[0].size();

  //std::cout << "min: " << min << std::endl;
  //std::cout << "index: " << index << std::endl;

  for(size_t i=0; i<file_word_maps.size(); ++i){ 
    if (file_word_maps[i].size()<min){
      index = i; 
      min = file_word_maps[i].size();
    }  
  }

  //std::cout << "min: " << min << std::endl;
  //std::cout << "index: " << index << std::endl;

/*
  std::cout << " ------ min -------- " << std::endl;
  for( auto& elem : file_word_maps[index])
    std::cout << "word: " << elem.first << " freq: " << elem.second << std::endl;
*/
  for( auto& word_pair : file_word_maps[index] ){
    bool exist_in_all = true;
    unsigned int min_freq = word_pair.second; 
    for( auto& map : file_word_maps){
      if(map[word_pair.first]==0) {
        exist_in_all = false;
        break; 
      }
      else{
        if(map[word_pair.first] < min_freq)
          min_freq = map[word_pair.first];
      }
    
    }//loop of files
    if(exist_in_all) common[word_pair.first] = min_freq; 
  }//loop of word

/*
  std::cout << " ------ common -------- " << std::endl;
  for( auto& elem : common)
    std::cout << "word: " << elem.first << " freq: " << elem.second << std::endl;
*/    
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    for( auto& word_pair : common ){
      if(word_pair.second < n) continue;
      out.push_back(word_pair.first);
    } 
    /* Your code goes here! */
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
