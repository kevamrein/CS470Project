CLUSTER_LDFLAG=-L/shared/lib/igraph-0.7.1/build/lib
CLUSTER_CFLAG=-I/shared/lib/igraph-0.7.1/build/include/igraph

default: community_center_serial

community_center_serial: community_center_serial.c
	gcc community_center_serial.c  $(CLUSTER_CFLAG) $(CLUSTER_LDFLAG) -ligraph -o community_center_serial

clean:
	rm -f community_center_serial
