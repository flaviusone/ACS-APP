/*
  !-----------------------------------------------------------------------
  ! Author: Ruud van der Pas, Sun Microsystems
  ! 
  ! Copyright: Sun Microsystems, All rights reserved, Un-authorized
  !            distribution not permitted
  !-----------------------------------------------------------------------
*/
#include <sunperf.h>

void mxv_lib(int m, int n, double *a, double *b, double *c)
{

/*-- This is needed for the Sun Performance Library routine DGEMV --*/

   char   transa = 'T';
   double alpha = 1.0, beta = 0.0;
   int    incc=1, inca=1, ldb;

/* y = alpha*A*x+beta*y */
/* a = alpha*B*c+beta*a */

      ldb = n;

      (void) dgemv(transa, n, m, alpha, b, ldb, c, incc, beta, a, inca);

}
