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
        "What was the name of the first civilization in ancient Mesopotamia?",
        "In Shakespeare's tragedy, what is the name of the Danish prince seeking revenge for his father's death?",
        "What is the name of the process by which plants convert sunlight into energy?",

        "What 16th century queen was known for her short reign and her persecution of Protestants in England?",
        "In J.R.R. Tolkien's epic fantasy series, what is the name of the wizard who guides Frodo and the Fellowship of the Ring?",
        "What is the term for a device that measures the intensity of light?",

        "What was the name of the ancient Egyptian writing system?",
        "What classic dystopian novel by George Orwell features a society controlled by a totalitarian government and a protagonist named Winston Smith?",
        "What is the name of the force that opposes motion between two surfaces in contact?",

        "Who was the Roman emperor responsible for building a wall across Britain in the second century AD?",
        "What is the one-word title of the novel by F. Scott Fitzgerald that features the character Jay Gatsby?",
        "What is the name of the unit used to measure electric current?"
    };
    char *a[] = {
        "Sumer",
        "Hamlet",
        "Photosynthesis",

        "Mary",
        "Gandalf",
        "Photometer",

        "Hieroglyphs",
        "1984",
        "Friction",

        "Hadrian",
        "Gatsby",
        "Ampere"
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

	for(int i = 0; i < NUM_QUESTIONS; i++) {
        if(questions[i].answered == false) {
            printf("|          $%d%s", questions[i].value, "          ");
		} else {
			printf("|                        ");
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
    int q_index = get_question_index(category, value);
    if (q_index >= 0) {
        printf("%s\n", questions[q_index].question);
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    int q_index = get_question_index(category, value);
    if (q_index >= 0) {
        if(strcasecmp(answer, questions[q_index].answer) == 0){
            questions[q_index].answered = true;
            return true;
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    int q_index = get_question_index(category, value);
    
    return questions[q_index].answered;
}

bool valid_category(char *category)
{
    for(int i = 0; i < NUM_CATEGORIES; i++){
        if(strcmp(categories[i], category) == 0){
            return true;
        }
    }
    return false;
}

bool valid_value(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value && questions[i].answered == false){
            return true;
        }
    }

    return false;
}

int get_question_index(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value  == value) {
            return i;
        }
    }
    printf("Error: Question not found.\n");

    return -1;
}

bool questions_left()
{
    for (int i =  0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered) {
            return true;
        }
    }
    
    return false;
}