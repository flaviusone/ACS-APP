#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

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
    fp = fopen ( strcat(output_file, "_H") , "w+" );
    if( !fp ) perror(output_file),exit(1);

   long i=0;
   while(i < lSize){
    const unsigned char*  b = boyermoore_horspool_memmem(haystack + i, lSize - i, needle, strlen((char*)needle));

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