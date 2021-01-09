#include "q1.cpp"
//#define Debug
using namespace std;

void q2(){
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

void gen_normal_distribution(){
    double avg, sd;
    cout << "正規分布の平均値を入力してください。" << endl;
    scanf("%d",&avg);
    cout << "正規分布の標準偏差を入力してください。" << endl;
    scanf("%d",&sd);

    random_device seed_gen;
    default_random_engine nd(seed_gen());
    
    normal_distribution<> dist(avg, sd);
}