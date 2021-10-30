#include<iostream>
using namespace std;
int main()
{
 int a[5],i,c=0,p=0;
 cout<<"Enter the marks got in following subject such as maths,english,physics,chemistry,cs";
 for(i=0;i<5i++)
 {cin>>a[i];
  c+=a[i];
 }
 cout<<"The percentage is:";
 p=c/5;
 cout<<p;
 return 0;
}
