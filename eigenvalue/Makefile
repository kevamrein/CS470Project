CLUSTER_LDFLAG=-L/shared/lib/igraph-0.7.1/build/lib
CLUSTER_CFLAG=-I/shared/lib/igraph-0.7.1/build/include/igraph

default: ec_serial ec_par

ec_serial: ec_serial.c
	gcc ec_serial.c  $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -ligraph -o ec_serial

ec_par: ec_par.c
	gcc ec_par.c  $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -fopenmp -ligraph -o ec_par

clean:
	rm -f ec_serial ec_par
