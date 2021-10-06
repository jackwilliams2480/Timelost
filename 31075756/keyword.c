//
// Created by Jack on 2/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keyword.h"
int eventroomtriggerfirst = 0;
int eventroomtriggersecond = 0;

struct Keyword *keyword(char *keyword, struct Keyword *next) {
    struct Keyword *k = (struct Keyword *) malloc(sizeof(struct Keyword));
    k->keyword = keyword;
    k->next = next;
    return k;
}

struct useItems *itemList(char *name, int state){
    struct useItems *u = (struct useItems*) malloc(sizeof(struct useItems));
    u->name = name;
    u->state = state;
    return u;
}

struct Player *player(struct Room *room, struct Item *itemlist) {
    struct Player *p = (struct Player *) malloc(sizeof(struct Player));
    p->omens = 0;
    p->currentroom = room;
    p->items = itemlist;
    return p;
}

int parse_command(char *command, char *item, struct Player *player,struct Room *list[],struct useItems *itemkey[]) {
    //takes given command and does the according command
    if (strcmp(command, "look") == 0) {
        area_desc(player);
        return 1;
    } else if (strcmp(command, "inventory") == 0) {
        printf("Your inventory consists of:");
        print_items(player->items);
        return 1;
    } else if (strcmp(command, "exit") == 0) {
        exit(0);
    } else if (strcmp(command, "take") == 0) {
        struct Item *i = player->currentroom->items;
        while (i != NULL) {
            if (strcmp(item, i->name) == 0) {
                printf("You have successfully picked up item %s\n", i->name);
                item_add(&(player->items), item_take(&(player->currentroom->items), item));
                return 1;
            }
            i = i->next;
        }
        printf("Error: Item not found\n");
    } else if (strcmp(command, "drop") == 0) {
        struct Item *i = player->items;
        while (i != NULL) {
            if (strcmp(item, i->name) == 0) {
                printf("You have successfully dropped item %s\n", i->name);
                item_add(&(player->currentroom->items), item_take(&(player->items), item));
                return 1;
            }
            i = i->next;
        }
        printf("Error: Item not found\n");
        //main command that lets you go to a given room
    } else if (strcmp(command, "go") == 0) {
        if(strcmp(item,"north") == 0){
            if(eventRoom(player, list,item) == 1){
                area_desc(player);
                return 1;
            }
            if(player->currentroom->north != NULL){
                player->currentroom = player->currentroom->north;
                area_desc(player);
            }else {
                if(room_exit_north(player->currentroom, get_random_room(list)) == 0){
                    return 0;
                }
                player->currentroom = player->currentroom->north;
                omen(player, list);
                area_desc(player);
            }
            return 1;
        }else if(strcmp(item,"east") == 0){
            if(eventRoom(player, list,item) == 1){
                area_desc(player);
                return 1;
            }
            if(player->currentroom->east != NULL){
                player->currentroom = player->currentroom->east;
                area_desc(player);
            }else {
                if(room_exit_east(player->currentroom, get_random_room(list)) == 0){
                    return 0;
                }
                player->currentroom = player->currentroom->east;
                omen(player, list);
                area_desc(player);
            }
            return 1;
        }else if(strcmp(item,"south") == 0){
            printf("You cannot go back\n");
            return 0;
        }else if(strcmp(item,"west") == 0){
            if(eventRoom(player, list,item) == 1){
                area_desc(player);
                return 1;
            }
            if(player->currentroom->west != NULL){
                player->currentroom = player->currentroom->west;
                area_desc(player);
            }else {
                if(room_exit_west(player->currentroom, get_random_room(list)) == 0){
                    return 0;
                }
                player->currentroom = player->currentroom->west;
                omen(player, list);
                area_desc(player);
            }
            return 1;
        }else if(strcmp(item,"up") == 0){
            if(eventRoom(player, list,item) == 1){
                area_desc(player);
                return 1;
            }
            if(player->currentroom->up != NULL){
                player->currentroom = player->currentroom->up;
                area_desc(player);
            }else {
                if(room_exit_up(player->currentroom, get_random_room(list)) == 0){
                    return 0;
                }
                player->currentroom = player->currentroom->up;
                omen(player, list);
                area_desc(player);
            }
            return 1;
        }else if(strcmp(item,"down") == 0){
            if(eventRoom(player, list,item) == 1){
                area_desc(player);
                return 1;
            }
            if(player->currentroom->down != NULL){
                player->currentroom = player->currentroom->down;
                area_desc(player);
            }else {
                if(room_exit_down(player->currentroom, get_random_room(list)) == 0){
                    return 0;
                }
                player->currentroom = player->currentroom->down;
                omen(player, list);
                area_desc(player);
            }
            return 1;
        }else{
            printf("Error: please re-enter desired direction\n");
            return 0;
        }
    }else if(strcmp(command, "hezen_corrective") == 0){
        printf("The Vex have no hope. No imagination, no drive, no fear. All they have is the Pattern.\n"
               "Everything must fit. If it can be made to fit, good. If it can't, it gets cut away.\n");
        printf("Without knowing it, you have recited a Vex command. You feel your body getting weak.\n");
        player->currentroom = list[0];
        printf("You suddenly find yourself in the starting room. Weird, this feels like deja vu...\n");
        area_desc(player);
    }else if(strcmp(command,"use") == 0){
        //Water Bottle
        if(strcmp(item,itemkey[0]->name) == 0 && itemInInv(player->items,item) == 1){
            printf("~Hint: using the Mind_forking_device in the lab will allow you to travel into the vex mind and stop\n"
                   "the paradox from eventually driving the research team mad.\n");
            return 1;
            //Radiolarian fluid
        }else if(strcmp(item,itemkey[1]->name) == 0 && itemInInv(player->items,item) == 1){
            if(itemkey[1]->state == 1){
                printf("You have already used this item");
                return 1;
            }
            printf("This fluid can be found inside the vex, it is an organic material that hosts the Vex's true form.\n"
                   "You have now given yourself the ability to enter the mind of the vex via the Mind_forking_device!\n");
            itemkey[1]->state = 1;
            return 1;
        }else if(strcmp(item,itemkey[2]->name) == 0 && itemInInv(player->items,item) == 1){
            if(itemkey[1]->state == 1 && player->currentroom == list[1]){
                printf("You have successfully used the Mind forking device within the lab, and have Won the game!\n");
                itemkey[2]->state = 1;
                return 1;
            }else{
                printf("You have not met the right conditions for this item, and therefore cannot use it.\n");
                return 1;
            }
        }else{
            printf("You either cannot use that item at this moment, or that item does not exist\n");
            return 0;
        }


    }
    return 0;
}

