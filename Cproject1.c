#include <stdio.h>
#include <string.h>

#define MAX_C 11 // Maximum number of candidates allowed is 10 (11 elements total)

// Structure to hold individual candidate profiles
typedef struct Candidate {
    char name[50]; 
    int votes;
    char symbol;
} Candidate;

// Global array to manage candidate records
Candidate allCandidates[MAX_C];

// Global counter tracking active candidates registered by the user
int candidateCount = 0;

// Set of 10 distinct characters assigned for election symbols
char symbols[10] = { '!', '@', '#', '$', '%', '^', '&', '*', '~', '+' };

// Tracking flags (0 = Available, 1 = Taken) to stop duplicate symbol assignment
int symbolTaken[11];

// Explicit function declarations for modular architecture
void fillCandidate(int);
void displayAllCandidates();
void getVotes(int);
void getResults();

int main()
{
    // Initialize the tracking array explicitly to zero out all symbol slots
    for (int i = 0; i < 11; i++) {
        symbolTaken[i] = 0;
    }

    printf("Enter the number of candidates: ");
    
    // SAFETY CHECK: Ensure the user typed an integer. If not, exit gracefully
    if (scanf("%d", &candidateCount) != 1) {
        printf("Invalid input. Please enter a valid number. Terminating.\n");
        return 0;
    }
    
    // Bound limits check to enforce limits and avoid out-of-bounds array access
    if (candidateCount >= MAX_C || candidateCount <= 0) {
        printf("Number of candidates must be between 1 and 10.\n Terminating the program\n\n");
        return 0;
    }

    // Sequence through setup for each registered candidate
    for (int i = 0; i < candidateCount; i++) {
        fillCandidate(i);
    }

    int numVoters;
    printf("Enter the number of voters: ");
    
    // SAFETY CHECK: Verify that voter count input is a numerical integer
    if (scanf("%d", &numVoters) != 1) {
        printf("Invalid input. Please enter a valid number. Terminating.\n");
        return 0;
    }

    // Process every single voter ballot systematically
    for (int i = 0; i < numVoters; i++) {
        getVotes(i);
    }

    // Collate metrics and determine results
    getResults();
    return 0;
}

// Registers names and signs unique election symbols to candidates safely
void fillCandidate(int cNum)
{
    int num = 0;
    int isValid = 0;

    // FIX: Replaced infinite-risk recursion with a controlled 'while' loop
    while (!isValid) {
        printf("\nAvailable Symbols: \n");
        for (int j = 0; j < 10; j++) {
            if (symbolTaken[j] == 1) continue; // Skip displaying symbols already taken
            printf("%d  %c\n", j + 1, symbols[j]);
        }

        printf("\nEnter the symbol number of candidate %d: ", cNum + 1);
        
        // FIX: If user types a character/letter, scanf fails. We must detect it.
        if (scanf("%d", &num) != 1) {
            printf("Invalid input! Please enter a number.\n");
            
            // THE CRITICAL FIX: "Flush" out the invalid text blocking the stream buffer.
            // It reads character by character until the user's Enter key newline is reached.
            while (getchar() != '\n'); 
            continue; // Jump right back to start the prompt over cleanly
        }

        // Validate choice availability and boundaries 
        if (num <= 0 || num > 10 || symbolTaken[num - 1] == 1) {
            printf("This Symbol is not available. Please choose from the available symbols\n");
        } else {
            isValid = 1; // Input matches criteria perfectly. Break out of processing loop.
        }
    }

    // Log the selected profile allocations securely
    symbolTaken[num - 1] = 1; // Mark the chosen symbol index as unavailable
    allCandidates[cNum].symbol = symbols[num - 1]; // Map asset character to structure
    
    printf("Enter the name of candidate %d: ", cNum + 1);
    
    // FIX: " %49[^\n]" tells scanf to swallow whitespace and accept multi-word names 
    // (e.g., "John Doe") safely up to 49 letters long without splitting input streams.
    scanf(" %49[^\n]", allCandidates[cNum].name); 

    allCandidates[cNum].votes = 0; // Initialize standard zero voter metrics
}

// Standard helper routine rendering current choices on a layout grid
void displayAllCandidates()
{
    for (int j = 0; j < candidateCount; j++) {
        printf("%s\t\t", allCandidates[j].name);
    }
    printf("\n");
    for (int j = 0; j < candidateCount; j++) {
        printf("%3c\t\t\t", allCandidates[j].symbol);
    }
    printf("\n");
}

// Secure voting collection tool ensuring reliable tally execution
void getVotes(int voterCount)
{
    int choice;
    int isValid = 0;

    // FIX: Using controlled loops to manage invalid votes instead of crash-prone recursive calls
    while (!isValid) {
        displayAllCandidates();
        printf("Voter %d, please enter your choice (1-%d): ", voterCount + 1, candidateCount);
        
        // Check structural input consistency (handles characters gracefully)
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clean the stream pipeline to avoid loop traps
            continue;
        }

        // Tally updates on verified entries
        if (choice >= 1 && choice <= candidateCount) {
            allCandidates[choice - 1].votes++; // Increment score counter array offset
            isValid = 1; // Mark transaction complete
        } else {
            printf("Invalid choice! Please vote again.\n");
        }
    }
}

// Determines the winner and flags potential tie-breaking scenarios
void getResults()
{
    int maxVotes = 0;
    int winnerIndex = -1;
    int winnerFrequency = 0;
    
    // Peak discovery logic finding highest score tier inside data set
    for (int i = 0; i < candidateCount; i++) {
        if (allCandidates[i].votes > maxVotes) {
            maxVotes = allCandidates[i].votes;
            winnerIndex = i;
        }
    }

    // Evaluates duplication metrics to filter cross-tie scenarios
    for (int i = 0; i < candidateCount; i++) {
        if (allCandidates[i].votes == maxVotes) {
            winnerFrequency++;
        }
    }

    printf("\n-----RESULT-----\n");

    // Decouples and renders dynamic context outcomes
    if (winnerFrequency > 1 && maxVotes > 0) {
        printf("No candidate has majority votes (It's a tie!)\n");
    } else if (winnerIndex != -1 && maxVotes > 0) {
        printf("The winner is: %s\nCandidate Symbol: %c\nwith %d votes!\n",
               allCandidates[winnerIndex].name,
               allCandidates[winnerIndex].symbol, maxVotes);
    } else {
        printf("No votes were cast.\n");
    }
}
