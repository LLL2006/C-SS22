#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} Account;

int loadAccounts(Account accounts[]) {
    FILE *file = fopen("accounts.txt", "rb");
    if (!file) {
        return 0;
    }
    int count = fread(accounts, sizeof(Account), 100, file);
    fclose(file);
    return count;
}

void saveAccounts(Account accounts[], int count) {
    FILE *file = fopen("accounts.txt", "wb");
    if (!file) {
        printf("Khong the mo file da luu du lieu!\n");
        return;
    }
    fwrite(accounts, sizeof(Account), count, file);
    fclose(file);
}

int isAccountExist(Account accounts[], int count, const char *username) {
    for (int i = 0; i < count; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1;
        }
    }
    return 0; 
}

void registerAccount(Account accounts[], int *count) {
    if (*count >= 100) {
        printf("So luong tai khoan da dat gioi han!\n");
        return;
    }

    Account newAccount;
    char confirmPassword[50];
    
    printf("Nhap tai khoan: ");
    scanf("%s", newAccount.username);

    if (isAccountExist(accounts, *count, newAccount.username)) {
        printf("Vui long thu lai.\n");
        return;
    }

    printf("Nhap mat khau: ");
    scanf("%s", newAccount.password);

    printf("Xac nhan mat khau: ");
    scanf("%s", confirmPassword);

    if (strcmp(newAccount.password, confirmPassword) != 0) {
        printf("Vui long thu lai.\n");
        return;
    }

    accounts[*count] = newAccount;
    (*count)++;
    saveAccounts(accounts, *count);

    printf("Ðang ky tai khoan thanh cong!\n");
}

void login(Account accounts[], int count) {
    char username[50], password[50];

    printf("Nhap tai khoan: ");
    scanf("%s", username);
    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < count; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("Ðang nhap thanh cong\n", username);
            return;
        }
    }

    printf("Ðang nhap that bai! Tai khoan hoac mat khau khong chinh xac.\n");
}

int main() {
    Account accounts[100];
    int count = loadAccounts(accounts);
    int choice;

    do {
    printf("\nMENU\n");
    printf("1. Dang nhap\n");
    printf("2. Dang ky\n");
    printf("3. Thoat\n");
    printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login(accounts, count);
                break;
            case 2:
                registerAccount(accounts, &count);
                break;
            case 3:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Vui long thu lai.\n");
        }
    } while (choice != 3);

    return 0;
}

