# Student Final Grade Calculator (v0.1)

Systemic Programming (PITs-25-NL-EN) – Spring 2026

## Final Points Calculation Formula
Final points = 0.4 × (Average of HW | Median of HW) + 0.6 × Exam

## What this project does
- Reads student records from a text file (supports the provided Lithuanian header format: `Vardas Pavarde ND1.. Egz.`)
- Stores homework marks in `std::vector<int>`
- Calculates final grade by **Average** and **Median**
- Sorts students by **Name** or **Surname**
- Prints a nicely formatted table with 2 decimal places

## How to run
### Compile
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -o app main.cpp
```

### Run
By default it tries `Students.txt` in the same folder:
```bash
./app
```

Or pass a file path:
```bash
./app students10000.txt
```

You can also choose sorting:
```bash
./app students10000.txt surname
```
Allowed sort modes: `name` or `surname`
