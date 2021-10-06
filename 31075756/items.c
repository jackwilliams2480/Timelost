//
// Created by Jack on 2/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

//create an item structure
struct Item *item(char *name, char *desc, struct Item *next)
{
    struct Item *i = (struct Item *)malloc(sizeof(struct Item));
    i->name = name;
    i->desc = desc;
    i->next = next;
    return i;
}

//returns name of this item
const char *item_name(struct Item *item)
{
    return item->name;
}

//returns description of this item
const char *item_desc(struct Item *item)
{
    return item->desc;
}

//returns next linked Item
struct Item *item_next(struct Item *item)
{
    return item->next;
}

struct Item *item_take(struct Item **item, char *name)
{
    if(item == NULL || *item == NULL){
        return NULL;
    }

    struct Item *head = *item;

    if (strcmp(head->name, name) == 0)
    {
        *item = (*item)->next;
        head->next = NULL;
        return head;
    }

    struct Item *curr = *item;
    struct Item *next = (*item)->next;

    while (next != NULL)
    {
        if (strcmp(next->name, name) == 0)
        {
            curr->next = next->next;
            next->next = NULL;
            return next;
        }
        next = next->next;
        curr = curr->next;
    }
}

void item_add(struct Item **list,struct Item *item){
    if(*list == NULL){
        *list = item;
        return;
    }
    struct Item *temp = *list;
    while((temp)->next != NULL){
        (temp) = (temp)->next;
    }
    (temp)->next = item;
}

void print_items(struct Item *list){
    if(list == NULL){
        printf("\n ~empty~ ");
    }
    struct Item *i = list;
    while(i != NULL){
        printf("\n%s: %s",i->name,i->desc);
        i = i->next;
    }
    printf("\n");
}

int amountOfItems(struct Item* list){
    if(list == NULL){
        return 0;
    }
    int itemcount = 0;
    struct Item *i = list;
    while(i != NULL){
        itemcount++;
        i = i->next;
    }
    return itemcount;
}

int itemInInv(struct Item* list,char *item){
    if(list == NULL){
        return 0;
    }
    struct Item *i = list;
    while(i != NULL){
        if(strcmp(i->name,item) == 0){
            return 1;
        };
        i = i->next;
    }
    return 0;
}

void itemFree(struct Item* items){
    if(items != NULL){
        itemFree(items->next);
        free(items);
    }
}