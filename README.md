# Student Result Management System in C

**First C Programming Learning Project — Anu Mahato**  
B.Sc. Computer Science Student · Salesian College (Autonomous), Siliguri Campus

I built this as a small command-line project to practice the basics of C programming through a student-result example.

## Features

- Add multiple student records
- Store roll number, name, and five subject marks
- Calculate total marks and percentage
- Assign a grade
- Determine PASS / FAIL from subject-wise pass marks
- Search for a student by roll number
- View all result cards
- Show a simple class summary
- Validate numeric input and prevent duplicate roll numbers

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

## Project Note

This is my first C programming project, created as part of my B.Sc. Computer Science learning journey.

The project demonstrates my current practice with core C concepts such as variables, conditions, loops, arrays, strings, functions, pointers, and structures.

I am continuing to study, test, explain, and improve the program as my C programming skills develop.

## Important Note

This first version keeps records in memory only. Closing the program clears the data. File storage can be added later as a separate learning step.

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
