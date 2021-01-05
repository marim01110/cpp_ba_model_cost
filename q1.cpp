#include "func_h.h"
using namespace std;

typedef struct connect_t{
    int next_node=-1;
    int cost;
}_connect;

typedef struct node_t{
    int node_num;
    int connected_nodes=0;
    _connect connect[NODES]={};
}_node;

_node node[NODES]={};
static int node_count=0;

void q1(){
    ba_init();
}

void ba_init(){
    for(int i=0;i<3;i++){
        
    }
}

void node_put(){
    node[node_count].node_num=node_count;
}

void node_connection(int node_num, int node_connect){
    int top=node[node_num].connected_nodes;
    node[node_num].connect[top].next_node=node_connect;
    node[node_num].connect[top].cost=DEFAULT_COST;
    node[node_num].connected_nodes+=1;

    top=node[node_connect].connected_nodes;
    node[node_connect].connect[top].next_node=node_num;
    node[node_connect].connect[top].cost=DEFAULT_COST;
    node[node_connect].connected_nodes+=1;
}