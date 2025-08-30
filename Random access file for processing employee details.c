#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

int main() {
    FILE *filePtr;
    struct Employee emp;

    // Open file in read/write mode; create if it doesn't exist
    filePtr = fopen("employee.dat", "rb+");
    if (filePtr == NULL) {
        filePtr = fopen("employee.dat", "wb+");
        if (filePtr == NULL) {
            printf("Error creating the file.\n");
            return 1;
        }
    }

    int choice;

    do {
        printf("\n--- Employee Database Menu ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp.empId);
                printf("Enter Employee Name: ");
                scanf("%s", emp.empName);
                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);

                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                printf("Employee details added successfully.\n");
                break;

            case 2:
                printf("Enter Employee ID to display: ");
                scanf("%d", &emp.empId);

                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) != 1) {
                    printf("Employee not found.\n");
                } else {
                    printf("\nEmployee ID: %d\n", emp.empId);
                    printf("Employee Name: %s\n", emp.empName);
                    printf("Employee Salary: %.2f\n", emp.empSalary);
                }
                break;

            case 3:
                printf("Enter Employee ID to update: ");
                scanf("%d", &emp.empId);

                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) != 1) {
                    printf("Employee not found.\n");
                } else {
                    printf("Enter new Employee Name: ");
                    scanf("%s", emp.empName);
                    printf("Enter new Employee Salary: ");
                    scanf("%f", &emp.empSalary);

                    fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                    fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                    printf("Employee details updated successfully.\n");
                }
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (choice != 4);

    fclose(filePtr);
    return 0;
}

