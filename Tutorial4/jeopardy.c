/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U: Operating Systems
 *
 * Copyright (C) 2023, Ahmaad Ansari / Huzaifa Zia / Hanzalah Patel / Sabeh Khalid
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
// #include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here
char current_player[MAX_LEN];
char current_category[MAX_LEN];
char current_answer[MAX_LEN];
int current_value;
bool error_check = true;
player players[NUM_PLAYERS];

void enter_player();
void enter_category_value();
void ask_question();
int random_number();

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
int tokenize(char *str, char *delim, char *tokens[], int max_tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players);


int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    int random_player = 0;
    
    // Display the game introduction and initialize the questions
    system("clear");
    initialize_game();

    // Prompt for players names, and initialize each of the players in the array
    for (int i = 0; i < NUM_PLAYERS; i++){
        players[i].score = 0;
        printf("Enter the name of player %d: ", (i + 1));
        scanf("%s", (char *) &players[i].name);
    }

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Execute the game until all questions are answered
        while (questions_left()) {
            system("clear");

            // Call functions from the questions and players source files
            enter_player();
            enter_category_value();

            while(!already_answered(current_category, current_value)){
                ask_question();
                if(valid_answer(current_category, current_value, current_answer)){
                    // Add points here
                    update_score(players, current_player, current_value);
                    printf("\n\nCORRECT! %d points have been awarded to %s!\n\n", current_value, current_player);
                    sleep(5);
                }
                else{
                    // Deduct points here
                    update_score(players, current_player, -current_value);
                    printf("\n\nINCORRECT! %d points have been deducted from %s!\n\n", current_value, current_player);
                    do {
                        random_player = random_number();
                    } while (strcmp(players[random_player].name, current_player) == 0);
                    // current_player = players[random_player].name;
                    strcpy(current_player, players[random_player].name);
                    // printf("%s, it is your turn to steal!", current_player);
                    sleep(5);
                }
            }
        }
        // Display the final results and exit
        show_results(players);
    }
    return EXIT_SUCCESS;
}

int tokenize(char *str, char *delim, char *tokens[], int max_tokens) {
    int count = 0;
    char *token = strtok(str, delim);
    while (token != NULL &&  count < max_tokens) {
        tokens[count++] = token;
        token = strtok(NULL, delim);
    }
    return count;
}

void enter_player() {
    do {
        printf("\nEnter the name of the player that will be playing: ");
        scanf("%s", (char *) &current_player);
        if(player_exists(players, current_player)){
            error_check = false;
        }
        else{
            printf("Player \"%s\" does not exist. Please enter in a valid players name.\n", current_player);
            error_check = true;
        }
    } while(error_check);
}

int random_number() {
    srand(time(NULL));
    return (rand() % 4);
}

void enter_category_value() {
    system("clear");
    display_categories();
    do {
        printf("%s, pick a category: ", current_player);
        scanf("%s", (char *) &current_category);            
        if(valid_category(current_category)){
            error_check = false;
        }
        else{
            printf("The category \"%s\" does not exist. Please enter a valid category.\n", current_category);
            error_check = true;
        }
    } while(error_check);
    do {
        printf("%s, enter a value (numbers only): ", current_player);
        scanf("%d", &current_value);
        if(valid_value(current_category, current_value)){
            error_check = false;
        }
        else{
            printf("The value \"%d\" does not exist. Please enter a valid value.\n", current_value);
            error_check = true;    
        }
    } while(error_check);
}

void ask_question() {
    system("clear");
    printf("This question is for: %s\n", current_player);
    printf("\nThe following is the question for %s $%d...\n", current_category, current_value);
    printf("Q: ");
    display_question(current_category, current_value);
    printf("A: ");

    // Consume any remaining characters in the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    
    fgets((char *) current_answer, MAX_LEN, stdin);
    // scanf("%s", (char *) &current_answer);
    
    bool err = false;
    char *tokens[10];
    int num_tokens = tokenize(current_answer, " \n", tokens, 10);
    if (strcmp(tokens[0], "what") != 0 && strcmp(tokens[0], "who") != 0) {
        strcpy(current_answer, "");
        err = true;
    }
    if (num_tokens < 3 || strcmp(tokens[1], "is") != 0) {
        strcpy(current_answer, "");
        err = true;
    }
    if (err) {
        printf("\nMake sure your answer starts with 'what is' or 'who is' next time!");
    }
    else {
        strcpy(current_answer, tokens[2]);
    }

}

void show_results(player *players) {
    system("clear");
    // Bubble Sort
    for (int i = 0; i < NUM_PLAYERS - 1; i++) {
        for (int j = 0; j < NUM_PLAYERS - i - 1; j++) {
            if (players[j].score < players[j+1].score) {
                player temp = players[j];
                
                players[j] = players[j+1];
                players[j+1] = temp;
            }
        }
    }

    for(int i = 0; i < NUM_PLAYERS; i++){
        printf("%s\t\t%d\n", players[i].name, players[i].score);
    }
}

