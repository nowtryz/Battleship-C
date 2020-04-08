#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h> // for the NULL cosntant
#include "types.h" // for tinyint

// Booleans
#define TRUE 1 // actually everything but 0, wich would be evaluated as false
#define FALSE 0

// Boats ids
#define CARRIER 0
#define CRUISER 1
#define SUBMARINE 2
#define PATROLBOAT 3

// Boats names
static char* boat_names[5] = {
    "Porte-avions",
    "Croiseur",
    "Sous-marrin"
    "Torpilleur",
};

#define BOATNAME(x) boat_names[x->type]

// Boats sizes
#define SIZE_CARRIER 5
#define SIZE_CRUISER 4
#define SIZE_SUBMARINE 3
#define SIZE_PATROLBOAT 2
#define BOATSIZE(x) boat_sizes[x->type]
static tinyint boat_sizes[5] = {
    SIZE_CARRIER,
    SIZE_CRUISER,
    SIZE_SUBMARINE,
    SIZE_PATROLBOAT,
};

// other boats information
#define BOATCOUNT 5 // per player
#define INITIALBOATS {                   \
    {CARRIER, SIZE_CARRIER},      \
    {CRUISER, SIZE_CRUISER},      \
    {SUBMARINE, SIZE_SUBMARINE},  \
    {SUBMARINE, SIZE_SUBMARINE},  \
    {PATROLBOAT, SIZE_PATROLBOAT}, \
}

// characters
#define NONE ' '
#define SCANNED 'X' // scan
#define FAILED 'O' // action
#define TOUCHED 'X' // action

//foreach
#define foreach(item, array) \
    for(int count = 0, size = sizeof (array) / sizeof *(array); \
        count < size; \
        item = array[count])

#endif
