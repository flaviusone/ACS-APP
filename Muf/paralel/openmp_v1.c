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

int first (unsigned char * haystack) {
  int delay = 0;
  while ((char)haystack[delay] != " ")
    delay++;
  return delay;
}

int last (unsigned char * haystack, int dim) {
  int final = CHUNKSIZE;
  if (dim <= CHUNKSIZE)
    return dim;
  while ((char)haystack[final] != " ")
    final++;
  return final;
}

int main(int argc, char *argv[]){
    // char haystack[] = "Test abc 123 abc2  bacabc d stuff abc final";
    // char* haystack = strdup("Test abc 123 abc2  bacabc d stuff abc final");

   /*======================================
   =            READ FROM FILE            =
   ======================================*/

    FILE *fp, *fpo;
    char input_file[50];
    char output_file[50];
    unsigned char needle[50];
    char buffer[50];
    struct timeval start,finish;
    double t, timp_total = 0;


    fp = fopen(argv[1], "r");
    // fp = fopen(argv[2], "r");

    fscanf(fp, "%s", input_file);
    fscanf(fp, "%s", output_file);
    fscanf(fp, "%s", needle);
    fclose(fp);

    long lSize;
    unsigned char *haystack, *hay;

    fp = fopen ( input_file , "rb" );
    if( !fp ) perror(input_file),exit(1);

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    int chunks = lSize / CHUNKSIZE + ((lSize % CHUNKSIZE) ? 1 : 0);
    int j;
    fpo = fopen ( strcat(output_file, "_H") , "w+" );
    if( !fpo ) perror(output_file),exit(1);
    for (j = 0; j < chunks; j++) {
      /* allocate memory for entire content */
      haystack = calloc (CHUNKSIZE + 200, sizeof(unsigned char));

      /* copy the file into the haystack */
      fseek(fp, j * CHUNKSIZE, SEEK_SET);
      // size_t dim = fread(haystack, sizeof(unsigned char), CHUNKSIZE + 200, fp);
      size_t dim = fread(haystack, sizeof(unsigned char), CHUNKSIZE, fp);
      int dimi = (int)dim;
      // int delay, final;
      // delay = first(haystack);
      // final = last(haystack, dim);

      // hay = calloc(final - delay, sizeof(unsigned char));
      // strncpy((char*)hay, (char*)haystack, final - delay);

      // int size = final - delay;
      // if (size > 0) {
      if (dimi > 0) {
        gettimeofday(&start,0);

         long i = 0;

         // #pragma omp parallel private(i)
         while(i < CHUNKSIZE){ //i < size; dim -> size
          const unsigned char*  b = boyermoore_horspool_memmem(haystack + i, dimi - i, needle, strlen((char*)needle));

          if(b == NULL){
            fprintf(fpo, "EOF\n");
            break;
          }

          int counter_start = 1;
          int counter_end = strlen((char*) needle);
          while(*(b-counter_start) != ' '){
            counter_start++;
          }
          while((*(b+counter_end) != ' ') && counter_end < dimi){
            counter_end++;
          }
          memset(buffer, 0, sizeof(buffer));
          strncpy(buffer, (char*) b - counter_start, counter_start+counter_end);
          buffer[counter_start + counter_end] = '\0';
          fprintf(fpo, "%s\n", buffer);

          i = b - haystack + strlen((char*)needle);
         }

        gettimeofday(&finish,0);

        t= (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec)
         / 1000000.0;
         timp_total += t;
         // #pragma omp barrier
      }
      free(haystack);
    }



    /* do your work here, haystack is a string contains the whole text */

    fclose(fp);

   /*-----  End of READ FROM FILE  ------*/




   fclose(fpo);
   // free(haystack);


  printf("Time elapsed %lf\n", timp_total);



   return 0;
}