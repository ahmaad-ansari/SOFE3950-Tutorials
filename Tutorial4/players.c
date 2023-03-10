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
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, char *name)
{
    for(int i = 0; i < NUM_PLAYERS; i++){
        if(strcmp(players[i].name, name) == 0){
            return true;
        }
    }
    return false;
}

// Go through the list of players and update the score for the 
// player given their name
void update_score(player *players, char *name, int score)
{
    for(int i = 0; i < NUM_PLAYERS; i++){
        if(strcmp(players[i].name, name) == 0){
            players[i].score += score;
        }
    }
}
