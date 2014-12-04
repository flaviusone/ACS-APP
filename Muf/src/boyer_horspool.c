#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "boyer_horspool.h"

int main(int argc, char *argv[]){

  /*==============================================
  =            Initializare variabile            =
  ==============================================*/
  FILE *fp;
  char input_file[50];            /* Input file */
  char output_file[50];           /* Output file */
  unsigned char needle[50];       /* Buffer ce stocheaza cuvantul de cautat */
  char buffer[50];                /* Buffer auxiliar */
  struct timeval start,finish;    /* Pentru calcul timp */
  double t;                       /* Pentru calcul timp */
  long lSize;                     /* Lungime haystack */
  unsigned char *haystack;        /* Buffer ce contine fisierul in care se cauta */
  long i=0;                       /* Aux */
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

  /* Alocam memorie pentru haystack (de dimensiunea fisierului) */
  haystack = calloc( 1, lSize+1 );
  if( !haystack ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

  /* Copiem fisierul in haystack */
  if( 1!=fread( haystack , lSize, 1 , fp) )
  fclose(fp),free(haystack),fputs("entire read fails",stderr),exit(1);
  fclose(fp);

  /* Deschidem fisier de output */
  fp = fopen ( strcat(output_file, "_H") , "w+" );
  if( !fp ) perror(output_file),exit(1);

  /* Start la numarare timp */
  gettimeofday(&start,0);


  while(i < lSize){

    /* Cautam urmatoarea aparitie a secventei de cautat */
    const unsigned char*  b = boyermoore_horspool_memmem(haystack + i, lSize - i, needle, strlen((char*)needle));

    /* Daca b null atunci am terminat */
    if(b == NULL){
      // fprintf(fp, "EOF\n");
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
    while((*(b+counter_end) != ' ') && counter_end < lSize){
      counter_end++;
    }

    /* Resetam buffer si copiem cuvantul in care se gaseste secventa noastra */
    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, (char*) b - counter_start, counter_start+counter_end);
    buffer[counter_start + counter_end] = '\0';

    /* Scriem cuvantul in fisier */
    fprintf(fp, "%s\n", buffer);

    i = b - haystack + strlen((char*)needle);
  }

  /* Stop la numarare timp */
  gettimeofday(&finish,0);

  /* Calcul timp desfasurare */
  t= (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec)
   / 1000000.0;
  printf("Time elapsed %lf\n", t);

  /* Cleanups */
  fclose(fp);
  free(haystack);

  return 0;
}