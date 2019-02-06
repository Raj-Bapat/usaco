#include <iostream>
#include <algorithm>
using namespace std;


struct part
{
    long long start,length,fun,cost;
};
bool comp(part a, part b)
{
    return a.start<b.start;
}
int main()
{
    int l, n,b;
    cin>>l>>n>>b;
    long long array1[l+1][b+1];
    part cap[n];
    int array2[l];
    for(int i=0;i<=l;i++) {
        array2[i]=0;
        for(int j=0;j<=b;j++) {
            array1[i][j]=-1;
        }
    }
    for(int i=0;i<n;i++) {
        
        cin>>cap[i].start>>cap[i].length>>cap[i].fun>>cap[i].cost;
        array2[cap[i].start]++;
    }
    //cout<<array2[0]<<endl;
    sort(cap,cap+n,comp);
    array1[0][0]=0;
    int x=0;
    for(int i=0;i<=l;i++) {
        for(int j=0;j<=b;j++) {
            //cout<<x<<endl;
            for(int f=x;f<x+array2[i];f++) {
                if(j+cap[f].cost<=b) {
                    if(array1[i][j]+cap[f].fun>array1[i+cap[f].length][j+cap[f].cost]&&array1[i][j]>-1) {
                        array1[i+cap[f].length][j+cap[f].cost]=array1[i][j]+cap[f].fun;
                    }
                }
            }
            
            //cout<<x<<endl;
        }
        x=x+array2[i];
    }
    
    int maxi=-50000;
    for(int j=0;j<=b;j++)
    {
        if(maxi<array1[l][j])
        {
            maxi=array1[l][j];
        }
    }
    cout<<maxi<<endl;
    
}
