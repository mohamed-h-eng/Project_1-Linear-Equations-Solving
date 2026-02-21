/*
    ------------------READ THIS--------------------
    this a change log to track changes made in code

        1.added code save const value after = sign 
          from every equation in matrix_const
*/
# include <iostream>
# include <string>
using namespace std;

int main(){
    string input;
    string equation;
    int n;
    cin >> n;
    // int matrix[3][3];
    // int matrix_const[3];
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    int* matrix_const = new int[n];
    int arr_index = 0;
    string temp= "";
    for(int i =0; i<n;i++){
        cin >> equation;
        
        // save const value after = sign from every equation in matrix_const
        for(int s =0;s<equation.length();s++){
            if(equation[s] == '='){
                temp = "";
                for(int k=s+1;k<equation.length();k++){
                    temp += equation[k];
                }
                cout << "const: " << temp << endl;
                matrix_const[i] = atof(temp.c_str());
                temp="";
            }
        }
        // remove = sign and after
        for(int i=0;i< equation.length();i++){
            if(equation[i] =='='){
                break;
            }else{
                temp +=equation[i];
            }
        }
        temp;
        int* arr = new int[n];
        
        // extract numbers and store in 2d array
        // each equation extracted into array
        // after all numbers extracted from one equation
        // we store the array into one main array called matrix
        int steps=0;
        for(int i =0; i< temp.length();i++){
            if(temp[i]=='x'){
                arr[steps] = temp[i-1] - '0';
                matrix[arr_index][steps] = arr[steps];
                steps ++;
            }
        }
        arr_index++;
        }
        // display 2d array(matrix)
        cout << "\nextract numbers\n";
        for (int i = 0; i < n; i++) {
            for(int k =0; k<n;k++){
                cout << matrix[i][k] << " ";
            }
            cout << endl;
    }
    // display const value after = sign
    for(int i =0;i<n;i++){
        cout << matrix_const[i] << " ";
    }


    // TODO
    //      [DONE]store the constant of each equation in array
    //      solve the matrix with Cramer’s rule
    // ...
}