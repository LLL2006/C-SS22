#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Student;

int loadStudents(Student students[]) {
    FILE *file = fopen("students.txt", "rb");
    if (!file) {
        return 0;
    }
    int n = fread(students, sizeof(Student), 100, file);
    fclose(file);
    return n;
}

void saveStudents(Student students[], int n) {
    FILE *file = fopen("students.txt", "wb");
    if (!file) {
        printf("Khong the mo file da ghi du lieu!\n");
        return;
    }
    fwrite(students, sizeof(Student), n, file);
    fclose(file);
}

void displayStudents(Student students[], int n) {
    if (n == 0) {
        printf("Danh sach sinh viên rong!\n");
        return;
    }
    printf("\nDanh sach sinh vien:\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
    }
}

void addStudent(Student students[], int *n) {
    if (*n >= 100) {
        printf("Danh sach da day!\n");
        return;
    }
    Student newStudent;
    printf("Nhap ID: ");
    scanf("%d", &newStudent.id);
    getchar();
    printf("Nhap ten: ");
    fgets(newStudent.name, 50, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    printf("Nhap tuoi: ");
    scanf("%d", &newStudent.age);

    students[*n] = newStudent;
    (*n)++;
    saveStudents(students, *n);
}

void editStudent(Student students[], int n) {
    int id, found = 0;
    printf("Nhap ID sinh viên can sua: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("Nhap ten moi: ");
            getchar();
            fgets(students[i].name, 50, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;
            printf("Nhap tuoi moi: ");
            scanf("%d", &students[i].age);

            saveStudents(students, n);
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien voi ID: %d\n", id);
    }
}

void deleteStudent(Student students[], int *n) {
    int id, found = 0;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < *n; i++) {
        if (students[i].id == id) {
            found = 1;
            for (int j = i; j < *n - 1; j++) {
                students[j] = students[j + 1];
            }
            (*n)--;
            saveStudents(students, *n);
            break;
        }
    }
    if (!found) {
        printf("Khpng tim thay sinh vien voi ID: %d\n", id);
    }
}

void searchStudent(Student students[], int n) {
    int id, found = 0;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("Tim thay sinh vien: ID: %d, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien voi ID: %d\n", id);
    }
}

void sortStudents(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (students[i].id > students[j].id) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveStudents(students, n);
    printf("Danh sach sinh vien da duoc sap xep theo ID.\n");
}

int main() {
    Student students[100];
    int n = loadStudents(students);
    int choice;

    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayStudents(students, n);
                break;
            case 2:
                addStudent(students, &n);
                break;
            case 3:
                editStudent(students, n);
                break;
            case 4:
                deleteStudent(students, &n);
                break;
            case 5:
                searchStudent(students, n);
                break;
            case 6:
                sortStudents(students, n);
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Vui long chon lai.\n");
        }
    } while (choice != 7);
    return 0;
}
