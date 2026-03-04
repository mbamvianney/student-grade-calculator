# Student Final Grade Calculator

Systemic Programming (PITs-25-NL-EN) – Spring 2026

## Description
Console application that reads student data (name, surname, homework results, exam result) and calculates final points.
Supports manual input (unknown number of homework marks), random generation, and reading from file.

## Final Points Calculation Formula
Final points = 0.4 × (Average of HW | Median of HW) + 0.6 × Exam

Where:
- HW = homework results
- Exam = exam score
- Homework score is computed using either Average or Median (user choice)

## Features (v0.1)
- Person class
- Rule of Three (copy constructor, assignment operator, destructor)
- std::vector for homework (unknown count)
- Overloaded >> (cin) and << (cout)
- Sorting by name or surname
- Formatted output (2 decimals)
- Read data from Students.txt
