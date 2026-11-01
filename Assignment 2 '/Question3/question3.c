/*
Programmer : Bilal Yawar
Roll Number : BDS 26K-2523
Date : 10/27/26
Program : Assignment 2 question 3 Temperature Analysis
*/
#include<stdio.h>
// Takes input of every temperature and stores it in a 2D array//
void readings(int sensors, int hours, int temp[sensors][hours])
{
    for(int i = 0; i < sensors; i++)
    {
        printf("Enter %d readings for sensor %d:\n", hours, i + 1);
        for(int j = 0; j < hours; j++)
        {
            scanf("%d", &temp[i][j]);
        }
    }
}
void analyze_sensor(int readings[], int hours, int *total, double *average, int *max, int *min, int *critical, int *warning, int *streak)

{
    *total = 0;
    *max = readings[0];
    *min = readings[0];
    *critical = 0;
    *warning = 0;
    *streak = 0;
    int current_streak = 0;

    for(int i = 0; i < hours; i++)
    {
        int j = readings[i];
        *total +=j;

        if(j > *max)
            *max = j;
        if(j < *min)
            *min = j;

if(j>=40)
{
    (*critical)++;
}
else if(j>=35)
{
    (*warning)++;
}
if(j>=35)
{
    current_streak++;
    if(current_streak > *streak)
        *streak = current_streak;
        
}
else
current_streak = 0;

}
*average = (double)(*total) / hours;
}
// Returns the sensor with the highest average temperature //
int highest_average_sensor(int sensors, double avg[])
{
    int best = 0;
    for(int i = 1; i < sensors; i++)
    if (avg[i] > avg[best])
        best = i;
        return best + 1;

}
int main()
{
    int sensors, hours;
    printf("Enter the number of sensors: ");
    scanf("%d", &sensors);
    printf("Enter the number of hours: ");
    scanf("%d", &hours);

    int temp[sensors][hours];
    readings(sensors, hours, temp);

    double avg[sensors];
    int total[sensors], max[sensors], min[sensors], critical[sensors], warning[sensors], streak[sensors];

    for(int i = 0; i < sensors; i++)
    {
        analyze_sensor(temp[i], hours, &total[i], &avg[i], &max[i], &min[i], &critical[i], &warning[i], &streak[i]);
        printf("\nSensor %d:\n", i + 1);
        printf("Total: %d\n", total[i]);
        printf("Average: %.2f\n", avg[i]);
        printf("Max: %d\n", max[i]);
        printf("Min: %d\n", min[i]);
        printf("Critical readings: %d\n", critical[i]);
        printf("Warning readings: %d\n", warning[i]);
        printf("Longest streak of readings >= 35°C: %d\n", streak[i]);
    }

    int best_sensor = highest_average_sensor(sensors, avg);
    printf("\nSensor with the highest average temperature: Sensor %d\n", best_sensor);

    return 0;
}