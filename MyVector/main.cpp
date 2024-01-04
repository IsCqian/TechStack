#include <iostream>
#include "Vec.h"
#include"test.h"

using namespace std;

int main(){
    int _=1;
    while(_--){
        create_test();
        Efficiency_Testing();
        add_delete_search_test();
    }
    return 0;
}