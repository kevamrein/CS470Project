#!/bin/bash
rm simple_output.txt 4_nodes_output.txt 6_nodes_output.txt 12_nodes_output.txt
make clean
make
./eigenvalue_est_serial simple.txt >> simple_output.txt
./eigenvalue_est_serial 4_nodes.txt >> 4_nodes_output.txt
./eigenvalue_est_serial 6_nodes.txt >> 6_nodes_output.txt
./eigenvalue_est_serial 12_nodes.txt >> 12_nodes_output.txt
