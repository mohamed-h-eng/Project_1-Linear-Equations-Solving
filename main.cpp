# include <iostream>
# include <string>
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
            for(int k=index;k<i;k++){
                (cooff) += (*temp_string)[k];
                index ++;
            }
            matrix[*eq_index][var_count] = atof((cooff).c_str());
            (cooff) = "";
            index ++;
            index ++;
            var_count ++;
        }
    }
}
void parse_equation(string *equation, string *temp_string,int ** matrix,int *matrix_const, int* index){
    get_left_side(equation, temp_string);
    get_cooff(temp_string,matrix,index); // extract cooff and store in matrix depends on index->(equation number)
    get_right_side(equation, matrix_const, index); // extract right side and store in matrix_const
}
void extend_matrix(int ** matrix, int ** matrix_ext, int *num_vars){
    for(int i=0;i<*num_vars;i++){
        for(int k=0; k<*num_vars;k++){
            matrix_ext[i][k] = matrix[i][k];
        }
        for(int s=0; s<2;s++){
            matrix_ext[i][s+*num_vars] = matrix[i][s];
        }
    }
}
void get_d_x(int ** matrix_ext,int **matrix, int * matrix_const, int *num_vars, int *index){
    for(int i =0;i<*num_vars;i++){
        matrix_ext[i][*index] = matrix_const[i];
        for(int s=0; s<*num_vars-1;s++){
            matrix_ext[i][s+*num_vars] = matrix_ext[i][s];
        }
    }
}
void get_positive_multiply(int **matrix_ext, float* result, int *num_vars) {
    int multiply = 1;
    for (int i = 0; i < *num_vars; i++) {       // each diagonal
        multiply = 1;
        for (int k = 0; k < *num_vars; k++) {   // each row
            multiply *= matrix_ext[k][k + i];   // column shifts right by i
        }
        *result += multiply;
    }
}
void get_negative_multiply(int **matrix_ext, float* result, int *num_vars) {
    *result = 0;
    int multiply = 1;
    // for (int i = *num_vars - 1; i < 2 * (*num_vars) - 1; i++) {  // start columns: 2,3,4
    for (int i = *num_vars - 1; i < ((*num_vars) - 1)+(*num_vars); i++) {  // start columns: 2,3,4
        multiply = 1;
        for (int k = 0; k < *num_vars; k++) {
            multiply *= matrix_ext[k][i - k];   // anti-diagonal
        }
        *result -= multiply;
    }
}
void solve(int *num_vars,int **matrix,int **matrix_ext,int *matrix_const, float * result, float *D_value, int *i){
    extend_matrix(matrix, matrix_ext, num_vars);
    get_d_x(matrix_ext,matrix,matrix_const,num_vars,i);
    get_negative_multiply(matrix_ext,result,num_vars);
    get_positive_multiply(matrix_ext,result,num_vars);
}
void show_matrix(int **matrix, int*num_vars){
    for (int i = 0; i < *num_vars; i++) {
        for(int k =0; k<*num_vars;k++){
            cout << matrix[i][k] << " ";
        }
        cout << endl;
    }
}
void show_d_x(int **matrix,int **matrix_ext,int *matrix_const, int*num_vars, int * index){
    extend_matrix(matrix, matrix_ext,num_vars);
    get_d_x(matrix_ext,matrix,matrix_const,num_vars,index);
    show_matrix(matrix_ext,num_vars);
}
int parse_command(string *command,char stop){
    int temp_int = 0;
    string temp_str = "";
    // cout << "column: " << *command  << "stop: " << stop << endl;
    for(int i=0;i<command->length();i++){
        if(char((*command)[i]) == stop){
            // cout << "length: " << command->length() << endl;
            for(int k=i+1;k<command->length();k++){
                temp_str += (*command)[k];
                // cout <<  "temp_str: " <<  temp_str<< endl;
            }
        }
    }
    temp_int = atof(temp_str.c_str());
    return temp_int;
}
void show_column_x(int **matrix,int * num_vars, int index){
    for (int i = 0; i <*num_vars; i++) {
        cout << matrix[i][index] << endl;
    }
}
void subtract(int** matrix,int *matrix_const, int* num_vars, int index1, int index2){
    for(int i =0;i<*num_vars;i++){
        for(int k =0;k<*num_vars;k++){
            cout << matrix[index1][k] - matrix[index2][k];
            cout << "x" << k+1;
        }
        cout << "=" << matrix_const[i] << endl;
    }
}
void substitute_variable(int **matrix, int *matrix_const, int *num_vars, int var_index, int eq1_index, int eq2_index) {
    if (matrix[eq2_index][var_index] == 0) {
        cout << "Cannot substitute: x" << var_index+1 << " has coefficient 0 in equation " << eq2_index+1 << endl;
        return;
    }
    float multiplier = (float)matrix[eq1_index][var_index] / (float)matrix[eq2_index][var_index];
    for (int k = 0; k < *num_vars; k++) {
        if (k == var_index) continue; // this variable is eliminated
        float new_coeff = matrix[eq1_index][k] - multiplier * matrix[eq2_index][k];
        if (new_coeff == 0) continue;
        cout << new_coeff << "x" << k+1;
    }
    cout << "=" << matrix_const[eq1_index] - multiplier * matrix_const[eq2_index] << endl;
}
int main(){
    string equation;
    string temp_string = "";
    int num_vars;
    float result = 0;
    float D_value =0;
    cin >> num_vars;
    cin.ignore();
    string* equations = new string[num_vars];
    int** matrix = new int*[num_vars];
    for (int i = 0; i < num_vars; i++) {
        matrix[i] = new int[num_vars];
    }
    int** matrix_ext = new int*[num_vars];
    for (int i = 0; i < num_vars; i++) {
        matrix_ext[i] = new int[2 * num_vars];
    }
    int* matrix_const = new int[num_vars];
    for(int i =0; i<num_vars;i++){
        cin >> equation;
        equations[i]   = equation;
        parse_equation(&equation, &temp_string,matrix,matrix_const, &i);
        equation = "";
        temp_string = "";
    }
    extend_matrix(matrix, matrix_ext, &num_vars);
    get_negative_multiply(matrix_ext,&result,&num_vars);
    get_positive_multiply(matrix_ext,&result,&num_vars);
    D_value = result;
    // add 1 3
    // subtract 1 3
    // [DONE] D x1 matrix of coofficients
    // [DONE] num_vars
    // [DONE] equation i
    // [DONE] column x2   coofficients for x2 in all equations
    // [DONE] D matrix of coofficients
    // [DONE] D_value
    // [DONE] solve prints x1,x2,x3 values
    string command;
    int temp_int=0;
    while (true){
        getline(cin, command);
        if(command == "num_vars"){
            cout << num_vars << endl;
        }else if(command[0] == 'e'){
            temp_int = parse_command(&command,' ');
            temp_int -=1;
            cout << equations[temp_int] << endl;
        }else if(command[0] == 'c'){
            temp_int = parse_command(&command,'x');
            temp_int -=1;
            show_column_x(matrix,&num_vars,temp_int);
        }else if((command[0] == 'D' ||command[0] == 'd' ) && command[2] =='x'){
            temp_int = parse_command(&command,'x');
            temp_int -=1;
            show_d_x(matrix,matrix_ext,matrix_const,&num_vars,&temp_int);
        }else if(command == "D" ||command == "d" ){
            show_matrix(matrix,&num_vars);
            cout << endl;
        }else if(command == "D_value"||command == "d_value"){
            cout << D_value << endl;
        }else if(command == "solve"){
            if(D_value==0){
                cout << "No Solution";
            }else{
                for(int i=0;i< num_vars;i++){
                    solve(&num_vars,matrix,matrix_ext,matrix_const,&result,&D_value,&i);
                    cout << "x" << i+1 << "=" << result/D_value << endl;
                }
            }
        }else if(command[0] == 's'){
            temp_int = parse_command(&command,' ');
            cout << "subtract: " << temp_int << endl;
        }else if(command == "exit"){
            cout << "end program" << endl;
            break;
        }else{
            continue;
        }
        command = "";
    }
    return 0;
}