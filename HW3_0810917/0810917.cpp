#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
class ListNode{
friend class List;
public:
    int data[4];
    string s;
    ListNode *link;
    ListNode(std::ifstream& ifs);
    ListNode();
    bool NextNotNull();
    bool NotNull();
};

class List{
public:
ListNode *first;
ListNode *last;
ListNode *current;
ListNode *previous;
List(std::ifstream& ifs,int term);
List();
void Plus(const List &l,const List &m);
void Minus(const List &l,const List &m);
void Mul(const List &l,const List &m);
void Del();
};


int main(int argc,char *argv[])
{
    vector<List> poly;
    ifstream ifs;
    ofstream ofs;
    int inst;
    int term;
    string x;
    string y;
    int x1,y1;
    ifs.open(argv[1]);
    ofs.open(argv[2]);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } else
    {
        while(ifs>>x)
        {

            inst=atoi(x.c_str());
            //cout<<inst;
            if(inst==0)
            {

                ifs>>x;
                term=atoi(x.c_str());
                List a1(ifs,term);
                //cout<<term;
                poly.push_back(a1);
            }
            else if(inst==1)
            {
                ifs>>x;
                ifs>>y;
                x1=atoi(x.c_str());
                y1=atoi(y.c_str());
                List a3;
                a3.Plus(poly[x1],poly[y1]);
                poly.push_back(a3);


            }
            else if(inst==2)
            {

                ifs>>x;
                ifs>>y;
                x1=atoi(x.c_str());
                y1=atoi(y.c_str());
                List a3;

                a3.Minus(poly[x1],poly[y1]);

                poly.push_back(a3);



            }
            else if(inst==3)
            {

                ifs>>x;
                ifs>>y;
                x1=atoi(x.c_str());
                y1=atoi(y.c_str());
                List a4;
                a4.Mul(poly[x1],poly[y1]);
                poly.push_back(a4);

            }
            else if(inst==4)
            {

                ifs>>x;
                x1=atoi(x.c_str());
                poly[x1].Del();
                poly.erase(poly.begin()+x1);

            }
        }
        int j=poly.size();

        for(int i=0; i<j; i++)
        {
            term=0;
            for(ListNode *ptr=poly[i].first; ptr; ptr=ptr->link)
            {

                term++;
            }
            ofs<<term<<endl;
            for(ListNode *ptr=poly[i].first;ptr;ptr=ptr->link)
            {
                ofs<<ptr->data[0]<<" ";
                ofs<<ptr->data[1]<<" ";
                ofs<<ptr->data[2]<<" ";
                ofs<<ptr->data[3]<<endl;
            }
        }








    }
    return 0;
}


List::List(std::ifstream& ifs,int term){
    first=0;
    last=0;
    for(int i=0;i<term;i++)
    {

        if(first==0)
        {
            first=new ListNode(ifs);
            last=first;
        }else
        {
            last->link=new ListNode(ifs);
            last=last->link;

        }

    }

}

List::List(){
    first=0;
    last=0;
}

void List::Del(){
    while(first->NotNull())
    {
      current=first;
      first=first->link;
      delete current;
    }

}


ListNode::ListNode(){
link=0;
}


ListNode::ListNode(std::ifstream& ifs){
    ifs>>s;
    data[0]=atoi(s.c_str());
    ifs>>s;
    data[1]=atoi(s.c_str());
    ifs>>s;
    data[2]=atoi(s.c_str());
    ifs>>s;
    data[3]=atoi(s.c_str());
    link=0;

}

