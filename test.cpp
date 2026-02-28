# include <iostream>
# include <string>
#include <cmath> 
using namespace std;

void get_left_side(const string *input, string *temp_string) {
    for(int i = 0; i < input->length(); i++) {
        if((*input)[i] == '=') {
            break;
        } else {
            *temp_string += (*input)[i];
        }
    }
}

void get_right_side(const string *input,int *matrix_const, int* index) {
    string temp = "";
    for(int i = 0; i < input->length(); i++) {
        if((*input)[i] == '=') {
            for(int k =i+1;k<input->length();k++){
                temp += (*input)[k];
            }
        }
    }
    matrix_const[*index] = atof((temp).c_str());
}

void get_cooff(string *temp_string, int **matrix, int *eq_index){
    int index = 0;
    int var_count = 0;
    string cooff = "";
    for(int i=0;i<temp_string->length();i++){
        if((*temp_string)[i] == 'x'){
            // store chars till reaching x then 
            for(int k=index;k<i;k++){
                (cooff) += (*temp_string)[k];
                index ++;
            }
            matrix[*eq_index][var_count] = atof((cooff).c_str());
            (cooff) = "";
            // skip char x1, x2 , ...
            index ++;
            index ++;
            // count number of variables extracted (helps in storing values in right position in matrix)
            var_count ++;
        }
    }
}

void parse_equation(string *equation, string *temp_string,int ** matrix,int *matrix_const, int* index){
    get_left_side(equation, temp_string);
    get_cooff(temp_string,matrix,index); // extract cooff and store in matrix depends on index->(equation number)
    get_right_side(equation, matrix_const, index); // extract right side and store in matrix_const
}

void extend_matrix(int ** matrix, int ** matrix_ext, int *n){
    for(int i=0;i<*n;i++){
        for(int k=0; k<*n;k++){
            matrix_ext[i][k] = matrix[i][k];
        }
        // copy the first 2 columns from matrix to matrix_ext
        for(int s=0; s<2;s++){
            matrix_ext[i][s+*n] = matrix[i][s];
        }
    }
}

void get_d_x(int ** matrix_ext,int **matrix, int * matrix_const, int *n, int index){
    for(int i =0;i<*n;i++){
        matrix_ext[i][index] = matrix_const[i];
        // copy the first 2 columns from matrix to matrix_ext
        for(int s=0; s<*n-1;s++){
            matrix_ext[i][s+*n] = matrix_ext[i][s];
        }
    }
}

void get_positive_multiply(int **matrix_ext, int* result){
    int zero = 0;
    int multiply=1;
    // int sum = 0;
    // 2# get positive multiplications
    cout << "\npositive multiply\n";
    for(int i =0;i<3;i++){
        for(int k=0;k<3;k++){
            // first_res*=matrix_ext[zero][k+i];
            cout << endl << "multiply: " << multiply << " * " << matrix_ext[zero][k+i] ;   
            multiply *= matrix_ext[zero][k+i];
            zero ++;
        }
        cout << endl << *result << " + " << multiply<< endl;
        *result += multiply;
        multiply =1;
        zero = 0;
    }
    cout << endl;
}

void get_negative_multiply(int **matrix_ext, int* result){
    int zero = 0;
    int multiply=1;
    *result = 0;
    for(int i =4;i>1;i--){
        for(int k=0;k<3;k++){
            cout << endl << "multiply: " << matrix_ext[k][i-k] << " * " << multiply;
            multiply*= matrix_ext[k][i-k];
        }
        cout << endl << *result << " - " << multiply<< endl;
        *result =*result - multiply;
        multiply=1;
    }

}

// void solve_cramer(int ** matrix, int ** matrix_ext, int *n){
//     extend_matrix(matrix, matrix_ext, n);
//     get_positive_multiply();
//     get_negative_multiply();
// }


int main(){
    string equation;
    string temp_string = "";
    string right_side = "";
    string cooff= "";
    
    int index=0;
    int n;
    int result = 0; // result of final results like D_value or x1 , x2, ...
    int D_value =0;
    cin >> n;
    // create an empty 2D matrix to store equations cooffecients
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    int** matrix_ext = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix_ext[i] = new int[n];
    }
    int* matrix_const = new int[n];
    
    //parsing the equations
    for(int i =0; i<n;i++){
        cin >> equation;   
        parse_equation(&equation, &temp_string,matrix,matrix_const, &i);
        cout << "\nparsing equation " << i;
        cout << "\nleft_side: " << temp_string;
        cout << "\nright_side: " << matrix_const[i] << endl << endl;
        equation = "";
        temp_string = "";
    }

    // display 2d array(matrix)
    cout << "\ndisplay matrix D\n";
    for (int i = 0; i < n; i++) {
        for(int k =0; k<n;k++){
            cout << matrix[i][k] << " ";
        }
        cout << endl;
    }

    // get d matrix and D_value
    extend_matrix(matrix, matrix_ext, &n);
    cout << "\ndisplay matrix D (extend)\n";
    for (int i = 0; i < n; i++) {
        cout << "[ ";
        for(int k =0; k<((n-1)*2)+1;k++){
            cout << matrix_ext[i][k] << " ";
        }
        cout << "]\n";
    }

    get_negative_multiply(matrix_ext,&result);
    get_positive_multiply(matrix_ext,&result);
    D_value = result;
    cout << "d_value= " << D_value << endl;
    
    for(int i=0;i< n;i++){
        // get d_x matrix and value
        // extend_matrix(matrix, matrix_ext, &n);
        cout << "\ndisplay matrix D_x" << i+1 << endl;
        extend_matrix(matrix, matrix_ext, &n);
        get_d_x(matrix_ext,matrix,matrix_const,&n,i);

        for (int s = 0; s < n; s++) {
            cout << "[ ";
            for(int k =0; k<((n-1)*2)+1;k++){
                cout << matrix_ext[s][k] << " ";
            }
            cout << "]\n";
        }
        get_negative_multiply(matrix_ext,&result);
        get_positive_multiply(matrix_ext,&result);
        cout << "x" << i+1 << "= " << result/D_value << endl;
        result = 0;
    }
}