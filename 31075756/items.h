//
// Created by Jack on 2/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Item structure that lets you use items within the project
struct Item
{
    char *name;
    char *desc;
    struct Item *next;
};

//create an item structure
struct Item *item(char *name, char *desc, struct Item *next);

//returns item name
const char *item_name(struct Item *item);

//return item desc
const char *item_desc(struct Item *item);

//returns next item
struct Item *item_next(struct Item *item);

//takes an item and also removes it from the room list
struct Item *item_take(struct Item **item, char *name);

//add an item to the current list of items
void item_add(struct Item** list,struct Item* item);

//print out the current list of items
void print_items(struct Item *list);

//returns the amount of items for the given structure
int amountOfItems(struct Item* list);

//returns if the item exists within the inventory
int itemInInv(struct Item* list,char *item);

//frees the passed item and proceeding items within the list
void itemFree(struct Item* items);