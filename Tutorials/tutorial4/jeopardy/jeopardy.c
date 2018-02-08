/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 2

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(struct player *players, int num_players);

int game_state;


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    struct player players[NUM_PLAYERS];  
    
    // Buffer for user input
    char input[BUFFER_LEN] = { 0 };

    printf("Welcome to Jeoprady\n");
    // Display the game introduction and initialize the questions
    initialize_game();
   
    for (int i =0;i<NUM_PLAYERS;i++){
        printf("Enter player %d name\n",i);
        fgets(input, BUFFER_LEN, stdin);
        strtok(input,"\n");
        strcpy(players[i].name,input);
        players[i].score=0;
    }
    
    int i=0;

    // Perform an infinite loop getting command input from users until game ends
    game_state = 1;
    while (game_state)
    {
        //new player turn
        int current_player = i%NUM_PLAYERS;
        printf("Players %s turn\n",players[current_player].name);
        
        //get input for catergory and dollar amount
        printf("Enter category name and dollar ammount\n");
        fgets(input, BUFFER_LEN, stdin);

        display_categories();
        char** tokens = (char**)malloc(sizeof(char*) * BUFFER_LEN); // 100 'char*'

        tokenize(input,tokens);
        
        char cat[BUFFER_LEN];
        strcpy(cat,tokens[0]);
        int val = atoi(tokens[1]);
        
        //show the selected question and get input
        display_question(tokens[0], val);
        printf("Enter Answer\n");
        fgets(input, BUFFER_LEN, stdin);
        char** answer_tokens = (char**)malloc(sizeof(char*) * BUFFER_LEN); // 100 'char*'

        tokenize(input,answer_tokens);
        
        
        if (already_answered(cat, val)){
              printf("Already Answered Please try again\n");
        }else{
             if (valid_answer(tokens[0],val,answer_tokens[2])){ 
                printf("Correct!\n");
                 players[current_player].score+=val;
             }else{
                printf("Incorrect!\n");
             }
        }
        for (int i=0;i<NUM_QUESTIONS;i++){
            if(questions[i].answered==true){
                game_state=0;
            }else{
                game_state=1;
                break;
            }
        }
        
        if(!game_state){
            show_results(players, NUM_PLAYERS);
        }
        
        i++;
        
    }
    return EXIT_SUCCESS;
    
  
}

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens){
    int token_cnt=0;
    char* token;
    
    token = (char*)malloc(sizeof(char) * BUFFER_LEN);   // 100 'char'
    
    int token_idx=0;
    for (int i = 0; input[i] != '\n';i++){
        if(input[i]==' '){
            tokens[token_cnt]=(char*)malloc(sizeof(char*) * BUFFER_LEN);  
            strcpy(tokens[token_cnt],token);
            token_cnt++;
            token_idx=0;
            token = (char*)malloc(sizeof(char) * BUFFER_LEN);   // 100 'char'

        }else{
            token[token_idx]=input[i];
            token_idx++;
        }
    } 
    tokens[token_cnt]=(char*)malloc(sizeof(char*) * BUFFER_LEN);  
    strcpy(tokens[token_cnt],token);
    token_cnt++;   
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(struct player *players, int num_players){
    printf("Final Scores!\n");
    for (int i =0 ;i < num_players;i++){
        printf("%s, %d\n",players[i].name,players[i].score);
    }
    game_state=0;
}