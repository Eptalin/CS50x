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
} pair;

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
bool cycle_found(int start, int current);
void print_winner(void);

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
    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // If name found in candidates array, record ranked vote
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // If no match is found
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Iterate over candidates who beat others
    for (int i = 0; i < candidate_count; i++)
    {
        // Iterate over candidates who lost to the above
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Iterate over the full preferences table
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // If candidate preferred over another, add pair and increment count
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}


// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble sort
    int i, j, flag;
    pair temp;
    for (i = 0; i < pair_count - 1; i++)
    {
        // Reset flag to 0 each pass
        flag = 0;
        // Each pass will be 1 shorter than the previous
        for (j = 0; j < pair_count-i-1; j++)
        {
            int left = preferences[pairs[j].winner][pairs[j].loser];
            int right = preferences[pairs[j+1].winner][pairs[j+1].loser];
            if (left < right)
            {
                flag = 1;
                // Store old left pair in temp
                temp.winner = pairs[j].winner;
                temp.loser = pairs[j].loser;
                // Move the right pair to the left
                pairs[j].winner = pairs[j+1].winner;
                pairs[j].loser = pairs[j+1].loser;
                // Replace old left pair with temp pair
                pairs[j+1].winner = temp.winner;
                pairs[j+1].loser = temp.loser;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
    return;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Iterate over pairs
    for (int i = 0; i < pair_count; i++)
    {
        // If cycle not found, lock pair
        if (!cycle_found(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = 1;
        }
    }
    return;
}


bool cycle_found(int start, int current)
{
    // Loop over relevant row of 2D array
    for (int next = 0; next < candidate_count; next++)
    {
        // If cycle found in current cell or descendant, return true.
        if (locked[current][next] && (next == start || cycle_found(start, next)))
        {
            return 1;
        }
    }
    // If no cycle found, return false
    return 0;
}


// Print the winner of the election
void print_winner(void)
{
    int flag;
    // Iterate over each column
    for (int column = 0; column < candidate_count; column++)
    {
        flag = 0;
        for (int row = 0; row < candidate_count; row++)
        {
            if (locked[row][column] == 1) 
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("%s\n", candidates[column]);
        }
    }
    return;
}
