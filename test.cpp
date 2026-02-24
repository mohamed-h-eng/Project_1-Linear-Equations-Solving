# include <iostream>
# include <string>
using namespace std;


void get_left_side(const string *input, string *left_side, string *right_side) {
    for(int i = 0; i < input->length(); i++) {
        if((*input)[i] == '=') {
            break;
        } else {
            *left_side += (*input)[i];
        }
    }
}

void get_right_side(const string *input, string *left_side, string *right_side) {
    for(int i = 0; i < input->length(); i++) {
        if((*input)[i] == '=') {
            for(int k =i+1;k<input->length();k++){
                *right_side += (*input)[k];
            }
        }
    }
}

void get_cooff(string *left_side, int **matrix, int *eq_index){
    int index = 0 ;
    int var_count = 0;
    string cooff = "";
    for(int i=0;i<left_side->length();i++){
        if((*left_side)[i] == 'x'){
            // store chars till reaching x then 
            for(int k=index;k<i;k++){
                (cooff) += (*left_side)[k];
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

void parse_equation(string *equation, string *left_side, string *right_side,int ** matrix, int* index){
    get_left_side(equation, left_side, right_side);
    get_right_side(equation, left_side, right_side);
    get_cooff(left_side,matrix,index);
}

void extend_matrix(int ** matrix, int ** matrix_ext, int *n){
    // extend matrix (copy the first columns except the last one 
    // -- and position them at the end of matrix)
    //for on the 3 equations
    cout << "\n"; // display
    for(int i=0;i<*n;i++){
        // get number
        // copys the first 3 columns from matrix to matrix_ext
        cout << "[ ";
        for(int k=0; k<*n;k++){
            matrix_ext[i][k] = matrix[i][k];
            cout << matrix_ext[i][k] << " ";
            // cout << "m[" <<i << "]" << "[" << k << "]" << "\n"; // display
        }
        // copy the first 2 columns from matrix to matrix_ext
        for(int s=0; s<2;s++){
                matrix_ext[i][s+*n] = matrix[i][s];
                cout << matrix_ext[i][s+*n] << " "; // display
            // cout << "m[" <<i << "]" << "[" << s << "]" << "\n"; // display
            }
            //----the result should generate the matrix_ext with all values
            // set number in matrix_ext
        cout << "]\n";
    }
}

void get_positive_multiply(){

}

void get_negative_multiply(){
    
}

void solve_cramer(int ** matrix, int ** matrix_ext, int *n){
    extend_matrix(matrix, matrix_ext, n);
    get_positive_multiply();
    get_negative_multiply();

}
int main(){
    string equation;
    string left_side = "";
    string right_side = "";
    string cooff= "";
    int index=0;
    int n;
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
    // int matrix_ext[n][(((n-1)*2)+1)]={0}; // test case (use static array) update with(dynamic array)
    // store equations constant at the right-side (after = sign)
    int* matrix_const = new int[n];
    
    //parsing the equations
    for(int i =0; i<n;i++){
        cin >> equation;   
        parse_equation(&equation, &left_side, &right_side, matrix,&i);
        cout << "\nparsing equation " << i;
        cout << "\nleft_side: " << left_side;
        cout << "\nright_side: " << right_side << endl << endl;
        equation = "";
        left_side = "";
        right_side = "";
    }

    // display 2d array(matrix)
    cout << "\ndisplay matrix D\n";
    for (int i = 0; i < n; i++) {
        for(int k =0; k<n;k++){
            cout << matrix[i][k] << " ";
        }
        cout << endl;
    }

    // solve the matrix by cramers rule
    solve_cramer(matrix, matrix_ext,&n);
}