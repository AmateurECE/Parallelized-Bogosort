################################################################################
# NAME:		    makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    The test makefile.
#
# CREATED:	    07/21/2017
#
# LAST EDITED:	    10/24/2017
###

TOP:=$(PWD)
CFLAGS = -Wall -O3 -fopenmp
LDLIBS = -fopenmp
CC=gcc

SRCS += bogosort.c
SRCS += bogosort_test.c

OBJS=$(patsubst %.c,%.o,$(SRCS))

.PHONY: force clean

bogosort_test: force $(OBJS) clean
	$(CC) $(CFLAGS) $(OBJS) \
		-o bogosort_test $(LDLIBS)

serial: force $(OBJS) clean
	$(CC) $(CFLAGS) -DCONFIG_SERIAL_THREADS $(OBJS) \
		-o bogosort_test $(LDLIBS)

$(OBJS): force

force:

clean:
	rm -f $(TOP)/*.o
	rm -f $(TOP)/*.c~ # Temp files created by emacs
	rm -f $(TOP)/*.h~ # ""

################################################################################
