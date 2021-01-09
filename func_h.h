#include <iostream>
#include <stdio.h>
#include <random>

#define NODES 100

void ba_init();
void node_put();
void node_connection(int node_num, int node_connect);
int define_connect_node();
void print_list();
int decide_start_node();