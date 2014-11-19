/*
  !-----------------------------------------------------------------------
  ! Author: Ruud van der Pas, Sun Microsystems
  ! 
  ! Copyright: Sun Microsystems, All rights reserved, Un-authorized
  !            distribution not permitted
  !-----------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

int check_results(char *comment, int m, int n, double *a, double *ref)
{
   double relerr;
   int   i, errors = 0;
   char  *marker;
   double TOL   = 100.0 * DBL_EPSILON;
   double SMALL = 100.0 * DBL_MIN;

   if ( (marker=(char *)malloc(m*sizeof(char))) == NULL ) {
        perror("array marker");
        exit(-1);
   }

   for (i=0; i<m; i++)
   {
       if ( fabs(ref[i]) > SMALL )
       {
          relerr = fabs((a[i]-ref[i])/ref[i]);
       }
       else
       {
          relerr = fabs((a[i]-ref[i]));
       }
       if ( relerr <= TOL )
       {
          marker[i] = ' ';
       }
       else
       {
          errors++;
          marker[i] = '*';
       }
   }
   if ( errors > 0 )
   {
     printf("Routine: %s\n",comment);
     printf("Found %d differences in results for m=%d n=%d:\n",
             errors,m,n);
     for (i=0; i<m; i++)
         printf("\t%c a[%d]=%f ref[%d]=%f\n",marker[i],i,a[i],i,ref[i]);
   }
   return(errors);
}
