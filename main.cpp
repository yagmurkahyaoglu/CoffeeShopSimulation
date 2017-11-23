#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>
#include <functional>
#include <queue>
#include "Cashier.h"
#include "Barista.h"
#include "Customer.h"
#include <cmath>
#include <stdio.h>

using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

struct comparePrice {
    bool operator()(Customer *C1, Customer *C2) const
    {
        return C1->price < C2->price;
    }
};
bool CompareTime(Customer *C1,Customer *C2){
    return C1->arrival > C2->arrival;
}
bool ComparePrice(Customer *C1, Customer *C2){
    return C1->price < C2->price;
}
bool CompareOut(Customer *C1, Customer *C2){
    return C1->total > C2->total;
}


int main(int argc, char* argv[]) {
    // below reads the input file
    if (argc != 3) {
        cout << "Run the code with the following command: ./project2 [input_file] [output_file]" << endl;
        return 1;
    }

    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;


    ifstream infile(argv[1]);
    string line;
    vector<string> input;
    // process first line
    getline(infile, line);
    int N = stoi(line);
    cout << "number of cashiers: " << N << endl;
    cout << "number of baristas: " << N / 3 << endl;
    getline(infile, line);
    int M = stoi(line);
    cout << "number of orders: " << M << endl;


    vector<Cashier *> cashVec(N);
    for (int i = 0; i < N; i++) { cashVec[i] = new Cashier(); }
    vector<Barista *> barVec(N / 3);
    for (int i = 0; i < N / 3; i++) { barVec[i] = new Barista(); }
    vector<Cashier *> cashVec2(N);
    for (int i = 0; i < N; i++) { cashVec2[i] = new Cashier(); }
    vector<Barista *> barVec2(N / 3);
    for (int i = 0; i < N / 3; i++) { barVec2[i] = new Barista(); }
    priority_queue<Customer, vector<Customer*>, function<bool(Customer*, Customer*)>> CashQ(CompareTime);
    priority_queue<Customer, vector<Customer*>, function<bool(Customer*, Customer*)>> BarQ(ComparePrice);
    priority_queue<Customer*, vector<Customer*>, function<bool(Customer*, Customer*)>> timeline(CompareOut);
    vector<Customer *> Cust(M);
    vector<Customer *> Cust2(M);
    for (int i = 0; i < M; i++) {
        getline(infile, line);
        vector<string> words;
        split1(line, words);
        Cust[i] = ((new Customer(stod(words[0]), stod(words[1]), stod(words[2]), stod(words[3]))));
        Cust2[i] =(new Customer(Cust[i]->arrival, Cust[i]->order, Cust[i]->brew, Cust[i]->price));

        timeline.push(Cust[i]);
    }
    int cashMax = 0;
    int barMax = 0;

    Customer *curr = timeline.top();
    while (!timeline.empty()){
        curr = timeline.top();
        timeline.pop();
        if (curr->where == 0){
            bool x = true;
            for(int k=0; k<cashVec.size(); k++){
                if(cashVec[k]->empty){
                    curr->where = 1;
                    cashVec[k]->empty = false;
                    curr->cash = k;
                    curr->orderIn = curr->total;
                    curr->total = curr->orderIn + curr->order;
                    cashVec[k]->workTime += curr->order;
                    timeline.push(curr);
                    x = false;
                    break;
                }
            }
            if(x){
                CashQ.push(curr);
                cashMax = fmax(cashMax, CashQ.size());

            }
        } else if (curr->where == 1){
            int index = curr->cash;
            if (!CashQ.empty()){
                Customer *next = CashQ.top();
                CashQ.pop();
                next->orderIn = curr->total;
                next->total = next->orderIn + next->order;
                next->cash = index;
                next->where = 1;
                cashVec[index]->workTime += next->order;
                timeline.push(next);
            } else {
                cashVec[index]->empty = true;
            }
            bool x = true;
            for(int k=0; k<barVec.size(); k++){

                if(barVec[k]->empty){
                    curr->where = 2;
                    barVec[k]->empty = false;
                    curr->bar = k;
                    curr->brewIn = curr->total;
                    curr->total = curr->brewIn + curr->brew;
                    barVec[k]->workTime += curr->brew;
                    timeline.push(curr);
                    x = false;
                    break;
                }
            }
            if(x) {
                BarQ.push(curr);
                barMax = fmax(barMax, BarQ.size());
            }
        }
        else if(curr->where == 2){
            int index = curr->bar;
            if (!BarQ.empty()){
                Customer *next = BarQ.top();
                BarQ.pop();
                next->brewIn = curr->total;
                next->total = next->brewIn + next->brew;
                next->bar = index;
                next->where = 2;
                barVec[index]->workTime += next->brew;
                timeline.push(next);
            } else {
                barVec[index]->empty = true;
            }
        }

    }

    double total1 = curr->total - Cust[0]->arrival;
    freopen(argv[2], "w", stdout);
    printf("%.2lf \n", total1);
    printf("%d \n", cashMax);
    printf("%d \n", barMax);

    for(int a=0; a<cashVec.size(); a++){
        printf("%.2lf \n", cashVec[a]->workTime/total1);
    }
    for(int b=0; b<barVec.size(); b++){
        printf("%.2lf \n", barVec[b]->workTime/total1);
    }
    for(int c=0; c<M; c++){
        printf("%.2lf \n", Cust[c]->total - Cust[c]->arrival);
    }



    for(int x=0; x<M; x++){
        timeline.push(Cust2[x]);
    }
    int cashMax2 = 0;
    vector<int> barMax2(N/3);
    priority_queue<Customer, vector<Customer*>,comparePrice> BarQ2[N/3];

    Customer *curr2 =timeline.top();
    while (!timeline.empty()){
        curr2 = timeline.top();
        timeline.pop();
        if (curr2->where == 0){
            bool x = true;
            for(int k=0; k<cashVec2.size(); k++){
                if(cashVec2[k]->empty){
                    curr2->where = 1;
                    cashVec2[k]->empty = false;
                    curr2->cash = k;
                    curr2->orderIn = curr2->total;
                    curr2->total = curr2->orderIn + curr2->order;
                    cashVec2[k]->workTime += curr2->order;
                    timeline.push(curr2);
                    x = false;
                    break;
                }
            }
            if(x){
                CashQ.push(curr2);
                cashMax2 = fmax(cashMax2, CashQ.size());

            }
        } else if (curr2->where == 1){
            int index = curr2->cash;
            if (!CashQ.empty()){
                Customer *next = CashQ.top();
                CashQ.pop();
                next->orderIn = curr2->total;
                next->total = next->orderIn + next->order;
                next->cash = index;
                next->where = 1;
                cashVec2[index]->workTime += next->order;
                timeline.push(next);
            } else {
                cashVec2[index]->empty = true;
            }
            if(barVec2[curr2->cash/3]->empty){
                curr2->where = 2;
                barVec2[curr2->cash/3]->empty = false;
                curr2->bar = curr2->cash/3;
                curr2->brewIn = curr2->total;
                curr2->total = curr2->brewIn + curr2->brew;
                barVec2[curr2->cash/3]->workTime += curr2->brew;
                timeline.push(curr2);
            } else {
                BarQ2[curr2->cash/3].push(curr2);
                barMax2[curr2->cash/3] = fmax(barMax2[curr2->cash/3], BarQ2[curr2->cash/3].size());
            }

        }
        else if(curr2->where == 2){
            int index = curr2->cash/3;
            if (!BarQ2[index].empty()){
                Customer *next = BarQ2[index].top();
                BarQ2[index].pop();
                next->brewIn = curr2->total;
                next->total = next->brewIn + next->brew;
                next->bar = index;
                next->where = 2;
                barVec2[index]->workTime += next->brew;
                timeline.push(next);
            } else {
                barVec2[index]->empty = true;
            }
        }

    }
    double total2 = curr2->total - Cust2[0]->arrival;
    printf("\n");
    printf("%.2lf \n", total2);
    printf("%d \n", cashMax2);
    for(int y=0; y<N/3; y++) {
        printf("%d \n", barMax2[y]);
    }
    for(int a=0; a<cashVec.size(); a++){
        printf("%.2lf \n", cashVec2[a]->workTime/total2);
    }
    for(int b=0; b<barVec.size(); b++){
        printf("%.2lf \n", barVec2[b]->workTime/total2);
    }
    for(int c=0; c<M; c++){
        printf("%.2lf \n", Cust2[c]->total - Cust2[c]->arrival);
    }

    fclose(stdout);





    return 0;
}
