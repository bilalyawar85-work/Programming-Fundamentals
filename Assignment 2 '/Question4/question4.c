/*
Programmer : Bilal Yawar
Roll Number : BDS 26K-2523
Date : 10/27/26
Program : Assignment 2 question 4 Festival Sales Analysis
*/
#include <stdio.h>
// declaring function prototypes //
int getValidDays();
float calculateDailySales(int dayNumber);
int findHighestSalesDay(float dailySales[], int numberOfDays);
void displayBarChart(float dailySales[], int numberOfDays);

int main()
{
    float dailySales[7];
    int days, i, highestDay;
    float festivalTotal = 0;
    float highestSales;
// calling the function to get valid number of days //
    days = getValidDays();
// calculating daily sales for each day and storing it in an array //
    for (i = 0; i < days; i++)
    {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal = festivalTotal + dailySales[i];
    }
// finding the day with the highest sales and the corresponding sales amount //
    highestDay = findHighestSalesDay(dailySales, days);
    highestSales = dailySales[highestDay - 1];
//  printing the festival summary and displaying the bar chart //
    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", highestDay);
    printf("Highest daily sales: Rs. %.2f\n", highestSales);
// calling the function to display the bar chart //
    displayBarChart(dailySales, days);

    return 0;
}

int getValidDays()
{
    int days;
// Asking the user for the number of festival days and validating the input //
    do
    {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);

        if (days < 1 || days > 7)
        {
            printf("Invalid input. Try again.\n");
        }
    } while (days < 1 || days > 7);

    return days;
}

float calculateDailySales(int dayNumber)
{
    int orders, i;
    float amount, total = 0, highest = 0, avg;
// Asking the user for the number of orders and validating the input //
    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &orders);

    for (i = 1; i <= orders; i++)
    {
        printf("Enter amount for order %d: ", i);
        scanf("%f", &amount);

        while (amount <= 0)
        {
            printf("Amount must be greater than zero. Enter again: ");
            scanf("%f", &amount);
        }
// calculating the total sales//
        total = total + amount;
// finding the highest order amount for the day//
        if (amount > highest)
        {
            highest = amount;
        }
    }

    avg = total / orders;
// printing the daily sales summary //
    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", avg);
    printf("Highest order: Rs. %.2f\n", highest);

    return total;
}

int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int i, highestDay = 1;
    float max = dailySales[0];
// finding the day with the highest sales by comparing each day's sales with the current maximum//
    for (i = 1; i < numberOfDays; i++)
    {
        if (dailySales[i] > max)
        {
            max = dailySales[i];
            highestDay = i + 1;
        }
    }

    return highestDay;
}

void displayBarChart(float dailySales[], int numberOfDays)
{
    int i, j, stars;
// dispplaying a bar chart representing the daily sales, each sterric represents 100 rs in sales //
    printf("\n===== DAILY SALES BAR CHART =====\n");

    for (i = 0; i < numberOfDays; i++)
    {
        stars = (int)(dailySales[i] / 100);

        printf("Day %d: ", i + 1);
        for (j = 0; j < stars; j++)
        {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}