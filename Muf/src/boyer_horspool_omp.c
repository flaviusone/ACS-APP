#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

#define CHUNKSIZE 102400
#define SIZE CHUNKSIZE+200

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
  double t, timp_total;           /* Pentru calcul timp */
  long lSize;                     /* Lungime haystack */
  unsigned char *haystack,*hay;   /* Buffer ce contine fisierul in care se cauta */
  int j;                          /* Aux */
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

  /* Deschidem fisier de output */
  fpo = fopen ( strcat(output_file, "_H_OMP") , "w+" );
  if( !fpo ) perror(output_file),exit(1);

  // #pragma omp parallel for private(j, haystack, hay, needle)
  for (j = 0; j < chunks; j++) {

    /* Alocam memorie pentru haystack (de dimensiunea chunksize+200) */
    haystack = calloc (CHUNKSIZE + 200, sizeof(unsigned char));

    /* Copiem un chunk in haystack */
    fseek(fp, j * CHUNKSIZE, SEEK_SET);
    int dimi = (int)fread(haystack, sizeof(unsigned char), CHUNKSIZE + 200, fp);

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
    if (size > 0)
    {
      gettimeofday(&start,0);

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
        while((*(b+counter_end) != ' ') && b-haystack+counter_end < size){
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

      gettimeofday(&finish,0);

      /* Calcul timp desfasurare */
      t= (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec)
       / 1000000.0;
       timp_total += t;
    }
    free(haystack);
  }

  fclose(fp);
  fclose(fpo);
  printf("Time elapsed %lf\n", timp_total);
  return 0;
}