/*
 *   Stack-based Quicksort
 *
 *   The quicksort algorithm works by repeatedly dividing unsorted
 *   sub-arrays into two pieces: one piece containing the smaller
 *   elements and the other piece containing the larger elements.
 *   The splitter element, used to subdivide the unsorted sub-array,
 *   ends up in its sorted location. By repeating this process on
 *   smaller and smaller sub-arrays, the entire array gets sorted.
 *
 *   The typical implementation of quicksort uses recursion. This
 *   implementation replaces recursion with iteration. It manages its
 *   own stack of unsorted sub-arrays. When the stack of unsorted
 *   sub-arrays is empty, the array is sorted.
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX_UNFINISHED 1000	/* Maximum number of unsorted sub-arrays */
/* Global shared variables */
struct {
    int first;			/* Low index of unsorted sub-array */
    int last;			/* High index of unsorted sub-array */
} unfinished[MAX_UNFINISHED];	/* Stack */
int unfinished_index;		/* Index of top of stack */
float *A;			/* Array of elements to be sorted */
int n;				/* Number of elements in ‘A’ */
/* Function 'swap' is called when we want to exchange two array elements */
void swap(float *x, float *y)
{
    float tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

/* Function 'partition' actually does the sorting by dividing an
   Unsorted sub-array into two parts: those less than or equal to the
   splitter, and those greater than the splitter. The splitter is the
   last element in the unsorted sub-array. The splitter ends up in its
   final, sorted location. The function returns the final location of
   the splitter (its index). This code is an implementation of the
   algorithm appearing in “Introduction to Algorithms, Second Edition”,
   by Cormen, Leiserson, Rivest, and Stein (The MIT Press, 2001). */
int partition(int first, int last)
{
    int i, j;
    float x;
    x = A[last];
    i = first - 1;
    for (j = first; j < last; j++)
	if (A[j] <= x) {
	    i++;
	    swap(&A[i], &A[j]);
	}
    swap(&A[i + 1], &A[last]);
    return (i + 1);
}

/* Function 'quicksort' repeatedly retrieves the indices of unsorted
   sub-arrays from the stack and calls 'partition' to divide these
   sub-arrays into two pieces. It keeps one of the pieces and puts the
   other piece on the stack of unsorted sub-arrays. Eventually it ends
   up with a piece that doesn't need to be sorted. At this point it
   gets the indices of another unsorted sub-array from the stack. The
   function continues until the stack is empty. */
void quicksort(void)
{
    int first;
    int last;
    int my_index;
    int q;			/* Split point in array */
    while (unfinished_index >= 0) {
	my_index = unfinished_index;
	unfinished_index--;
	first = unfinished[my_index].first;
	last = unfinished[my_index].last;
	while (first < last) {
	    /* Split unsorted array into two parts */
	    q = partition(first, last);
	    /* Put upper portion on stack of unsorted sub-arrays */
	    if ((unfinished_index + 1) >= MAX_UNFINISHED) {
		printf("Stack overflow\n");
		exit(-1);
	    }
	    unfinished_index++;
	    unfinished[unfinished_index].first = q + 1;
	    unfinished[unfinished_index].last = last;
	    /* Keep lower portion for next iteration of loop */
	    last = q - 1;
	}
    }
}

/* Function 'print_float_array', given the address and length of an
   Array of floating-point values, prints the values to standard
   output, one element per line. */
void print_float_array(float *A, int n)
{
    int i;
    printf("Contents of array:\n");
    for (i = 0; i < n; i++)
	printf("%6.4f\n", A[i]);
}

/* Function 'verify_sorted' returns 1 if the elements of array 'A'
   are in monotonically increasing order; it returns 0 otherwise. */
int verify_sorted(float *A, int n)
{
    int i;
    for (i = 0; i < n - 1; i++)
	if (A[i] > A[i + 1])
	    return 0;
    return 1;
}

/* Function 'main' gets the array size and random number seed from
   the command line, initializes the array, prints the unsorted array,
   sorts the array, and prints the sorted array. */
int main(int argc, char *argv[])
{
    int i;
    int seed;			/* Seed component input by user */
    unsigned short xi[3];	/* Random number seed */
    if (argc != 3) {
	printf("Command-line syntax: %s <n> <seed>\n", argv[0]);
	exit(-1);
    }
    seed = atoi(argv[2]);
    xi[0] = xi[1] = xi[2] = seed;
    n = atoi(argv[1]);
    A = (float *) malloc(n * sizeof(float));
    for (i = 0; i < n; i++)
	A[i] = erand48(xi);
/*
   print_float_array (A, n);
*/
    unfinished[0].first = 0;
    unfinished[0].last = n - 1;
    unfinished_index = 0;
    quicksort();
/*
   print_float_array (A, n);
*/
    if (verify_sorted(A, n))
	printf("Elements are sorted\n");
    else
	printf("ERROR: Elements are NOT sorted\n");
    return 0;
}
