#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    double balance;
};

// Function declarations
void addRecord(FILE *fPtr);
void displayAll(FILE *fPtr);
void searchRecord(FILE *fPtr);
void updateRecord(FILE *fPtr);
void deleteRecord(FILE *fPtr);

int main()
{
    FILE *fPtr;
    int choice;

    // Open file
    fPtr = fopen("credit.dat", "rb+");

    if (fPtr == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    do
    {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Add Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Record\n");
        printf("4. Update Record\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addRecord(fPtr);
            break;

        case 2:
            displayAll(fPtr);
            break;

        case 3:
            searchRecord(fPtr);
            break;

        case 4:
            updateRecord(fPtr);
            break;

        case 5:
            deleteRecord(fPtr);
            break;

        case 6:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 6);

    fclose(fPtr);

    return 0;
}

// ================= ADD RECORD =================
void addRecord(FILE *fPtr)
{
    struct clientData c = {0};
    int acc;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    fseek(fPtr, (acc - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&c, sizeof(struct clientData), 1, fPtr);

    if (c.acctNum != 0)
    {
        printf("Account already exists!\n");
    }
    else
    {
        printf("Enter Last Name: ");
        scanf("%s", c.lastName);

        printf("Enter First Name: ");
        scanf("%s", c.firstName);

        printf("Enter Balance: ");
        scanf("%lf", &c.balance);

        c.acctNum = acc;

        fseek(fPtr, (acc - 1) * sizeof(struct clientData), SEEK_SET);
        fwrite(&c, sizeof(struct clientData), 1, fPtr);

        printf("Record Added Successfully!\n");
    }
}

// ================= DISPLAY ALL =================
void displayAll(FILE *fPtr)
{
    struct clientData c;

    rewind(fPtr);

    printf("\n======= ALL RECORDS =======\n");

    printf("%-10s %-15s %-15s %-10s\n",
           "Acc No", "First Name", "Last Name", "Balance");

    while (fread(&c, sizeof(struct clientData), 1, fPtr))
    {
        if (c.acctNum != 0)
        {
            printf("%-10d %-15s %-15s %-10.2lf\n",
                   c.acctNum,
                   c.firstName,
                   c.lastName,
                   c.balance);
        }
    }
}

// ================= SEARCH RECORD =================
void searchRecord(FILE *fPtr)
{
    int acc;
    struct clientData c;

    printf("Enter Account Number to Search: ");
    scanf("%d", &acc);

    fseek(fPtr, (acc - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&c, sizeof(struct clientData), 1, fPtr);

    if (c.acctNum == 0)
    {
        printf("Record Not Found!\n");
    }
    else
    {
        printf("\nRecord Found:\n");

        printf("Account Number : %d\n", c.acctNum);
        printf("First Name     : %s\n", c.firstName);
        printf("Last Name      : %s\n", c.lastName);
        printf("Balance        : %.2lf\n", c.balance);
    }
}

// ================= UPDATE RECORD =================
void updateRecord(FILE *fPtr)
{
    int acc;
    struct clientData c;

    printf("Enter Account Number to Update: ");
    scanf("%d", &acc);

    fseek(fPtr, (acc - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&c, sizeof(struct clientData), 1, fPtr);

    if (c.acctNum == 0)
    {
        printf("Record Not Found!\n");
    }
    else
    {
        printf("\nExisting Balance: %.2lf\n", c.balance);

        printf("Enter New Balance: ");
        scanf("%lf", &c.balance);

        fseek(fPtr, (acc - 1) * sizeof(struct clientData), SEEK_SET);
        fwrite(&c, sizeof(struct clientData), 1, fPtr);

        printf("Record Updated Successfully!\n");
    }
}

// ================= DELETE RECORD =================
void deleteRecord(FILE *fPtr)
{
    int acc;
    struct clientData c;
    struct clientData blank = {0};

    printf("Enter Account Number to Delete: ");
    scanf("%d", &acc);

    fseek(fPtr, (acc - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&c, sizeof(struct clientData), 1, fPtr);

    if (c.acctNum == 0)
    {
        printf("Record Not Found!\n");
    }
    else
    {
        fseek(fPtr, (acc - 1) * sizeof(struct clientData), SEEK_SET);
        fwrite(&blank, sizeof(struct clientData), 1, fPtr);

        printf("Record Deleted Successfully!\n");
    }
}