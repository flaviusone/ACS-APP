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

void mxv_col(int m, int n, double *a, double *b, double *c)
{
   int i, j;

   //   threshold_col = 375;
   # pragma omp parallel if (m > threshold_col) default (none) \
            private (i,j) shared(a, b, c, n, m)
   {
   #pragma omp for
   for (i=0; i<m; i++)
       a[i] = b[i*n]*c[0];

   for (j=1; j<n; j++)
     {
   #pragma omp for
     for (i=0; i<m; i++)
       a[i] += b[i*n+j]*c[j];
     }

   } /* -- End of parallel region --*/
}
