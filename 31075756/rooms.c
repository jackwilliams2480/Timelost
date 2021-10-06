//
// Created by Jack on 2/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rooms.h"

//not including starting room
#define ROOMS 7;
int totalrooms = 7;

struct Room *room(char *desc, int visited, struct Item *items,
                  struct Room *north, struct Room *south,
                  struct Room *east, struct Room *west,
                  struct Room *up, struct Room *down) {
    struct Room *r = (struct Room *) malloc(sizeof(struct Room));
    r->desc = desc;
    r->items = items;
    r->north = north;
    r->south = south;
    r->east = east;
    r->west = west;
    r->up = up;
    r->down = down;
    r->visited = 0;
    return r;
}

int room_exit_north(struct Room *current, struct Room *other) {
    if(current == NULL || other == NULL){
        return 0;
    }
    current->north = other;
    return 1;
    //cannot go back
}

int room_exit_east(struct Room *current, struct Room *other) {
    if(current == NULL || other == NULL){
        return 0;
    }
    current->east = other;
    other->west = current;
    return 1;
}

int room_exit_south(struct Room *current, struct Room *other) {
    if(current == NULL || other == NULL){
        return 0;
    }
    //you are not allowed to exit south
}

int room_exit_west(struct Room *current, struct Room *other) {
    if(current == NULL || other == NULL){
        return 0;
    }
    current->west = other;
    other->east = current;
    return 1;
}

int room_exit_up(struct Room *current, struct Room *other) {
    if(current == NULL || other == NULL){
        return 0;
    }
    current->up = other;
    other->down = current;
    return 1;
}

int room_exit_down(struct Room *current, struct Room *other) {
    if(current == NULL || other == NULL){
        return 0;
    }
    current->down = other;
    other->up = current;
    return 1;
}

int possible_paths() {
    return totalrooms;
}

struct Room* get_random_room(struct Room *head[]){
    if(totalrooms == 0){
        printf("You have ran out of possible paths without finishing the game! You have lost\n");
        return NULL;
    }

    int n,rooms;
    rooms = ROOMS;
    time_t t;
    srand((unsigned) time(&t));
    n = rand() % rooms + 1;

    while(head[n]->visited == 1){
        n = rand() % rooms + 1;
    }
    head[n]->visited = 1;
    totalrooms--;
    return head[n];
}

void minusroom(){
    totalrooms--;
};

