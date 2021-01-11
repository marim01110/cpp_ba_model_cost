#include <iostream>
#include <stdio.h>
#include <random>

#define INF 99999
#define NODES 100
#define DONE 1
#define UNDONE -1
#define YES 1
#define NO -1
#define HSIZE NODES*10//history array size
#define UNUSED 0
#define USED 1

//Create Network
void ba_init();
void node_put();
void node_connection(int node_num, int node_connect);
int define_connect_node();
void print_list();
int decide_start_node();
//dijkstra
void dijkstra_init(int input, int* x);
void find_node(int from);
void dijkstra_position_update(int* from);
void print_cost_list();
int print_route(int start);
//decide cost
void ba_init_nd();
void node_connection_nd(int node_num, int node_connect);
void gen_normal_distribution();
void dijkstra_init_nd(int input, int* x);
void dijkstra_position_update_nd(int* from);