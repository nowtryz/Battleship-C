#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h> // for the NULL cosntant
#include "types.h" // for tinyint

// directions
#define UP '8' // Up direction char code (numpad)
#define DOWN '2' // Down direction char code (numpad)
#define LEFT '4' // Left direction char code (numpad)
#define RIGHT '6' // Right direction char code (numpad)

// Boats ids
#define CARRIER 0
#define CRUISER 1
#define SUBMARINE 2
#define PATROLBOAT 3

// Boats names
char* boat_names[5] = {
    "Porte-avions",
    "Croiseur",
    "Sous-marrin"
    "Torpilleur",
};

#define BOATNAME(x) boat_names[x->type] // Get the boat name from a Boat pointer

// Boats sizes
#define SIZE_CARRIER 5
#define SIZE_CRUISER 4
#define SIZE_SUBMARINE 3
#define SIZE_PATROLBOAT 2
#define BOATSIZE(x) boat_sizes[x->type] // Get the boat size from a Boat pointer
tinyint boat_sizes[5] = {
    SIZE_CARRIER,
    SIZE_CRUISER,
    SIZE_SUBMARINE,
    SIZE_PATROLBOAT,
};

// other boats information
#define BOATCOUNT 5 // boat count per player
// initial boat array for each player
#define INITIALBOATS {            \
    {CARRIER, SIZE_CARRIER},      \
    {CRUISER, SIZE_CRUISER},      \
    {SUBMARINE, SIZE_SUBMARINE},  \
    {SUBMARINE, SIZE_SUBMARINE},  \
    {PATROLBOAT, SIZE_PATROLBOAT}, \
}

// characters
#define NONE ' ' // default character to display
#define FAILED 'O' // character to display where an attack failed
#define TOUCHED 'X' // character to display where an attack succeed
#define SCANNED '$' // character to display where a scan failed

// Simulate a foreach loop
#define foreach(item, array) \
    for(int count = 0, size = sizeof (array) / sizeof *(array); \
        count < size; \
        item = array[count])

#endif
