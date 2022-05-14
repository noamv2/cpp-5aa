#include "OrgChart.hpp"

using namespace ariel;
using namespace std;


int main(){


    OrgChart og;

    string menu ="Chart created, you can modify it with the following commands:\n"
    "0: insert/edit root\n"
    "1: insert new subordinate\n"
    "2: print OrgChart\n"
    "3: print menu\n"
    "4: quit the program";
    
    cout<<menu<<endl;

    int choice = 1;
    string in1,in2;
    while(choice != 4){
        cout<<"Insert your choice: \n";
        cin>>choice;
        switch (choice)
        {
        case 0:
            try{
                cout<<"Insert root name\n";
                cin>>in1;
                og.add_root(in1);
            }
            catch(exception& e){
                
            }
            break;
        case 1:
            try{
                cout<<"Insert parent name\n";
                cin>>in1;
                cout<<"Insert new sub name\n";
                cin>>in2;
                og.add_sub(in1, in2);
            }
            catch(exception& e){
                cout<<"Parent node does not exist"<<endl;
            }
            break;
        case 2:
            cout<<og;
            break;

        case 3:
            cout<<menu<<endl;
            break;
        
        case 4:
            break;
        }
    
    }
    return 0;
}