#include <iostream>
using namespace std;

int max1(int A,int B){
    if(A>B)return A;
    else return B;
}


int max2(int A,int B,int C){
    int one = max1(A,B);
    int two = C;
    if(one>two)return one;
    else return two;
}




int Seq_Align(string A,string B,int m,int n){
    int S[m+1][n+1];
    for(int i=0;i<=m;i++)S[i][0]=-i;
    for(int j=0;j<=n;j++)S[0][j]=-j;

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            int s1;
            if(A[i-1]==B[j-1])s1=S[i-1][j-1]+1;
            else s1=S[i-1][j-1]-1;
            int s2 = S[i-1][j]-1;
            int s3 = S[i][j-1]-1;
            S[i][j]=max2(s1,s2,s3);
        }
    }

    for(int i=0;i<=m;i++){
        for(int j=0;j<=n;j++){
            cout<<S[i][j]<<" ";
        }
        cout<<endl;
    }
    return S[m][n];
}


int main(){
    string A,B;
    cin>>A>>B;
    int answer = Seq_Align(A,B,A.size(),B.size());
    cout<<answer<<endl;
}

