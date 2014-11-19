/*
  !-----------------------------------------------------------------------
  ! Author: Ruud van der Pas, Sun Microsystems
  ! 
  ! Copyright: Sun Microsystems, All rights reserved, Un-authorized
  !            distribution not permitted
  !-----------------------------------------------------------------------
*/
#include "labs.h"
#ifdef _OPENMP
#include <omp.h>
#endif

void init_data (int m, int n, double *a, double *b, double *c, double *ref)
{
   int i, j;

   for (j=0; j<n; j++)
      c[j] = 1.0;

   # pragma omp parallel for if (m > threshold_row) default (none) \
            private (i,j) shared(a, b, n, m, ref)
   for (i=0; i<m; i++)
   {
      ref[i] = n*i;
      a[i]   = -2005.0;
      for (j=0; j<n; j++)
         b[i*n+j] = i;
   } 

}
