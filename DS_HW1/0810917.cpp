#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

struct MatrixTerm{
    int row,col,value;
};

class sparceMatrix{
public:
    int Rows,Cols,Terms;
    vector<MatrixTerm> smArray;
    sparceMatrix(std::ifstream& ifs);
    sparceMatrix Transpose(std::ifstream& ifs);
    sparceMatrix Mult(const sparceMatrix& B,std::ifstream& ifs);

};




int main(int argc,char *argv[]) {

    ifstream ifs;
    ofstream ofs;
    string s;
    ifs.open(argv[1]);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } else {
        while(ifs>>s){

            if(s=="A")
            {
                ifs>>s;
                sparceMatrix A(ifs);
                ifs>>s;
                sparceMatrix B(ifs);

                sparceMatrix C(ifs);
                if(A.Cols==B.Rows)
                {
                    cout<<"a";

                    C=A.Mult(B,ifs);

                }
                else if(A.Rows==B.Rows)
                {
                    cout<<"b";
                    A=A.Transpose(ifs);

                    C=A.Mult(B,ifs);
                }
                else if(A.Cols==B.Cols)
                {
                    cout<<"c";
                    B=B.Transpose(ifs);
                    C=A.Mult(B,ifs);
                }
                else if(A.Rows==B.Cols)
                {
                    cout<<"d";
                    A=A.Transpose(ifs);
                    B=B.Transpose(ifs);

                    C=A.Mult(B,ifs);
                }

                ofs.open(argv[2]);
                if (!ofs.is_open()) {
                cout << "Failed to open file.\n";
                } else {
                    int oflag=0;
                    for(int a=0;a<C.Rows;a++){
                        for(int b=0;b<C.Cols;b++){
                            oflag=0;

                            for(int i=0;i<C.Terms;i++)
                            {
                               if(a==C.smArray[i].row&&b==C.smArray[i].col){
                                oflag=1;
                                ofs<<C.smArray[i].value<<" ";
                               }
                            }
                            if(oflag==0)
                            {
                                ofs<<0<<" ";
                            }

                        }
                        ofs<<";"<<endl;
                    }

                }
            }
    }
    ifs.close();
    ofs.close();
    }
    return 0;
}




sparceMatrix::sparceMatrix(std::ifstream& ifs){
    string a;
    MatrixTerm m;
    int c=0,r=0,t=0;
    if(ifs.eof())
    {
        Rows=0;
        Cols=0;
        Terms=0;
    }
    else{

        while(ifs>>a){
            if(a=="B")
                break;
            else if(a=="0")
                c++;
            else if(a==";"){
                r++;
                Cols=c;
                c=0;
            }
            else{
                m.col=c;
                m.row=r;
                m.value=atoi(a.c_str());
                smArray.push_back(m);
                c++;
                t++;
            }
        }
        Rows=r;
        Terms=t;
    }
}
sparceMatrix sparceMatrix::Transpose(std::ifstream& ifs){
    sparceMatrix ans(ifs);

    ans.Cols=Rows;
    ans.Rows=Cols;
    ans.Terms=Terms;
    MatrixTerm m;
    for(int t=0;t<Terms;t++){
        m.col=smArray[t].row;
        m.row=smArray[t].col;
        m.value=smArray[t].value;
        ans.smArray.push_back(m);

    }

    return ans;
}

sparceMatrix sparceMatrix::Mult(const sparceMatrix& B,std::ifstream& ifs){
    MatrixTerm m;
    int flag;
    sparceMatrix ans(ifs);
    ans.Cols=B.Cols;
    ans.Rows=Rows;
    ans.Terms=0;
    for(int i=0;i<Terms;i++){
        for(int j=0;j<B.Terms;j++){
            if(smArray[i].col==B.smArray[j].row){

                //is it exit?
                flag=0;
                for(int x=0;x<ans.Terms;x++){
                    if((ans.smArray[x].row==smArray[i].row)&&(ans.smArray[x].col==B.smArray[j].col)){
                        ans.smArray[x].value+=smArray[i].value*B.smArray[j].value;
                        //cout<<"f"<<smArray[i].value<<B.smArray[j].value<<smArray[i].value*B.smArray[j].value<<endl;
                        flag=1;
                        }
                    }
                if(flag==0){
                   m.row=smArray[i].row;
                    m.col=B.smArray[j].col;
                    m.value=smArray[i].value*B.smArray[j].value;
                    //cout<<smArray[i].value<<B.smArray[j].value<<m.value<<endl;
                    ans.smArray.push_back(m);
                    ans.Terms+=1;
                }


            }

        }
    }
    return ans;
}

