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
    print_list();
}

void ba_init(){
    for(int i=0;i<3;i++){
        node_put();
    }
    node_connection(0,1);
    node_connection(0,2);
    node_connection(1,2);
}

void node_put(){
    node[node_count].node_num=node_count;
    node_count+=1;
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

void print_list(){
    cout << "Total: " << node_count << "." << endl;
    for(int i=0;i<node_count;i++){
        int top=node[i].connected_nodes;
        cout << "Node_num:" << i << ", Connected_node_num: ";
        for(int j=0;j<top;j++){
            cout << node[i].connect[j].next_node << ",";
        }
        cout << endl;
    }
    cout << endl;
}