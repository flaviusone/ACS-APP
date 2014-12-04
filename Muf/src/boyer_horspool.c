#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "boyer_horspool.h"

#define CHUNKSIZE 102400

int last (unsigned char * haystack, int dim) {
  int final = CHUNKSIZE;
  if (dim <= CHUNKSIZE)
    return dim;
  while ((char)haystack[final] != ' ')
    final++;
  return final;
}

void cautare_aparitii(unsigned char* haystack,unsigned char* needle, int size, FILE *fpo) {

  char buffer[50];
  long i = 0;
  while(i < size){

    /* Cautam urmatoarea aparitie a secventei de cautat */
    const unsigned char*  b = boyermoore_horspool_memmem(haystack + i, size - i, needle, strlen((char*)needle));

    /* Daca b null atunci am terminat */
    if(b == NULL){
      break;
    }

    /* Setam capetele de cautare */
    int counter_start = 1;
    int counter_end = strlen((char*) needle);

    /* Cautam de la cuvant in spate pana la space */
    while(*(b-counter_start) != ' '){
      counter_start++;
    }
    /* Cautam de la cuvant in fata pana la space */
    while((*(b+counter_end) != ' ') && b-haystack + counter_end < size){
      counter_end++;
    }

    /* Resetam buffer si copiem cuvantul in care se gaseste secventa noastra */
    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, (char*) b - counter_start, counter_start+counter_end);
    buffer[counter_start + counter_end] = '\0';

    /* Scriem cuvantul in fisier */
    fprintf(fpo, "%s\n", buffer);

    i = b - haystack + strlen((char*)needle);
  }
  free(haystack);

}


int main(int argc, char *argv[]){

  /*==============================================
  =            Initializare variabile            =
  ==============================================*/
  FILE *fp, *fpo;
  char input_file[50];            /* Input file */
  char output_file[50];           /* Output file */
  unsigned char needle[50];       /* Buffer ce stocheaza cuvantul de cautat */
  char buffer[50];                /* Buffer auxiliar */
  struct timeval start,finish;    /* Pentru calcul timp */
  double t, timp;                 /* Pentru calcul timp */
  long lSize;                     /* Lungime haystack */
  unsigned char *haystack, *hay;  /* Buffer ce contine fisierul in care se cauta */
  long i=0;                       /* Aux */
  int j, offset;
  char **results;
  /*-----  End of Initializare variabile  ------*/

  /*  Citire date test din fisier  */
  fp = fopen(argv[1], "r");
  fscanf(fp, "%s", input_file);
  fscanf(fp, "%s", output_file);
  fscanf(fp, "%s", needle);
  fclose(fp);

  /* Deschidem fisierul pentru a-i afla dimensiunea */
  fp = fopen ( input_file , "rb" );
  if( !fp ) perror(input_file),exit(1);
  fseek( fp , 0L , SEEK_END);
  lSize = ftell( fp );
  rewind( fp );

  /* Calculam nr de chunks */
  int chunks = lSize / CHUNKSIZE + ((lSize % CHUNKSIZE) ? 1 : 0);
  results = calloc(chunks, sizeof(char *));

  /* Deschidem fisier de output */
  fpo = fopen ( strcat(output_file, "_H") , "w+" );
  if( !fpo ) perror(output_file),exit(1);

  offset = 0;

  for (j = 0; j < chunks; j++) {
    /* Alocam memorie pentru haystack (de dimensiunea chunksize+200) */
    haystack = calloc (CHUNKSIZE + 200, sizeof(unsigned char));

    fseek(fp, offset, SEEK_SET);
    int dim = (int)fread(haystack, sizeof(unsigned char), CHUNKSIZE + 200, fp);

    int size = last(haystack, dim);
    offset += size;
    /* Alocam spatiu pentru noul chunk format */
    hay = calloc(size, sizeof(unsigned char));
    strncpy((char*)hay, (char*)haystack, size);
    free(haystack);
    haystack = hay;
    i = 0;

    /* Start la numarare timp */
    gettimeofday(&start,0);

    /* Cautam toate aparitiile lui needle in haystack in chunk-ul j */
    cautare_aparitii(haystack, needle, size, fpo);

    /* Stop la numarare timp */
    gettimeofday(&finish,0);

    /* Calcul timp desfasurare */
    t = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec)
    / 1000000.0;
    timp += t;
  }

  printf("Time elapsed %lf\n", timp);

  /* Cleanups */
  fclose(fp);
  fclose(fpo);

  return 0;
}