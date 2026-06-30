#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <iostream>
using namespace std;

inline int fibonacciDynamic(int n) {
    if (n <= 1) return n;
    int fib[n + 1];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib[n];
}

inline void multiplyMatrix(int F[2][2], int M[2][2]) {
    int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

inline void matrixPower(int F[2][2], int n) {
    if (n == 0 || n == 1) return;
    int M[2][2] = {{1, 1}, {1, 0}};
    matrixPower(F, n / 2);
    multiplyMatrix(F, F);
    if (n % 2 != 0) multiplyMatrix(F, M);
}

inline int fibonacciMatrix(int n) {
    if (n == 0) return 0;
    int F[2][2] = {{1, 1}, {1, 0}};
    matrixPower(F, n - 1);
    return F[0][0];
}

inline int fibonacciRecursive(int n) {
    if (n <= 1) return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

inline void runFibonacciMenu() {
    int n;
    cout << "Enter the Fibonacci position (n): ";
    cin >> n;
    cout << "Fibonacci number at position " << n << " (dynamic programming): "
         << fibonacciDynamic(n) << endl;
    cout << "Fibonacci number at position " << n << " (matrix multiplication): "
         << fibonacciMatrix(n) << endl;
    cout << "Fibonacci number at position " << n << " (recursive): "
         << fibonacciRecursive(n) << endl;
}

#endif
