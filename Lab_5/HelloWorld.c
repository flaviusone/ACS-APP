#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>
void main(int argc,char *argv[]) {

  int ID; 		/* Thread identification number*/
  int numThreads;	/* Current number of threads running */

  /**************************************************************
   * You can internally set the number of threads the program is to
   * use, with
   *
   *    omp_set_num_threads(4); 
   *
   * but then you must recompile for each number of processors.
   *
   *    omp_get_num_thread(); 
   * returns the number of threads currently being used, so it will 
   * be 1 if outside a pragma (i.e., in the master thread).
   */

   numThreads = omp_get_num_threads();
   printf("Outside of the pragma, the number of threads is %d\n\n", 
           numThreads);
   #pragma omp parallel private(ID)
   {
       numThreads = omp_get_num_threads();
       printf("Inside the pragma, the number of threads is %d\n", 
               numThreads);
       printf("\n");

       ID = omp_get_thread_num();

       printf("Hello(%d)",ID);
       printf(" world from process %d!\n", ID);
   }

   /* 
    * Not strictly needed but makes makefile target "run" end
    * without error
    */
   exit(0);

}
