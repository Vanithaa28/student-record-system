#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Structure Definition ---
struct Student {
    int roll_number;
    char name[50];
    char address[100];
    float marks;
};

// --- Function Prototypes ---
void mainMenu();
void addRecord();
void viewAllRecords();
void searchRecord();
void updateRecord();
void deleteRecord();
void displayRecord(struct Student s);

// --- Main Function ---
int main() {
    system("cls || clear");
    mainMenu();
    return 0;
}

// --- Main Menu Function ---
void mainMenu() {
    int choice;
    do {
        printf("\n\n\t\t===== STUDENT RECORD MANAGEMENT SYSTEM =====\n");
        printf("\t\t------------------------------------------\n");
        printf("\t\t1. Add New Record\n");
        printf("\t\t2. View All Records\n");
        printf("\t\t3. Search Record\n");
        printf("\t\t4. Update Record\n");
        printf("\t\t5. Delete Record\n");
        printf("\t\t0. Exit System\n");
        printf("\t\t------------------------------------------\n");
        printf("\t\tEnter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1: addRecord(); break;
            case 2: viewAllRecords(); break;
            case 3: searchRecord(); break;
            case 4: updateRecord(); break;
            case 5: deleteRecord(); break;
            case 0: printf("\n\t\tExiting the system. Goodbye!\n"); break;
            default: printf("\n\t\tInvalid choice. Please try again.\n");
        }
    } while (choice != 0);
}

// --- Utility Function to Display a Single Record ---
void displayRecord(struct Student s) {
    printf("\n\tRoll Number: %d", s.roll_number);
    printf("\n\tName: %s", s.name);
    printf("\n\tMarks: %.2f", s.marks);
    printf("\n\tAddress: %s", s.address);
    printf("\n\t-------------------------------------\n");
}

// --- 1. Add New Record ---
void addRecord() {
    FILE *fp;
    struct Student s;
    char another = 'y';

    // Open file in append binary mode
    fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("\n\tError opening file for writing!");
        return;
    }

    system("cls || clear");
    printf("\n\t\t===== ADD NEW STUDENT RECORD =====\n");

    while (another == 'y' || another == 'Y') {
        printf("\n\tEnter Roll Number: ");
        scanf("%d", &s.roll_number);
        getchar();

        printf("\tEnter Student Name: ");
        fgets(s.name, 50, stdin);
        s.name[strcspn(s.name, "\n")] = 0; // Remove newline

        printf("\tEnter Marks (0-100): ");
        scanf("%f", &s.marks);
        getchar();

        printf("\tEnter Address: ");
        fgets(s.address, 100, stdin);
        s.address[strcspn(s.address, "\n")] = 0; // Remove newline

        // Write the structure to the file
        fwrite(&s, sizeof(struct Student), 1, fp);

        printf("\n\tRecord added successfully!");
        printf("\n\tDo you want to add another record? (y/n): ");
        scanf(" %c", &another); // Space before %c to skip whitespace/newlines
    }

    fclose(fp);
    printf("\n\tPress Enter to return to main menu...");
    getchar(); // Wait for user
    getchar(); // Wait for user (in case previous scanf left input)
    system("cls || clear");
}

// --- 2. View All Records ---
void viewAllRecords() {
    FILE *fp;
    struct Student s;
    int count = 0;

    // Open file in read binary mode
    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\n\tNo records found! (File not present or error)");
        printf("\n\tPress Enter to return to main menu...");
        getchar();
        return;
    }

    system("cls || clear");
    printf("\n\t\t===== VIEW ALL STUDENT RECORDS =====\n");

    // Read all records until end of file
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        displayRecord(s);
        count++;
    }

    if (count == 0) {
        printf("\n\tNo student records available.\n");
    }

    fclose(fp);
    printf("\n\tTotal Records Found: %d", count);
    printf("\n\tPress Enter to return to main menu...");
    getchar();
    system("cls || clear");
}

