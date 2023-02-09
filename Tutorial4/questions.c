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
// #include "questions.h" // HAD TO REMOVE THIS LINE FOR THE MAKEFILE TO RUN

// Initializes the array of questions for the game
void initialize_game(void)
{
    printf("Welcome to the C Command Line version of Jeopardy!\n\n");
    printf("In this game, you will be given a category and a clue. Your task is to provide the correct answer.\n");
    printf("The value of each question will be determined by its difficulty. The more difficult the question, the higher the value.\n");
    printf("Let's get started! Good luck and have fun!\n\n");

    char *categories[] = {
        "History", 
        "Literature", 
        "Science and Technology"
    }
    char *questions[] = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    }
    char *answers[] = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    }
    int values[] = {
        100,
        200,
        300,
        400
    }

    // initialize each question struct and assign it to the questions array
    for (int i = 0; i < 12; i++) {
        strcpy(questions[i].category, "");
        strcpy(questions[i].question, "");
        strcpy(questions[i].answer, "");
        strcpy(questions[i].value, "");
        strcpy(questions[i].answered, FALSE);

        char category[MAX_LEN];
        char question[MAX_LEN];
        char answer[MAX_LEN];
        int value;
        bool answered;
    }



}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}
