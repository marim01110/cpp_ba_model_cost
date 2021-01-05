#include <iostream>
#include <stdio.h>
#include <random>

#define NODES 10
#define DEFAULT_COST 1

void ba_init();
void node_put();
void node_connection(int node_num, int node_connect);
void print_list();