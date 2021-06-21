# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

# define LEN_ALPHABET 26

char* alphabet = "abcdefghijklmnopqrstuvwxyz";

/* Initialise arrays to all 0 */
int counts[LEN_ALPHABET] = {};
float proportions[LEN_ALPHABET] = {};
int rounded_proportions[LEN_ALPHABET] = {};

void update_counts(int counts[], int i)
{
    counts[i] += 1;
}

void print_counts(int counts[])
{
    for (int i = 0; i < LEN_ALPHABET; i++)
    {
        printf("Character %c has count %d \n", alphabet[i], counts[i]);
    }
}

int compare_chars(char c, char* alphabet)
{
    for (int i = 0; alphabet[i]; i++)
    {
        if (c == alphabet[i])
        {
            update_counts(counts, i);
            return 1;
        }
    }
    return 0;
}

void calculate_proportions(int counts[], float proportions[], int num_letters)
{
    for (int i = 0; i < LEN_ALPHABET; i++)
    {
        float count = (float) counts[i];
        float prop = (count / (float) num_letters) * 100;
        proportions[i] = prop;
    }
}

void print_proportions(float proportions[])
{
    for (int i = 0; i < LEN_ALPHABET; i++)
    {
        printf("Character %c has proportion %0.2f%% \n", alphabet[i], proportions[i]);
    }
}

void round_proportions(float proportions[], int rounded_proportions[])
{
    for (int i = 0; i < LEN_ALPHABET; i++)
    {
        int rounded_prop = round(proportions[i]);
        rounded_proportions[i] = rounded_prop;
    }
}

void print_rounded_proportions(int rounded_proportions[])
{
    for (int i = 0; i < LEN_ALPHABET; i++)
    {
        printf("Character %c has rounded proportion %d%% \n", alphabet[i], rounded_proportions[i]);
    }
}

struct Popular
{
    int max_prop;
    char most_pop;
};

struct Popular most_popular;
struct Popular* popular_pointer = &most_popular;

struct Popular* max_rounded_proportion(int rounded_porportions[], char* alphabet, struct Popular* popular_pointer)
{
    int max = 0;
    char most_popular = ' ';
    for (int i = 0; i < LEN_ALPHABET; i++)
    {
        int elem = rounded_proportions[i];
        if (elem > max)
        {
            max = elem;
            most_popular = alphabet[i];
        }
    }
    popular_pointer->max_prop = max;
    popular_pointer->most_pop = most_popular;
    return popular_pointer;
}

void generate_histogram(char* alphabet, int max)
{
    // Each row of the histogram
    for (int i = max; i > 0; i--)
    {
        char row[27] = "                          ";
        // Each element of that row
        for (int j = 0; j < LEN_ALPHABET; j++)
        {
            char c = alphabet[j];
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
    }
}

int main(int argc, char* argv[])
{

    if (argc == 1)
    {
        printf("Why not feed me a string? I don't bite. \n");
        exit(0);
    }
    if (argc > 2)
    {
        printf("Just one string at a time please. I'm only a little fox. \n");
        exit(0);
    }

    printf("\nMmm, that's some tasty text! \n");
    
    // Read string to analyse from command line args
    char* str = argv[1];
    int num_letters = 0;

    for (int i = 0; str[i]; i++)
    {
        int is_char = 0;
        char c = tolower(str[i]);
        is_char = compare_chars(c, alphabet);
        if (is_char)
        {
            num_letters += 1;
        }
    }

    printf("\nSo many letters. I taste... %d of them. \n", num_letters);
    
    calculate_proportions(counts, proportions, num_letters);
    round_proportions(proportions, rounded_proportions);
    
    struct Popular* popular_char = max_rounded_proportion(rounded_proportions, alphabet, popular_pointer);
    int max = popular_char->max_prop;
    char most_popular = popular_char->most_pop;
    
    printf("\nHere's your letter popularity histogram. \n");
    printf("BUUUURP \n");    
    
    printf("\n");
    generate_histogram(alphabet, max);
    
    printf("\nLooks like '%c' is the most popular! \n", most_popular);
    
    printf("\nDo stop by and feed me again sometime. \n");
    printf("\n");

    return 0;

}