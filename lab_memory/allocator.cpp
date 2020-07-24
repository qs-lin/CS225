/**
 * @file allocator.cpp
 * Implementation of the Allocator class.
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "allocator.h"
#include "fileio.h"



Allocator::Allocator(){

  roomCount = 9;
  rooms = new Room[roomCount];


} 

Allocator::Allocator(const std::string& studentFile, const std::string& roomFile)
{
    createLetterGroups();
    loadStudents(studentFile);
    loadRooms(roomFile);
}


Allocator::~Allocator(){


  if(alpha!=nullptr)
    delete[] alpha;


  //clear();


  //if(rooms!=nullptr){delete rooms; } 
  if(rooms!=nullptr){delete[] rooms; } 
}

void Allocator::clear(){

  std::cout << "dtr : roomCount " << roomCount << std::endl;
  for(int i=0;i<roomCount;i++){
    std::cout << "freeing room : " << i << std::endl;
    rooms[i].pubclear();
  }

}


void Allocator::createLetterGroups()
{
    // Make letters (A - Z lettergroups)
    alpha = new Letter[26];
    for (int i = 0; i < 26; i++)
        alpha[i].letter = 'A' + i;
}

void Allocator::loadStudents(const std::string& file)
{
    // Read in students
    fileio::loadStudents(file);
    studentCount = fileio::getNumStudents();

    for (int i = 0; i < studentCount; i++) {
        std::string name = fileio::nextStudent();
        char letter = name[0];
        int index = (int)letter - 'A';
        alpha[index].addStudent();
    }
}

void Allocator::loadRooms(const std::string& file)
{
    // Read in rooms
    fileio::loadRooms(file);
    roomCount = fileio::getNumRooms();
    rooms = new Room[roomCount];

    totalCapacity = 0;
    int i = 0;
    while (fileio::areMoreRooms()) {
        rooms[i] = fileio::nextRoom();
        totalCapacity += rooms[i].capacity;
	//std::cout << "i: " << i << "name: " << rooms[i].name << " letterCount: " << rooms[i].letterCount <<  " capacity: " << rooms[i].capacity << std::endl;
        i++; 
    }
}


void Allocator::printStudents(std::ostream & stream /* = std::cout */)
{
    // Output number of each last letter name
    stream << "Student counts (" << studentCount << " total)" << std::endl;
    for (int i = 0; i < 26; i++)
        stream << alpha[i].letter << ": " << alpha[i].count << std::endl;
}

void Allocator::allocate()
{
    // Perform the allocation
    int border = solve();
    //std::cout << "border in the end: " << border << std::endl;

    // Check for an error
    if (border < 0) {
        std::cerr << std::endl << "Cannot allocate all students." << std::endl << std::endl;
        exit(-1);
    }
}

void Allocator::printRooms(std::ostream & stream /* = std::cout */)
{
    // Output the allocation
    stream << "Room Allocation (" << studentCount << "/" << totalCapacity << ")"
         << std::endl;
    for (int i = 0; i < roomCount; i++)
        rooms[i].print(stream);
}

int Allocator::solve()
{
    std::stable_sort(alpha, alpha + 26);

/*
    for (int L = 0; L < 26; L++) {
	//if(alpha[L].count==0) continue;
    Room* r = largestOpening();
	std::cout << "room name: " << r->name << " letter:" << alpha[L].letter << " count: " << alpha[L].count << std::endl;
	std::cout << " ---- before -------- " << std::endl;
	std::cout << " space remaining: " << r->spaceRemaining() << std::endl;
	std::cout << " letter count: "    << r->letterCount      << std::endl;
    r->addLetter(alpha[L]);
	std::cout << " ---- after  -------- " << std::endl;
	std::cout << " space remaining: " << r->spaceRemaining() << std::endl;
	std::cout << " letter count: "    << r->letterCount      << std::endl;
	int lc = r->letterCount;
	std::cout << "newest letter: " << r->letters[lc-1].letter << std::endl; 
	//std::cout << r->name << " letter:" << alpha[L].letter << " count: " << alpha[L].count << " space remaining: " << r->spaceRemaining() << std::endl; 
	if(L==25){
	  std::cout << (r) << std::endl;
	  std::cout << sizeof(*r) << std::endl;
	  std::cout << r->letters[r->letterCount-1].letter << std::endl;
	  std::cout << r->letters[r->letterCount-2].letter << std::endl;
	  std::cout << r->letters[r->letterCount-3].letter << std::endl;
	  std::cout << r->letters[r->letterCount-4].letter << std::endl;
	}

    }//end of alpha loop
*/

    //for(int L=0; L<26; L++){
    for(int L=0; L<26; L++){
      Room* r = largestOpening();
      r->addLetter(alpha[L]);
      //std::cout << sizeof(*(r->letters)) << std::endl;
    }

/*
    std::cout << alpha[25].letter << std::endl;
    std::cout << alpha[25].count << std::endl;
    Room* r = largestOpening();
    r->debug();
    //r->pubclear();
    //r->addLetter(alpha[25]);
    std::cout << "size of rooms " << sizeof(*r) << std::endl;
    //r->pubclear();
    //r->debug();

    //debug3();
*/
    return minSpaceRemaining();
}

