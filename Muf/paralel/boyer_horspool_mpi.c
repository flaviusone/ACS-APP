#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mpi.h"

/* Returns a pointer to the first occurrence of "needle"
 * within "haystack", or NULL if not found. Works like
 * memmem().
 */

/* Note: In this example needle is a C string. The ending
 * 0x00 will be cut off, so you could call this example with
 * boyermoore_horspool_memmem(haystack, hlen, "abc", sizeof("abc")-1)
 */
const unsigned char *
boyermoore_horspool_memmem(const unsigned char* haystack, size_t hlen,
                           const unsigned char* needle,   size_t nlen)
{
    size_t scan = 0;
    size_t bad_char_skip[UCHAR_MAX + 1]; /* Officially called:
                                          * bad character shift */

    /* Sanity checks on the parameters */
    if (nlen <= 0 || !haystack || !needle)
        return NULL;

    /* ---- Preprocess ---- */
    /* Initialize the table to default value */
    /* When a character is encountered that does not occur
     * in the needle, we can safely skip ahead for the whole
     * length of the needle.
     */
    for (scan = 0; scan <= UCHAR_MAX; scan = scan + 1)
        bad_char_skip[scan] = nlen;

    /* C arrays have the first byte at [0], therefore:
     * [nlen - 1] is the last byte of the array. */
    size_t last = nlen - 1;

    /* Then populate it with the analysis of the needle */
    for (scan = 0; scan < last; scan = scan + 1)
        bad_char_skip[needle[scan]] = last - scan;

    /* ---- Do the matching ---- */

    /* Search the haystack, while the needle can still be within it. */
    while (hlen >= nlen)
    {
        /* scan from the end of the needle */
        for (scan = last; haystack[scan] == needle[scan]; scan = scan - 1)
            if (scan == 0) /* If the first byte matches, we've found it. */
                return haystack;
        /* otherwise, we need to skip some bytes and start again.
           Note that here we are getting the skip value based on the last byte
           of needle, no matter where we didn't match. So if needle is: "abcd"
           then we are skipping based on 'd' and that value will be 4, and
           for "abcdd" we again skip on 'd' but the value will be only 1.
           The alternative of pretending that the mismatched character was
           the last character is slower in the normal case (E.g. finding
           "abcd" in "...azcd..." gives 4 by using 'd' but only
           4-2==2 using 'z'. */
        hlen     -= bad_char_skip[haystack[scan]];
        haystack += bad_char_skip[haystack[scan]];
    }

    return NULL;
}

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
  int chunksize;                 /* Lungime chunk haystack */
  unsigned char *chunk_haystack;  /* Buffer ce contine un chunk din fisierul in care se cauta */
  char *out_buff=NULL;
  char *final_buff=NULL;
  int rc, numtasks, rank;  /* Aux (MPI) */
  int *strlens;
  /*-----  End of Initializare variabile  ------*/

  /*==========  MPI Inits  ==========*/
  rc = MPI_Init(NULL, NULL);
  if (rc != MPI_SUCCESS) {
      printf ("Error starting MPI program. Terminating.\n");
      MPI_Abort(MPI_COMM_WORLD, rc);
  }
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0)
  {
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
    fp = fopen ( strcat(output_file, "_H_MPI") , "w+" );
    if( !fp ) perror(output_file),exit(1);

    /* Calculam chunksize pentru procesare */
    chunksize = lSize / numtasks;

    /* Alocam Strlens vector */
    strlens = malloc(numtasks*sizeof(int));

    /* Start la numarare timp */
    gettimeofday(&start,0);
  }

  /* Trimitem chunksize calculat catre toate nodurile */
  MPI_Bcast(&chunksize, 1, MPI_INT, 0, MPI_COMM_WORLD);

  /* Trimitem needle la toata lumea */
  MPI_Bcast(needle, 50, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

  /* Alocam chunk_haystack */
  chunk_haystack = (unsigned char*)malloc(chunksize*sizeof(unsigned char));

  /* Facem scatter la haystack initial catre toate procesele */
  MPI_Scatter(haystack, chunksize, MPI_UNSIGNED_CHAR, chunk_haystack, chunksize, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

  // MPI_Barrier(MPI_COMM_WORLD);
  out_buff=malloc(sizeof(char));
  i = 0;
  while(i < chunksize){

    /* Cautam urmatoarea aparitie a secventei de cautat */
    const unsigned char*  b = boyermoore_horspool_memmem(chunk_haystack + i, chunksize - i, needle, strlen((char*)needle));

    // /* Daca b null atunci am terminat */
    if(b == NULL) break;

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
    buffer[counter_start + counter_end] = '\n';
    buffer[counter_start + counter_end+1] = '\0';

    /* Scriem cuvantul in fisier */
    // fprintf(fp, "%s\n", buffer);

    out_buff = realloc(out_buff, strlen(out_buff) + strlen(buffer) + sizeof(char));
    if (!out_buff){
       printf("Error Realloc\n");
      return -1;
    }
    strcat(out_buff, buffer);

    i = b - chunk_haystack + strlen((char*)needle);
  }

  /* Calculam valoarea strlen de out_buff */
  int strlen_val = (int)strlen(out_buff)+1;

  /* Toata lumea trimite valoarea lui strlen(out_buff) la master */
  MPI_Gather(&strlen_val, 1, MPI_INT, strlens, 1, MPI_INT, 0, MPI_COMM_WORLD);

  /* Fiecare rank trimite catre rank 0 out_buff */
  if( rank != 0){
    MPI_Send(out_buff, strlen_val, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }

  if(rank == 0)
  {

    /* Calculez suma la strlen-uri si aloc final_buff */
    int sum = 0;
    for (i = 0; i < numtasks; ++i)
    {
      sum += *(strlens+i);
    }
    final_buff = malloc(sum*sizeof(char));

    /* Pun intai bucata mea in final_buff */
    sprintf(final_buff, "%s", out_buff);


    /* Fac recieve de la toate celelalte taskuri la out_buff */
    for (i = 1; i < numtasks; ++i)
    {
      char* aux_buffer = malloc(strlens[i]*sizeof(char));
      MPI_Recv(aux_buffer, strlens[i], MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      strcat(final_buff, aux_buffer);
      free(aux_buffer);
    }

    // printf("%s\n", final_buff);
    fprintf(fp, "%s",final_buff);

    /* Stop la numarare timp */
    gettimeofday(&finish,0);

    /* Calcul timp desfasurare */
    t= (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec)
     / 1000000.0;
    printf("Time elapsed %lf\n", t);

    /* Cleanups */
    fclose(fp);
    free(haystack);
  }

  MPI_Finalize();
  return 0;
}