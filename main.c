#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Student Result Management System in C
 * First C programming learning project
 */

#define MAX_STUDENTS 50
#define SUBJECT_COUNT 5
#define PASS_MARK 35
#define DATA_FILE "students.dat"

const char *subjects[SUBJECT_COUNT] = {
    "Subject 1",
    "Subject 2",
    "Subject 3",
    "Subject 4",
    "Subject 5"
};

typedef struct {
    int roll_no;
    char name[60];
    int marks[SUBJECT_COUNT];
} Student;

int read_int(const char *prompt, int min, int max);
void read_name(char name[], size_t size);
int find_student(const Student students[], int count, int roll_no);
int calculate_total(const Student *student);
double calculate_percentage(const Student *student);
int passed_all_subjects(const Student *student);
char grade_for(double percentage, int passed_all);
void print_result(const Student *student);
void add_student(Student students[], int *count);
void show_all(const Student students[], int count);
void search_student(const Student students[], int count);
void show_summary(const Student students[], int count);
void show_menu(void);
int load_students(Student students[], int *count);
int save_students(const Student students[], int count);

int read_int(const char *prompt, int min, int max) {
    char line[100];

    while (1) {
        char *end;
        long value;

        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nInput ended. Exiting.\n");
            exit(EXIT_SUCCESS);
        }

        errno = 0;
        end = NULL;
        value = strtol(line, &end, 10);

        if (end != line && errno != ERANGE) {
            while (*end != '\0' && isspace((unsigned char)*end)) {
                end++;
            }

            if (*end == '\0' && value >= min && value <= max) {
                return (int)value;
            }
        }

        printf("Please enter a number from %d to %d.\n", min, max);
    }
}

void read_name(char name[], size_t size) {
    while (1) {
        printf("Student name: ");

        if (fgets(name, (int)size, stdin) == NULL) {
            printf("\nInput ended. Exiting.\n");
            exit(EXIT_SUCCESS);
        }

        size_t length = strlen(name);
        if (length > 0 && name[length - 1] == '\n') {
            name[length - 1] = '\0';
        } else {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Discard characters beyond the name buffer. */
            }
        }

        if (strlen(name) > 0) {
            return;
        }

        printf("Name cannot be empty.\n");
    }
}

int find_student(const Student students[], int count, int roll_no) {
    for (int i = 0; i < count; i++) {
        if (students[i].roll_no == roll_no) {
            return i;
        }
    }
    return -1;
}

int calculate_total(const Student *student) {
    int total = 0;
    for (int i = 0; i < SUBJECT_COUNT; i++) {
        total += student->marks[i];
    }
    return total;
}

double calculate_percentage(const Student *student) {
    return (calculate_total(student) / (double)(SUBJECT_COUNT * 100)) * 100.0;
}

int passed_all_subjects(const Student *student) {
    for (int i = 0; i < SUBJECT_COUNT; i++) {
        if (student->marks[i] < PASS_MARK) {
            return 0;
        }
    }
    return 1;
}

char grade_for(double percentage, int passed_all) {
    if (!passed_all) return 'F';
    if (percentage >= 90.0) return 'A';
    if (percentage >= 80.0) return 'B';
    if (percentage >= 70.0) return 'C';
    if (percentage >= 60.0) return 'D';
    if (percentage >= 50.0) return 'E';
    return 'P';
}

void print_result(const Student *student) {
    int total = calculate_total(student);
    double percentage = calculate_percentage(student);
    int passed = passed_all_subjects(student);
    char grade = grade_for(percentage, passed);

    printf("\n----------------------------------------\n");
    printf("Roll No : %d\n", student->roll_no);
    printf("Name    : %s\n", student->name);
    printf("----------------------------------------\n");

    for (int i = 0; i < SUBJECT_COUNT; i++) {
        printf("%-10s : %d/100\n", subjects[i], student->marks[i]);
    }

    printf("----------------------------------------\n");
    printf("Total      : %d/%d\n", total, SUBJECT_COUNT * 100);
    printf("Percentage : %.2f%%\n", percentage);
    printf("Grade      : %c\n", grade);
    printf("Result     : %s\n", passed ? "PASS" : "FAIL");
    printf("----------------------------------------\n");
}

void add_student(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Student limit reached.\n");
        return;
    }

    int roll_no = read_int("Roll number: ", 1, 999999);
    if (find_student(students, *count, roll_no) != -1) {
        printf("This roll number is already assigned.\n");
        return;
    }

    Student *student = &students[*count];
    student->roll_no = roll_no;
    read_name(student->name, sizeof(student->name));

    printf("Enter marks (0-100):\n");
    for (int i = 0; i < SUBJECT_COUNT; i++) {
        char prompt[40];
        snprintf(prompt, sizeof(prompt), "%s: ", subjects[i]);
        student->marks[i] = read_int(prompt, 0, 100);
    }

    (*count)++;
    if (save_students(students, *count)) {
        printf("Student record added and saved successfully.\n");
    } else {
        printf("Student record added in memory, but saving failed.\n");
    }
}

void show_all(const Student students[], int count) {
    if (count == 0) {
        printf("No student records have been added yet.\n");
        return;
    }

    printf("\n========== ALL RESULTS ==========\n");
    for (int i = 0; i < count; i++) {
        print_result(&students[i]);
    }
}

