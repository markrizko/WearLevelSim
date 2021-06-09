#include <iostream>
#include <random>
#include <ctime>
#include "disk.h"

// random int, matching int means same data
// in order the data will be written
int dataset[1500] = {0};

int main(){
    srand(time(NULL));
    int length = sizeof(dataset) / sizeof(dataset[0]);
    disk dynamic, statci, none;

    for (int i = 0; i < 1500; ++i){
        dataset[i] = rand() % 6 + 1; // data between 1-6
    }
    for (int i = 0; i < 50; ++i){ // 50 random 7s will be in dataset to represent static "less used" data
        dataset[rand() % 999] = 7;
    }

    dynamic.writeDynamic(dataset, length);
    none.noWearLeveling(dataset, length);
    statci.writeStatic(dataset, length);

    cout << endl << "Dynamic Wear Leveling" << endl;
    dynamic.printDisk();
    cout << endl << "No Wear Leveling" << endl;
    none.printDisk();
    cout << endl << "Static Wear Leveling" << endl;
    statci.printDisk();

    return 0;

}

