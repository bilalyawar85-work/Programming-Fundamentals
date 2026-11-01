/*
** PROGRAMMER NAME : SHAIKH BILAL YAWAR **
** DATE : 10/27/26                      **
** CODE : ASSIGNMENT 2 QUESTION 1 CINEMA SEATING ARRANGEMENT **
*/
#include<stdio.h>
int main()
{
// taking number of rows as input and seats in each row// 
    int rows, seats, k;
     printf("Enter number of rows: ");
scanf("%d", &rows);

printf("Enter number of seats per row: ");
scanf("%d", &seats);
printf("Enter the number of customers : \n");
scanf("%d", &k);
// This condition breaks the program if the number of customers is less than or equal to 0 or greater than the number of seats in a row//
if(k <= 0 || k > seats)
{
    printf("Invalid group size!\n");
    return 0;
}

    // to find out if the seat is available or no , 0 = available, 1 = not available//
    int status[rows][seats];
    printf("Enter the status of each seat (0 for available, 1 for not available):\n");
    // taking the status of each seat as input from the user//
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<seats; j++)
        {
            printf("Row %d, Seat %d: ", i, j);
            scanf("%d", &status[i][j]);
        }
    }
    // printing the seating arrangement in a tabular format//
printf("\nSeating Arrangement:\n");
printf("     ");

for(int j = 0; j < seats; j++)
{
    printf("%d ", j);
}
printf("\n");

for(int i = 0; i < rows; i++)
{
    printf("Row %d: ", i);

    for(int j = 0; j < seats; j++)
    {
        if(status[i][j] == 0)
        {
            printf("_ ");
        }
        else
        {
            printf("X ");
        }
    }
    printf("\n");
}


printf("\nAvailable Seats:\n");
int available;
int total = 0;

for(int i = 0; i < rows; i++)
{
    available = 0;

    for(int j = 0; j < seats; j++)
    {
        if(status[i][j] == 0)
        {
            available++;
            total++;
        }
    }

    printf("Row %d: %d available seats\n", i, available);
}

printf("Total available seats: %d\n", total);
// finding the middle row and searching for k consecutive available seats in the middle row and then searching in the rows above and below it//
int middle = rows / 2;
int found = 0;
int bookedRow = -1;
int startSeat = -1;

for(int distance = 0; distance < rows && found == 0; distance++)
{
    int row1 = middle - distance;
    int row2 = middle + distance;

    for(int r = 0; r < 2 && found == 0; r++)
    {
        int currentRow;

        if(r == 0)
            currentRow = row1;
        else
            currentRow = row2;

        if(currentRow < 0 || currentRow >= rows)
            continue;

        if(r == 1 && distance == 0)
            continue;

        int count = 0;

        for(int j = 0; j < seats; j++)
        {
            if(status[currentRow][j] == 0)
                count++;
            else
                count = 0;

            if(count == k)
            {
                bookedRow = currentRow;
                startSeat = j - k + 1;
                found = 1;
                break;
            }
        }
    }
}
if(found == 1)
{
    printf("\nBooking successful!\n");
    printf("Allocated row: %d\n", bookedRow);
    printf("Allocated seats: ");

    for(int j = startSeat; j < startSeat + k; j++)
    {
        printf("%d ", j);
        status[bookedRow][j] = 1;
    }

    printf("\n\nUpdated Seating Arrangement:\n");

    for(int j = 0; j < seats; j++)
        printf("%d ", j);

    printf("\n");

    for(int i = 0; i < rows; i++)
    {
        printf("Row %d: ", i);

        for(int j = 0; j < seats; j++)
        {
            if(status[i][j] == 0)
                printf("_ ");
            else
                printf("X ");
        }

        printf("\n");
    }

    total = 0;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < seats; j++)
        {
            if(status[i][j] == 0)
                total++;
        }
    }

    printf("Remaining available seats: %d\n", total);
}
else
{
    printf("\nBooking unsuccessful! No consecutive seats available.\n");
}


}