void List::Plus(const List &l,const List &m){
    ListNode *a=l.first;
    ListNode *b=m.first;
    ListNode *x;
    int flag;
    while(a->NotNull()&&b->NotNull())
    {
        x=new ListNode;
        flag=0;
        for(int i=1;i<=3;i++)
        {
          if(a->data[i]>b->data[i])
            {
                x->data[0]=a->data[0];
                x->data[1]=a->data[1];
                x->data[2]=a->data[2];
                x->data[3]=a->data[3];
                if(this->first==0)
                {
                    this->first=x;
                    this->last=this->first;
                    a=a->link;
                    flag=1;
                    break;
                }
                else
                {
                    this->last->link=x;
                    this->last=this->last->link;
                    a=a->link;
                    flag=1;
                    break;
                }
            }
            else if(a->data[i]<b->data[i])
            {
                x->data[0]=b->data[0];
                x->data[1]=b->data[1];
                x->data[2]=b->data[2];
                x->data[3]=b->data[3];
                if(this->first==0)
                {
                    this->first=x;
                    this->last=this->first;
                    b=b->link;
                    flag=1;
                    break;
                }
                else
                {
                    this->last->link=x;
                    this->last=this->last->link;
                    b=b->link;
                    flag=1;
                    break;
                }
            }
        }
        if(flag==0)
        {
           if(this->first==0)
                {

                    x->data[0]=a->data[0]+b->data[0];
                    x->data[1]=b->data[1];
                    x->data[2]=b->data[2];
                    x->data[3]=b->data[3];
                    first=x;
                    this->last=this->first;
                    b=b->link;
                    a=a->link;

                }
                else
                {
                    x->data[0]=a->data[0]+b->data[0];
                    x->data[1]=b->data[1];
                    x->data[2]=b->data[2];
                    x->data[3]=b->data[3];
                    this->last->link=x;
                    this->last=this->last->link;
                    b=b->link;
                    a=a->link;
                }

        }
    }
    while(a->NotNull())
    {
        x=new ListNode;
        if(this->first==0)
                {
                    x->data[0]=a->data[0];
                    x->data[1]=a->data[1];
                    x->data[2]=a->data[2];
                    x->data[3]=a->data[3];
                    this->first=x;
                    this->last=this->first;
                    a=a->link;
                }
                else
                {
                    x->data[0]=a->data[0];
                    x->data[1]=a->data[1];
                    x->data[2]=a->data[2];
                    x->data[3]=a->data[3];
                    this->last->link=x;
                    this->last=this->last->link;
                    a=a->link;
                }
    }
    while(b->NotNull())
    {
        x=new ListNode;
        if(this->first==0)
                {
                    x->data[0]=b->data[0];
                    x->data[1]=b->data[1];
                    x->data[2]=b->data[2];
                    x->data[3]=b->data[3];
                    this->last=this->first;
                    b=b->link;
                }
                else
                {
                    x->data[0]=b->data[0];
                    x->data[1]=b->data[1];
                    x->data[2]=b->data[2];
                    x->data[3]=b->data[3];
                    this->last->link=x;
                    this->last=this->last->link;
                    b=b->link;
                }
    }
    if(first==0)
    {
        first=new ListNode;
    first->data[0]=0;
    first->data[1]=0;
    first->data[2]=0;
    first->data[3]=0;
    }
}

