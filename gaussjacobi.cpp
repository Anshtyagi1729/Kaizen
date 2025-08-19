#include<bits/stdc++.h>
using namespace std;
//trial may do gauss siedel after this 
//works like shit btw

bool diagDom(vector<vector<double>>& A, vector<double>& B) {
    int n = A.size();
    vector<int> used(n, 0);   
    vector<vector<double>> newA(n, vector<double>(n, 0));
    vector<double> newB(n, 0);

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int r = 0; r < n; r++) {
            if (used[r]) continue;
            double diag = fabs(A[r][i]);
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) sum += fabs(A[r][j]);
            }
            if (diag >= sum) {
                newA[i] = A[r];
                newB[i] = B[r];
                used[r] = 1;
                found = true;
                break;
            }
        }
        if (!found) {
            return false; 
        }
    }
    A = newA;
    B = newB;
    return true;
}

vector<double> scheme(vector<vector<double>>& A, vector<double>& solk, vector<double>& B) {
    int n = A.size();
    vector<double> solk1(n, 0.0);

    for (int i = 0; i < n; i++) {
        double sigma = 0.0;
        for (int j = 0; j < n; j++) {
            if (j != i) sigma += A[i][j] * solk[j];
        }
        solk1[i] = (B[i] - sigma) / A[i][i];
    }
    return solk1;
}

double errorNorm(vector<double>& xNew, vector<double>& xOld) {
    double err = 0.0;
    for (int i = 0; i < xNew.size(); i++) {
        err = max(err, fabs(xNew[i] - xOld[i]));
    }
    return err;
}

int main() {
    int n;
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n, 0));
    vector<double> B(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }

    if (!diagDom(A, B)) {
        cout << "cant make it dominant enuff\n";
    }

    vector<double> x(n, 0.0);
    vector<double> xNew(n, 0.0);

    double tol;
    cin >> tol;  
    int maxIter = 1000; 

    int iter = 0;
    while (iter < maxIter) {
        xNew = scheme(A, x, B);
        double err = errorNorm(xNew, x);
        if (err < tol) break;
        x = xNew;
        iter++;
    }

    cout << "Solution after " << iter << " iterations:\n";
    for (int i = 0; i < n; i++) {
        cout << xNew[i] << " ";
    }
    cout << endl;

    return 0;
}
