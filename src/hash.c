#include "hash.h"

//generate a random 32 bit prime integer
unsigned int getPrime(){

  unsigned int number;

  srand(time(NULL));

  number =(unsigned int) rand();

  while(number % 2 != 0)number++;

  return number;

}

//algorithm for hashing a string based on djb2 , Dan Bernstein
unsigned int hash(unsigned int seed ,char* key){

  unsigned int hash = seed;

  unsigned int c;

  while((c = *key++)) hash = ((hash<<5) + hash) + c; // hash * 33 + c

  return hash;

}

//iterable hashing with linnear probing, good for ascii english words
unsigned int hashString(const unsigned int seed, const char* const key, unsigned int tableSize, unsigned int iteration){

  unsigned int position = hash(seed, (char*)key);

  position = position + iteration * (position * 2 + 1);

  return position % tableSize;

}
