#include <stdio.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int attendanceCount;
};

struct Student s[100];
int count = 0;

// Add new student
void addStudent() {
    printf("Enter Student ID: ");
    scanf("%d", &s[count].id);
    printf("Enter Student Name: ");
    scanf("%s", s[count].name);
    s[count].attendanceCount = 0;
    count++;
    printf("Student Added Successfully!\n");
}

// Mark attendance
void markAttendance() {
    int id;
    printf("Enter Student ID to mark attendance: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (s[i].id == id) {
            s[i].attendanceCount++;
            printf("Attendance Marked for %s\n", s[i].name);
            return;
        }
    }
    printf("Student Not Found!\n");
}

// View report
void viewReport() {
    printf("\n--- ATTENDANCE REPORT ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Attendance: %d\n",
               s[i].id, s[i].name, s[i].attendanceCount);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Add Student\n");
        printf("2. Mark Attendance\n");
        printf("3. View Attendance Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: markAttendance(); break;
            case 3: viewReport(); break;
            case 4: return 0;
            default: printf("Invalid Choice!\n");
        }
    }
}

