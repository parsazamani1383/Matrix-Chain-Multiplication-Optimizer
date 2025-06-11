# 📦 Matrix Chain Multiplication Optimizer

A C++ project that finds the most efficient way to multiply a sequence of matrices using **Dynamic Programming**. This reduces the total number of scalar multiplications needed, improving performance in large-scale matrix computations.

---

## 📚 Project Overview

Matrix multiplication is associative, meaning the result of multiplying matrices A, B, and C is the same whether we compute (A×B)×C or A×(B×C). However, the **cost** of these operations can differ dramatically.  
This program finds the **optimal parenthesization** that minimizes the number of scalar multiplications.

---

## 🎯 Project Objectives

- Demonstrate dynamic programming through matrix chain multiplication.
- Support both manual and random input of matrix dimensions.
- Visualize the DP computation using cost (`m`) and split (`s`) tables.
- Compute the **Catalan number** to show the number of valid parenthesizations.
- Store results in a formatted `.txt` file.

---

## 📌 Real-World Applications

Matrix Chain Multiplication optimization is critical in:

- **Database query optimizers**
- **Computer graphics & simulations**
- **Scientific computing**
- **Compiler design** (expression evaluation trees)
- **AI & ML models** involving large matrix chains

---

## ✨ Features

| Feature                        | Status |
|-------------------------------|--------|
| Manual or random input mode   | ✅     |
| Validates and stores inputs   | ✅     |
| Matrix chain DP algorithm     | ✅     |
| Optimal parenthesis output    | ✅     |
| Catalan number calculation    | ✅     |
| DP tables (`m` and `s`)       | ✅ (optional) |
| Output to text file           | ✅     |

---

## 🧠 Algorithm Explanation

The algorithm builds two tables:

- `m[i][j]`: minimum number of multiplications needed to compute Ai...Aj
- `s[i][j]`: index `k` where the optimal split occurs between Ai...Aj

### Recurrence relation:

