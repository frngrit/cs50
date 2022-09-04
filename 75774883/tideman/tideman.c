#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool circle(int winner, int loser);
int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{

    //loop over all candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //check if name is valid
        if (strcmp(candidates[i], name) == 0)
        {
            //if name is valid put the candidate's index in ranks array by rank
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    // TODO
    int winner, loser;
    //loop over ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        //check with the following index i
        //ex. at index 0 check with 1, 2, 3, ..., N
        for (int j = i + 1; j < candidate_count; j++)
        {
            //the one with more rank (i) is the winner
            //the lower is a loser
            winner = ranks[i];
            loser = ranks[j];
            preferences[winner][loser] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //loop for left triangle of pref matrix
    int left_corner = candidate_count * (candidate_count - 1) / 2; //calculate number of member in half left corner (HLC)

    //loop over HLC
    //inital index start from prefernces[0][1]
    int i = 0, j = 1, k = 1;
    for (int n = 0; n < left_corner; n++)
    {

        if (j == candidate_count)
        {
            i = 0;
            j = k + 1;
            k++;
        }
        if (preferences[i][j] > preferences[j][i])
        {

            pairs[pair_count].winner = i;
            pairs[pair_count].loser = j;
            pair_count++;
        }
        else if (preferences[i][j] < preferences[j][i])
        {
            pairs[pair_count].loser = i;
            pairs[pair_count].winner = j;
            pair_count++;
        }
        i++;
        j++;
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int max = 0, loser, winner, votes;
    pair first;
    int max_index;

    for (int j = 0; j < pair_count - 1; j++)
    {
        bool found = false;
        for (int i = j; i < pair_count; i++)
        {
            //selection sort
            //find maximum

            //get loser and winner pair to check at pref
            loser = pairs[i].loser;
            winner = pairs[i].winner;


            //check at pref and get number of votes
            votes = preferences[winner][loser] - preferences[loser][winner];


            //check if votes is maximum
            if (votes > max)
            {
                max = votes;
                max_index = i;
                found = true;
            }
        }
        if (found)
        {
            first = pairs[j];
            pairs[j] = pairs[max_index];
            pairs[max_index] = first;
        }
    }
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        if (!circle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", (int) locked[i][j]);
        }
        printf("\n");
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                bool flag = false;
                for (int k = 0; k < candidate_count; k++)
                {
                    if (locked[k][i])
                    {
                        flag = true;
                    }
                }
                if (!flag)
                {
                    printf("%s\n", candidates[i]);
                    return;
                }
            }
        }
    }
}

bool circle(int winner, int loser)
{
    if (loser == winner)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (circle(winner, i))
            {
                return true;
            }
        }
    }
    return false;
}