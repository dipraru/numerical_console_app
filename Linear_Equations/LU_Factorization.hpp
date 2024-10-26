// #include "input_output.hpp"
void LUdecomposition(vector<vector<double>> &a, vector<vector<double>> &l, vector<vector<double>> &u, int n) {
   for (int i=0;i<n;i++) {
      for (int j=0;j<n;j++) 
      {
         if (j<i) l[j][i] = 0;
         else 
         {
            l[j][i] = a[j][i];
            for (int k=0;k<i;k++) l[j][i]=l[j][i]-l[j][k]*u[k][i];
         }
      }
      for (int j=0;j<n;j++) {
         if (j < i) u[i][j]=0;
         else if (j == i) u[i][j]=1;
         else {
            u[i][j] = a[i][j] / l[i][i];
            for (int k=0;k<i;k++) u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
         }
      }
   }
}
vector<double> ForwardSub(vector<vector<double>>&l,vector<double>&b) {
    int n=l.size();
    vector<double> y(n);
    for (int i=0;i<n;i++) {
        y[i]=b[i];
        for (int j=0;j<i;j++) y[i]-=l[i][j]*y[j];
        y[i]/=l[i][i];
    }
    return y;
}

vector<double> BackwardSub(vector<vector<double>>&u,const vector<double>&y) {
    int n=u.size();
    vector<double> x(n);
    for (int i=n-1;i>=0;i--) {
        x[i]=y[i];
        for (int j=i+1;j<n;j++) x[i]-=u[i][j]*x[j];
        x[i]/=u[i][i];
    }
    return x;
}
vector<double> solveLU(vector<vector<double>> &a,vector<double>&b) {
    int n=b.size();
    vector<vector<double>> l(n,vector<double>(n)), u(n,vector<double>(n));
    LUdecomposition(a,l,u,n);
    return BackwardSub(u,ForwardSub(l,b));
}
void callLUFactorization()
{
   int n=input(0);
   auto p=input1(n);
   auto a=p.first;
   auto d=p.second;
   display1(solveLU(a,d));
}
