//
// Created by Jack on 2/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"

//keyword structure
struct Keyword{
    char *keyword;
    struct Keyword *next;
};

//player structure to store the current room
struct Player{
    int omens;
    struct Room *currentroom;
    struct Item *items;
};

//structure items
struct useItems{
    char *name;
    int state;
};

//create keyword structure
struct Keyword *keyword(char* keyword,struct Keyword *next);

//the main method that takes in commands through the command line
int parse_command(char* command, char* item,struct Player *player,struct Room *list[],struct useItems *itemkey[]);

//create player structure
struct Player *player(struct Room *room,struct Item *itemlist);

//prints out the area desc
void area_desc(struct Player *player);

//if the given room is an event room
int eventRoom(struct Player *p, struct Room* list[],char *dir);

//add count to omen list
void omen(struct Player *p, struct Room* list[]);

//find possible direction
int findAvlDir(struct Player *p,struct Room *list[]);

//move method for the event room
int eventRoomMove(struct Player *p,struct Room *list[], char *dir);

//creates the useItems list
struct useItems *itemList(char *name, int state);

//add keyword to list
void addKeyword(struct Keyword *k,char *key);

//free keywords
void keywordsFree(struct Keyword* k);
