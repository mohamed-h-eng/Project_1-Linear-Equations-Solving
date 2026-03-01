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

void get_positive_multiply(int **matrix_ext, int* result, int *num_vars) {
    int multiply = 1;
    for (int i = 0; i < *num_vars; i++) {       // each diagonal
        multiply = 1;
        for (int k = 0; k < *num_vars; k++) {   // each row
            multiply *= matrix_ext[k][k + i];   // column shifts right by i
        }
        *result += multiply;
    }
}

void get_negative_multiply(int **matrix_ext, int* result, int *num_vars) {
    *result = 0;
    int multiply = 1;
    for (int i = *num_vars - 1; i < 2 * (*num_vars) - 1; i++) {  // start columns: 2,3,4
        multiply = 1;
        for (int k = 0; k < *num_vars; k++) {
            multiply *= matrix_ext[k][i - k];   // anti-diagonal
        }
        *result -= multiply;
    }
}

string get_equation(string *command, string *equations){
    int temp_int = 0;
    string temp_str = "";
    for(int i=0;i<command->length();i++){
        if((*command)[i] == 'n'){
            for(int k=i+2;k<command->length();k++){
                temp_str += (*command)[k];
            }
        }
    }
    temp_int = atof(temp_str.c_str())-1;
    return equations[temp_int];
}

void solve(int *num_vars,int **matrix,int **matrix_ext,int *matrix_const, int * result, int *D_value, int *i){
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
    // extend_matrix(matrix, matrix_ext,num_vars);
    get_d_x(matrix_ext,matrix,matrix_const,num_vars,index);
    show_matrix(matrix,num_vars);
}
int parse_command(string *command,string stop){
    int temp_int = 0;
    string temp_str = "";
    for(int i=0;i<command->length();i++){
        if((*command)[i] == 'n'){
            for(int k=i+2;k<command->length();k++){
                temp_str += (*command)[k];
            }
        }
    }
    temp_int = atof(temp_str.c_str())-1;
    return temp_int;
}
int main(){
    string equation;
    string temp_string = "";
    int num_vars;
    int result = 0;
    int D_value =0;
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
    
    //parsing the equations
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
    // [DONE] num_vars
    // [DONE] equation i
    // column x2   coofficients for x2 in all equations
    // add 1 3
    // subtract 1 3
    // [DONE] D matrix of coofficients
    // D x1 matrix of coofficients
    // [DONE] D_value
    // [DONE] solve prints x1,x2,x3 values
    string command;
    // string temp_str="";
    int temp_int=0;
    while (true){
        getline(cin, command);
        if (command.empty()) continue;
        if(command == "num_vars"){
            cout << num_vars << endl;
        }else if(command[0] == 'e'){
            temp_int = parse_command(&command," ");
            cout << equations[temp_int] << endl;
            // cout << get_equation(&command,equations) << endl;
        }else if(command[0] == 'c'){
            cout << "column x2" << endl;
        }else if(command[0] == 'D' && command[2] =='x'){
            temp_int = parse_command(&command,"x");
            show_d_x(matrix,matrix_ext,matrix_const,&num_vars,&temp_int);
            continue;
        }else if(command == "D"){
            show_matrix(matrix,&num_vars);
            cout << endl;
        }else if(command == "D_value"){
            cout << D_value << endl;
        }else if(command == "solve"){
            for(int i=0;i< num_vars;i++){
                solve(&num_vars,matrix,matrix_ext,matrix_const,&result,&D_value,&i);
                cout << "x" << i+1 << "=" << result/D_value << endl;
            }
        }else if(command == "exit"){
            cout << "end program" << endl;
            break;
        }else{
            cout << "else\n";
            continue;
        }
        command = "";
        // temp_str="";
        // temp_int=0;
    }
    return 0;
}