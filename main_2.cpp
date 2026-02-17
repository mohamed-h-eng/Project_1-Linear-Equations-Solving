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
    int matrix[3][3];
    int matrix_const[3];
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
        int arr[3];
        
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
        for (int i = 0; i < 3; i++) {
            for(int k =0; k<3;k++){
                cout << matrix[i][k] << " ";
            }
            cout << endl;
    }
    // display const value after = sign
    for(int i =0;i<n;i++){
        cout << matrix_const[i]-2 << " ";
    }

    // solve the equations

    /*
    in this part we need to calculate d_value , d_x1, d_x2, d_x3
    then getting value for all variables:
            x1 = d_x1/d_value        ,x2 = d_x2/d_value        ,x3 = d_x3/d_value

    1-solving d_value
    ._+   -   +_.
    | 2 , 3 , 4 | 2 , 3
    | 1 , 2 , 1 | 1 , 2 
    |_3 , 1 , 2_| 3 , 1

        2   * (   2    *     2   -    1    *     1   ) -    3    * (   1    *     2   -    1    *    3   ) +    4    * (  1     *     1   -     2    *     3   )  = -11
    m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1] ) - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) + m[0][2] * (m[1][0] * m[2][1] -  m[1][1] * m[2][0] )  = result
    |_________________________________________________|  |________________________________________________|  |__________________________________________________|
    we could get this by muli-processing 
        1- get the first matched number 2 at index m[0][0]
        2- then store matrix in temp variable
        3- remove the selected row and coloumn
    
    */

    // TODO
    //      [DONE]store the constant of each equation in array
    //      solve the matrix with Cramer’s rule
    // ...
}