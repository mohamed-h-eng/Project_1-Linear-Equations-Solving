#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;           // number of equations
    int matrix[10][4];  // store coefficients + constant term (last column)

    for (int i = 0; i < n; i++) {
        string eq;
        cin >> eq;

        int col = 0;      // column index for coefficients
        int num = 0;      // temporary number
        bool negative = false;

        for (int j = 0; j < eq.length(); j++) {
            char c = eq[j];

            // check for negative sign
            if (c == '-') {
                negative = true;
            } 
            // extract digits
            else if (isdigit(c)) {
                num = num * 10 + (c - '0');
            } 
            // if we reach 'x', store the coefficient
            else if (c == 'x') {
                if (negative) num = -num;
                matrix[i][col++] = num;
                num = 0;
                negative = false;
            } 
            // if we reach '=', store the constant term
            else if (c == '=') {
                j++; // move to next char
                int constant = 0;
                negative = false;
                while (j < eq.length()) {
                    if (eq[j] == '-') negative = true;
                    else if (isdigit(eq[j])) {
                        constant = constant