void search_student(const Student students[], int count) {
    if (count == 0) {
        printf("No student records have been added yet.\n");
        return;
    }

    int roll_no = read_int("Enter roll number to search: ", 1, 999999);
    int index = find_student(students, count, roll_no);

    if (index == -1) {
        printf("No student matches roll number %d.\n", roll_no);
        return;
    }

    print_result(&students[index]);
}

void show_summary(const Student students[], int count) {
    if (count == 0) {
        printf("No student records have been added yet.\n");
        return;
    }

    int pass_count = 0;
    int fail_count = 0;
    double percentage_sum = 0.0;

    for (int i = 0; i < count; i++) {
        if (passed_all_subjects(&students[i])) {
            pass_count++;
        } else {
            fail_count++;
        }
        percentage_sum += calculate_percentage(&students[i]);
    }

    printf("\n========== CLASS SUMMARY ==========\n");
    printf("Students recorded : %d\n", count);
    printf("Passed            : %d\n", pass_count);
    printf("Failed            : %d\n", fail_count);
    printf("Average percentage: %.2f%%\n", percentage_sum / count);
}

void show_menu(void) {
    printf("\n========================================\n");
    printf("       STUDENT RESULT MANAGER\n");
    printf("========================================\n");
    printf("1. Add student record\n");
    printf("2. View all results\n");
    printf("3. Search by roll number\n");
    printf("4. Show class summary\n");
    printf("5. Exit\n");
    printf("========================================\n");
}

/*
 * Read the data file into a temporary array first. If the file is malformed,
 * keep the application running with an empty in-memory list rather than
 * partially loading records.
 */
int load_students(Student students[], int *count) {
    FILE *file = fopen(DATA_FILE, "rb");
    Student loaded[MAX_STUDENTS];
    size_t records;

    *count = 0;
    if (file == NULL) {
        if (errno == ENOENT) {
            return 1; /* First run: data file does not exist yet. */
        }
        perror("Could not open student data file");
        return 0;
    }

    records = fread(loaded, sizeof(Student), MAX_STUDENTS, file);
    if (ferror(file)) {
        perror("Could not read student data file");
        fclose(file);
        return 0;
    }

    /* A file larger than the supported record count is rejected. */
    if (records == MAX_STUDENTS && fgetc(file) != EOF) {
        fprintf(stderr, "Data file has more than %d records; not loaded.\n",
                MAX_STUDENTS);
        fclose(file);
        return 0;
    }

    /* Detect a trailing partial record instead of silently accepting it. */
    if (records < MAX_STUDENTS && !feof(file)) {
        int extra = fgetc(file);
        if (extra != EOF) {
            fprintf(stderr, "Data file is incomplete or corrupted; not loaded.\n");
            fclose(file);
            return 0;
        }
    }

    if (fclose(file) != 0) {
        perror("Could not close student data file");
        return 0;
    }

    for (size_t i = 0; i < records; i++) {
        if (loaded[i].roll_no < 1 || loaded[i].roll_no > 999999 ||
            memchr(loaded[i].name, '\0', sizeof(loaded[i].name)) == NULL) {
            fprintf(stderr, "Invalid student record in data file; not loaded.\n");
            return 0;
        }

        for (int j = 0; j < SUBJECT_COUNT; j++) {
            if (loaded[i].marks[j] < 0 || loaded[i].marks[j] > 100) {
                fprintf(stderr, "Invalid marks in data file; not loaded.\n");
                return 0;
            }
        }

        for (size_t j = 0; j < i; j++) {
            if (loaded[i].roll_no == loaded[j].roll_no) {
                fprintf(stderr, "Duplicate roll number in data file; not loaded.\n");
                return 0;
            }
        }
    }

    memcpy(students, loaded, records * sizeof(Student));
    *count = (int)records;
    return 1;
}

int save_students(const Student students[], int count) {
    FILE *file = fopen(DATA_FILE, "wb");
    if (file == NULL) {
        perror("Could not save student data");
        return 0;
    }

    if (fwrite(students, sizeof(Student), (size_t)count, file) != (size_t)count) {
        perror("Could not write all student records");
        fclose(file);
        return 0;
    }

    if (fclose(file) != 0) {
        perror("Could not finish saving student data");
        return 0;
    }

    return 1;
}

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    printf("Student Result Management System\n");

    if (load_students(students, &count)) {
        printf("Loaded %d student record(s) from %s.\n", count, DATA_FILE);
    } else {
        printf("Could not load saved records. Starting with an empty list.\n");
    }

    do {
        show_menu();
        choice = read_int("Choose an option: ", 1, 5);

        switch (choice) {
            case 1:
                add_student(students, &count);
                break;
            case 2:
                show_all(students, count);
                break;
            case 3:
                search_student(students, count);
                break;
            case 4:
                show_summary(students, count);
                break;
            case 5:
                if (save_students(students, count)) {
                    printf("Records saved. Goodbye.\n");
                } else {
                    printf("Warning: records could not be saved.\n");
                }
                break;
        }
    } while (choice != 5);

    return 0;
}