// --- 3. Search Record ---
void searchRecord() {
    FILE *fp;
    struct Student s;
    int roll_to_search, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\n\tNo records found! (File not present or error)");
        printf("\n\tPress Enter to return to main menu...");
        getchar();
        return;
    }

    system("cls || clear");
    printf("\n\t\t===== SEARCH STUDENT RECORD =====\n");
    printf("\n\tEnter Roll Number to search: ");
    scanf("%d", &roll_to_search);
    getchar();

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.roll_number == roll_to_search) {
            printf("\n\t*** Record Found ***");
            displayRecord(s);
            found = 1;
            break; // Exit loop once found
        }
    }

    if (!found) {
        printf("\n\tRecord with Roll Number %d not found.", roll_to_search);
    }

    fclose(fp);
    printf("\n\tPress Enter to return to main menu...");
    getchar();
    system("cls || clear");
}

// --- 4. Update Record ---
void updateRecord() {
    FILE *fp, *ft; // fp for students.dat, ft for temp.dat
    struct Student s;
    int roll_to_update, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\n\tNo records to update! (File not present or error)");
        printf("\n\tPress Enter to return to main menu...");
        getchar();
        return;
    }

    ft = fopen("temp.dat", "wb"); // Temporary file for writing updated records
    if (ft == NULL) {
        printf("\n\tError opening temporary file!");
        fclose(fp);
        return;
    }

    system("cls || clear");
    printf("\n\t\t===== UPDATE STUDENT RECORD =====\n");
    printf("\n\tEnter Roll Number to update: ");
    scanf("%d", &roll_to_update);
    getchar();

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.roll_number == roll_to_update) {
            printf("\n\t*** Record Found. Enter new details ***");

            printf("\n\tOld Name: %s", s.name);
            printf("\n\tEnter New Student Name: ");
            fgets(s.name, 50, stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("\n\tOld Marks: %.2f", s.marks);
            printf("\n\tEnter New Marks (0-100): ");
            scanf("%f", &s.marks);
            getchar();

            printf("\n\tOld Address: %s", s.address);
            printf("\n\tEnter New Address: ");
            fgets(s.address, 100, stdin);
            s.address[strcspn(s.address, "\n")] = 0;

            found = 1;
        }
        // Write the (possibly updated) record to the temporary file
        fwrite(&s, sizeof(struct Student), 1, ft);
    }

    fclose(fp);
    fclose(ft);

    if (found) {
        remove("students.dat");        // Delete the original file
        rename("temp.dat", "students.dat"); // Rename the temp file to the original
        printf("\n\tRecord updated successfully!");
    } else {
        remove("temp.dat"); // Delete temp file if no update occurred
        printf("\n\tRecord with Roll Number %d not found.", roll_to_update);
    }

    printf("\n\tPress Enter to return to main menu...");
    getchar();
    system("cls || clear");
}

// --- 5. Delete Record ---
void deleteRecord() {
    FILE *fp, *ft;
    struct Student s;
    int roll_to_delete, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\n\tNo records to delete! (File not present or error)");
        printf("\n\tPress Enter to return to main menu...");
        getchar();
        return;
    }

    ft = fopen("temp.dat", "wb");
    if (ft == NULL) {
        printf("\n\tError opening temporary file!");
        fclose(fp);
        return;
    }

    system("cls || clear");
    printf("\n\t\t===== DELETE STUDENT RECORD =====\n");
    printf("\n\tEnter Roll Number to delete: ");
    scanf("%d", &roll_to_delete);
    getchar();

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.roll_number == roll_to_delete) {
            found = 1;
            // DO NOT write this record to the temp file (this is the delete action)
        } else {
            // Write all other records to the temp file
            fwrite(&s, sizeof(struct Student), 1, ft);
        }
    }

    fclose(fp);
    fclose(ft);

    if (found) {
        remove("students.dat");
        rename("temp.dat", "students.dat");
        printf("\n\tRecord with Roll Number %d deleted successfully!", roll_to_delete);
    } else {
        remove("temp.dat");
        printf("\n\tRecord with Roll Number %d not found.", roll_to_delete);
    }

    printf("\n\tPress Enter to return to main menu...");
    getchar();
    system("cls || clear");
}