void area_desc(struct Player *player){
    printf("\n%s\n", player->currentroom->desc);
    printf("You notice that there are some items in the room...");
    print_items(player->currentroom->items);
}

int eventRoom(struct Player *p, struct Room* list[],char *dir){
    if(eventroomtriggerfirst == 1 && eventroomtriggersecond == 1){
        return 0;
    }
    if(p->currentroom == list[2] && eventroomtriggerfirst == 0){
        eventRoomMove(p,list,dir);
        eventroomtriggerfirst = 1;
        return 1;
    }else if(p->currentroom == list[5] && eventroomtriggersecond == 0){
        eventRoomMove(p,list,dir);
        eventroomtriggersecond = 1;
        return 1;
    }
    return 0;
}

void omen(struct Player *p, struct Room* list[]){
    if(p->currentroom == list[3] || p->currentroom == list[1]){
        p->omens++;
    }
}

int eventRoomMove(struct Player *p,struct Room *list[], char *dir){
    if(strcmp(dir,"north") == 0){
        if(list[0]->south == NULL || p->currentroom->north == NULL){
            list[0]->south = p->currentroom;
            p->currentroom->north = list[0];
            p->currentroom = list[0];
        }else{
            findAvlDir(p,list);
        }
        return 1;
    }else if(strcmp(dir,"east") == 0){
        if(list[0]->west == NULL || p->currentroom->east == NULL){
            list[0]->west = p->currentroom;
            p->currentroom->east = list[0];
            p->currentroom = list[0];
        }else{
            findAvlDir(p,list);
        }
        return 1;
    }else if(strcmp(dir,"south") == 0){
        printf("You cannot go back\n");
        return 0;
    }else if(strcmp(dir,"west") == 0 ){
        if(list[0]->east == NULL || p->currentroom->west == NULL){
            list[0]->east = p->currentroom;
            p->currentroom->west = list[0];
            p->currentroom = list[0];
        }else{
            findAvlDir(p,list);
        }
        return 1;
    }else if(strcmp(dir,"up") == 0){
        if(list[0]->down == NULL || p->currentroom->up == NULL){
            list[0]->down = p->currentroom;
            p->currentroom->up = list[0];
            p->currentroom = list[0];
        }else{
            findAvlDir(p,list);
        }
        return 1;
    }else if(strcmp(dir,"down") == 0) {
        if(list[0]->up == NULL || p->currentroom->down == NULL){
            list[0]->up = p->currentroom;
            p->currentroom->down = list[0];
            p->currentroom = list[0];
        }else{
            findAvlDir(p,list);
        }
        return 1;
    }
    return 0;
}

int findAvlDir(struct Player *p,struct Room *list[]){
    if(list[0]->north == NULL || p->currentroom->south == NULL){
        list[0]->north = p->currentroom;
        p->currentroom->south = list[0];
        p->currentroom = list[0];
        return 1;
    }else if(list[0]->east == NULL || p->currentroom->west == NULL){
        list[0]->east = p->currentroom;
        p->currentroom->west = list[0];
        p->currentroom = list[0];
        return 1;
    }else if(list[0]->west == NULL || p->currentroom->east == NULL){
        list[0]->west = p->currentroom;
        p->currentroom->east = list[0];
        p->currentroom = list[0];
        return 1;
    }else if(list[0]->up == NULL || p->currentroom->down == NULL){
        list[0]->up = p->currentroom;
        p->currentroom->down = list[0];
        p->currentroom = list[0];
        return 1;
    }else if(list[0]->down == NULL || p->currentroom->up == NULL){
        list[0]->down = p->currentroom;
        p->currentroom->up = list[0];
        p->currentroom = list[0];
        return 1;
    }else if(list[0]->south == NULL || p->currentroom->north == NULL){
        list[0]->south = p->currentroom;
        p->currentroom->north = list[0];
        p->currentroom = list[0];
        return 1;
    }else{
        printf("Event failed, no more available locations\n");
        return -1;
    }
}

void addKeyword(struct Keyword *k,char *key){
    if(k == NULL){
        k = keyword(key,NULL);
    }
    struct Keyword *temp = k;
    while(temp != NULL){
        temp = temp->next;
    }
    temp->next = k;
}

void keywordsFree(struct Keyword* k){
    if(k != NULL){
        keywordsFree(k->next);
        free(k);
    }
}