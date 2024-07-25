#include <main_header.h>


// parsed value from argv individual char to write() is an issue.
// convert character into int.  
// != itoa 
// take a buffer and convert it into a value 
int my_ctoi(char *str, size_t n)
{
    int num = 0;
    int mult = 1;
    n =(int)n < 0 ? -n : n; // check abs val
    //for every value in array
    while (n--)
    {
        if ((str[n] < '0' || str[n]> '9') && str[n] != '-')
        { //check for int or '-'
            if(num)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        if (str[n] == '-')
        { // if '-' negate
            if (num)
            {
                num = -num;
                break;
            }
        }
        else
        {
            num += (str[n]- '0')*mult; // convert to numeric value
            mult *=10;

        }
    }
    return num;
}