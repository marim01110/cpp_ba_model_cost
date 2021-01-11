#include "q1.cpp"
#define Debug
using namespace std;

static double cost_candidates[NODES]={};

void q2(){
    int start_node, from, find_status, node_dones=0;

    gen_normal_distribution();

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
    bf_init(start_node, &from);
    cout << "ノード " << from << " から探索を開始します。" << endl;

    do{
        find_node(from);
        node_done[from]=DONE;
        node_remains-=1;
        node_dones=0;
        for(int i=0;i<NODES;i++){
            if(node_done[i]==DONE) node_dones+=1;
        }
        #ifdef Debug
        cout << "node_remains: " << node_remains-1 << ", node_dones: " << node_dones << endl;
        #endif

        if(node_dones==NODES-1){
            cout << "全ノードの経路探索が終了しました。" << endl;
            cout << endl;
            break;
        }
        if(node_remains<0){
            cout << "閉路を検知しました。" << endl;
            cout << endl;
            break;
        }
        bf_position_update(&from);
    }while(true);

    print_cost_list();
    do{
        int error=print_route(start_node);
        if(error!=0) break;
    }while(true);
}

void ba_init_nd(){
    for(int i=0;i<3;i++){
        node_put();
    }
    node_count=0;
    node_connection_nd(0,1);
    node_count+=1;
    node_connection_nd(0,2);
    node_count+=1;
    node_connection_nd(1,2);
    node_count+=1;
    connect_node_total=6;
}//Checked 2021.01.11 17.34

void node_connection_nd(int node_num, int node_connect){
    int top=node[node_num].connected_nodes;
    node[node_num].connect[top].next_node=node_connect;
    node[node_num].connect[top].cost=cost_candidates[node_count];
    node[node_num].connected_nodes+=1;
    connect_node_total+=1;

    top=node[node_connect].connected_nodes;
    node[node_connect].connect[top].next_node=node_num;
    node[node_connect].connect[top].cost=cost_candidates[node_count];
    node[node_connect].connected_nodes+=1;
    connect_node_total+=1;
}//Checked 2021.01.11 17.34

void gen_normal_distribution(){
    double avg, sd;
    cout << "正規分布の平均値を入力してください。" << endl;
    cin >> avg;
    cout << "正規分布の標準偏差を入力してください。" << endl;
    cin >> sd;

    random_device seed_gen;
    default_random_engine nd(seed_gen());
    
    normal_distribution<> dist(avg, sd);
    
    for(int i=0;i<NODES;i++){
        cost_candidates[i]=dist(nd);
        cout << cost_candidates[i] << endl;
    }
}//Checked 2021.01.11 17.34

void bf_init(int input, int* x){
    //set position to goal node
    *x=input;

    //array init
    for(int i=0;i<NODES;i++){
        cost_array[i]=INF;
        node_done[i]=UNDONE;
    }
    cost_array[input]=0;//set cost of start node to zero
}//checked 2020.01.11 18.10

void bf_position_update(int* from){
    double min=INF;

    for(int i=0;i<NODES;i++){
        if(node_done[i] == UNDONE){
            if(min > cost_array[i]){
                min=cost_array[i];
                *from = i;
            }
        }
    }
}//checked 2021.01.09 21.29