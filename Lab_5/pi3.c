/*
 * This code calculates pi using the formula to calculate
 * the atan(z) which is the integral from 0 to z of 1/(1+x*x)
 * times dx.  atan(1) is 45 degrees or pi/4
 *
 * Interestingly enough, this version disagrees with the others in
 * the last two decimal places shown. (floating point error 
 * accumulation?)
 */

#include <omp.h>

static long num_steps = 100000;  /* number of intervals             */
double step;                     /* the size of the interval - dx   */

#define NUM_THREADS 2

void main () {	  

   int i;                        /* Loop control variable            */
   double  x;                    /* Actually not used                */
   double  pi;                   /* final results                    */
   double  sum[NUM_THREADS];     /* Maintains partial sum for thread */

   step = 1.0 / ( double ) num_steps;

   /*
    * This may be done more flexibly by using an environment 
    * variable instead.
    */
   omp_set_num_threads( NUM_THREADS );

   /*
    * Each thread executes the code below
    */
   #pragma omp parallel 
   {	  
      double x;     /* The current x position for function
                       evaluation                            */
      int id;       /* The identity of the thread            */

      id = omp_get_thread_num();       

      sum[ id ] = 0;

      /*
       * We didn't need to make i private because the pragma
       * below does that for us.  However, it may cost us some
       * as more processes may be spawned
       */
      #pragma omp for

      /*
       * Calculate the integral
       */
      for ( i = id; i < num_steps; i++ ) {
         x = ( i + 0.5 ) * step;
	 sum[ id ] += 4.0 / ( 1.0 + x * x );
      }

   }	  

   /*
    * Multiply by dx
    */
   for ( i = 0, pi = 0.0; i < NUM_THREADS; i++ )
      pi += sum[ i ] * step;

   printf( "The computed value of pi is %f\n", pi );

}

