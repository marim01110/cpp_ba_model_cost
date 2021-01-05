#include "func.cpp"
using namespace std;

typedef struct connect_t{
    int next_node;
    int cost;
}_connect;

typedef struct node_t{
    int node_num;
    _connect connect[NODES];
}_node;

void q1(){
    ba_init();
}

void ba_init(){
    cout<<endl;
}