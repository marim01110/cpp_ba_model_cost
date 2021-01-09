#include "func_h.h"
//#define Debug
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
static int route_array[NODES]={}, node_done[NODES]={}, cost_array[NODES]={};
static int node_count=0, connect_node_total=0, node_remains=NODES;

void q1(){
    int start_node, from, find_status;

    ba_init();

    for(int i=node_count;i<NODES;i++){
        node_put();
        node_count-=1;
        node_connection(i,define_connect_node());
        node_count+=1;
    }
    print_list();
    
    //search state
    start_node=decide_start_node();
    dijkstra_init(start_node, &from);
    cout << "ノード " << from << " から探索を開始します。" << endl;

    do{
        find_node(from);
        node_done[from]=DONE;
        node_remains-=1;
        #ifdef Debug
        cout << "node_remains: " << node_remains-1 <<endl;
        #endif
        if(node_remains==1){
            cout << "全ノードの経路探索が終了しました。" << endl;
            cout << endl;
            break;
        }
        dijkstra_position_update(&from);
    }while(true);

    print_cost_list();
    do{
        int error=print_route(start_node);
        if(error!=0) break;
    }while(true);
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
}//Checked 2021.01.09 21.24

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

int decide_start_node(){
    int node;
    cout << "スタートノードを設定してください。[0-" << NODES - 1 << "]" << endl;
    scanf("%d",&node);
    return node;
}//Checked 2021.01.09 21.24

void dijkstra_init(int input, int* x){
    //set position to goal node
    *x=input;

    //array init
    for(int i=0;i<NODES;i++){
        cost_array[i]=UNDONE;
        node_done[i]=UNDONE;
    }
    cost_array[input]=0;//set cost of start node to zero
}//checked 2020.01.03 00.47

void find_node(int from){
    int top=node[from].connected_nodes, temp_cost;
    for(int i=0;i<top;i++){
        temp_cost=DEFAULT_COST;
        if((cost_array[node[from].connect[i].next_node] > cost_array[from] + temp_cost) and (cost_array[node[from].connect[i].next_node] > 0)){
            cost_array[node[from].connect[i].next_node]=cost_array[from]+temp_cost;
            route_array[node[from].connect[i].next_node]=from;
        }
        if(cost_array[node[from].connect[i].next_node] == UNDONE){
            cost_array[node[from].connect[i].next_node]=cost_array[from]+temp_cost;
            route_array[node[from].connect[i].next_node]=from;
        }
    }
}//Checked 2021.01.09 21.24

void dijkstra_position_update(int* from){
    int min=INF;

    for(int i=0;i<NODES;i++){
        if((node_done[i] == UNDONE) and (cost_array[i] > 0)){
            if(min > cost_array[i]){
                min=cost_array[i];
                *from = i;
            }
        }
    }
}//checked 2021.01.09 21.29

void print_cost_list(){
    for(int i=0;i<NODES;i++){
        cout << "Node_num:" << i << ", Cost: " << cost_array[i] << endl;
    }
    cout << endl;
}//checked 2021.01.09 21.37

int print_route(int start){
    int to, count;
    int temp[HSIZE]={};

    cout << "目標地点を設定してください。[0-" << NODES-1 << "] 範囲外の地点を入力すると終了します。" << endl;
    scanf("%d", &to);
    cout << endl;
    count=0;
    if((to >= NODES) or (to < 0)) return -1;
    else if(to == start){
        cout << "スタートノードと目標ノードが同一ノードです。" << endl;
    }
    else{
        temp[count]=to;
        do{
            count+=1;
            temp[count]=route_array[temp[count-1]];
            if(temp[count] == start) break;
        }while(true);

        cout << start << " から、" << to << " までの最短経路は以下の通りです。" << endl;
        
        for(int i=count;i>=0;i--){
            if(i!=0) cout << temp[i] << " -> ";
            if(i==0) cout << temp[i] << endl;
        }

        cout << "また距離（コスト）は、" << cost_array[to] << "です。" << endl;
    }
    cout << endl;
    return 0;
}