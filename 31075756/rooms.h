//
// Created by Jack on 2/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

//room structure
struct Room{
    char *desc;
    int visited;
    struct Item *items;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    struct Room *up;
    struct Room *down;
};

//create a room structure
struct Room *room(char *desc, int visited, struct Item *items,
                   struct Room *north, struct Room *south,
                   struct Room *east, struct Room *west,
                   struct Room *up, struct Room *down);

//exit the current room to a random room in given direction
int room_exit_north(struct Room *current, struct Room *other);

//exit the current room to a random room in given direction
int room_exit_east(struct Room *current, struct Room *other);

//exit the current room to a random room in given direction
int room_exit_south(struct Room *current, struct Room *other);

//exit the current room to a random room in given direction
int  room_exit_west(struct Room *current, struct Room *other);

//exit the current room to a random room in given direction
int  room_exit_up(struct Room *current, struct Room *other);

//exit the current room to a random room in given direction
int room_exit_down(struct Room *current, struct Room *other);

//possible paths, aka still random rooms avl
int possible_paths();

//get a random room to use in room exit method
struct Room *get_random_room(struct Room *head[]);

//minus totalrooms
void minusroom();