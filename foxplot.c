# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

const int len_alphabet = 26;
char* alphabet = "abcdefghijklmnopqrstuvwxyz";

/* Initialise arrays to all 0 */
int counts[26] = {};
float proportions[26] = {};
int rounded_proportions[26] = {};

//char* histogram[];

void update_counts(int counts[], int i)
{
    counts[i] += 1;
}

void print_counts(int counts[])
{
    for (int i = 0; i < len_alphabet; i++)
    {
        printf("Character %c has count %d \n", alphabet[i], counts[i]);
    }
}

int compare_chars(char c, char* alphabet)
{
    for (int i = 0; alphabet[i]; i++)
    {
        /* printf("Alphabet[i] is: %c \n", alphabet[i]); */
        if (c == alphabet[i])
        {
            /*printf("Character %c is in alphabet \n", c);*/
            update_counts(counts, i);
            return 1;
        }
        /*printf("Character %c is not in alphabet \n", c);*/
    }
    return 0;
}

void calculate_proportions(int counts[], float proportions[], int num_letters)
{
    for (int i = 0; i < len_alphabet; i++)
    {
        float count = (float) counts[i];
        //printf("count: %f", count);
        float prop = (count / (float) num_letters) * 100;
        //printf("prop: %f", prop);
        proportions[i] = prop;
    }
}

void print_proportions(float proportions[])
{
    for (int i = 0; i < len_alphabet; i++)
    {
        printf("Character %c has proportion %0.2f%% \n", alphabet[i], proportions[i]);
    }
}

void round_proportions(float proportions[], int rounded_proportions[])
{
    for (int i = 0; i < len_alphabet; i++)
    {
        int rounded_prop = round(proportions[i]);
        rounded_proportions[i] = rounded_prop;
    }
}

void print_rounded_proportions(int rounded_proportions[])
{
    for (int i = 0; i < len_alphabet; i++)
    {
        printf("Character %c has rounded proportion %d%% \n", alphabet[i], rounded_proportions[i]);
    }
}

int max_rounded_proportion(int rounded_porportions[])
{
    int max = 0;
    for (int i = 0; i < len_alphabet; i++)
    {
        int elem = rounded_proportions[i];
        if (elem > max)
        {
            max = elem;
        }
    }
    return max;
}

void generate_histogram(char* alphabet, int max)
{
    // Each row of the histogram
    for (int i = max; i > 0; i--)
    {
        //char char_i = (char) i;
        //char row[] = {char_i};
        char row[27] = "                          ";
        
        // Each element of that row
        for (int j = 0; j < len_alphabet; j++)
        {
            char c = alphabet[j];
            //char space = ' ';
            if (i <= rounded_proportions[j])
            {
                // Add a letter character to the row
                row[j] = c;
            }
            else
            {
                row[j] = ' ';
            }
        }
        printf("%s\n", row);
        //histogram[i] = row;
    }
}

/*
void print_histogram(char* histogram[], int max)
{
    for (int i = 0; i < max; i++)
    {
        printf("%s \n", histogram[i]);
    }
}
*/

int main(int argc, char* argv[])
{

    if (argc == 1)
    {
        printf("Feed me a string or a txt file. \n");
        exit(0);
    }
    if (argc > 2)
    {
        printf("Just one string or txt file please. \n");
        exit(0);
    }

    /* Read string to analyse from command line args */
    char* str = argv[1];
    printf("%s", str);
    int num_letters = 0;

    /*print_counts(counts);*/

    for (int i = 0; str[i]; i++)
    {
        int is_char = 0;
        char c = tolower(str[i]);
        is_char = compare_chars(c, alphabet);
        if (is_char)
        {
            num_letters += 1;
        }
        /*printf("Counted number of letters in string is: %d \n", num_letters);*/
    }

    /*print_counts(counts);*/
    printf("Number of letters in string is: %d \n", num_letters);
    calculate_proportions(counts, proportions, num_letters);
    print_proportions(proportions);

    /*
    float total_prop = 0;
    for (int i = 0; i < len_alphabet; i++)
    {
        total_prop += proportions[i];
    }
    printf("total prop: %f", total_prop);
    */
      
    round_proportions(proportions, rounded_proportions);
    //print_rounded_proportions(rounded_proportions);
    int max = max_rounded_proportion(rounded_proportions);
    printf("Max rounded prop: %d \n", max);
    printf("HISTOGRAM: \n");
    generate_histogram(alphabet, max);
    //print_histogram(histogram, max);

    return 0;

}