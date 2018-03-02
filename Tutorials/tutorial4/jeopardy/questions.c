/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2018, Devon McGrath, Mike Setnyk, Tyler Messenger-Lehmann
 * All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

enum colour { black = 30, red, green, brown, blue, purple, cyan, grey };

// Posts text to the terminal on a specific line and column
// with a specified colour
void post(int line, int col, const char *text, int colour_code){
	printf("\033[0;%im\033[%i;%iH%s\033[0m",
		colour_code, line, col, text);
}

// Clears the terminal
void clear_terminal() {
	//J = clear, 2J = clear whole screen
	//line ; col H = cursor position
	//https://en.wikipedia.org/wiki/ANSI_escape_code
	printf("\033[2J\033[1;1H");
}

// Initializes the array of questions for the game
void initialize_game(void) {

	char quests[12][MAX_LEN] = {
		// programming category
		"What is a programming construct used by many languages to define an object?",
		"How many bits are used to store a char in Java?",
		"When a variable is dynamically created, where is it stored?",
		"How many decimal places can be represented accurately with a 64-bit floating point?",

		// algorithms category
		"What class of algorithms takes the most possible at each step?",
		"What is the best way to solve the Towers of Hanoi problem?",
		"",
		"",

		// databases category
		"How is data logically stored in a relational database?",
		"What Java library is used to interface with databases?",
		"What type of processing is used in data warehouses?",
		"What software is generally used to process high-volume transactions? (e.g. for a bank)"
	};

	char answers[12][MAX_LEN] = {
		// programming category
		"class",
		"16",
		"heap",
		"16",

		// algorithms category
		"greedy",
		"recursion",
		"",
		"",

		// databases category
		"table",
		"JDBC",
		"OLAP",
		"CICS"
	};

    // initialize each question struct and assign it to the questions array
	for (int i = 0; i < NUM_QUESTIONS; i++) {
		question q = {.category = i / 4, .question = "",
			.answer = "", .value = 0, .answered = false};
		strcpy(q.question, quests[i]);
		strcpy(q.answer, answers[i]);
		switch (i%4) {
			case 0:
			q.value = 200;
			break;
			case 1:
			q.value = 400;
			break;
			case 2:
			q.value = 600;
			break;
			case 3:
			q.value = 800;
		}
		questions[i] = q;
	}
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void) {
    // print categories and dollar values for each unanswered question in questions array
	clear_terminal();
	post(1, 25, "Operating Systems - Jeopardy", green);
	int n = NUM_CATEGORIES;
	int start_x[n];
	start_x[0] = 5;
	for (int i = 1; i < n; i ++) {
		start_x[i] = start_x[i-1] + strlen(categories[i-1]) + 5;
	}

	// Post the categories
	for (int i = 0; i < n; i ++) {
		post(3, start_x[i], categories[i], green);
	}

	// Post the questions
	n = NUM_QUESTIONS / NUM_CATEGORIES;
	for (int row = 0; row < n; row ++) {
		for (int cat = 0; cat < NUM_CATEGORIES; cat ++) {
			question q = questions[row + cat * n];
			char num[10];
			sprintf(num, "$%d", q.value);
			post(4 + row * 2, start_x[cat], num, q.answered? red : cyan);
		}
	}
	post(4 + n * 2, 5, "Enter category and value: ", purple);
}

// Displays the question for the category and dollar value
void display_question(int category, int value) {
	int index = get_question_index(category, value);
	if (index < 0) {
		return;
	}

	// Display the question
	clear_terminal();
	question q = questions[index];
	char line[MAX_LEN];
	sprintf(line, "Category: %s\tValue: $%d", categories[q.category],
		value);
	post(1, 1, line, green);
	post(3, 5, q.question, cyan);
	post(5, 10, "Answer: ", purple);
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(int category, int value, char *answer) {
    int index = get_question_index(category, value);
	if (index < 0) {
		return false;
	}
    return strcmp(questions[index].answer, answer) == 0;
}

// Returns true if the question has already been answered
bool already_answered(int category, int value) {
    int index = get_question_index(category, value);
	if (index < 0) {
		return true;
	}
    return questions[index].answered;
}

// Returns the index of the question or -1 if it doesn't exist
int get_question_index(int category, int value) {

	// Special cases
	if (category < 0 || category >= NUM_CATEGORIES) {
		return -1;
	} else if (value < 0 || value % 100 != 0) {
		return -1;
	}

	// Calculate the index
	value = (value / 200) - 1;
	if (value < 0 || value >= NUM_QUESTIONS / NUM_CATEGORIES) {
		return -1;
	}

	return category * (NUM_QUESTIONS / NUM_CATEGORIES) + value;
}

// Returns the index of the category or -1 if it doesn't exist
int get_category_index(const char *category) {
	for (int i = 0; i < NUM_CATEGORIES; i ++) {
		if (strcmp(category, categories[i]) == 0) {
			return i;
		}
	}
	return -1;
}
