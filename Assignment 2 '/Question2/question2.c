#include <stdio.h>

// creating a function to return the sum of the proper divisors of a number "x" //
int sum_of_proper_divisors(int x)
{
    if(x<=0)
    return 0;

    int sum = 1;
    for(int i = 2; i*i <= x; i++)
    {
        if(x % i == 0)
        {
            sum += i;
            if(sum != x / i)
            sum += x / i;
        }
    }
    return sum;
}
int main()
{
 int n, count = 0;
//Taking Input n //
printf("Enter n : \n");
scanf("%d", &n);
printf("Amicable Pairs upto %d are : \n", n);
for(int i = 2; i <= n; i++)
{
    int j = sum_of_proper_divisors(i);
    if(j > i && j <= n && sum_of_proper_divisors(j) == i)
    {
        printf("(%d, %d)\n", i, j);
        count++;
    }
}
    if(count == 0)
    {
        printf("No amicable pairs found up to %d.\n", n);
    }
else
    {
        printf("Total amicable pairs found: %d\n", count);
    }


	return 0;
}
