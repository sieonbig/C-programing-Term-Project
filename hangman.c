#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 6
#define SCORE_PER_LETTER 10
#define BONUS_PER_LIFE 5

const char *wordList[] = {
    "programming",
    "hangman",
    "computer",
    "science",
    "keyboard",
    "developer",
    "algorithm",
    "variable",
    "function",
    "pointer"
};
const int wordCount = sizeof(wordList) / sizeof(wordList[0]);

int playRound(int *totalScore, int *winCount);
void drawHangman(int wrongGuesses);
void displayWord(const char *word, const int *guessedLetters);

int main() {
    srand((unsigned int)time(NULL));

    int totalScore = 0;
    int totalWins = 0;
    int isPlaying = 1;

    printf("=========================================\n");
    printf("           HANGMAN GAME                  \n");
    printf("  Survive as many rounds as possible!    \n");
    printf("=========================================\n\n");

    while (isPlaying) {
        int result = playRound(&totalScore, &totalWins);
        
        if (result == 0) {
            printf("\n>>> GAME OVER! You failed to guess the word. <<<\n");
            isPlaying = 0;
        } else {
            printf("\n>>> Congratulations! Moving to the next round... <<<\n");
            printf("Press Enter to continue...");
            while (getchar() != '\n');
            getchar();
        }
    }

    printf("\n=========================================\n");
    printf("               GAME STATS                \n");
    printf("=========================================\n");
    printf(" Total Successful Rounds : %d\n", totalWins);
    printf(" Total Score Achieved    : %d points\n", totalScore);
    printf("=========================================\n");
    printf("Thank you for playing!\n");

    return 0;
}

int playRound(int *totalScore, int *winCount) {
    int wordIndex = rand() % wordCount;
    const char *targetWord = wordList[wordIndex];
    int wordLength = strlen(targetWord);

    int guessedLetters[26] = {0};
    int wrongGuesses = 0;

    printf("\n--- NEW ROUND START ---\n");

    while (wrongGuesses < MAX_TRIES) {
        drawHangman(wrongGuesses);
        
        printf("\nWord: ");
        displayWord(targetWord, guessedLetters);
        
        printf("\nTries left: %d", MAX_TRIES - wrongGuesses);
        printf("\nGuess a letter: ");

        char guess;
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (guess < 'a' || guess > 'z') {
            printf("Invalid input. Please enter a letter a-z.\n");
            continue;
        }

        if (guessedLetters[guess - 'a']) {
            printf("You already guessed '%c'.\n", guess);
            continue;
        }

        guessedLetters[guess - 'a'] = 1;

        int found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (targetWord[i] == guess) {
                found = 1;
            }
        }

        if (found) {
            printf("Good guess! '%c' is in the word.\n", guess);
            
            int allGuessed = 1;
            for (int i = 0; i < wordLength; i++) {
                if (!guessedLetters[targetWord[i] - 'a']) {
                    allGuessed = 0;
                    break;
                }
            }

            if (allGuessed) {
                drawHangman(wrongGuesses);
                printf("\nWord: %s\n", targetWord);
                
                int roundScore = (wordLength * SCORE_PER_LETTER) + ((MAX_TRIES - wrongGuesses) * BONUS_PER_LIFE);
                *totalScore += roundScore;
                (*winCount)++;
                
                printf("You guessed the word! (+%d points)\n", roundScore);
                return 1;
            }
        } else {
            printf("Wrong guess! '%c' is not in the word.\n", guess);
            wrongGuesses++;
        }
    }

    drawHangman(wrongGuesses);
    printf("\nThe word was: %s\n", targetWord);
    return 0;
}

void displayWord(const char *word, const int *guessedLetters) {
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        if (guessedLetters[word[i] - 'a']) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
}

void drawHangman(int wrongGuesses) {
    printf("\n");
    printf("  +---+\n");
    printf("  |   |\n");
    
    if (wrongGuesses >= 1) printf("  O   |\n");
    else printf("      |\n");
    
    if (wrongGuesses == 2)      printf("  |   |\n");
    else if (wrongGuesses == 3) printf(" /|   |\n");
    else if (wrongGuesses >= 4) printf(" /|\\  |\n");
    else                        printf("      |\n");

    if (wrongGuesses == 5)      printf(" /    |\n");
    else if (wrongGuesses >= 6) printf(" / \\  |\n");
    else                        printf("      |\n");
    
    printf("      |\n");
    printf("=========\n");
}