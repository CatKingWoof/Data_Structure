#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class node{
friend class bucket;
public:
    string str;
    int content[27];
    int sum;
    //node *link;
    //bool NextNotNull();
    node(string chars);

};
class bucket{
public:
    //node *first;
    //void append(node n1);
    //bucket();
    bool search(node n1,ofstream &ofs);
	vector <node> chain;
};
int main(int argc,char *argv[])
{
    ifstream ifs,ifi;
    ofstream ofs;
    //vector<bucket> table;
    //table.resize(540);
	bucket table[227];
    ifs.open(argv[1]);
    ifi.open(argv[2]);
    ofs.open(argv[3]);
    if (!ifs.is_open()||!ifi.is_open()) {
        cout << "Failed to open file.\n";
    } else
    {
		//int xx=0;
        string n="abc";
        while(ifs>>n)
        {
			//xx+=1;
            node n1(n);
            table[n1.sum].chain.push_back(n1);
			/*if(xx==10000)
			{
				cout<<"aa";
				xx=0;
			}*/
        }
	
        while(ifi>>n)
        {
            node n1(n);
            bool f=false;
			bool flag;
            //f=table[n1.sum].search(n1,ofs);
			int l=table[n1.sum].chain.size();
			for(int i=0;i<l;i++)
			{
				flag=true;
				for(int j=0;j<27;j++)
				{
					if(table[n1.sum].chain[i].content[j]!=n1.content[j])
					{
						flag=false;
						break;
					}
				}
				if(flag==true)
				{
					ofs<<table[n1.sum].chain[i].str<<" ";
					f=true;
				}
			}
            if(f==false)
            {
                ofs<<"0";
            }
            ofs<<endl;
        }
    }
    return 0;
}


node::node(string chars)
{
	for(int i=0;i<27;i++)
	{
		content[i]=0;
	}
    sum=0;
    str=chars;
    //link=0;
    vector<char> vec_str(str.begin(), str.end());
    int l=vec_str.size();
    int n;
    for(int i=0;i<l;i++)
    {
        n=(int)vec_str[i]-96;
        content[n]+=1;
        sum+=n;
    }
	sum%=227;

}
/*bucket::bucket()
{
    first=0;
}*/



/*void bucket::append(node n1){

    if(first==0)
    {
        first=n1;
    }

    else
    {
        node *cur;
        cur=first;
        while(cur->link)
            cur=cur->link;
        cur->link=n1;
    }

}*/

/*bool bucket::search(node n1,ofstream &ofs){

    node *cur;
    cur=first;
    bool f=false;
    while(cur!=0)
    {
        int flag=0;
        for(int i=1;i<27;i++)
        {
            if(cur->content[i]!=n1->content[i])
                {
                    flag=1;
                    break;
                }
        }
        if(flag==0)
        {
            ofs<<cur->str<<" ";
            f=true;
        }
        cur=cur->link;
    }
    return f;

}*/


/*bool node::NextNotNull(){
if(this->link)
    return true;
else
    return false;
}
*/