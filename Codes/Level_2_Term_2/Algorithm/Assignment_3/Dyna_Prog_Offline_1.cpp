#include <iostream>
#include <algorithm>
using namespace std;
#define NULL_VALUE -99999


int Seq_Align(string A,string B,int m,int n){
    string outA="";
    string outB="";
    int S[m+1][n+1];
    int P[m+1][n+1];
    for(int i=0;i<=m;i++){
        S[i][0]=-i;
        P[i][0]=-1;
    }
    for(int j=0;j<=n;j++){
        S[0][j]=-j;
        P[0][j]=-1;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            int s1;
            if(A[i-1]==B[j-1])s1=S[i-1][j-1]+1;
            else s1=S[i-1][j-1]-1;
            int s2 = S[i-1][j]-1;
            int s3 = S[i][j-1]-1;
            S[i][j]=max(s1,max(s2,s3));
            if(S[i][j]==s1)P[i][j]=1;
            else if(S[i][j]==s2)P[i][j]=2;
            else if(S[i][j]==s3)P[i][j]=3;
        }
    }


    for(int i=0;i<=m;i++){
        for(int j=0;j<=n;j++){
            if(S[i][j]>=0)cout<<" "<<S[i][j]<<" ";
            else cout<<S[i][j]<<" ";
        }
        cout<<endl;
    }

    int x,y;
    x=m;
    y=n;
    while(x>0 && y>0){
        if(P[x][y]==1){
            outA+=A[x-1];
            outB+=B[y-1];
            x--;
            y--;
        }
        else if(P[x][y]==2){
            outA+=A[x-1];
            outB+="_";
            x--;
        }
        else if(P[x][y]==3){
            outA+="_";
            outB+=B[y-1];
            y--;
        }
    }
    reverse(outA.begin(),outA.end());
    reverse(outB.begin(),outB.end());
    cout<<outA<<endl<<outB<<endl;
    return S[m][n];
}


int main(){
    string A,B;
    cin>>A>>B;
    int answer = Seq_Align(A,B,A.size(),B.size());
    cout<<answer<<endl;
}

