#include "table.h"
#include "entities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

entry_t* entryInit(const char* const misspelling, const char* const correctWord ){

  unsigned int mlen   = strlen(misspelling) + 1;
  unsigned int clen   = strlen(correctWord) + 1;

  entry_t* entry      = malloc(sizeof(entry_t));
  entry->misspelling  = calloc(mlen, sizeof(char));
  strncpy(entry->misspelling, misspelling, mlen);
  entry->correctWord  = calloc(clen, sizeof(char));
  strncpy(entry->correctWord, correctWord, clen);
  entry->exists       = 1;

  return entry;
}

table_t* tableInit(const unsigned int size){

  table_t* table     = malloc(sizeof(table_t));
  table->entries     = calloc(size,sizeof(entry_t));
  table->seed        = getPrime();
  table->size        = size;
  table->usedEntries = 0U;

  return table;
}

unsigned int tableInsert(table_t* table,const char* const misspelling, const char* const correctWord){

  unsigned int cutoff = (unsigned int)(2*(table->size / 3));

  if( table->usedEntries >= cutoff ) tableResize(table, table->size*2);

  entry_t* entry = NULL;
  unsigned int index;
  auto unsigned int position = 0;

  while(position != table->size){

    //calculate hash of the string based on linear probing
    index = hashString(table->seed,misspelling,table->size, position);
    //retrieve the entry of the table to check wether it exists or not
    entry = &table->entries[index];

    //entry doesnt exist so we write to them
    if(entry->exists == 0){

      *entry = *entryInit(misspelling, correctWord);
      table->usedEntries++;
      return index;

    }
    position++;
  }
  return -1;
}

//resize the table given, rehash all the items with the new linear probe
void tableResize(table_t *table, const unsigned int newSize) {

  // most likely wont happen but if there is an overflow then we have a problem
  if (table->size > newSize)
    return;

  // temp table that we store the results
  table_t *temp = tableInit(newSize);

  // copy the seed
  temp->seed = table->seed;

  // iterator-like entry
  entry_t *iterator;
  // index for the hash table
  unsigned int pos = 0;
  unsigned int index = 0;

  while (pos != table->size) {

    // get entry of the old table
    iterator = &table->entries[pos];
    // if it exists write it to the new table
    if (iterator->exists == 1) index = tableInsert(temp, iterator->misspelling, iterator->correctWord);
    pos++;
  }

  free(table->entries);

  table->entries = temp->entries;

  table->size = temp->size;

  table->usedEntries = temp->usedEntries;

}

const char *tableGet(const table_t *const table, const char *const misspelling) {

  char* toReturn = NULL;

  unsigned int index;

  entry_t* entry;

  for(auto unsigned int iteration = 0; iteration< table->size; ++iteration){

    index = hashString(table->seed, misspelling,table->size, iteration);

    entry = &table->entries[index];

    if(entry->exists== 1 && strcmp(misspelling, entry->misspelling) ==0){

      toReturn = calloc(strlen(entry->correctWord) +1, sizeof(char));

      strncpy(toReturn, entry->correctWord, strlen(entry->correctWord));

      return entry->correctWord;

    }
  }
  return NULL;
}

void tableDestroy(table_t *table) {

  entry_t *entry = NULL;

  for (auto unsigned int i = 0; i < table->size; i++) {

    entry = &table->entries[i];

    if(entry->exists ==1){
      free(entry->misspelling);
      free(entry->correctWord);
    }
  }
  free(table);
}