void List::Minus(const List &l,const List &m){
    ListNode *a=l.first;
    ListNode *b=m.first;
    ListNode *x;
    int flag;
    while(a->NotNull()&&b->NotNull())
    {

        x=new ListNode;
        flag=0;
        for(int i=1;i<=3;i++)
        {
          if(a->data[i]>b->data[i])
            {
                if(this->first==0)
                {
                    x->data[0]=a->data[0];
                    x->data[1]=a->data[1];
                    x->data[2]=a->data[2];
                    x->data[3]=a->data[3];
                    this->first=x;
                    this->last=this->first;
                    a=a->link;
                    flag=1;
                    break;
                }
                else
                {
                    x->data[0]=a->data[0];
                    x->data[1]=a->data[1];
                    x->data[2]=a->data[2];
                    x->data[3]=a->data[3];
                    this->last->link=x;
                    this->last=this->last->link;
                    a=a->link;
                    flag=1;
                    break;
                }

            }
            else if(a->data[i]<b->data[i])
            {
                 x->data[0]=(b->data[0])*-1;
                x->data[1]=b->data[1];
                x->data[2]=b->data[2];
                x->data[3]=b->data[3];
                if(this->first==0)
                {

                    first=x;
                    b=b->link;
                    this->last=this->first;
                    flag=1;
                    break;
                }
                else
                {
                    this->last->link=x;
                    this->last=this->last->link;
                    b=b->link;
                    flag=1;
                    break;
                }
            }
        }
        if(flag==0)
        {

           if(a->data[0]-b->data[0]!=0)
           {

                x->data[0]=a->data[0]+(b->data[0])*-1;
                x->data[1]=b->data[1];
                x->data[2]=b->data[2];
                x->data[3]=b->data[3];
              if(this->first==0)
                {
                    first=x;
                    this->last=this->first;
                    b=b->link;
                    a=a->link;

                }
                else
                {
                    last->link=x;
                    this->last=this->last->link;
                    b=b->link;
                    a=a->link;
                }
           }
           else
           {

               b=b->link;
               a=a->link;
           }

        }

    }

    while(a->NotNull())
    {
        x=new ListNode;
                x->data[0]=a->data[0];
                x->data[1]=a->data[1];
                x->data[2]=a->data[2];
                x->data[3]=a->data[3];
        if(this->first==0)
                {
                    first=x;
                    this->last=this->first;
                    a=a->link;
                }
                else
                {
                    this->last->link=x;
                    this->last=this->last->link;
                    a=a->link;
                }
    }
    while(b->NotNull())
    {
        x=new ListNode;
            x->data[0]=(b->data[0])*-1;
            x->data[1]=b->data[1];
            x->data[2]=b->data[2];
            x->data[3]=b->data[3];
        if(this->first==0)
                {
                    first=x;
                    this->last=this->first;
                    b=b->link;
                }
                else
                {
                    last->link=x;
                    b=b->link;
                }

    }
    if(first==0)
    {
    first=new ListNode;
    first->data[0]=0;
    first->data[1]=0;
    first->data[2]=0;
    first->data[3]=0;
    first->link=0;
    }
}


void List::Mul(const List &l,const List &m){
ListNode *a=l.first;
ListNode *b=m.first;
ListNode *x;
int flag;
this->first=new ListNode;
if((b->data[0])*(a->data[0])==0)
{
    first=new ListNode;
    first->data[0]=0;
    first->data[1]=0;
    first->data[2]=0;
    first->data[3]=0;
}
else
{
this->first->data[0]=(b->data[0])*(a->data[0]);
this->first->data[1]=b->data[1]+(a->data[1]);
this->first->data[2]=b->data[2]+(a->data[2]);
this->first->data[3]=b->data[3]+(a->data[3]);
current=first->link;
previous=first;
last=first;
if(b->link->NotNull())
    {
        b=b->link;
    }
    else{
        a=a->link;
    }

while(a->NotNull())
    {

        while(b->NotNull())
        {
            x=new ListNode;
            x->data[0]=(b->data[0])*(a->data[0]);
            x->data[1]=b->data[1]+(a->data[1]);
            x->data[2]=b->data[2]+(a->data[2]);
            x->data[3]=b->data[3]+(a->data[3]);
            flag=0;
            while(flag==0)
            {
                if(current->NotNull())
                {
                      for(int i=1;i<=3;i++)
                    {
                        if(x->data[i]>current->data[i])
                        {

                            x->link=current;
                            previous->link=x;
                            previous=x;
                            flag=1;
                            break;
                        }
                        else
                        if(x->data[i]<current->data[i])
                        {
                            break;
                        }

                    }
                    if(x->data[3]==current->data[3]&&x->data[2]==current->data[2]&&x->data[1]==current->data[1])
                    {

                        if((current->data[0])+x->data[0]!=0)
                        {
                           current->data[0]=current->data[0]+x->data[0];
                        }
                        else
                        {
                            previous->link=current->link;
                            delete current;
                            current=previous->link;
                            if(!current->NotNull())
                                last=previous;
                        }
                        flag=1;
                    }
                    if(flag==0)
                    {
                        current=current->link;
                        previous=previous->link;
                    }

                }
                else
                {
                    last->link=x;
                    last=last->link;
                    flag=1;

                }

            }
               b=b->link;
        }
        a=a->link;
        b=m.first;
        current=first->link;
        previous=first;

    }
}
}


bool ListNode::NextNotNull(){
if(this->link)
    return true;
else
    return false;
}



bool ListNode::NotNull(){
return (this!=0);
}






