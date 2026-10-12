# Student Result Management System in C

**First C Programming Learning Project — Anu Mahato**  
B.Sc. Computer Science Student · Salesian College (Autonomous), Siliguri Campus

I built this as a small command-line project to practice the basics of C programming through a student-result example.

## Features

- Add multiple student records (up to 50)
- Store roll number, name, and five subject marks
- Calculate total marks and percentage
- Assign a grade
- Determine PASS / FAIL from subject-wise pass marks
- Search for a student by roll number
- View all result cards
- Show a simple class summary
- Validate numeric input and prevent duplicate roll numbers
- Save records to `students.dat` and load them automatically on the next run

## C Concepts Practiced

- Variables and constants
- `if` / `switch` conditions
- `for` loops
- Arrays
- Strings
- Functions
- Structures (`struct`)
- Pointers and passing structures to functions
- Basic input validation
- File handling with `fopen`, `fread`, `fwrite`, and `fclose`

## Project Note

This is my first C programming project, created as part of my B.Sc. Computer Science learning journey.

The project demonstrates my current practice with core C concepts such as variables, conditions, loops, arrays, strings, functions, pointers, structures, input validation, and file handling.

I am continuing to study, test, explain, and improve the program as my C programming skills develop.

## Data Storage

Student records are saved in a local file named `students.dat` in the program's current working directory. The program attempts to load this file on startup and saves records after a new student is added and when the program exits.

**Important:** Keep `students.dat` in a safe place if the records matter. This is a beginner project, not a production database. The file stores C structure data in a binary format, so it is intended for use with the same program structure/compiler environment. This version supports up to 50 records and does not include editing or deleting records, automatic backups, or protection against disk failure.

## Grading Used in This Project

- A: 90% and above
- B: 80% to 89.99%
- C: 70% to 79.99%
- D: 60% to 69.99%
- E: 50% to 59.99%
- P: 35% to 49.99%
- F: below 35% or any subject below the 35-mark pass level

## Compile and Run

### GCC

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o student_result
./student_result
```

On Windows with MinGW:

```text
gcc -std=c11 -Wall -Wextra -pedantic main.c -o student_result.exe
student_result.exe
```

Run the program from the same folder each time so it can find `students.dat`.

## Example Run

A simple example of the program flow:

```text
Student Result Management System
Loaded 0 student record(s) from students.dat.

Student Result Manager
1. Add student record
2. View all results
3. Search by roll number
4. Show class summary
5. Exit

Choose an option: 1
Roll number: 101
Student name: Sample Student
Enter marks (0-100):
Subject 1: 78
Subject 2: 82
Subject 3: 75
Subject 4: 80
Subject 5: 85
Student record added and saved successfully.
```

The next time the program starts, it will try to load that saved record from `students.dat`.

## Project Structure

```text
student-result-management-c/
├── main.c
├── README.md
├── LICENSE
└── .gitignore
```

## Feedback

Feedback is welcome.

If you find a bug, have a suggestion, or have an idea for improvement, feel free to open an Issue in this repository.

## License

This project is licensed under the MIT License.

You are free to use, copy, modify, merge, publish, distribute, sublicense, and sell copies of the software, subject to the terms of the MIT License. The original copyright notice and license notice must be included in copies or substantial portions of the software.
