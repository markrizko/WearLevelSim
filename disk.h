#include <iostream>

using namespace std;



class block{
    public:
        block(){
            data = 0;
            w_no = 0;
        }

        block(int d, int w){
            data = d;
            w_no = w;
        }

        int getWriteNo(){
            return w_no;
        }

        int getData(){
            return data;
        }



        void setData(int d){
            data = d;
        }

        void incWrite(){
            w_no++;
        }

        

    private:
        int data; // random data larger than 0
        int w_no; // number of writes to block
};

class disk{
    public:
        disk(){
            
        }
        // get next empty block with least writes
        int getEmptyBlock(){
            block d(0, 5000);
            int cur = 0;

            for (int i = 0; i < 10; ++i){
                if (blocks[i].getData() == 0){
                    if (blocks[i].getWriteNo() < d.getWriteNo()){
                        d = blocks[i];
                        cur = i;
                    }
                }
            }
            return cur;
        }

        int getLeastWritten(){
            block d(0, 5000);
            int cur = 0;
            for (int i = 0; i < 10; ++i){
                if (blocks[i].getWriteNo() < d.getWriteNo()){
                    d = blocks[i];
                    cur = i;
                }
            }
            return cur;
        }

        int getMostWritten(){
            block d(0, -1);
            int cur = 0;
            for (int i = 0; i < 10; ++i){
                if (blocks[i].getWriteNo() > d.getWriteNo()){
                    d = blocks[i];
                    cur = i;
                }
            }
            return cur;
        }
        
        int getTotalWrites(){
            int sum = 0;
            for (int i = 0; i < 10; ++i){
                sum+= blocks[i].getWriteNo();
            }
            return sum;
        }

        int onDisk(int d){
            for (int i = 0; i < 10; ++i){
                if (blocks[i].getData() == d){
                    return i;
                }
            }
            return -1;
        }

        void writeDynamic(int *dataset, int length){
            for (int i = 0; i < length; ++i){
                if (onDisk(dataset[i]) == -1){ // if not in there, find empty block and write
                    writeBlock(dataset[i], getEmptyBlock()); // write empty block 
                    cout << "Writing empty" << endl; 
                }
                else{ // if on disk, delete current location and write to a newer block
                    emptyBlock(onDisk(dataset[i]));
                    writeBlock(dataset[i], getEmptyBlock());
                    cout << "Moving " << dataset[i] << " to position " << getEmptyBlock() << endl;
                }
            }
        }

        void writeStatic(int *dataset, int length){
            int least, empty;
            for (int i = 0; i < length; ++i){
                least = getLeastWritten();
                empty = getEmptyBlock();

                if (i % 5 == 0 && blocks[least].getData() != 0){
                    writeBlock(blocks[least].getData(), empty);
                    emptyBlock(least);
                    
                }
                if (onDisk(dataset[i]) == -1){ // if not in there, find empty block and write
                    writeBlock(dataset[i], getEmptyBlock()); // write empty block 
                    cout << "Writing empty" << endl; 
                }
                else{ // if on disk, delete current location and write to a newer block
                    emptyBlock(onDisk(dataset[i]));
                    writeBlock(dataset[i], getEmptyBlock());
                    cout << "Moving " << dataset[i] << " to position " << getEmptyBlock() << endl;
                }
                // every 10 operations move least to most
                // if (onDisk(dataset[i]) == -1){
                //     cout << "Writing empty" << endl; 
                //     if (onDisk(least) == -1){ // if spot with least writes is empty, no problem
                //         writeBlock(dataset[i], least); 
                //     }
                //     else{ // move least to empty and replace it with current
                //        writeBlock(blocks[least].getData(), getEmptyBlock());
                //        writeBlock(dataset[i], least);
                //     }
                    
                // }
                // else{ // if block already there delete it and do same logic
                //     emptyBlock(onDisk(dataset[i]));
                //     if (onDisk(least) == -1){ // if spot with least writes is empty, no problem
                //         writeBlock(dataset[i], least); 
                //     }
                //     else{ // move least to empty and replace it with current
                //        writeBlock(blocks[least].getData(), onDisk(dataset[i]));
                //        writeBlock(dataset[i], least);
                //     }
                // }
            }
        }

        void noWearLeveling(int *dataset, int length){
            for (int i = 0; i < length; ++i){
                if (onDisk(dataset[i]) == -1){
                    writeBlock(dataset[i], getEmptyBlock());
                    cout << "Writing empty" << endl;
                }
                else{
                    writeBlock(dataset[i], onDisk(dataset[i]));
                    cout << "Overwriting " << dataset[i] << " at same location " << onDisk(dataset[i]) << endl;
                }
            }
        }


        void emptyBlock(int pos){
            blocks[pos].setData(0);
        }

        void writeBlock(int d, int pos){
            blocks[pos].setData(d);
            blocks[pos].incWrite();
        }


        void printDisk(){
            cout << "Disk:\n";
            for (int i = 0; i < 10; ++i){
                cout << i <<  "     Data: " << blocks[i].getData() << "     #of Writes: " << blocks[i].getWriteNo() << endl;
            }
            cout << "-------------------------------------------------------" << endl;

            cout << endl << "Total Writes: " << getTotalWrites() << endl;
        }
        

    private:
        block blocks[10];
};
