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
void tokenize(char *input, char **tokens);

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

    enter_player();
    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files
        while (questions_left()) {
            enter_category_value();
        

            while(!already_answered(current_category, current_value)){
                ask_question();
                if(valid_answer(current_category, current_value, current_answer)){
                    // Add points here
                    update_score(players, current_player, current_value);
                    printf("\n\nCORRECT! %d points have been awarded to %s!\n\n", current_value, current_player);
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
                    printf("%s, it is your turn to steal!", current_player);
                }
                show_results(players);
            }
        }
        
        


        // Execute the game until all questions are answered

        // Display the final results and exit
    }
    return EXIT_SUCCESS;
}

void enter_player(){
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

void enter_category_value(){
    do {
        display_categories();
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
        printf("%s, enter a value: ", current_player);
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

void ask_question(){
    printf("\nThe following is the question for %s $%d...\n", current_category, current_value);
    printf("Q: ");
    display_question(current_category, current_value);
    printf("A: ");
    scanf("%s", (char *) &current_answer);
}

void show_results(player *players){
    printf("\n\n");
    for(int i = 0; i < NUM_PLAYERS; i++){
        printf("%s\t\t%d\n", players[i].name, players[i].score);
    }
    printf("\n\n");
}

