/*******************************************************************************
 * NAME:	    bogosort.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Contains the source code for the Parallelized-Bogosort
 *		    library.
 *
 * CREATED:	    07/21/2017
 *
 * LAST EDITED:	    07/21/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#if defined(_OPENMP) && !defined(CONFIG_SERIAL_THREADS)
#include <omp.h>
#endif

#include "bogosort.h"

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

#if defined(_OPENMP) && !defined(CONFIG_SERIAL_THREADS)
#define CFG_MT
#else
#undef CFG_MT
#endif /* defined(_OPENMP) && !defined(CONFIG_SERIAL_THREADS) */

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static int issorted(int *, int);

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    bogosort
 *
 * DESCRIPTION:	    Sorts an array, using a non-deterministic variant of
 *		    bogosort. Multithreaded!!
 *
 * ARGUMENTS:	    array: (int *) -- the array to sort.
 *
 * RETURN:	    int -- 0 on success, 1 otherwise.
 *
 * NOTES:	    All openmp code is wrapped in the CFG_MT macro. If
 *		    _OPENMP is undefined or source is compiled with 
 *		    CONFIG_SERIAL_THREADS option, this macro expands to nothing.
 ***/
int bogosort(int * array, int size)
{
  if (array == NULL)
    return 1;

  srand((unsigned)time(NULL));

/* #ifdef CFG_MT */
/*   omp_lock_t mutex[size % 13 + 1]; /\* A prime number + 1, just in case. *\/ */
/*   for (int i = 0; i < size % 10; i++) */
/*     omp_init_lock(&mutex[i]); */
/* #endif */

  int sorted = issorted(array, size);
  while (!sorted) {

#ifdef CFG_MT
#pragma omp parallel shared(sorted)
#pragma omp for reduction(+:sorted)
#endif
    for (int i = 0; i < size; i++) {

#ifdef CFG_MT
      /* omp_set_lock(&mutex[i]); */
#pragma omp cancellation point for
#endif

      int index = 0;
      do { index = rand() % size; } while (index == i);
#pragma omp critical
      {
	int temp = array[i];
	array[i] = array[index];
	array[index] = temp;
	/* } */
	/* #ifdef CFG_MT */
	/*       omp_unset_lock(&mutex[i]); */
	/* #endif */

	printf("Thread num %d says: ( ", omp_get_thread_num());
	for (int j = 0; j < size; j++) {
	  printf("%d ", array[j]);
	}
	printf(")\n");

	if (issorted(array, size)) {

#ifdef CFG_MT
#pragma omp critical (junk)
	  sorted = 1;
	  
/* #pragma omp cancel for */
#else
	  sorted = 1;
	  break;
#endif
	}
      }
#pragma omp cancel for
#pragma omp cancellation point for
    }
  }

  return 0;
}

/* int normal(int * array, int size) */
/* { */

/*   if (array == NULL) */
/*     return 1; */

/*   srand((unsigned)time(NULL)); */

/*   int sorted = issorted(array, size); */
/*   while (!sorted) { */
/*     for (int i = 0; i < 10; i++) { */
/*       int index = 0; */
/*       do { index = rand() % size; } while (index == i); */
/*       int temp = array[i]; */
/*       array[i] = array[index]; */
/*       array[index] = temp; */

/*       if (issorted(array, size)) { */
/* 	sorted = 1; */
/* 	break; */
/*       } */
/*     } */
/*   } */

/*   return 0; */
/* } */

/*******************************************************************************
 * STATIC FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    issorted
 *
 * DESCRIPTION:	    Determines if the array passed is correctly sorted.
 *
 * ARGUMENTS:	    array: (int *) -- the array to check.
 *		    size: (int) -- the size of the array.
 *
 * RETURN:	    int -- 1 if the array is sorted, 0 otherwise.
 *
 * NOTES:	    None.
 ***/
static int issorted(int * array, int size)
{
  for (int i = 0; i < size - 1; i++)
    if (array[i] > array[i + 1])
      return 0;
  return 1;
}

/******************************************************************************/
