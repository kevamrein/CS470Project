CLUSTER_LDFLAG=-L/shared/lib/igraph-0.7.1/build/lib
CLUSTER_CFLAG=-I/shared/lib/igraph-0.7.1/build/include/igraph

default: eigenvalue_est_serial

eigenvalue_est_serial: eigenvalue_est_serial.c
	gcc eigenvalue_est_serial.c  $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -ligraph -o eigenvalue_est_serial

clean:
	rm -f eigenvalue_est_serial
