#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "table.h"

static const char* const DELIMS =" . ? ! - > \n ";

static inline void         readFromFile(const char* const, table_t*);

static inline char*        replace(char*,char*,char*);

static inline void         repairSentence(const table_t* const,char*,int);

static inline void         readInputAndFixIt(const table_t* const);
