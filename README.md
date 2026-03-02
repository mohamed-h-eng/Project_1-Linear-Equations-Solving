# Linear Equations Solver

A C++ program that solves a system of **n linear equations** with **n unknowns** using **Cramer's Rule** with the **Sarrus diagonal method** for computing determinants. After reading the equations, the program enters an interactive command loop until `exit` is entered.

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
num_vars
D_value
solve
exit
```

### Equation Format Rules
- Variables are written as `x1`, `x2`, `x3`, etc.
- Coefficients are written immediately before the variable: `2x1`, `3x2`
- Terms are joined by `+` or `-`
- The right-hand side follows `=`
- Example: `2x1+3x2-4x3=10`

---

## Command Usage

After the equations are read, the program accepts the following commands:

### Level 1 — Basic Queries

#### `num_vars`
Prints the total number of distinct variables across all equations.
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

#### `add i j`
Adds equation `i` and equation `j` together and prints the resulting equation.
```
Input:  add 1 3
Output: 4x1+4x2+6x3+x4=29
```

#### `subtract i j`
Subtracts equation `j` from equation `i` and prints the resulting equation.
```
Input:  subtract 3 1
Output: 2x1-1x2+1x3+x4=5
```

#### `substitute xk i j`
Removes variable `xk` from equation `i` by substituting equation `j` in its place, then prints the result.
```
Input:  substitute x2 1 3
Output: <result equation with x2 eliminated>
```

---

### Level 3 — Cramer's Rule

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
Prints the Cramer matrix with the RHS constants substituted into the column of variable `xi`.
```
Input:  D x2
Output:
2 16 4
1 8  1
3 13 2
```

#### `D_value`
Prints the determinant of the coefficient matrix.
```
Input:  D_value
Output: -11
```

#### `solve`
Computes and prints the value of each variable using Cramer's Rule. Prints `No Solution` if the determinant is 0.
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
- **`get_cooff`** — walks the LHS string, reads coefficients before each `x`, and stores them in the coefficient matrix `matrix[][]`

### Step 2 — Cramer's Rule

For a system `Ax = b`, Cramer's Rule gives:

```
xi = det(Ai) / det(A)
```

Where `Ai` is the matrix `A` with column `i` replaced by the constants vector `b`.

### Step 3 — Determinant via Sarrus' Rule
The matrix is extended by appending its first `n-1` columns to the right (`extend_matrix`). Then:

- **`get_positive_multiply`** — sums the products along the main diagonals (top-left → bottom-right)
- **`get_negative_multiply`** — subtracts the products along the anti-diagonals (top-right → bottom-left)

The determinant = positive diagonals sum + negative diagonals sum.

---

## Code Structure

| Function | Purpose |
|---|---|
| `get_left_side` | Extracts the LHS of an equation string |
| `get_right_side` | Extracts the RHS constant and stores it |
| `get_cooff` | Parses coefficients from LHS into the matrix |
| `parse_equation` | Calls the three functions above for one equation |
| `extend_matrix` | Appends first 2 columns to matrix for Sarrus |
| `get_d_x` | Replaces column `i` with constants for Cramer's Dx |
| `get_positive_multiply` | Computes sum of positive Sarrus diagonals |
| `get_negative_multiply` | Computes sum of negative Sarrus diagonals |
| `get_equation` | Parses equation index from command string (unused) |
| `parse_command` | Extracts integer argument from a command string |
| `solve` | Runs Cramer's Rule for one variable |
| `show_matrix` | Prints the n×n matrix to stdout |
| `show_d_x` | Prints the Cramer matrix for variable `i` |
| `main` | Reads input, builds matrix, runs command loop |

---

## Known Limitations

- **Integer arithmetic only** — all coefficients and results are stored as `int`; fractional answers are truncated (e.g. `2.5` becomes `2`)
- **Implicit coefficients not supported** — `x1` or `-x2` (without explicit `1`) will be parsed as coefficient `0`
- **Single-digit variable indices only** — works for `x1`–`x9`; `x10` and above will mis-parse

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
