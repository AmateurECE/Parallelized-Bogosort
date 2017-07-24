/*******************************************************************************
 * NAME:	    bogosort.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file containing the public interface for the
 *		    parallelized bogosort algorithm library. And no, this is
 *		    not supposed to be serious.
 *
 * CREATED:	    07/21/2017
 *
 * LAST EDITED:	    07/21/2017
 ***/

/**
 * \file bogosort.h
 * \author Ethan D. Twardy
 * \date 07/21/2017
 * \brief Parallel-Bogosort Header File
 *
 * <p>This header file contains the public interface for the parallelized-bogosort
 * algorithm library. If OpenMP is installed on your system, the library will
 * compile to utilize it. Otherwise, the library is still usable without.</p>
 * <p>In addition, compiling with the option -D CONFIG_SERIAL_THREADS will
 * prevent compilation with OpenMP.
 */

#ifndef __ET_BOGOSORT_H__
#define __ET_BOGOSORT_H__

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/**
 * \brief This is the bogosort function. It does that thing.
 * \param array The array of integers to sort.
 * \return Anything at all, if you're lucky.
 */
int bogosort(int * array, int size);
int normal(int * array, int size);
#endif /* __ET_BOGOSORT_H__ */

/******************************************************************************/
