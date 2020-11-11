#pragma once

typedef struct __attribute__((packed)) __entry {

  char *misspelling;

  char *correctWord;

  unsigned int exists : 1;

} entry_t;

typedef struct __table {

  unsigned int size;

  unsigned int usedEntries;

  entry_t *entries;

  unsigned int seed;

} table_t;
