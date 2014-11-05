/*
 * This code calculates pi using the formula to calculate
 * the atan(z) which is the integral from 0 to z of 1/(1+x*x)
 * times dx.  atan(1) is 45 degrees or pi/4
 */

#include <omp.h>

static long num_steps = 100000;  /* number of intervals             */
double step;                     /* the size of the interval - dx   */

#define NUM_THREADS 2

void main () {

   int i;                        /* Loop control variable            */
   double  x;                    /* The current x position for 
                                    function evaluation              */
   double  pi=0.0;               /* final results                    */
   double  sum;                  /* Maintains sum of partial results */


  step = 1.0 / ( double ) num_steps;

   /*
    * This may be done more flexibly by using an environment
    * variable instead.
    */
  omp_set_num_threads( NUM_THREADS );

  /*
   * Each thread executes the code in the pragma below
   *
   * See what happens if i is not private!
   */
  #pragma omp parallel private ( i, x, sum )
  {	 
     int id;       /* The identity of the thread */

     id = omp_get_thread_num();

      /*
       * Calculate the integral
       */
     for ( i = id, sum = 0.0; i < num_steps; i = i + NUM_THREADS ) {
        x = ( i + 0.5 ) * step;
        sum += 4.0 / ( 1.0 + x * x );
     }


     /* Because pi is shared between threads, this step must be
      * carried out autonomously.
      * 
      * See what happens when this pragma is removed!
      */
     #pragma omp critical

     /*
      * Multiply by dx
      */
     pi += sum * step;

  } /* end #pragma omp parallel */

  printf( "The computed value of pi is %f\n", pi );

}

