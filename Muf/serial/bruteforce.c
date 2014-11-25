#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

const unsigned char * BF(const unsigned char* haystack, size_t hlen,
                           const unsigned char* needle,   size_t nlen)
{
   size_t i, j;

   /* Searching */
   for (j = 0; j <= hlen - nlen; ++j) {
      for (i = 0; i < nlen && needle[i] == haystack[i + j]; ++i);
      if (i >= nlen)
         return haystack+j;
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
    fp = fopen ( strcat(output_file, "_BF") , "w+" );
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