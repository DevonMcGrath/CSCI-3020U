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
      int dollars;
      char category[BUFFER_LEN];

        //new player turn
        int current_player = i%NUM_PLAYERS;
        printf("Players %s turn\n",players[current_player].name);

        //get input for catergory and dollar amount

        //this loop is a safety precaution incase input is incorrect
        bool catergory_input_invalid = true;
        while(catergory_input_invalid){
          printf("Enter category name and dollar ammount\n");
          fgets(input, BUFFER_LEN, stdin);
          display_categories();
          char** tokens = (char**)malloc(sizeof(char*) * BUFFER_LEN); // 100 'char*'

          tokenize(input,tokens);

          int token_cnt=0;
          for (int i=0; tokens[i]!= NULL;i++){
              token_cnt+=1;
          }
          //makes sure a catergory and a question is asked
          if (token_cnt!=2){
            printf("ERROR: Please enter a catergory and a number\n");
          }else{

            //make sure that the dollar is an integer
            //TODO use regex to remove $signs
            strcpy(category,tokens[0]);
            dollars = atoi(tokens[1]);
            printf("catergory %s, dollars %d \n",category,dollars);

            if(dollars!= 0 ){
              catergory_input_invalid=false;
              display_question(category, dollars);
            }else{
              printf("ERROR: Please enter a catergory and a number\n");
            }
          }
        }


        printf("Enter Answer\n");
        fgets(input, BUFFER_LEN, stdin);
        char** answer_tokens = (char**)malloc(sizeof(char*) * BUFFER_LEN); // 100 'char*'
        tokenize(input,answer_tokens);

        int token_cnt=0;
        for (int i=0; answer_tokens[i]!= NULL;i++){
            token_cnt+=1;
        }

        //make sure that "who is" and "what is" are ignored
        if (token_cnt<3){
          printf("Incorrect!\n");

        }else{
          //make sure that the first to tokens follow
          //the Jeporady format
          if((strcmp(answer_tokens[0],"Who") ||
          strcmp(answer_tokens[0],"What")) && strcmp(answer_tokens[1],"is")){
            char answer[BUFFER_LEN];

            //create a string that has the answer
            for (int i=2; answer_tokens[i]!= NULL;i++){
              strcat(answer," ");
              strcat(answer,answer_tokens[i]);
            }

            //test if the answer has already been ansered
            if (already_answered(category, dollars)){
                  printf("Already Answered Please try again\n");
                  i--;
                  continue;
            }else{
                //answer is valid
                if (valid_answer(category,dollars,answer)){
                   printf("Correct!\n");
                   players[current_player].score+=dollars;
                }else{
                   printf("Incorrect!\n");
                }
            }
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
