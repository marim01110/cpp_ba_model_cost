#include "func.cpp"
using namespace std;

typedef struct connect_t{
    int next_node;
    int cost;
}_connect;

typedef struct node_t{
    int node_num;
    _connect connect[NODES]={NULL};
}_node;

_node node[NODES]={NULL};
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

void node_connection(int node_num){
    
}