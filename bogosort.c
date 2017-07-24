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

#ifdef CFG_MT
#define pfor(var, ...)						\
  _Pragma("omp parallel")					\
  _Pragma("omp for reduction(+:sorted)")			\
  for(__VA_ARGS__)

#else
#define pfor(var, ...) for(__VA_ARGS__)
#endif /* CFG_MT */

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

#ifdef CFG_MT
  omp_lock_t mutex[size % 10]; /* Probably no reason to have more than 10. */
  for (int i = 0; i < size % 10; i++)
    omp_init_lock(&mutex[i]);
#endif /* CFG_MT */

  int sorted = issorted(array, size);
  while (!sorted) {
    pfor (socket, int i = 0; i < size; i++) {

      int index = 0;
      do { index = rand() % size; } while (index == i);
      int temp = array[i];

#ifdef CFG_MT
      omp_set_lock(&mutex[i]);
#endif /* CFG_MT */
      array[i] = array[index];
      array[index] = temp;
#ifdef CFG_MT
      omp_unset_lock(&mutex[i]);
#endif /* CFG_MT */

      if (issorted(array, size)) {
#ifdef CFG_MT
#pragma omp critical
	{
	  sorted = 1;
	}
	
#pragma omp cancel for
#else
	sorted = 1;
	break;
#endif /* CFG_MT */
      }

#ifdef CFG_MT
#pragma omp cancellation point for
#endif /* CFG_MT */
    }
  }

  return 0;
}

int normal(int * array, int size)
{

  if (array == NULL)
    return 1;

  srand((unsigned)time(NULL));

  int sorted = issorted(array, size);
  while (!sorted) {
    for (int i = 0; i < 10; i++) {
      int index = 0;
      do { index = rand() % size; } while (index == i);
      int temp = array[i];
      array[i] = array[index];
      array[index] = temp;

      for(int i = 0; i < size; i++) {
	printf("%d ", array[i]);
      }
      printf("\n");

      if (issorted(array, size)) {
	sorted = 1;
	break;
      }
    }
  }

  return 0;
}

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
