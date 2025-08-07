#include<bits/stdc++.h>
using namespace std;
vector<double> gaussElimination(vector<vector<double>> a,vector<double>b){
    //forming the augmented matrix assuming here both are square
    int n = a.size();
    for ( int i=0;i<n;i++){
        a[i].push_back(b[i]);
    }
    for (int i=0;i<n-1;i++)
    {
        int currMax=i;
        for(int j=i+1;j<n;j++){
            if (fabs(a[j][i])>fabs(a[currMax][i])){
                currMax=j;
            }
        }
        swap(a[i],a[currMax]);
        for(int j=i+1;j<n;j++){
            double fact=a[j][i]/a[i][i];
            for ( int k=i;k<=n;++k){
                a[j][k]-=fact*a[i][k];
            }
        }
        // now use the formed upper triangular and backsubs to get the solution set x
   
    }
         vector<double>x(n);
    for (int j=n-1;j>=0;j--){
        x[j]=a[j][n];
        for(int k=j+1;k<n;k++){
            x[j]-=a[j][k]*x[j];
        }
        x[j]/=a[j][j];
    }
    return x;
}

//another use is to get the inverse using the gauss jordan method form a A|I and turn a into identity using the pivot method and the other turns to A^-1
void gaussJordanInverse(vector<vector<double>>& A) {
    int n = A.size();

    // Augment A with the identity matrix
    vector<vector<double>> augmented(n, vector<double>(2 * n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            augmented[i][j] = A[i][j];

    for (int i = 0; i < n; ++i)
        augmented[i][i + n] = 1;

    // Gauss-Jordan Elimination
    for (int col = 0; col < n; ++col) {
        
        double diag = augmented[col][col];
        for (int j = 0; j < 2 * n; ++j)
            augmented[col][j] /= diag;

        // Make all other elements in this column 0
        for (int row = 0; row < n; ++row) {
            if (row != col) {
                double factor = augmented[row][col];
                for (int j = 0; j < 2 * n; ++j)
                    augmented[row][j] -= factor * augmented[col][j];
            }
        }
    }

    
    cout << "Inverse:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = n; j < 2 * n; ++j)
            cout << setw(10) << fixed << setprecision(5) << augmented[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    vector<vector<double>> A = {
        {2, 1, -1},
        {-3, -1, 2},
        {-2, 1, 2}
    };

    vector<double> b = {8, -11, -3};

    vector<double> result = gaussElimination(A, b);

    cout << "Solution:\n";
    for (int i = 0; i < result.size(); ++i) {
        cout << "x" << i + 1 << " = " << result[i] << endl;
    }
    gaussJordanInverse(A);

    return 0;
}