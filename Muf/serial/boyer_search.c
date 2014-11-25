#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

void preBmBc(const unsigned char *x, int m, int bmBc[]) {
   int i;

   for (i = 0; i < UCHAR_MAX; ++i)
      bmBc[i] = m;
   for (i = 0; i < m - 1; ++i)
      bmBc[x[i]] = m - i - 1;
}


void suffixes(const unsigned char *x, int m, int *suff) {
   int f, g, i;

   suff[m - 1] = m;
   g = m - 1;
   for (i = m - 2; i >= 0; --i) {
      if (i > g && suff[i + m - 1 - f] < i - g)
         suff[i] = suff[i + m - 1 - f];
      else {
         if (i < g)
            g = i;
         f = i;
         while (g >= 0 && x[g] == x[g + m - 1 - f])
            --g;
         suff[i] = f - g;
      }
   }
}

void preBmGs(const unsigned char *x, int m, int bmGs[]) {
   int i, j, suff[UCHAR_MAX];

   suffixes(x, m, suff);

   for (i = 0; i < m; ++i)
      bmGs[i] = m;
   j = 0;
   for (i = m - 1; i >= 0; --i)
      if (suff[i] == i + 1)
         for (; j < m - 1 - i; ++j)
            if (bmGs[j] == m)
               bmGs[j] = m - 1 - i;
   for (i = 0; i <= m - 2; ++i)
      bmGs[m - 1 - suff[i]] = m - 1 - i;
}


const unsigned char * BF(const unsigned char* haystack, size_t hlen,
                           const unsigned char* needle,   size_t nlen)
{
   int i, j, bmGs[UCHAR_MAX], bmBc[UCHAR_MAX];

   /* Preprocessing */
   preBmGs(needle, nlen, bmGs);
   preBmBc(needle, nlen, bmBc);

   /* Searching */
   j = 0;
   while (j <= hlen - nlen) {
      for (i = nlen - 1; i >= 0 && needle[i] == haystack[i + j]; --i);
      if (i < 0) {
         // return haystack+j;
         printf("%d\n", j);
         j += bmGs[0];
      }
      else
         j += MAX(bmGs[i], bmBc[haystack[i + j]] - nlen + 1 + i);
      // printf("while loop\n");
   }
   return NULL;
}

int main(int argc, char *argv[]){
    // char haystack[] = "Test abc 123 abc2  bacabc d stuff abc final";
    // char* haystack = strdup("Test abc 123 abc2  bacabc d stuff abc final");

   /*======================================
   =            READ FROM FILE            =
   ======================================*/

    FILE *fp;
    char input_file[50];
    char output_file[50];
    unsigned char needle[50];
    char buffer[50];


    fp = fopen(argv[1], "r");
    fscanf(fp, "%s", input_file);
    fscanf(fp, "%s", output_file);
    fscanf(fp, "%s", needle);
    fclose(fp);

    long lSize;
    unsigned char *haystack;

    fp = fopen ( input_file , "rb" );
    if( !fp ) perror(input_file),exit(1);

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    /* allocate memory for entire content */
    haystack = calloc( 1, lSize+1 );
    if( !haystack ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    /* copy the file into the haystack */
    if( 1!=fread( haystack , lSize, 1 , fp) )
    fclose(fp),free(haystack),fputs("entire read fails",stderr),exit(1);

    /* do your work here, haystack is a string contains the whole text */

    fclose(fp);


   /*-----  End of READ FROM FILE  ------*/
    fp = fopen ( output_file , "w+" );
    if( !fp ) perror(output_file),exit(1);

   long i=0;
   while(i < lSize){
    const unsigned char*  b = BF(haystack + i, lSize - i, needle, strlen((char*)needle));

    if(b == NULL){
      fprintf(fp, "EOF\n");
      return -1;
    }

    int counter_start = 1;
    int counter_end = strlen((char*) needle);
    while(*(b-counter_start) != ' '){
      counter_start++;
    }
    while((*(b+counter_end) != ' ') && counter_end < lSize){
      counter_end++;
    }
    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, (char*) b - counter_start, counter_start+counter_end);
    buffer[counter_start + counter_end] = '\0';
    fprintf(fp, "%s\n", buffer);

    i = b - haystack + strlen((char*)needle);

   }
   fclose(fp);
   free(haystack);
   return 0;
}