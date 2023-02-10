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
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    printf("Welcome to the C Command Line version of Jeopardy!\n\n");
    printf("In this game, you will be given a category and a clue. Your task is to provide the correct answer.\n");
    printf("The value of each question will be determined by its difficulty. The more difficult the question, the higher the value.\n");
    printf("Let's get started! Good luck and have fun!\n\n");

    char *q[] = {
        "What year did the American Civil War end?",
        "Who wrote the novel 'Pride and Prejudice'?",
        "Who is considered the father of the computer?",

        "Who was the first president of the United States?",
        "Who wrote the novel 'Moby Dick'?",
        "What is the study of life called?",

        "What was the date of the attack on Pearl Harbor?",
        "Who wrote the play 'Hamlet'?",
        "What is the chemical symbol for gold?",

        "Who was Julius Caesar assassinated by?",
        "Who wrote the novel 'To Kill a Mockingbird'?",
        "What is the name of the first artificial satellite to be launched into space?"
    };
    char *a[] = {
        "1865",
        "Jane Austen",
        "Charles Babbage",

        "George Washington",
        "Herman Melville",
        "Biology",

        "December 7, 1941",
        "William Shakespeare",
        "Au",

        "Marcus Brutus and other senators",
        "Harper Lee",
        "Sputnik 1"
    };
    int v[] = {
        100,
        200,
        300,
        400 
    };

    // initialize each question struct and assign it to the questions array
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        strcpy(questions[i].category, categories[i%3]);
        strcpy(questions[i].question, q[i]);
        strcpy(questions[i].answer, a[i]);
        questions[i].value = v[i/3];
        questions[i].answered = false;
    }

}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    int width = 24;

    for (int i = 0; i < NUM_CATEGORIES; ++i) {
		putchar('+');
		for (int j = 0; j < width; ++j) {
			putchar('-');
        }
	}
	printf("+\n");

	for(int i = 0; i < NUM_CATEGORIES; i++) {
		printf("| %-*s", width - 1, categories[i]);
    }
	printf("|\n");

	for (int i = 0; i < NUM_CATEGORIES; ++i) {
		putchar('+');
		for (int j = 0; j < width; ++j) {
			putchar('-');
        }
	}
    printf("+\n");

    // for(int i = 0; i < NUM_QUESTIONS; i++) {
    //     printf("%s ", questions[i].category);
    //     printf("%s ", questions[i].question);
    //     printf("%s ", questions[i].answer);
    //     printf("%d\n", questions[i].value);
    // }

	for(int i = 0; i < NUM_QUESTIONS; i++) {
		
        if(questions[i].answered == false) {
			// printf("| $%d", questions[i].value);
            printf("| $%s", questions[result].category);
		} else {
			printf("| %-*s", width - 2, " - ");
		}

		if(i % NUM_CATEGORIES == 2)
			printf("|\n");
	}

	for (int i = 0; i < NUM_CATEGORIES; ++i) {
		putchar('+');
		for (int j = 0; j < width; ++j) {
			putchar('-');
        }
	}
    printf("+\n");

    return 0;
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
