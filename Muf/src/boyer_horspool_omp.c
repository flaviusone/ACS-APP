#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>
#include "boyer_horspool.h"

#define CHUNKSIZE 102400
#define SIZE CHUNKSIZE+200



int first (unsigned char * haystack, int chunk_size) {
  int delay = 0;
  // while ((char)haystack[delay] != ' ' && (delay<chunk_size))
  while ((char)haystack[delay] != ' ')
    delay++;
  return delay;
}

int last (unsigned char * haystack, int dim) {
  int final = CHUNKSIZE;
  if (dim <= CHUNKSIZE)
    return dim;
  // while ((char)haystack[final] != ' ' && (final<=dim))
  while ((char)haystack[final] != ' ')
    final++;
  return final;
}

/**
*
* Cauta toate aparitiile lui needle in haystack
* Returneaza un string cu cuvintele gasite separate prin \n
*
**/

char* cauare_aparitii(unsigned char* haystack,unsigned char* needle, int size)
{
  char* thread_buff;
  long i = 0;
  char buffer[50];                /* Buffer auxiliar */

  /* Alocam bufferul privat thread_buff */
  thread_buff = calloc(1, sizeof(char));

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
    while((*(b+counter_end) != ' ') && b-haystack+counter_end < size){
      counter_end++;
    }

    /* Resetam buffer si copiem cuvantul in care se gaseste secventa noastra */
    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, (char*) b - counter_start, counter_start+counter_end);
    buffer[counter_start + counter_end] = '\n';
    buffer[counter_start + counter_end+1] = '\0';

    /* Adaugam cuvantul la bufferul local */
    thread_buff = realloc(thread_buff, strlen(thread_buff) + strlen(buffer) + sizeof(char));
    if (!thread_buff){
       printf("Error Realloc\n");
       // return -1;
    }
    strcat(thread_buff, buffer);

    i = b - haystack + strlen((char*)needle);
  }

  free(haystack);

  return thread_buff;
}

int main(int argc, char *argv[]){

  /*==============================================
  =            Initializare variabile            =
  ==============================================*/
  FILE *fp, *fpo;
  char input_file[50];            /* Input file */
  char output_file[50];           /* Output file */
  unsigned char needle[50];       /* Buffer ce stocheaza cuvantul de cautat */
  double timp_total;              /* Pentru calcul timp */
  long lSize;                     /* Lungime haystack */
  unsigned char *haystack,*hay;   /* Buffer ce contine fisierul in care se cauta */
  int j,numthreads;               /* Aux */
  int i;                          /* Aux */
  char **results;
  /*-----  End of Initializare variabile  ------*/

  /*  Citire date test din fisier  */
  fp = fopen(argv[2], "r");
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
  fpo = fopen ( strcat(output_file, "_H_OMP") , "w+" );
  if( !fpo ) perror(output_file),exit(1);

  /* Setam num threads */
  omp_set_num_threads(atoi(argv[1]));

  #pragma omp parallel for private(j, haystack, hay) shared(timp_total)
  for (j = 0; j < chunks; j++) {
    /* Alocam memorie pentru haystack (de dimensiunea chunksize+200) */
    haystack = calloc (CHUNKSIZE + 200, sizeof(unsigned char));

    /* Copiem un chunk in haystack */
    int dimi;
    #pragma omp critical
    {
      fseek(fp, j * CHUNKSIZE, SEEK_SET);
      dimi = (int)fread(haystack, sizeof(unsigned char), CHUNKSIZE + 200, fp);
    }

    /* Sarim peste primul cuvant si luam ultimul cuvant */
    int delay, final;
    delay = first(haystack, CHUNKSIZE+200);
    final = last(haystack, dimi);

    /* Alocam spatiu pentru noul chunk format */
    hay = calloc(final - delay, sizeof(unsigned char));
    strncpy((char*)hay, (char*)haystack+delay, final - delay);
    free(haystack);
    haystack = hay;

    /* Procesam cu noul size */
    int size = final - delay;

    double start_time = omp_get_wtime();

    /* Cautam toate aparitiile lui needle in haystack in chunk-ul j */
    results[j] = cauare_aparitii(haystack, needle, size);

    double stop_time = omp_get_wtime();

    #pragma omp atomic
    timp_total += stop_time - start_time;
  }

  /* Scriem rezultatele in fisier */
  for (i = 0; i < chunks; ++i)
    fprintf(fpo, "%s", results[i]);

  fclose(fp);
  fclose(fpo);
  printf("%d %lf\n", atoi(argv[1]), timp_total/atoi(argv[1]));
  return 0;
}