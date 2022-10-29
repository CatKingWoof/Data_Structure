#include <iostream>
#include <fstream>
using namespace std;

class task{
public:
    int first,rear,egg;
    int maxsize;
    char* q;
    task();
    ~task();
    bool IsEmpty();
    void Add(const char& item);
    void QDelete();
    void SDelete();
    void result(std::ofstream& ofs);
    //char* QDelete(char& x);
    //char* SDelete(char& x);
    char Throw();
    char Do_your_job();
};




int main(int argc,char *argv[])
{
    int num;
    int worker;
    char inst[10];
    char job;
    char doing_job;
    ifstream ifs;
    ofstream ofs;
    ifs.open(argv[1]);
    ofs.open(argv[2]);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } else
        {
        ifs>>num;
        task *processors= new task[num+1];
        task *task_done= new task[num+1];
        while(ifs>>inst)
        {

            if(inst[0]=='A')
            {

                ifs>>worker;
                ifs>>job;
                processors[worker].Add(job);
            }
            else if(inst[0]=='E')
            {
                ifs>>worker;

                if( !processors[worker].IsEmpty())
                {
                    processors[worker].QDelete();
                    doing_job=processors[worker].Do_your_job();
                    task_done[worker].Add(doing_job);


                }else
                {
                    int max_egg=0;
                    for(int i=1;i<=num;i++)
                    {
                        if(processors[i].egg>max_egg)
                        {
                            max_egg=processors[i].egg;
                        }
                    }
                    for(int i=1;i<=num;i++)
                    {
                        if( processors[i].egg==max_egg)
                        {
                            doing_job=processors[i].Throw();
                            task_done[worker].Add(doing_job);
                            processors[i].SDelete();
                            break;
                        }
                    }

                }

            }
            else if(inst[0]=='S')
            {
                ofs<<"Queuing"<<endl;
                for(int i=1;i<=num;i++)
                {
                    ofs<<i<<" ";
                    processors[i].result(ofs);
                    ofs<<endl;

                }
                ofs<<"Executed"<<endl;
                for(int i=1;i<=num;i++)
                {
                    ofs<<i<<" ";
                    task_done[i].result(ofs);
                    ofs<<endl;

                }
                break;
            }


        }




        ifs.close();
        ofs.close();
        delete []processors;
        }

    return 0;
}

task::task(): first(-1),rear(-1),egg(0)
{
    this->maxsize=1000000;
    q=new char[maxsize];

}

task::~task(){
delete []q;
}

void task::result(std::ofstream& ofs){
    while(first%maxsize!=rear%maxsize)
    {
        first++;
        ofs<<q[first];

    }

}

bool task::IsEmpty(){
    return(first==rear);
}

void task::Add(const char& item){
    rear=(rear+1)%maxsize;
    q[rear]=item;
    egg++;

}

void task::QDelete(){
    first=(first+1)%maxsize;
    egg--;
}
void task::SDelete(){
    rear=(rear-1)%maxsize;
    egg--;
}
/*char* task::QDelete(char& x){
    first=(first+1)%maxsize;
    x=q[first];
    return &x;

}
char* task::SDelete(char& x){
    rear=(rear-1)%maxsize;
    x=q[first];
    return &x;

}*/

char task::Throw(){
    return this->q[rear];
}

char task::Do_your_job(){
    return this->q[first];
}

