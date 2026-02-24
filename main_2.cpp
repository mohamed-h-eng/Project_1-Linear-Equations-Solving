/*
    ------------------READ THIS--------------------
    this a change log to track changes made in code

        1.added code save const value after = sign 
          from every equation in matrix_const
*/
# include <iostream>
# include <string>
using namespace std;

int cramer_solve(int matrix_ext) {
    int sum = 0;
    int subtract = 0;
    int multiply = 1;

    // --- Get positive multiplications ---
    // for(int i = 0; i < 3; i++) {
    //     multiply = 1; 
    //     for(int k = 0; k < 3; k++) {
    //         cout << matrix_ext[k][k + i] << " ";
    //         multiply *= matrix_ext[k][k + i];
    //     }
    //     sum += multiply;
        
    //     cout << endl << endl;
    // }
    // cout << endl;

    // // --- Get negative multiplications ---
    // for(int i = 4; i > 1; i--) {
    //     multiply = 1; 
    //     for(int k = 0; k < 3; k++) {
    //         multiply *= matrix_ext[k][i - k];
    //     }
    //     subtract -= multiply; 
    // }

    return sum + subtract;
}

int main(){
    // initializing variables
    string equation; // temp variable to store input equation
    int n; // number of equations user want to enter
    cin >> n; // get input from user
    // create an empty 2D matrix to store equations cooffecients
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    // store equations constant at the right-side (after = sign)
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

    // extend the matrix with (( n - 1 ) * 2 ) + 1
    // int ext = ((n - 1) * 2) + 1;
    // int matrix_ext[n][ext];
    int matrix_ext[n][(((n-1)*2)+1)]={0}; // test case (use static array) update with(dynamic array)
    //for on the 3 equations
    cout << "\n"; // display
    for(int i=0;i<n;i++){
        // get number
        // copys the first 3 columns from matrix to matrix_ext
        cout << "[ ";
        for(int k=0; k<n;k++){
            matrix_ext[i][k] = matrix[i][k];
            cout << matrix_ext[i][k] << " ";
            // cout << "m[" <<i << "]" << "[" << k << "]" << "\n"; // display
        }
        // copy the first 2 columns from matrix to matrix_ext
        for(int s=0; s<2;s++){
                matrix_ext[i][s+n] = matrix[i][s];
                cout << matrix_ext[i][s+n] << " "; // display
            // cout << "m[" <<i << "]" << "[" << s << "]" << "\n"; // display
            }
            //----the result should generate the matrix_ext with all values
            // set number in matrix_ext
        cout << "]\n";
    }
    
    // this a test case
    // for(int i =0;i<6;i++){
    //     cout << i << "repeat\n";
    //     for(int k=0;k<3;k++){
    //         cout << "m[" << i << "]" << "["  << k << "] , ";
    //     }
    //     cout <<"\n";
    // }

    // cout << "\ncramer: " << cramer_solve(matrix_ext)<< endl;
    // get positive multiplications
    int zero = 0;
    int first_res =1;
    
    int multiply = 1;
    int sum = 0;
    
    for(int i =0;i<3;i++){
        for(int k=0;k<3;k++){
            first_res*=matrix_ext[zero][k+i];
            cout << matrix_ext[zero][k+i] << " ";
            multiply *=matrix_ext[zero][k+i];
            zero ++;
        }
        sum += multiply;
        multiply =1;
        zero = 0;

        cout << endl;
        cout << endl;
    }
    cout << endl;
    // get negative multiplications
    zero = 0;
    int second_res =0;
    int subtract = 0;
    for(int i =4;i>1;i--){
        for(int k=0;k<3;k++){
            multiply*= matrix_ext[k][i-k];
        }
        subtract -= multiply;
        multiply=1;
    }
    
    // get D_value
    int d_value = subtract + sum;
    cout << "\nD_value: " << d_value;
    
    // move the constant through all columns to get D_x1, D_x2 and so
    for(int i=0;i<n;i++){
        matrix_ext[i][0] = matrix_const[i];
    }
    
    zero = 0;
    multiply=1;
    sum = 0;
    subtract = 0;
    // 2# get positive multiplications
    for(int i =0;i<3;i++){
        for(int k=0;k<3;k++){
            first_res*=matrix_ext[zero][k+i];
            multiply *=matrix_ext[zero][k+i];
            zero ++;
        }
        sum += multiply;
        multiply =1;
        zero = 0;
    }
    cout << endl;
    // get negative multiplications
    zero = 0;
    multiply=1;

    for(int i =4;i>1;i--){
        for(int k=0;k<3;k++){
            multiply*= matrix_ext[k][i-k];
        }
        subtract -= multiply;
        multiply=1;
    }

    // calculate D_x1
    cout << "\nD_x1: " << subtract + sum;
    cout << "\nx1= " << (subtract + sum)/d_value;


    /*
    in this part we need to calculate d_value , d_x1, d_x2, d_x3
    then getting value for all variables:
            x1 = d_x1/d_value        ,x2 = d_x2/d_value        ,x3 = d_x3/d_value

    1-solving d_value
    ._+   -   +_.
    | 2 , 3 , 4 |
    | 1 , 2 , 1 |
    |_3 , 1 , 2_|

    
    2   * (   2    *     2   -    1    *     1   ) -    3    * (   1    *     2   -    1    *    3   ) +    4    * (  1     *     1   -     2    *     3   )  = -11
    m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1] ) - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) + m[0][2] * (m[1][0] * m[2][1] -  m[1][1] * m[2][0] )  = result
    |_________________________________________________|  |________________________________________________|  |__________________________________________________|
    we could get this by muli-processing 
    1- get the first matched number 2 at index m[0][0]
    2- then store matrix in temp variable
    3- remove the selected row and coloumn
    
    #2 method
    ._                 _
    | 2 , 3 , 4 , 2 , 3 |
    | 1 , 2 , 1 , 1 , 2 |
    |_3 , 1 , 2 , 3 , 1_|

    -(m[0][4] * m[1][3] * m[2][2]) - (m[0][3] * m[1][2] * m[2][1]) - (m[0][2] * m[1][1] * m[2][0]) + (m[0][0] * m[1][1] * m[2][2]) + (m[0][1] * m[1][2] * m[2][2]) + (m[0][2] * m[1][3] * m[2][4])
    -(   3    *     1   *    2   ) - (   2    *    1    *    1   ) - (    4   *    2    *     3  ) + (   2    *    2    *    2   ) + (   3    *    1    *    3   ) + (   4    *    1    *     1  )
    |_____________________________________________________________________________________________|  |____________________________________________________________________________________________|

    // TODO
    //      [DONE]store the constant of each equation in array
    //      solve the matrix with Cramer’s rule:
            [DONE]extend the matrix with length of (( n - 1 ) * 2 ) + 1
            get numbers in right sequnce re.remember start equation
    // ...
    */
}