/*
  !-----------------------------------------------------------------------
  ! Unauthorized use or distribution of this program is not permitted.
  !
  ! Author: Ruud van der Pas 
  !
  ! Copyright 2007 - Sun Microsystems
  !-----------------------------------------------------------------------
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "labs.h"
#include "interface.h"

void main(int argc, char *argv[])
{
   FILE      *fp;
   int       m, n, tid;
   long long kr, fixed_repeat_count, repeat_count;
   float     mflops, memsize;
   double    *a, *b, *c, *ref, ts, te_col, te_row, te_lib,
             perf_col, perf_row, perf_lib;
   double tstart,tend;
   //   volatile long unsigned t;
   /*
   tstart = time(NULL);
   tend = time(NULL);
   printf("Loop used %f seconds.\n", difftime(end, start));
   */
   //   printf("Argv 2-6 %s %s %s.\n", argv[2], argv[3], argv[4]);
   n = atoi(argv[2]);
   m = atoi(argv[4]);
   //     printf("n %d m %d", n, m);

/*
  ------------------------------------------------------------------------ 
  Get command line options and the number of threads in use
  ------------------------------------------------------------------------ 
*/
//   (void) get_command_line_options(argc, argv, &m, &n, &threshold_row, 
//                                   &threshold_col, &fixed_repeat_count);
   tid = omp_get_thread_num();
   if (tid == 0)
     {
       nthreads = omp_get_num_threads(); /*-- Returns the number of active threads --*/
//       printf("Starting matrix multiple example with %d threads\n",nthreads);

       threshold_row = 1;
       threshold_col = 1;
       fixed_repeat_count = 3;
     }
/*
  ------------------------------------------------------------------------ 
  Check for the plot file. If it is not present, open it and write the
  header. Otherwise, open it in append mode.
  ------------------------------------------------------------------------ 
*/
   if ( (fp = fopen("perf.dat","r")) == NULL) {
      if ( (fp = fopen("perf.dat","w")) != NULL) {
         fprintf(fp,"# M\tN\tMemory Footprint\tPerformance\t\t\tExecution Time\n");
         fprintf(fp,"#\t\t\tRow\tColumn\tPerfLib\tRow\tColumn\tPerfLib\n");
         fprintf(fp,"#  \t \t(KByte)\t(Mflop/s)\t(Mflop/s)\t(Mflop/s)\t(seconds)\t(seconds)\t(seconds)\n");
      }
      else
         {perror("open file perf.dat for writing"); exit(-1); }
   }
   else
   {
     if ( (fp = fopen("perf.dat","a")) == NULL) {
        perror("open file perf.dat in append mode"); exit(-1);
     }
   }

/*
  ------------------------------------------------------------------------ 
  Allocate storage.
  ------------------------------------------------------------------------ 
*/
   if ( (a=(double *)malloc(m*sizeof(double))) == NULL ) {
      perror("array a"); exit(-1);
   }
   if ( (b=(double *)malloc(m*n*sizeof(double))) == NULL ) {
      perror("array b"); exit(-1);
   }
   if ( (c=(double *)malloc(n*sizeof(double))) == NULL ) {
      perror("array c"); exit(-1);
   }
   if ( (ref=(double *)malloc(m*sizeof(double))) == NULL ) {
      perror("array ref"); exit(-1);
   }

/*
  ------------------------------------------------------------------------ 
  Initialize data, compute floating-point operations and memory use
  ------------------------------------------------------------------------ 
*/
   (void) init_data(m, n, a, b, c, ref);

   mflops   = 3.0*m*n*1.0E-06;
   memsize  = sizeof(double)*(m+m*n+n)/1024.0; /*-- KByte --*/

/*
  ------------------------------------------------------------------------ 
  Computational part - For all three versions, do the following:
     - Get repeat count needed to obtain accurate timings
     - Execute matrix times vector algorithm
     - Check results
  ------------------------------------------------------------------------ 
*/
   if ( fixed_repeat_count == 0 )
     {repeat_count = fixed_repeat_count;}
	  //estimate_repeat_count(m, n, a, b, c, mxv_row);}
   else 
      {repeat_count = fixed_repeat_count; }

   //tstart = time(NULL);
   tstart = clock();
   //   ts = sats_timer();
   for ( kr=0; kr < repeat_count; kr++)
       (void) mxv_row(m, n, a, b, c);
   //   te_row   = sats_timer() - ts;
   //tend = time(NULL);
   tend = clock();
   //printf("%.5lf \n", (te-tst)/CLOCKS_PER_SEC);
   //te_row = (double) difftime(tend, tstart);
   te_row = (tend - tstart)/CLOCKS_PER_SEC;
   perf_row = repeat_count*mflops/te_row;

   if (check_results("mxv_row",m, n, a, ref) > 0 ) exit(-2);

   if ( fixed_repeat_count == 0 )
     {repeat_count = fixed_repeat_count;}
	  //estimate_repeat_count(m, n, a, b, c, mxv_col);}
   else 
      {repeat_count = fixed_repeat_count; }

   tstart = clock();
   //   ts = sats_timer();
   for ( kr=0; kr < repeat_count; kr++)
       (void) mxv_col(m, n, a, b, c);
   tend = clock();
   te_col = (tend - tstart)/CLOCKS_PER_SEC;
   //te_col = (double) difftime(tend, tstart);
   //   te_col   = sats_timer() - ts;
   perf_col = repeat_count*mflops/te_col;

   if (check_results("mxv_col",m, n, a, ref) > 0 ) exit(-2);

   if ( fixed_repeat_count == 0 )
     {repeat_count = fixed_repeat_count;}
	  //estimate_repeat_count(m, n, a, b, c, mxv_lib);}
   else
      {repeat_count = fixed_repeat_count; }

   /*   ts  = sats_timer();
   for ( kr=0; kr < repeat_count; kr++)
       (void) mxv_lib(m, n, a, b, c);
   te_lib   = sats_timer() - ts;
   perf_lib = repeat_count*mflops/te_lib;
   */
   //if (check_results("mxv_lib",m, n, a, ref) > 0 ) exit(-2);

/*
  ------------------------------------------------------------------------ 
  Done - print results and release memory and close output file
  ------------------------------------------------------------------------ 
*/

   fprintf(fp,"%5d\t%5d\t%11.2f\t%10.1f\t%10.1f\t%10.1f\t%9.2f\t%9.2f\t%9.2f\n",
           m,n,memsize,perf_row,perf_col,perf_lib,te_row,te_col,te_lib);

   //   if ( check_header() == 'y' ) {
      printf("----------------------------------------------------------------------\n");
      printf("   M    N   Mem(KB)   Threads   Thresholds       Performance (Mflop/s)\n"); 
      printf("                                 Row   Col       Row      Col      Lib\n");
      printf("----------------------------------------------------------------------\n");
      //   }

   printf("%4d %4d %9.2f   %7d   %4d  %4d  %8.1f %8.1f %8.1f\n",
          m,n,memsize,nthreads,threshold_row,threshold_col,perf_row,perf_col,perf_lib);

   free(a); free(b); free(c); free(ref);

   fclose(fp);
   return;
}
