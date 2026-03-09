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
void get_right_side(const string *input,float* matrix_const, int* index) {
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

void get_cooff(string *temp_string, float** matrix, int *eq_index){
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

void parse_equation(string *equation, string *temp_string,float** matrix,float* matrix_const, int* index){
    get_left_side(equation, temp_string);
    get_cooff(temp_string,matrix,index);
    get_right_side(equation, matrix_const, index);
}

void get_d_x(float ** matrix_temp,float **matrix, float * matrix_const, int *num_vars, int *index){
    for(int i =0;i<*num_vars;i++){
        for(int k=0; k<*num_vars;k++){
            matrix_temp[i][k] = matrix[i][k];
        }
        matrix_temp[i][*index] = matrix_const[i];
        for(int s=0; s<*num_vars-1;s++){
            matrix_temp[i][s+*num_vars] = matrix_temp[i][s];
        }
    }
}
float gaussian_det(float** matrix, int *num_vars) {
    int n = *num_vars;
    float** tmp = new float*[n];
    for(int i=0;i<n;i++){
        tmp[i] = new float[n];
        for(int k=0;k<n;k++) tmp[i][k] = matrix[i][k];
    }
    float det = 1;
    for(int col=0;col<n;col++){
        int pivot = -1;
        for(int row=col;row<n;row++){ if(tmp[row][col] != 0){ pivot=row; break; } }
        if(pivot == -1){ det=0; break; }
        if(pivot != col){
            float* t = tmp[col]; tmp[col]=tmp[pivot]; tmp[pivot]=t;
            det *= -1;
        }
        det *= tmp[col][col];
        for(int row=col+1;row<n;row++){
            float factor = tmp[row][col] / tmp[col][col];
            for(int k=col;k<n;k++) tmp[row][k] -= factor * tmp[col][k];
        }
    }
    for(int i=0;i<n;i++) delete[] tmp[i];
    delete[] tmp;
    return det;
}
void solve(int *num_vars, float** matrix, float* matrix_const) {
    int n = *num_vars;
    float** aug = new float*[n];
    for(int i=0;i<n;i++){
        aug[i] = new float[n+1];
        for(int k=0;k<n;k++)aug[i][k] = matrix[i][k];
        aug[i][n] = matrix_const[i];
    }
    for(int col=0;col<n;col++){
        int pivot = -1;
        for(int row=col;row<n;row++){ if(aug[row][col] != 0){ pivot=row; break; } }
        if(pivot == -1){ cout << "No solution" << endl; return; }
        if(pivot != col){ float* t=aug[col]; aug[col]=aug[pivot]; aug[pivot]=t; }
        for(int row=col+1;row<n;row++){
            float factor = aug[row][col] / aug[col][col];
            for(int k=col;k<=n;k++) aug[row][k] -= factor * aug[col][k];
        }
    }
    float* x = new float[n];
    for(int i=n-1;i>=0;i--){
        x[i] = aug[i][n];
        for(int k=i+1;k<n;k++) x[i] -= aug[i][k] * x[k];
        x[i] /= aug[i][i];
    }
    for(int i=0;i<n;i++) cout << "x" << i+1 << "=" << x[i] << endl;
    delete[] x;
    for(int i=0;i<n;i++) delete[] aug[i];
    delete[] aug;
}
void show_matrix(float** matrix, int*num_vars){
    for (int i = 0; i < *num_vars; i++) {
        for(int k =0; k<*num_vars;k++){
            cout << matrix[i][k] << " ";
        }
        cout << endl;
    }
}
void show_d_x(float** matrix,float** temp_matrix,float* matrix_const, int*num_vars, int * index){
    get_d_x(temp_matrix,matrix,matrix_const,num_vars,index);
    show_matrix(temp_matrix,num_vars);
}

int parse_command_first(string *command, char stop){
    int temp_int = 0;
    string temp_str = "";
    bool collecting = false;
    for(int i=0;i<command->length();i++){
        if(char((*command)[i]) == stop && !collecting){
            collecting = true;
            continue;
        }
        if(collecting){
            if((*command)[i] == stop) break;
            temp_str += (*command)[i];
        }
    }
    temp_int = atof(temp_str.c_str());
    return temp_int;
}
int parse_command(string *command,char stop){
    int temp_int = 0;
    string temp_str = "";
    for(int i=0;i<command->length();i++){
        if(char((*command)[i]) == stop){
            temp_str = "";
            for(int k=i+1;k<command->length();k++){
                temp_str += (*command)[k];
            }
        }
    }
    temp_int = atof(temp_str.c_str());
    return temp_int;
}
void show_column_x(float** matrix,int * num_vars, int index){
    for (int i = 0; i <*num_vars; i++) {
        cout << matrix[i][index] << endl;
    }
}
void subtract(float** matrix,float* matrix_const, int* num_vars, int index1, int index2){
    int result =0;
    for(int k =0;k<*num_vars;k++){
        result =  matrix[index1][k] - matrix[index2][k];
        if (result > 0 && k >0){
            cout << "+";
        }
        cout << result << "x" << k+1;
    }
    cout << "=" << matrix_const[index1] - matrix_const[index2] << endl;  // subtract right-hand side constants
}
void add(float** matrix,float* matrix_const, int* num_vars, int index1, int index2){
    int result =0;
    for(int k =0;k<*num_vars;k++){
        result =  matrix[index1][k] + matrix[index2][k];
        if (result > 0 && k >0){
            cout << "+";
        }
        cout << result << "x" << k+1;
    }
    cout << "=" << matrix_const[index1] + matrix_const[index2] << endl;
}
void substitute_variable(float** matrix, float* matrix_const, int *num_vars, int var_index, int eq1_index, int eq2_index) {
    if (matrix[eq2_index][var_index] == 0) {
        cout << "Cannot substitute: x" << var_index+1 << " has coefficient 0 in equation " << eq2_index+1 << endl;
        return;
    }
    float multiplier = (float)matrix[eq1_index][var_index] / (float)matrix[eq2_index][var_index];
    for (int k = 0; k < *num_vars; k++) {
        if (k == var_index) continue;
        float new_coeff = matrix[eq1_index][k] - multiplier * matrix[eq2_index][k];
        if (new_coeff == 0){
            continue;
        }else if (new_coeff > 0 && k > 0){
            cout << "+" << new_coeff << "x" << k+1;
        }else{
            cout << new_coeff << "x" << k+1;
        }
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
    float** matrix = new float*[num_vars];
    for (int i = 0; i < num_vars; i++) {
        matrix[i] = new float[num_vars];
    }
    float** temp_matrix = new float*[num_vars];
    for (int i = 0; i < num_vars; i++) {
        temp_matrix[i] = new float[2 * num_vars];
    }
    float* matrix_const = new float[num_vars];
    for(int i =0; i<num_vars;i++){
        cin >> equation;
        equations[i]   = equation;
        parse_equation(&equation, &temp_string,matrix,matrix_const, &i);
        equation = "";
        temp_string = "";
    }
    D_value = gaussian_det(matrix, &num_vars);
    string command;
    int temp_int=0;
    int var_index;
    int first_idx=0;
    int second_idx=0;
    while (true){
        getline(cin, command);
        if(command == "num_vars"){
            cout << num_vars << endl;
        }else if(command[0] == 'e'){
            temp_int = parse_command(&command,' ') - 1;
            cout << equations[temp_int] << endl;
        }else if(command[0] == 'c'){
            temp_int = parse_command(&command,'x') - 1;
            show_column_x(matrix,&num_vars,temp_int);
        }else if(command[0] == 'D' && command[2] =='x'){
            temp_int = parse_command(&command,'x') - 1;
            show_d_x(matrix,temp_matrix,matrix_const,&num_vars,&temp_int);
        }else if(command == "D"){
            show_matrix(matrix,&num_vars);
        }else if(command == "D_value"){
            cout << D_value << endl;
        }else if(command == "solve"){
            if(D_value==0){
                cout << "No solution" << endl;
            } else {
                solve(&num_vars, matrix, matrix_const);
            }
        }else if(command[0] == 's' && command[3] == 's'){
            string prefix = command.substr(0, command.rfind(' '));
            var_index= parse_command(&command, 'x') - 1;
            first_idx= parse_command(&prefix,  ' ') - 1;
            second_idx= parse_command(&command, ' ') - 1;
            substitute_variable(matrix, matrix_const, &num_vars, var_index, first_idx, second_idx);
        }else if(command[0] == 's'){
            first_idx = parse_command_first(&command,' ')- 1;
            second_idx = parse_command(&command,' ')-1;
            subtract(matrix, matrix_const, &num_vars, first_idx, second_idx);
        }else if(command[0] == 'a'){
            first_idx  = parse_command_first(&command,' ') -1;
            second_idx = parse_command(&command,' ') -1;
            add(matrix, matrix_const, &num_vars, first_idx, second_idx);
        }else if(command == "quit"){
            cout << "end program" << endl;
            break;
        }else{
            continue;
        }
        command = "";
        temp_int = 0;
    }
    return 0;
}