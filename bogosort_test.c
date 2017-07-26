/*******************************************************************************
 * NAME:	    bogosort_test.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Test harness for the bogosort.c library.
 *
 * CREATED:	    07/21/2017
 *
 * LAST EDITED:	    07/21/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <assert.h>

#include "bogosort.h"

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static int test_sorted();
static int test_unsorted();

/*******************************************************************************
 * MAIN
 ***/

int main(int argc, char * argv[])
{

  assert(test_sorted());
  assert(test_unsorted());

}

/*******************************************************************************
 * STATIC FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    test_sorted
 *
 * DESCRIPTION:	    Test the bogosort library with an already sorted array.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test fails, 1 if the test passes.
 *
 * NOTES:	    none.
 ***/
static int test_sorted()
{

  int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  if (bogosort(test_arr, (sizeof(test_arr) / sizeof(int))))
    return 0;

  for (int i = 0; i < (sizeof(test_arr) / sizeof(int)); i++)
    printf("%d ", test_arr[i]);
  printf("\n");

  return 1;
}

/*******************************************************************************
 * FUNCTION:	    test_unsorted
 *
 * DESCRIPTION:	    Test the bogosort library with an unsorted array.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test fails, 1 if the test passes.
 *
 * NOTES:	    Might never finish.
 ***/
static int test_unsorted()
{

  int test_arr[] = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9};

  if (bogosort(test_arr, (sizeof(test_arr) / sizeof(int))))
    return 0;

  for (int i = 0; i < (sizeof(test_arr) / sizeof(int)); i++)
    printf("%d ", test_arr[i]);
  printf("\n");
  
  return 1;
}

/******************************************************************************/
