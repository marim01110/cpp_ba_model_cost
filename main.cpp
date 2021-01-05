#include <iostream>
#include <stdio.h>

#include "q1.cpp"
//#include "q2.cpp"

using namespace std;

int main(){
    int sel;
    cout << "課題何番を実行しますか？[1/2]" << endl;
    scanf("%d",&sel);
    switch(sel){
        case 1: q1();
                break;
        case 2: //q2();
                break;
        default:cout << sel << "番の課題はありません。" << endl;
                break;
    }
    
    cout << "プログラムを終了します。" << endl;
    return 0;
}