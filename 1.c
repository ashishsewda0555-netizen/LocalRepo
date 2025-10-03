#include <stdio.h>
#include <string.h>

#define MAX 100   // maximum number of students we can store

/* ---- Student structure ---- */
struct Student {
    char name[50];
    int roll;
    float marks;
};

/* ---- Function prototypes ---- */
void addStudent(struct Student s[], int *n);
void displayAll(struct Student s[], int n);
void findTopper(struct Student s[], int n);
void searchByRoll(struct Student s[], int n, int roll);

/* ---- main ---- */
int main(void) {
    struct Student students[MAX]; // the array that stores all students
    int n = 0;                   // current count of stored students
    int choice;
    int roll;

    while (1) {
        printf("\n--- Student Record System ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Find Topper\n");
        printf("4. Search by Roll\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        /* read menu choice safely */
        if (scanf("%d", &choice) != 1) {
            // clear bad input from buffer
            int c; while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid input. Please enter a number from 1 to 5.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(students, &n);
                break;
            case 2:
                displayAll(students, n);
                break;
            case 3:
                findTopper(students, n);
                break;
            case 4:
                printf("Enter roll number to search: ");
                if (scanf("%d", &roll) != 1) {
                    int c; while ((c = getchar()) != '\n' && c != EOF);
                    printf("Invalid roll number.\n");
                } else {
                    searchByRoll(students, n, roll);
                }
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

/* ---- addStudent ----
   s[] : array of Student structs (same array used in main)
   n   : pointer to the number of stored students (so we can update it here)
*/
void addStudent(struct Student s[], int *n) {
    if (*n >= MAX) {
        printf("Cannot add more students — storage full.\n");
        return;
    }

    /* Read name: the format " %[^\n]" skips any leading whitespace
       and then reads until newline (so name can include spaces). */
    printf("Enter name: ");
    scanf(" %[^\n]", s[*n].name);

    printf("Enter roll number: ");
    scanf("%d", &s[*n].roll);

    printf("Enter marks: ");
    scanf("%f", &s[*n].marks);

    (*n)++;  // increment the count in main (because we received pointer to it)
    printf("Student added. Total students = %d\n", *n);
}

/* ---- displayAll ----
   prints students from index 0 to n-1
*/
void displayAll(struct Student s[], int n) {
    if (n == 0) {
        printf("No students to display.\n");
        return;
    }
    printf("\n--- Student List ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Name: %s | Roll: %d | Marks: %.2f\n", i+1, s[i].name, s[i].roll, s[i].marks);
    }
}

/* ---- findTopper ----
   finds student with maximum marks and prints it
*/
void findTopper(struct Student s[], int n) {
    if (n == 0) {
        printf("No students available.\n");
        return;
    }
    int topperIndex = 0;
    for (int i = 1; i < n; i++) {
        if (s[i].marks > s[topperIndex].marks) {
            topperIndex = i;
        }
    }
    printf("Topper: %s (Roll %d) with %.2f marks\n",
           s[topperIndex].name, s[topperIndex].roll, s[topperIndex].marks);
}

/* ---- searchByRoll ----
   linear search for student with given roll
*/
void searchByRoll(struct Student s[], int n, int roll) {
    for (int i = 0; i < n; i++) {
        if (s[i].roll == roll) {
            printf("Found: Name: %s | Roll: %d | Marks: %.2f\n", s[i].name, s[i].roll, s[i].marks);
            return;
        }
    }
    printf("Student with roll %d not found.\n", roll);
}
