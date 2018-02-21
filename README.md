# Lab 4

## Sequential
g++ -std=c++11 -o sequential sequential.cpp
./sequential {square dimension}
eg: ./sequential 100


## Parallel For
g++ -fopenmp -std=c++11 -o parallel_for parallel_for.cpp
./sequential {square dimension}
eg: ./parallel_for 100