int Allocator::minSpaceRemaining()
{
    int border = 1000000;
    for (int i = 0; i < roomCount; i++)
        if (rooms[i].spaceRemaining() < border)
            border = rooms[i].spaceRemaining();
    return border;
}

Room* Allocator::largestOpening()
{
    int index = 0;
    int max_remaining = 0;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].spaceRemaining() > max_remaining) {
            index = i;
            max_remaining = rooms[i].spaceRemaining();
        }
    }
    return &rooms[index];
}


void Allocator::debug2(const std::string& roomFile){

   //roomCount = 9;
   //rooms = new Room[roomCount];
  std::cout << "before loading " << std::endl;
/*
  for(int i=0;i<roomCount;i++){
    std::cout << "name: " << rooms[i].name << " capacity: " << rooms[i].capacity << " addr: " << &rooms[i] << std::endl;
    std::cout << "letters addr: " << rooms[i].letters << std::endl;
  }
*/
  fileio::loadRooms(roomFile);
  roomCount = fileio::getNumRooms();

  totalCapacity = 0;
  int i = 0;
  std::cout << "during loading " << std::endl;
  while (fileio::areMoreRooms()){
    rooms[i] = fileio::nextRoom();
    //std::cout << "name: " << rooms[i].name << " capacity: " << rooms[i].capacity << " addr: " << &rooms[i] << std::endl;
    std::cout << "letters addr: " << rooms[i].letters << std::endl;
    totalCapacity += rooms[i].capacity;
    std::cout << "------------" << std::endl;
    i++;
  }
/*
  std::cout << "after loading file" << std::endl;
  for(int i=0;i<roomCount;i++){
    std::cout << "name: " << rooms[i].name << " capacity: " << rooms[i].capacity << " addr: " << &rooms[i] << std::endl;
    std::cout << "letters addr: " << rooms[i].letters << std::endl;
  }
*/

}

void Allocator::debug3(){

  for(int i=0;i<roomCount;i++){
    std::cout << "name: " << rooms[i].name << " addr: " << &rooms[i] << std::endl;
    std::cout << "letters: " << rooms[i].letters << " sizeof: " << sizeof(*rooms[i].letters) << std::endl;

  }




}



void Allocator::debug(){

  std::stable_sort(alpha, alpha + 26);

  for(int i=0;i<roomCount;i++){
    std::cout << "name: " << rooms[i].name << " capacity: " << rooms[i].capacity << " addr: " << &rooms[i] << std::endl;
    std::cout << "letters addr: " << rooms[i].letters << std::endl; 
  }


  std::cout << "checking letter address" << std::endl;
  std::cout << rooms[3].letters << std::endl;
  std::cout << rooms[4].letters << std::endl;

  std::cout << std::endl;
  rooms[3].addLetter(alpha[0]);
  rooms[3].addLetter(alpha[1]);

  for(int l=0; l<rooms[3].letterCount; l++){
  //for(int l=0; l<26; l++){
    std::cout << "letter: " << rooms[3].letters[l].letter << " addr: " << (&rooms[3].letters[l]) << std::endl;
    std::cout << "letter: " << rooms[4].letters[l].letter << " addr: " << (&rooms[4].letters[l]) << std::endl;
  }

/*
  Room* r = largestOpening();
  std::cout << "large open: " << r->name << " capacity: " << r->capacity << " addr: " << r << std::endl;

  std::cout << alpha[3].letter << std::endl;
  std::cout << alpha[4].letter << std::endl;

  std::cout << r->letterCount << std::endl;
  r->addLetter(alpha[3]);
  r->addLetter(alpha[4]);

  for(int l=0; l<rooms[3].letterCount; l++){
    //std::cout << rooms[3].letters[l].letter << std::endl;
    std::cout << "letter: " << rooms[3].letters[l].letter << " addr: " << (&(rooms[3].letters[l])) << std::endl;
    std::cout << "letter: " << rooms[8].letters[l].letter << " addr: " << (&(rooms[8].letters[l])) << std::endl;
  }
*/
  
}


