#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// const unsigned char * BF(const unsigned char* haystack, size_t hlen,
                           // const unsigned char* needle,   size_t nlen)
// {
void BF(char *x, int m, char *y, int n) {
   size_t i, j;

   /* Searching */
   for (j = 0; j <= n - m; ++j) {
      for (i = 0; i < m && x[i] == y[i + j]; ++i);
      if (i >= m)
         OUTPUT(j);
   }
}