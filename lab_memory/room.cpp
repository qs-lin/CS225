/**
 * @file room.cpp
 * Implementation of the Room class.
 */

#include <iostream>
#include "room.h"

Room::Room()
    : capacity(0), count(0), max_letters(26), letters(NULL), letterCount(0)
{
}

Room::Room(const std::string& init_name, int init_capacity)
    : name(init_name),
      capacity(init_capacity),
      count(0),
      max_letters(26),
      letterCount(0)
{
    //letters = new Letter[max_letters];
    letters = new Letter[26];
}

Room::Room(const Room& other)
{
    copy(other);
}

Room& Room::operator=(const Room& other)
{
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

Room::~Room()
{
    clear();
}

void Room::addLetter(const Letter& L)
{
    //letters[letterCount++] = L;
    letters[letterCount] = L;
    //std::cout << letters << std::endl;
    letterCount+=1;
    count += L.count;
}

int Room::spaceRemaining()
{
    return capacity - count;
}

void Room::print(std::ostream & stream /* = std::cout */)
{
    stream << name << " (" << count << "/" << capacity << "):";
    for (int L = 0; L < letterCount; L++)
        stream << " " << letters[L].letter;
    stream << std::endl;
}

void Room::debug(){

  std::cout << name << std::endl;
  std::cout << this << std::endl;
  std::cout << letters << std::endl;
  std::cout << spaceRemaining() << std::endl;
  std::cout << sizeof(*this) << std::endl;
  std::cout << sizeof(letters) << std::endl;
  std::cout << letterCount << std::endl;
  for(int l=0; l<letterCount; l++){
    std::cout << letters[l].letter << std::endl;
  }


}


void Room::pubclear()
{
    if (letters != NULL)

        delete[] letters;
}

void Room::clear()
{
    if (letters != NULL)

        delete[] letters;
}

void Room::copy(const Room& other)
{
    name = other.name;
    capacity = other.capacity;
    count = other.count;
    letterCount = other.letterCount;
    //letters = other.letters;
    //letters = new Letter(*other.letters);
    letters = new Letter[max_letters];
    for(int i=0;i<max_letters;i++){
      letters[i] = other.letters[i];
    }
    //std::cout << "copy letters: " << letters << std::endl;
}
