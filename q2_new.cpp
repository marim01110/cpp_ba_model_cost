#include "q1.cpp"
//#define Debug
using namespace std;

static double cost_candidates[NODES]={};

void q2(){
    int start_node, from, find_status, node_dones=0, continue_num;

    continue_num=gen_normal_distribution();
    if(continue_num!=YES){
        cout << "プログラムを終了します。" << endl;
        exit(-1);
    }

    ba_init_nd();

    for(int i=node_count;i<NODES;i++){
        node_put();
        node_count-=1;
        node_connection_nd(i,define_connect_node());
        node_count+=1;
    }
    print_list();
    
    //search state
    start_node=decide_start_node();
    dijkstra_init(start_node, &from);
    cout << "ノード " << from << " から探索を開始します。" << endl;
