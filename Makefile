################################################################################
# NAME:		    makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    The test makefile.
#
# CREATED:	    07/21/2017
#
# LAST EDITED:	    07/21/2017
###

CFLAGS = -g -Wall -O0 -fopenmp
LDLIBS = -fopenmp
CC = gcc

bogosort_test: bogosort.c

