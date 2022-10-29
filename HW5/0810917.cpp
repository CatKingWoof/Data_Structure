#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <fstream>
#include <cstdlib>
#include <string>
#include <math.h>
using namespace std;


const int MAX_D = 1000000;
class Graph_SP{
private:
    int num_vertex;
    vector<list<pair<int,int> > > Adj;
    vector<int> predecessor, distance;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        Adj.resize(num_vertex);
    }
    void InitAdj(ifstream& ifs);
    void Print(vector<int> array,vector<int> weight,ofstream& ofs);

    void InitializeSingleSource(int Start);
    void compare(int X, int Y, int weight);
    void BellmanFord(int Start ,ofstream& ofs);
};

void Graph_SP::BellmanFord(int Start,ofstream& ofs){

    InitializeSingleSource(Start);
    for (int i = 0; i < num_vertex-1; i++) {
        for (int j = 0 ; j < num_vertex; j++) {
            for (list<pair<int,int> >::iterator itr = Adj[j].begin();
                 itr != Adj[j].end(); itr++) {
                compare(j, (*itr).first, (*itr).second);
            }
        }
    }

    for (int i = 0; i < num_vertex; i++) {
        for (list<pair<int,int> >::iterator itr = Adj[i].begin();
             itr != Adj[i].end(); itr++) {
            if (distance[(*itr).first] > distance[i]+(*itr).second) {
                vector<int> neg;
                int flag=0;
				int j;
                while(flag==0)
                {
					j=neg.size();
                    for(int n=0;n<j;n++)
                    {
                        if(i==neg[n])
                        {
                            flag=n;
                            break;
                        }
                    }
                    neg.push_back(i);
                    i=predecessor[i];

                }
                int p=neg.size();
                for(int i=0;i<p-flag;i++)
                {
                    if(i!=0)
                        ofs<<"-";
                    ofs<<neg[neg.size()-1-i];
                }
                return ;
            }
        }
    }


    Print(predecessor,distance,ofs);

}
void Graph_SP::Print(vector<int> array,vector<int> weight,ofstream& ofs){
    vector<int> ans[num_vertex];
    for(int i=1;i<num_vertex;i++)
    {
        int a;
        a=array[i];
        ans[i].push_back(i);
        ans[i].push_back(a);
        while(a!=0)
        {
            a=array[a];
            ans[i].push_back(a);
        }
    }
    for(int i=1;i<num_vertex;i++)
    {
        int b=ans[i].size()-1;
        int p=ans[i].size();
        for(int j=0;j<p;j++)
        {
            if(j!=0)
                ofs<<"-";
            ofs<<ans[i].at(b);
            b--;
        }
        ofs<<" "<<weight[i];
        ofs<<endl;
    }



}
void Graph_SP::InitializeSingleSource(int Start){

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        distance[i] = MAX_D;
        predecessor[i] = -1;
    }
    distance[Start] = 0;
}
void Graph_SP::compare(int from, int to, int weight){

    if (distance[to] > distance[from] + weight) {
        distance[to] = distance[from] + weight;
        predecessor[to] = from;
    }
}
void Graph_SP::InitAdj(ifstream& ifs){
    int weight;
    for(int i=0;i<num_vertex;i++)
    {
        for(int j=0;j<num_vertex;j++)
        {
            ifs>>weight;
            if(weight!=0)
            Adj[i].push_back(make_pair(j,weight));
        }
    }

}

int main(int argc,char *argv[]){
    ifstream ifs;
    ofstream ofs;
    ifs.open(argv[1]);
    ofs.open(argv[2]);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } else
    {
     int num=0;
     string x;
     while(ifs>>x)
     {
         num++;
     }
     ifs.close();
     ifs.open(argv[1]);
     Graph_SP graph(sqrt(num));
     graph.InitAdj(ifs);
     graph.BellmanFord(0,ofs);
    }
    return 0;
}
