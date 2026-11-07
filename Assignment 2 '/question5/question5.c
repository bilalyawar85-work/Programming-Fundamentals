/*
Programmer : Bilal Yawar
Roll Number : BDS 26K-2523
Date : 11/07/26
Program : Assignment 2 question 5 University Library Management System
*/
#include <stdio.h>
#include <string.h>

#define MAX_BORROW 3
#define STUDENT 1
#define FACULTY 2

// declaring function prototypes //
void displayMenu();
void registerMember(char name[], int *studentID, int *memberType);
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks);
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType);
float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine);
void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver);
int readInteger();

int main()
{
    // initializing the book inventory //
    int bookIDs[4] = {101, 102, 103, 104};
    char bookTitles[4][50] = {"Programming in C", "Data Structures", "Database Systems", "Computer Networks"};
    int availableCopies[4] = {5, 3, 0, 4};
    int totalBooks = 4;

    // initializing the member record variables //
    char name[50] = "";
    int studentID = 0, memberType = 0;
    int borrowedBookIDs[MAX_BORROW];
    int borrowedCount = 0;
    float totalFine = 0, fineAfterWaiver = 0, currentFine;
    int registered = 0;
    int choice;

    // displaying the menu repeatedly until the user chooses exit //
    do
    {
        displayMenu();
        choice = readInteger();

        switch (choice)
        {
        case 1:
            // a new member cannot replace the current member while books are still borrowed //
            if (registered == 1 && borrowedCount > 0)
            {
                printf("Current member still has borrowed books. Return them first.\n");
            }
            else
            {
                registerMember(name, &studentID, &memberType);
                registered = 1;
                borrowedCount = 0;
                totalFine = 0;
                fineAfterWaiver = 0;
                printf("Member registered successfully.\n");
            }
            break;

        case 2:
            displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
            break;

        case 3:
            if (registered == 0)
            {
                printf("Please register a member first (option 1).\n");
            }
            else
            {
                borrowBook(bookIDs, bookTitles, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType);
            }
            break;

        case 4:
            if (registered == 0)
            {
                printf("Please register a member first (option 1).\n");
            }
            else
            {
                currentFine = returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                // adding the fine payable for this return to the final fine //
                fineAfterWaiver = fineAfterWaiver + currentFine;
            }
            break;

        case 5:
            if (registered == 0)
            {
                printf("Please register a member first (option 1).\n");
            }
            else
            {
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
            }
            break;

        case 6:
            printf("Exiting the program. Goodbye!\n");
            break;

        default:
            printf("Invalid menu choice. Please select 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}

// reads an integer safely and asks again if the user types letters or symbols //
int readInteger()
{
    int value;

    while (scanf("%d", &value) != 1)
    {
        // clearing the invalid input from the buffer //
        while (getchar() != '\n')
            ;
        printf("Invalid input. Enter a number: ");
    }

    return value;
}

void displayMenu()
{
    printf("\n===== UNIVERSITY LIBRARY MANAGEMENT SYSTEM =====\n");
    printf("1. Member Registration\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    // taking the name with spaces //
    printf("\nEnter member name: ");
    scanf(" %49[^\n]", name);

    // validating the student ID //
    printf("Enter student ID: ");
    *studentID = readInteger();
    while (*studentID <= 0)
    {
        printf("Student ID must be positive. Enter again: ");
        *studentID = readInteger();
    }

    // validating the membership type //
    do
    {
        printf("Enter membership type (1 = Student, 2 = Faculty): ");
        *memberType = readInteger();

        if (*memberType != STUDENT && *memberType != FACULTY)
        {
            printf("Invalid membership type. Try again.\n");
        }
    } while (*memberType != STUDENT && *memberType != FACULTY);
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks)
{
    int i;
    // displaying all the books in a table //
    printf("\n%-6s %-25s %-8s\n", "ID", "Title", "Copies");
    printf("------------------------------------------\n");

    for (i = 0; i < totalBooks; i++)
    {
        printf("%-6d %-25s %-8d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType)
{
    int id, days, i, index = -1, allowedDays;

    // checking the maximum borrowing limit //
    if (*borrowedCount >= MAX_BORROW)
    {
        printf("Borrowing limit reached. A member can borrow a maximum of %d books.\n", MAX_BORROW);
        return;
    }

    printf("\nEnter book ID to borrow: ");
    id = readInteger();

    // searching for the book ID in the inventory //
    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            index = i;
        }
    }

    if (index == -1)
    {
        printf("Invalid book ID.\n");
        return;
    }

    if (availableCopies[index] <= 0)
    {
        printf("Sorry, no copies of \"%s\" are available.\n", bookTitles[index]);
        return;
    }

    // preventing the same book from being borrowed twice //
    for (i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == id)
        {
            printf("You have already borrowed this book.\n");
            return;
        }
    }

    // validating the number of days //
    printf("Enter number of days you intend to keep the book: ");
    days = readInteger();
    while (days <= 0)
    {
        printf("Days must be positive. Enter again: ");
        days = readInteger();
    }

    // student = 14 days, faculty = 30 days //
    if (memberType == STUDENT)
    {
        allowedDays = 14;
    }
    else
    {
        allowedDays = 30;
    }

    if (days > allowedDays)
    {
        printf("Note: Your permitted period is %d days. Late fine applies after that.\n", allowedDays);
    }

    // recording the borrowed book and decreasing the available copies //
    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[index]--;

    printf("Book \"%s\" borrowed successfully.\n", bookTitles[index]);
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine)
{
    int id, days, i, bookIndex = -1, borrowedIndex = -1, allowedDays, extraDays, finePerDay;
    float lateFine = 0, finePayable = 0;
    char code[20];

    if (*borrowedCount == 0)
    {
        printf("\nYou have not borrowed any books.\n");
        return 0;
    }

    printf("\nEnter book ID to return: ");
    id = readInteger();

    // verifying that the book ID exists in the inventory //
    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            bookIndex = i;
        }
    }

    if (bookIndex == -1)
    {
        printf("Invalid book ID.\n");
        return 0;
    }

    // verifying that the member has borrowed this book //
    for (i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == id)
        {
            borrowedIndex = i;
        }
    }

    if (borrowedIndex == -1)
    {
        printf("You have not borrowed this book.\n");
        return 0;
    }

    // validating the actual number of days //
    printf("Enter actual number of days the book was kept: ");
    days = readInteger();
    while (days <= 0)
    {
        printf("Days must be positive. Enter again: ");
        days = readInteger();
    }

    // setting the allowed days and the fine per day according to the membership type //
    if (memberType == STUDENT)
    {
        allowedDays = 14;
        finePerDay = 20;
    }
    else
    {
        allowedDays = 30;
        finePerDay = 10;
    }

    // increasing the available copies after a valid return //
    availableCopies[bookIndex]++;

    // removing the returned book from the borrowed list by shifting the remaining books //
    for (i = borrowedIndex; i < *borrowedCount - 1; i++)
    {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }
    (*borrowedCount)--;

    // calculating the late fine if the book was kept beyond the permitted period //
    if (days > allowedDays)
    {
        extraDays = days - allowedDays;
        lateFine = (float)(extraDays * finePerDay);
        printf("Book returned %d day(s) late. Late fine: Rs. %.2f\n", extraDays, lateFine);

        // adding to the cumulative fine before waiver //
        *totalFine = *totalFine + lateFine;

        // asking for the membership code to apply the waiver //
        printf("Enter membership code (press any text if you do not have one): ");
        scanf("%19s", code);

        if (strcmp(code, "LIB2026") == 0)
        {
            finePayable = lateFine * 0.5f;
            printf("Correct code! 50%% waiver applied.\n");
        }
        else
        {
            finePayable = lateFine;
            printf("Incorrect code. No waiver applied.\n");
        }

        printf("Fine payable for this return: Rs. %.2f\n", finePayable);
    }
    else
    {
        printf("Book returned on time. No fine.\n");
    }

    return finePayable;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver)
{
    int i;
    // displaying the member information and the current borrowing record //
    printf("\n===== MEMBER RECORD =====\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);

    if (memberType == STUDENT)
    {
        printf("Membership type: Student\n");
    }
    else
    {
        printf("Membership type: Faculty\n");
    }

    printf("Currently borrowed books: ");
    if (borrowedCount == 0)
    {
        printf("None");
    }
    else
    {
        for (i = 0; i < borrowedCount; i++)
        {
            printf("%d ", borrowedBookIDs[i]);
        }
    }
    printf("\n");

    printf("Total fine charged (before waiver): Rs. %.2f\n", totalFine);
    printf("Final fine payable (after waiver): Rs. %.2f\n", fineAfterWaiver);
}