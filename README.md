# Linear Equations Solver

A C++ program that solves a system of **n linear equations** with **n unknowns** using **Gaussian Elimination**. After reading the equations, the program enters an interactive command loop until `exit` is entered.

---

## How to Compile & Run

```bash
g++ -o solver main.cpp
./solver
```

---

## Input Format

The program reads from **standard input** (no prompts).

1. First line: integer `n` — the number of equations (and variables)
2. Next `n` lines: one equation per line
3. Then commands, one per line, until `exit`

```
3
2x1+3x2+4x3=16
1x1+2x2+1x3=8
3x1+1x2+2x3=13
```

### Equation Format Rules
- Variables are written as `x1`, `x2`, `x3`, etc. — any number of digits supported (`x1`, `x10`, `x100`)
- Coefficients are written immediately before the variable: `2x1`, `3x2`
- Implicit coefficients are supported: `x1` and `+x1` parse as `1`, `-x1` parses as `-1`
- Terms are joined by `+` or `-`
- The right-hand side follows `=`
- Examples: `2x1+3x2-4x3=10`, `x1-x2+x3=2`, `-x1+2x2+x3=4`

---

## Command Usage

After the equations are read, the program accepts the following commands:

### Level 1 — Basic Queries

#### `num_vars`
Prints the total number of variables.
```
Input:  num_vars
Output: 3
```

#### `equation ni`
Prints the equation at position `i` (1-based index) in its stored form.
```
Input:  equation n2
Output: 1x1+2x2+1x3=8
```

#### `column xi`
Prints the coefficient of variable `xi` from each equation, one value per line.
```
Input:  column x2
Output:
3
2
1
```

---

### Level 2 — Equation Arithmetic

#### `subtract i j`
Subtracts equation `j` from equation `i` and prints the resulting equation.
```
Input:  subtract 3 1
Output: 1x1-2x2-2x3=-3
```

#### `substitute xk i j`
Removes variable `xk` from equation `i` by substituting equation `j` in its place, then prints the result.
```
Input:  substitute x2 1 3
Output: -7x1-2x3=-23
```

---

### Level 3 — Matrix & Determinant

#### `D`
Prints the full n×n coefficient matrix, one row per line, values space-separated.
```
Input:  D
Output:
2 3 4
1 2 1
3 1 2
```

#### `D xi`
Prints the matrix with the RHS constants substituted into the column of variable `xi`.
```
Input:  D x2
Output:
2 16 4
1  8 1
3 13 2
```

#### `D_value`
Prints the determinant of the coefficient matrix, computed via Gaussian elimination.
```
Input:  D_value
Output: -11
```

#### `solve`
Solves the system using Gaussian elimination with back-substitution and prints each variable. Prints `No solution` if the determinant is 0.
```
Input:  solve
Output:
x1=3
x2=2
x3=1
```

---

### Program Control

#### `exit`
Terminates the command loop and ends the program.
```
Input:  exit
Output: end program
```

---

## Full Session Example

```
3
2x1+3x2+4x3=16
1x1+2x2+1x3=8
3x1+1x2+2x3=13
num_vars
3
D
2 3 4
1 2 1
3 1 2
D_value
-11
solve
x1=3
x2=2
x3=1
exit
end program
```

---

## How It Works

### Step 1 — Parsing
Each equation string is split at `=` into a left-hand side and a right-hand side.

- **`get_left_side`** — extracts the LHS string (everything before `=`)
- **`get_right_side`** — extracts the RHS value and stores it in `matrix_const[]`
- **`get_cooff`** — walks the LHS string, reads the coefficient string before each `x`, handles implicit coefficients (`x`, `+x` → 1, `-x` → -1), skips all digits of the variable index, and stores the result in `matrix[][]`

### Step 2 — Determinant via Gaussian Elimination
`gaussian_det` makes a float working copy of the matrix and performs forward elimination with partial pivoting. At each column it finds the first non-zero row, swaps it to the diagonal (flipping the sign of the determinant), multiplies the running determinant by the diagonal value, then eliminates all rows below. The final determinant is the accumulated product. Works for any n×n matrix.

### Step 3 — Solving via Gaussian Elimination
`solve` builds an augmented matrix `[A|b]` and performs the same forward elimination. It then back-substitutes from the last row upward — each row uses the already-known variables below it to isolate the next unknown.

---

## Code Structure

| Function | Purpose |
|---|---|
| `get_left_side` | Extracts the LHS of an equation string |
| `get_right_side` | Extracts the RHS constant and stores it |
| `get_cooff` | Parses coefficients from LHS into the matrix, handles implicit coefficients and multi-digit indices |
| `parse_equation` | Calls the three functions above for one equation |
| `extend_matrix` | Copies matrix into `matrix_ext` for use by `show_d_x` |
| `get_d_x` | Replaces column `i` with constants for the `D xi` command |
| `gaussian_det` | Computes the determinant via Gaussian elimination with partial pivoting |
| `solve` | Solves the system via Gaussian elimination and back-substitution |
| `show_matrix` | Prints the n×n matrix to stdout |
| `show_d_x` | Prints the substituted matrix for the `D xi` command |
| `parse_command` | Extracts the value after the last occurrence of a stop character |
| `parse_command_first` | Extracts the value between the first and second occurrence of a stop character |
| `show_column_x` | Prints one column of the coefficient matrix |
| `subtract` | Subtracts one equation from another and prints the result |
| `substitute_variable` | Eliminates a variable from one equation using another and prints the result |
| `get_equation` | Helper to extract equation index from a command string (defined but unused) |
| `main` | Reads input, builds matrix, computes determinant, runs command loop |

---

## Known Limitations

- **Integer coefficients only** — all coefficients and RHS constants are stored as `int`; fractional inputs will be truncated on read. Solution values are computed and printed as `float`.

---

## Dependencies

- Standard C++ library only (`<iostream>`, `<string>`)
- No external libraries required

---

## Credits

| Name | Email |
|---|---|
| Mohamed Hany Mohamed | mohamedhany1615@gmail.com |
| Yahia Ahmed Mohamed | y.ahmed0112000@gmail.com |
| Mohamed Khaled Farouq | itsmebazooka@gmail.com |
| Shrouk Mohamed Sayed | shrouk26529@gmail.com |
| Hanem Atef Elsayed | hanematef111@gmail.com |

**Course:** Data Structures & Algorithms — Faculty of Engineering, Computer Science Department  
**Academic Year:** 2025 / 2026