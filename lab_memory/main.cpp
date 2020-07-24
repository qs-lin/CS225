/**
 * @file main.cpp
 * A simple program that allocates students to rooms.
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "fileio.h"
#include "letter.h"
#include "room.h"
#include "allocator.h"

/**
 * Main routine.
 * Creates an Allocator object and allocates the students.
 */
int main()
{
    std::cout << std::endl;

    fileio::init();
    Allocator theAllocator("students.txt", "rooms.txt");
    //Allocator theAllocator;
    //theAllocator.debug3();
    theAllocator.allocate();
    //theAllocator.debug3();
    theAllocator.printRooms();
    
    fileio::halt();
    //theAllocator.debug2("rooms.txt"); 
    //theAllocator.debug();

/*
    Room room1("test1",100);
    Room room2("test2",100);
    std::cout << room1.letters << std::endl;
    std::cout << room2.letters << std::endl;
*/
    std::cout << std::endl;
    return 0;
}
