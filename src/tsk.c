#include "tsk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFromFile(const char* const fileName, table_t* table){

  FILE *fp = fopen(fileName, "r");

  char *buffer = NULL;

  unsigned long len = 0;

  int read = 0;

  char* misspelling = NULL;

  char* correctWord = NULL;

  while((read = getline(&buffer, &len, fp))!= -1 ){

    misspelling = strtok(buffer, DELIMS);

    correctWord = strtok(NULL,DELIMS);

    tableInsert(table, misspelling, correctWord);
  }
}

static inline char* replace(char *sentence, char *misspelling, char *correctedWord) {

  //new size shall be l of the temp - l of miss + l of corr + 1
  unsigned int newSize = strlen(sentence) - strlen(misspelling) + strlen(correctedWord) + 1;

  //new char* to be returned
  char* dst = malloc(newSize*sizeof(char));

  char* ptr;
  //copy the old contents of the temp to the returning string
  strcpy(dst, sentence);

 //get the location of the misspelled word in the string
  ptr = strstr(dst, misspelling);
  //replace the misspelled word with the correct word
  memmove(ptr+strlen(correctedWord), ptr+strlen(misspelling), strlen(ptr+strlen(misspelling)) + 1 );
  //copy the corrected word to the location of the ptr
  strncpy(ptr,correctedWord,strlen(correctedWord));

  return dst;
}

static inline void repairSentence(const table_t* const table,char *sentence, int len) {

  //allocate the new sentence in the memory
  char* temp = malloc((strlen(sentence) + 1 ) *sizeof(char));
  //copy the sentence in the temp, dont use the same var because strcpy changes the string
  strcpy(temp,sentence);

  printf("%s", temp);
  //this will be the corrected word that will be received form the table
  char* corrected = NULL;
  //start tokenising the sentence into words
  char* token = strtok(sentence,DELIMS);

  while(token != NULL){

    //if we find the word inthe memory
    if((corrected = tableGet(table, token)) != NULL)temp = replace(temp, token, corrected);

    token = strtok(NULL, DELIMS);
  }

  printf("%s\n", temp);

}


int main(int argc, char** argv){

  table_t* table = tableInit(1024);

  readFromFile(argv[1],table);

  FILE* f = fopen(argv[2], "r");

  char *sentence = NULL;

  unsigned long len = 0;

  int read = 0;

  char* res = NULL;

  while ((read = getline(&sentence, &len, f)) != -1) {

    repairSentence(table,sentence, len);

  }

  tableDestroy(table);

  return 0;
}
