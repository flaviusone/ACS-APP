/*
 * This code calculates pi using the formula to calculate
 * the atan(z) which is the integral from 0 to z of 1/(1+x*x)
 * times dx.  atan(1) is 45 degrees or pi/4
 */

#include <omp.h>

static long num_steps = 100000;  /* number of intervals             */
double step;                     /* the size of the interval - dx   */

#define NUM_THREADS 2

void main ()
{	  

   int i;                        /* Loop control variable            */
   double  x;                    /* Not used                         */
   double  pi;                   /* final results                    */
   double  sum=0.0;              /* Maintains sum of partial results */

   step = 1.0 / ( double ) num_steps;

   /*
    * This may be done more flexibly by using an environment
    * variable instead.
    */

   omp_set_num_threads( NUM_THREADS );

   /*
    * Each thread executes the code in the pragma below
    *
    * When more than one value is being put into the 
    * shared variable sum at the same time, they get combined
    * (reduced) by using addition
    *
    * The "for" part of the pragma ensures that i is private
    */
   #pragma omp parallel for reduction( +:sum ) private( x )

      /*
       * Calculate the integral
       */
      for ( i = 1; i <= num_steps; i++ ) {
         x = ( i - 0.5 ) * step;
         sum = sum + 4.0 / ( 1.0 + x * x );
      }

   /*
    * Multiply by dx
    */
   pi = step * sum;
   
   printf( "The computed value of pi is %f\n", pi );
}

