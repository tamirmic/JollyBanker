#include <iostream>
#include "jolly_banker.h"

int main(int argc, char *argv[]){
    if (argc != 2){
        cout << "ERROR: This program requires a file to run" << endl;
        return 0;
    }
    JollyBanker jolly_banker = JollyBanker();
    jolly_banker.Init(string(argv[1]));
    jolly_banker.Process();
    jolly_banker.Display();
}