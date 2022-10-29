#include <iostream>
#include <fstream>
#include<vector>
using namespace std;
int n=0;

void interchange(int &i,int &j);
void Quicksort(int *list,int left,int right);
int main(int argc,char *argv[])
{
    ifstream ifs;
    ofstream ofs;
    vector <int> list;
    int a;
    int x;
    ifs.open(argv[1]);
    ofs.open(argv[2]);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } else
    {
        while(ifs>>a)
        {
            list.push_back(a);
        }
        x=list.size()-1;
        int *l=&list[0];
        Quicksort(l,0,x);
        ofs<<n;
    }
    return 0;
}


void interchange(int &i,int &j)
{
    ++n;
    int t;
    t=i;
    i=j;
    j=t;
}

void Quicksort(int *list,int left,int right)
{
    if(left<right){
        int i=left;
        int j=right+1;
        int pivot=list[left];
        do{
            do{++i;}while(i<right&&list[i]<pivot);
            do{--j;}while(list[j]>pivot);
            if(i<j) interchange(list[i],list[j]);
        }while(i<j);
        if(left!=j)
        interchange(list[left],list[j]);
        if(j-1>left)
        Quicksort(list,left,j-1);
        if(j+1<right)
        Quicksort(list,j+1,right);

    }
}
