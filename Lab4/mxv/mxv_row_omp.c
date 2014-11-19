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

void mxv_row(int m, int n, double *a, double *b, double *c)
{
   int i, j;

   //   threshold_row = 45;
   # pragma omp parallel for if (m > threshold_row) default (none) \
            private (i,j) shared(a, b, c, n, m)
   for (i=0; i<m; i++)
   {
     a[i] = 0.0;
     for (j=0; j<n; j++)
       a[i] += b[i*n+j]*c[j];
   }
}
