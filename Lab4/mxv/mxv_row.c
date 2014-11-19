/*
  !-----------------------------------------------------------------------
  ! Author: Ruud van der Pas, Sun Microsystems
  ! 
  ! Copyright: Sun Microsystems, All rights reserved, Un-authorized
  !            distribution not permitted
  !-----------------------------------------------------------------------
*/
#include "labs.h"

void mxv_row(int m, int n, double *a, double *b, double *c)
{
   int i, j;

   for (i=0; i<m; i++)
   {
     a[i] = 0.0;
     for (j=0; j<n; j++)
       a[i] += b[i*n+j]*c[j];
   }
}
