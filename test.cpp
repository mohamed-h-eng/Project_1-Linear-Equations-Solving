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
// extracts the number after the FIRST occurrence of stop char (used to get index1 from "subtract 1 3")
int parse_command_first(string *command, char stop){
    int temp_int = 0;
    string temp_str = "";
    for(int i=0;i<command->length();i++){
        if(char((*command)[i]) == stop){
            // collect digits until next space or end of string
            for(int k=i+1;k<command->length();k++){
                if((*command)[k] == ' ') break;
                temp_str += (*command)[k];
            }
            break; // stop after first occurrence
        }
    }
    temp_int = atof(temp_str.c_str());
    return temp_int;
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
    // subtract equation index2 from equation index1 and print the resulting equation
    for(int k =0;k<*num_vars;k++){
        cout << matrix[index1][k] - matrix[index2][k];  // subtract coefficients of each variable
        cout << "x" << k+1;
    }
    cout << "=" << matrix_const[index1] - matrix_const[index2] << endl;  // subtract right-hand side constants
}

// --- ADDED: Parse the variable index from "substitute xN eq1 eq2" command ---
// Extracts the variable number after 'x' in the substitute command
// e.g. "substitute x2 1 3" -> returns 2
int parse_substitute_var(string *command) {
    string temp_str = "";
    for (int i = 0; i < command->length(); i++) {
        // find 'x' character which marks the variable
        if ((*command)[i] == 'x') {
            // collect digits right after 'x' until a space
            for (int k = i + 1; k < command->length(); k++) {
                if ((*command)[k] == ' ') break;
                temp_str += (*command)[k];
            }
            break;
        }
    }
    return atof(temp_str.c_str()); // return variable index (1-based)
}

// --- ADDED: Parse the two equation indices from "substitute xN eq1 eq2" command ---
// Extracts eq1 and eq2 (the two space-separated numbers after xN)
// e.g. "substitute x2 1 3" -> eq1_index=1, eq2_index=3
void parse_substitute_equations(string *command, int *eq1_index, int *eq2_index) {
    string temp_str = "";
    int space_count = 0;     // counts spaces encountered after 'x'
    bool past_var = false;   // flag: true once we've passed the xN token

    for (int i = 0; i < command->length(); i++) {
        if ((*command)[i] == 'x') {
            past_var = true; // now we are past the variable token
            continue;
        }
        if (!past_var) continue; // skip everything before 'x'

        if ((*command)[i] == ' ') {
            // on each space, store the accumulated number into eq1 or eq2
            if (!temp_str.empty()) {
                space_count++;
                if (space_count == 1) *eq1_index = atof(temp_str.c_str());
                if (space_count == 2) *eq2_index = atof(temp_str.c_str());
                temp_str = "";
            }
        } else {
            temp_str += (*command)[i];
        }
    }
    // capture the last token (eq2 if not yet captured)
    if (!temp_str.empty()) {
        space_count++;
        if (space_count == 1) *eq1_index = atof(temp_str.c_str());
        if (space_count == 2) *eq2_index = atof(temp_str.c_str());
    }
}

// --- ADDED: Substitute variable xN in equation eq1 using its expression from equation eq2 ---
// Removes xN from eq1 by substituting eq2 (solved for xN) into eq1, then prints result.
// Formula: new_coeff[j] = eq1_coeff[j] - (eq1_coeff[var] / eq2_coeff[var]) * eq2_coeff[j]
// new_const        = eq1_const        - (eq1_coeff[var] / eq2_coeff[var]) * eq2_const
void substitute_variable(int **matrix, int *matrix_const, int *num_vars, int var_index, int eq1_index, int eq2_index) {
    // var_index, eq1_index, eq2_index are all 0-based here

    // coefficient of the target variable in eq2 (used as the divisor)
    int eq2_var_coeff = matrix[eq2_index][var_index];

    if (eq2_var_coeff == 0) {
        // cannot solve for xN from eq2 if its coefficient is 0
        cout << "Cannot substitute: x" << var_index + 1
             << " has coefficient 0 in equation " << eq2_index + 1 << endl;
        return;
    }

    // coefficient of the target variable in eq1 (the one being eliminated)
    int eq1_var_coeff = matrix[eq1_index][var_index];

    // multiplier = eq1_var_coeff / eq2_var_coeff  (how much of eq2 to subtract from eq1)
    float multiplier = (float)eq1_var_coeff / (float)eq2_var_coeff;

    // print the resulting equation after substitution
    bool first_term = true; // used to handle leading '+' sign formatting
    for (int k = 0; k < *num_vars; k++) {
        if (k == var_index) continue; // skip the substituted variable (its coefficient becomes 0)

        // compute new coefficient for variable k
        float new_coeff = matrix[eq1_index][k] - multiplier * matrix[eq2_index][k];

        if (new_coeff == 0) continue; // skip zero-coefficient terms

        // print sign and coefficient
        if (!first_term && new_coeff > 0) cout << "+";
        cout << new_coeff << "x" << k + 1;
        first_term = false;
    }

    // compute new right-hand side constant
    float new_const = matrix_const[eq1_index] - multiplier * matrix_const[eq2_index];

    cout << "=" << new_const << endl;
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
    // string temp_str="";
    int temp_int=0;
    while (true){
        getline(cin, command);
        if (command.empty()) continue;
        if(command == "num_vars"){
            cout << num_vars << endl;
        }else if(command[0] == 'e'){
            temp_int = parse_command(&command,' ');
            temp_int -=1;
            cout << equations[temp_int] << endl;
            // cout << get_equation(&command,equations) << endl;
        }else if(command[0] == 'c'){
            temp_int = parse_command(&command,'x');
            temp_int -=1;
            show_column_x(matrix,&num_vars,temp_int);
        }else if(command[0] == 'D' && command[2] =='x'){
            temp_int = parse_command(&command,'x');
            temp_int -=1;
            show_d_x(matrix,matrix_ext,matrix_const,&num_vars,&temp_int);
            continue;
        }else if(command == "D"){
            show_matrix(matrix,&num_vars);
            cout << endl;
        }else if(command == "D_value"){
            cout << D_value << endl;
        }else if(command == "solve"){
            if(D_value==0){
                cout << "No solution";
            }
            for(int i=0;i< num_vars;i++){
                solve(&num_vars,matrix,matrix_ext,matrix_const,&result,&D_value,&i);
                cout << "x" << i+1 << "=" << result/D_value << endl;
            }
        }else if(command[0] == 's'){
            // parse first equation index (the number before the space after 'subtract')
            int sub_index1 = parse_command(&command,' ');
            // parse second equation index (the number after the last space)
            int sub_index2 = parse_command(&command, command[command.rfind(' ')]);
            // convert to 0-based indices to match matrix storage
            sub_index1 -= 1;
            sub_index2 -= 1;
            subtract(matrix, matrix_const, &num_vars, sub_index1, sub_index2);
        }else if(command[0] == 's' && command[1] == 'u'){ // --- ADDED: handle "substitute xN eq1 eq2" command ---
            // parse the variable index (e.g. x2 -> var_index = 2)
            int var_index = parse_substitute_var(&command);
            // parse the two equation indices (e.g. "1 3" -> eq1=1, eq2=3)
            int eq1_idx = 0, eq2_idx = 0;
            parse_substitute_equations(&command, &eq1_idx, &eq2_idx);
            // convert to 0-based indices to match matrix storage
            var_index -= 1;
            eq1_idx   -= 1;
            eq2_idx   -= 1;
            // perform substitution and print result equation
            substitute_variable(matrix, matrix_const, &num_vars, var_index, eq1_idx, eq2_idx);

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