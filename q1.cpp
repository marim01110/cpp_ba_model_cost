#include "func_h.h"
//#define Debug
#define DEFAULT_COST 1
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
static int node_count=0, connect_node_total=0;

void q1(){
    ba_init();

    for(int i=node_count;i<NODES;i++){
        node_put();
        node_count-=1;
        node_connection(i,define_connect_node());
        node_count+=1;
    }

    print_list();
}

void ba_init(){
    for(int i=0;i<3;i++){
        node_put();
    }
    node_connection(0,1);
    node_connection(0,2);
    node_connection(1,2);
    connect_node_total=6;
}//Checked 2021.01.09 17.31

void node_put(){
    node[node_count].node_num=node_count;
    node_count+=1;
}//Checked 2021.01.09 17.31

void node_connection(int node_num, int node_connect){
    int top=node[node_num].connected_nodes;
    node[node_num].connect[top].next_node=node_connect;
    node[node_num].connect[top].cost=DEFAULT_COST;
    node[node_num].connected_nodes+=1;
    connect_node_total+=1;

    top=node[node_connect].connected_nodes;
    node[node_connect].connect[top].next_node=node_num;
    node[node_connect].connect[top].cost=DEFAULT_COST;
    node[node_connect].connected_nodes+=1;
    connect_node_total+=1;
}//Checked 2021.01.09 17.31

int define_connect_node(){
    int node_sel=0;
    long double rd_temp;
    long double priority[node_count]={};

    for(int i=0;i<node_count;i++){
        priority[i]=(long double)node[i].connected_nodes/connect_node_total;
    }

    mt19937 rd{random_device{}()};
    uniform_real_distribution<long double> dist(0, 1);
    rd_temp=dist(rd);
    #ifdef Debug
    cout << "init rd_temp: " << rd_temp << endl;
    #endif

    do{
        rd_temp-=priority[node_sel];
        if(rd_temp<=0) break;
        node_sel+=1;
    }while(true);
    #ifdef Debug
    cout << "cur_max_nodes: " << node_count + 1 << ", selected: " << node_sel << endl;
    #endif
    return node_sel;
}

void print_list(){
    cout << "Total: " << node_count << " nodes" << endl;
    for(int i=0;i<node_count;i++){
        int top=node[i].connected_nodes;
        cout << "Node_num:" << i << ", Total connected nodes: " << top << ", Connected_node_num: ";
        for(int j=0;j<top;j++){
            if(j!=top-1)cout << node[i].connect[j].next_node << ",";
            else cout << node[i].connect[j].next_node << endl;
        }
    }
    cout << endl;
}//Checked 2021.01.09 18.18