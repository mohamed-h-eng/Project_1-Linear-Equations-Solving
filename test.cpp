# include <iostream>
# include <string>
using namespace std;

int main(){
    string e = "3x1+1x2+2x3=13";
    string number="";
    int n;
    for(int i =0;i<e.length();i++){
        if(e[i] == '='){
            for(int k=i+1;k<e.length();k++){
                number += e[k];
            }
        }
    }
    n = atof(number.c_str());
    cout << n-1;
    return 0;
}