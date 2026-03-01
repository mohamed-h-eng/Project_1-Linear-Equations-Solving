# Linear Equations Solver

A C++ program that solves a system of **n linear equations** with **n unknowns** using **Cramer's Rule** with the **Sarrus diagonal method** for computing determinants.

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

```
3
2x1+3x2+4x3=16
1x1+2x2+1x3=8
3x1+1x2+2x3=13
```

### Equation Format Rules
- Variables are written as `x1`, `x2`, `x3`, etc.
- Coefficients are written immediately before the variable: `2x1`, `3x2`
- Terms are joined by `+` or `-`
- The right-hand side follows `=`
- Example: `2x1+3x2-4x3=10`

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

## Example

**Input:**
```
3
2x1+3x2+4x3=16
1x1+2x2+1x3=8
3x1+1x2+2x3=13
```

**Output:**
```
x1= 3
x2= 2
x3= 1
```

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
| `main` | Reads input, builds matrix, computes and prints solution |

---

## Known Limitations

- **Integer arithmetic only** — all coefficients and results are stored as `int`; fractional answers are truncated (e.g. `2.5` becomes `2`)
- **Implicit coefficients not supported** — `x1` or `-x2` (without explicit `1`) will be parsed as coefficient `0`
- **Single-digit variable indices only** — works for `x1`–`x9`; `x10` and above will mis-parse
- **Sarrus extension hardcoded to 2 columns** — only correct for 3×3 systems; 2×2 and 4×4+ give wrong results
- **No command interface** — only solves and prints; no `equation i`, `add`, `D`, etc.
- **No "No Solution" check** — divides by zero silently if the determinant is 0

---

## Dependencies

- Standard C++ library only (`<iostream>`, `<string>`)
- No external libraries required
