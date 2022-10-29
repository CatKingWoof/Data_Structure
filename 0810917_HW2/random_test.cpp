#include <iostream>
#include <fstream>
using namespace std;
int main(){



  int min = 1;
  int max = 5;
  ofstream ofs;
   ofs.open("in8.txt");
  /* 產生 [min , max] 的整數亂數 */
  ofs<<5<<endl;
  for(int i=0;i<1000000;i++)
  {
      ofs<<"ASSIGN"<<" ";
     int x = rand() % (max - min + 1) + min;
     switch(x)
     {
        case 5:
        ofs<<5<<" ";
        break;
        case 4:
        ofs<<4<<" ";
        break;
        case 3:
        ofs<<3<<" ";
        break;
        case 2:
        ofs<<2<<" ";
        break;
        case 1:
        ofs<<1<<" ";
        break;
     }
     int y = rand() % (max - min + 1) + min;
     switch(y)
     {
     case 5:
        ofs<<'A'<<endl;
        break;
         case 4:
        ofs<<'B'<<endl;
        break;
         case 3:
        ofs<<'C'<<endl;
        break;
         case 2:
        ofs<<'D'<<endl;
        break;
         case 1:
        ofs<<'E'<<endl;
        break;

     }
  }

  for(int i=0;i<500000;i++)
  {
      ofs<<"EXEC"<<" ";
      int x = rand() % (max - min + 1) + min;
      switch(x)
     {
        case 5:
        ofs<<5<<endl;
        break;
        case 4:
        ofs<<4<<endl;
        break;
        case 3:
        ofs<<3<<endl;
        break;
        case 2:
        ofs<<2<<endl;
        break;
        case 1:
        ofs<<1<<endl;
        break;
     }
  }
  ofs<<"STOP";

  ofs.close();
  return 0;
}
