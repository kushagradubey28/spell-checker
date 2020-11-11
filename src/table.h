#include <stdio.h> //io
#include <stdlib.h>//memory management
#include <string.h>//compare functions

#include "entities.h"
#include "hash.h"

entry_t*            entryInit(const char* const, const char* const);

table_t*            tableInit(const unsigned int);

unsigned int        tableInsert(table_t*, const char* const, const char* const);

void                tableResize(table_t *, const unsigned int);

const char*         tableGet(const table_t* const, const char* const);

void                tableDestroy(table_t*);
