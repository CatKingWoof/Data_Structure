#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

class maxheap{
public:
    int data[100000];
    void ins(int x);
    void del();
    int sz=0;
    void out_level(std::ofstream& ofs);
    void out_pre(std::ofstream& ofs,int cur);
    void out_in(std::ofstream& ofs,int cur);
    void out_post(std::ofstream& ofs,int cur);
};



int main(int argc,char *argv[])
{
    maxheap heap;
    ifstream ifs;
    ofstream ofs;
    int inst;
    int x;
    ifs.open(argv[1]);
    ofs.open(argv[2]);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } else
    {
        while(ifs>>inst)
        {
            int cur=1;
             if(inst==0)
             {
                 ifs>>x;
                 heap.ins(x);
             }
             else if(inst==1)
             {
                 heap.del();
             }
             else if(inst==2)
             {
                 heap.out_level(ofs);
             }
             else if(inst==3)
             {
                 heap.out_pre(ofs,cur);
                 ofs<<endl;
             }
             else if(inst==4)
             {
                 heap.out_in(ofs,cur);
                 ofs<<endl;
             }
             else if(inst==5)
             {
                 heap.out_post(ofs,cur);
                 ofs<<endl;
             }

        }
    }
    return 0;
}


void maxheap::ins(int x){
    sz++;
    int i;
    for(i=sz;i!=1;i=i/2){
        if(x<=data[i/2])
            break;
        data[i]=data[i/2];
    }
    data[i]=x;

}
void maxheap::del(){
    int k=data[sz];
    sz--;
    int i;
    int j;
    for(i=1,j=2;j<=sz;i=j,j*=2){
        if((j<sz)&&(data[j]<data[j+1]))
            ++j;
        if(k>=data[j])
            break;
        data[i]=data[j];
    }
    data[i]=k;

}
void maxheap::out_level(std::ofstream& ofs)
{
    for(int i=1;i<=sz;i++)
    {
        ofs<<data[i]<<" ";
    }
    ofs<<endl;
}
void maxheap::out_in(std::ofstream& ofs,int cur)
{
    if(cur<=sz)
    {
        this->out_in(ofs,cur*2);
        ofs<<data[cur]<<" ";
        this->out_in(ofs,cur*2+1);
    }

}
void maxheap::out_pre(std::ofstream& ofs,int cur)
{

    if(cur<=sz)
    {
        ofs<<data[cur]<<" ";
        this->out_pre(ofs,cur*2);
        this->out_pre(ofs,cur*2+1);
    }

}
void maxheap::out_post(std::ofstream& ofs,int cur)
{
    if(cur<=sz)
    {
        this->out_post(ofs,cur*2);
        this->out_post(ofs,cur*2+1);
        ofs<<data[cur]<<" ";
    }

}
