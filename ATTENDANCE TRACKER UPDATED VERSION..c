/* attendance_tracker.c
   Attendance Tracker System
   - Linked list of students
   - Persistent storage (students.dat)
   - Mark attendance once per day (uses system date)
   - Export CSV report
   Compile: gcc -o attendance_tracker attendance_tracker.c
   Run: ./attendance_tracker
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_FILE "students.dat"
#define CSV_FILE "attendance_report.csv"
#define NAME_LEN 50
#define DATE_LEN 11  // "YYYY-MM-DD" + '\0'

// Student record
typedef struct Student {
    int id;
    char name[NAME_LEN];
    int attendanceCount;
    char lastMarkedDate[DATE_LEN]; // YYYY-MM-DD of last attendance marking
} Student;

// Linked list node
typedef struct Node {
    Student data;
    struct Node *next;
} Node;

Node *head = NULL;

/* ---------- Utility functions ---------- */

// Get today's date string "YYYY-MM-DD"
void get_today(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, DATE_LEN, "%04d-%02d-%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
}

// Create a new node
Node* create_node(int id, const char *name) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    n->data.id = id;
    strncpy(n->data.name, name, NAME_LEN-1);
    n->data.name[NAME_LEN-1] = '\0';
    n->data.attendanceCount = 0;
    n->data.lastMarkedDate[0] = '\0';
    n->next = NULL;
    return n;
}

// Find node by ID
Node* find_node(int id) {
    Node *cur = head;
    while (cur) {
        if (cur->data.id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

// Clear newline from fgets input
void strip_newline(char *s) {
    char *p = strchr(s, '\n');
    if (p) *p = '\0';
}

/* ---------- File I/O ---------- */

// Load students from DATA_FILE into linked list
void load_from_file() {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) {
        // File may not exist first time — that's okay
        return;
    }
    Student temp;
    while (fread(&temp, sizeof(Student), 1, fp) == 1) {
        Node *n = create_node(temp.id, temp.name);
        n->data.attendanceCount = temp.attendanceCount;
        strncpy(n->data.lastMarkedDate, temp.lastMarkedDate, DATE_LEN);
        // append to list
        n->next = head;
        head = n;
    }
    fclose(fp);
}

// Save current linked list to DATA_FILE (overwrite)
void save_to_file() {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (!fp) {
        perror("fopen for write");
        return;
    }
    Node *cur = head;
    while (cur) {
        fwrite(&cur->data, sizeof(Student), 1, fp);
        cur = cur->next;
    }
    fclose(fp);
}

/* ---------- Core operations ---------- */

// Add a new student (fail if ID exists)
void add_student() {
    int id;
    char name[NAME_LEN];

    printf("Enter Student ID (integer): ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n'); // clear

    if (find_node(id)) {
        printf("Student with ID %d already exists.\n", id);
        return;
    }

    printf("Enter Student Name: ");
    if (!fgets(name, NAME_LEN, stdin)) return;
    strip_newline(name);

    Node *n = create_node(id, name);
    n->next = head;
    head = n;
    printf("Student added: %d | %s\n", id, name);
}

// Delete student by ID
void delete_student() {
    int id;
    printf("Enter Student ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Node *cur = head, *prev = NULL;
    while (cur) {
        if (cur->data.id == id) {
            if (prev) prev->next = cur->next;
            else head = cur->next;
            printf("Deleted student: %d | %s\n", cur->data.id, cur->data.name);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("Student with ID %d not found.\n", id);
}

// Mark attendance by ID — only once per day
void mark_attendance() {
    int id;
    char today[DATE_LEN];
    get_today(today);

    printf("Enter Student ID to mark attendance: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Node *n = find_node(id);
    if (!n) {
        printf("Student Not Found!\n");
        return;
    }

    if (strcmp(n->data.lastMarkedDate, today) == 0) {
        printf("Attendance already marked today for %s (ID %d).\n", n->data.name, id);
    } else {
        n->data.attendanceCount += 1;
        strncpy(n->data.lastMarkedDate, today, DATE_LEN-1);
        n->data.lastMarkedDate[DATE_LEN-1] = '\0';
        printf("Attendance marked for %s (ID %d). Total: %d\n",
               n->data.name, id, n->data.attendanceCount);
    }
}

// View attendance report (list all students)
void view_report() {
    if (!head) {
        printf("No students found.\n");
        return;
    }
    printf("\n--- ATTENDANCE REPORT ---\n");
    printf("%-8s %-30s %-10s %-12s\n", "ID", "Name", "Count", "Last Date");
    printf("--------------------------------------------------------------\n");
    Node *cur = head;
    // Print in sorted order by ID for readability: collect to array then sort (optional)
    // For simplicity, iterate and print
    while (cur) {
        printf("%-8d %-30s %-10d %-12s\n",
               cur->data.id,
               cur->data.name,
               cur->data.attendanceCount,
               cur->data.lastMarkedDate[0] ? cur->data.lastMarkedDate : "N/A");
        cur = cur->next;
    }
    printf("--------------------------------------------------------------\n\n");
}

// Search student by ID and display details
void search_student() {
    int id;
    printf("Enter Student ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Node *n = find_node(id);
    if (!n) {
        printf("Student not found.\n");
    } else {
        printf("ID: %d\nName: %s\nAttendance Count: %d\nLast Marked Date: %s\n",
               n->data.id,
               n->data.name,
               n->data.attendanceCount,
               n->data.lastMarkedDate[0] ? n->data.lastMarkedDate : "N/A");
    }
}

// Export CSV
void export_csv() {
    FILE *fp = fopen(CSV_FILE, "w");
    if (!fp) {
        perror("fopen CSV");
        return;
    }
    fprintf(fp, "ID,Name,AttendanceCount,LastMarkedDate\n");
    Node *cur = head;
    while (cur) {
        // Escape commas in name if any (simple approach)
        fprintf(fp, "%d,\"%s\",%d,%s\n",
                cur->data.id,
                cur->data.name,
                cur->data.attendanceCount,
                cur->data.lastMarkedDate[0] ? cur->data.lastMarkedDate : "");
        cur = cur->next;
    }
    fclose(fp);
    printf("Exported CSV to %s\n", CSV_FILE);
}

/* ---------- Menu & main ---------- */

void print_menu() {
    printf("\n======= Attendance Tracker =======\n");
    printf("1. Add Student\n");
    printf("2. Delete Student\n");
    printf("3. Mark Attendance (by ID)\n");
    printf("4. View Attendance Report\n");
    printf("5. Search Student (by ID)\n");
    printf("6. Export Report to CSV\n");
    printf("7. Save & Exit\n");
    printf("Enter choice: ");
}

int main() {
    load_from_file();
    printf("Attendance Tracker loaded. (%s)\n", DATA_FILE);

    int choice;
    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); // consume newline

        switch (choice) {
            case 1: add_student(); break;
            case 2: delete_student(); break;
            case 3: mark_attendance(); break;
            case 4: view_report(); break;
            case 5: search_student(); break;
            case 6: export_csv(); break;
            case 7:
                save_to_file();
                printf("Data saved to %s. Exiting.\n", DATA_FILE);
                // free memory
                while (head) {
                    Node *t = head;
                    head = head->next;
                    free(t);
                }
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

