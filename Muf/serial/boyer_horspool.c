#include <string.h>
#include <limits.h>
#include <stdio.h>

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
        hlen     -= bad_char_skip[haystack[last]];
        haystack += bad_char_skip[haystack[last]];
    }

    return NULL;
}

int main(){
   char haystack[] = "Test abc 123 abc2  bacabc d stuff";
   char needle[] = "abc";
   char buffer[50];
   int hlen = strlen(haystack);
   // char b[] = "abc";

   int i=0;
   while(i < hlen){
    const char* b = boyermoore_horspool_memmem(haystack + i, hlen, needle, sizeof("abc")-1);

    if(b == NULL){
      printf("Null\n");
      return -1;
    }

    int counter_start = 1;
    int counter_end = strlen(needle);
    while(*(b-counter_start) != ' '){
      counter_start++;
    }
    while((*(b+counter_end) != ' ') && counter_end < hlen){
      counter_end++;
    }

    strncpy(buffer, b - counter_start, counter_start+counter_end);
    printf("buffer = %s\n", buffer);

    printf("%s\n", b);

    i = b - haystack + strlen(needle);

   }



   return 0;
}