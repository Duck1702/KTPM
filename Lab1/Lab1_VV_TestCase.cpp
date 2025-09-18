#include <bits/stdc++.h>
using namespace std;

// ===== f1 =====
int f1(int x) {
    if (x > 10) return 2*x;
    else return -x;
}

// f1 buggy (để so sánh)
int f1_bug(int x) {
    if (x > 10) return 2*x;
    else if (x > 0) return -x;
    else return 2*x;
}

// ===== f2 =====
int f2(int x) {
    if (x < 10) return 2 * x;
    else if (x < 2) return -x;   
    else return 2 * x;
}

// ===== f3 =====
int f3(int x) {
    double val = x * x * cos(x);
    if (val <= 0) throw runtime_error("log domain error");
    if (log(val) < 3.0 * x) return 2*x;
    else return 2*x;
}

// ===== findMax =====
int findMax_bug(int num1, int num2, int num3) {
    int max = 0;
    if ((num1 > num2) && (num1 > num3)) max = num1;
    if ((num2 > num1) && (num2 > num3)) max = num2;
    if ((num3 > num1) && (num3 > num2)) max = num3;
    return max;
}

int findMax_fixed(int num1, int num2, int num3) {
    int mx = num1;
    if (num2 > mx) mx = num2;
    if (num3 > mx) mx = num3;
    return mx;
}

// ===== solveQuartic =====
int solveQuartic(double a, double b, double c, double x[]) {
    if (a == 0 && b == 0 && c == 0) return -1;
    if (a == 0 && b == 0) return 0;
    if (a == 0) {
        double y = -c / b;
        if (y < 0) return 0;
        x[0] = sqrt(y);
        x[1] = -sqrt(y);
        return 2;
    }
    double delta = b*b - 4*a*c;
    if (delta < 0) return 0;

    double y1 = (-b + sqrt(delta)) / (2*a);
    double y2 = (-b - sqrt(delta)) / (2*a);
    int count = 0;
    if (y1 >= 0) {
        x[count++] = sqrt(y1);
        x[count++] = -sqrt(y1);
    }
    if (y2 >= 0 && y2 != y1) {
        x[count++] = sqrt(y2);
        x[count++] = -sqrt(y2);
    }
    return count;
}

// ====== Test runner ======
int main() {
    // f1
    cout << "=== f1 tests ===\n";
    for (int x : {11, 10, -5}) {
        cout << "x="<<x<<" | f1="<<f1(x)<<" | f1_bug="<<f1_bug(x)<<"\n";
    }

    // f2
    cout << "\n=== f2 tests ===\n";
    for (int x : {1,5,10}) {
        cout << "x="<<x<<" | f2="<<f2(x)<<"\n";
    }

    // findMax
    cout << "\n=== findMax tests ===\n";
    vector<tuple<int,int,int>> cases = {
        {3,2,1}, {1,3,2}, {1,2,3}, {-1,-2,-3}, {2,2,1}, {2,2,2}
    };
    for (auto &t: cases) {
        int a,b,c; tie(a,b,c) = t;
        cout << "input=("<<a<<","<<b<<","<<c<<") expected="<<findMax_fixed(a,b,c)
             <<" | bug="<<findMax_bug(a,b,c)<<"\n";
    }

    // f3
    cout << "\n=== f3 tests ===\n";
    for (int x : {1,2,3}) {
        try {
            cout << "x="<<x<<" -> "<<f3(x)<<"\n";
        } catch (exception &e) {
            cout << "x="<<x<<" -> exception: "<<e.what()<<"\n";
        }
    }

    // solveQuartic
    cout << "\n=== solveQuartic tests ===\n";
    double arr[4];
    vector<tuple<double,double,double>> qcases = {
        {0,0,0}, {0,0,1}, {0,2,-8}, {1,0,-4},
        {1,-5,4}, {1,0,1}, {1,-2,1}, {1,2,1}
    };
    for (auto &t: qcases) {
        double a,b,c; tie(a,b,c) = t;
        int n = solveQuartic(a,b,c,arr);
        cout << "a="<<a<<", b="<<b<<", c="<<c<<" -> n="<<n;
        if (n>0) {
            cout << " {";
            for (int i=0;i<n;i++) cout << arr[i] << (i==n-1? "":", ");
            cout << "}";
        }
        cout << "\n";
    }
    return 0;
}
