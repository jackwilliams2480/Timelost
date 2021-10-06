#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keyword.h"

int main() {
    /*
     * Created by Jack Williams for CS230
     * I dont know if this is necessary but im writing this here just incase. I took a lot of the game descriptions from one of my favorite online extended universe games called Destiny.
     * So the lore used here is not 100% my own writing, but the entire game is my own extension using the lore in the game. The link to the lore website I used is
     * https://destiny.fandom.com/wiki/Destiny_Wiki and also https://www.destinypedia.com/Venus (note that this game is not a text based adventure game but a large MMOFPS game from Bungie)
     * Throwing in my sources here just incase whatever you use to check plagiarism ends up tagging me, hopefully not though!
     */
    struct Room *startingRoom = room(
            "\"Welcome back Doctor Shim\", you hear a female robotic voice chime at you. \"Good Morning\", you say back, as you\n"
                  "enter into the research laboratory. You remember from last night that you had just received a new live Vex specimen\n"
                  "to examine for today, subject 12, and are eager to begin."
                  ,1,NULL,NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *lab = room(
            "~Lab~\n"
            "You enter a room that contains large scale incubation tubes of the Vex species. You spot a Esi, a colleague working\n"
                  "on one of the tubes who seems distressed. You approach her to ask about what she is working on...\n"
                  "You have acquired an OMEN!\n",0,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *library = room(
            "~Event Triggered~\n"
            "You have entered the library of the research facility, otherwise known as the ishtar archives. This place contains\n"
            "the greatest compilation of knowledge through the system and details many expansive scientific breakthroughs.\n"
            "While looking for a textbook to check more on the Vex mind, you accidentally stumble upon a secret lever.\n"
            "Hmmm... I wonder what this does. You pull the lever, but nothing seems to happen...",0,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *network = room(
            "Networking room\n"
            "You enter the center hub for both the power and networking infrastructure of the research facility. Something seems off...\n"
            "You see what seems to be some type of weird centipede crawl across the floor and under one of the servers. That looks\n"
            "an awful lot like a Vex machine you think to yourself.\n"
            "You have acquired an OMEN!\n",0,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *hallway = room(
            "You enter a hallway that connects the research facilities. Under you is glass floor in which\n"
            "you can see water towers. These are what provide us clean water to drink from.",0,
            item("Notes", "Research notes that detail what you have learned from the vex",
                 NULL), NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *eventRoom = room(
            "~Event Room~\n"
            "You accidentally stumble into Maya's room, another colleague of yours, and one that has been studying the complexities\n"
            "of the vex mind. She breaks some concerning news to you, that the vex are currently simulating the entire research lab with 100% accuracy.\n"
            "She says that, \"We're inside it. By any reasonable philosophical standard, we are inside that Vex.\"\n"
            "You start to thing about the implications of this...If the Vex can simulate this entire facility,\n"
            " how can we be sure we are not in a simulation right now? You decide to call a team meeting...\n"
            "~Hmmmm, I have a weird feeling about this. I have an indescribable feeling that something is horribly wrong.~"
            ,0,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *bedroom = room(
            "You have made it to you bedroom. Feel free to store and items you currently have in your bedroom. ",0,
            item("Radiolarian_fluid", "Part of the organic material found in the vex.",
                 NULL), NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *mystery = room(
            "Werid... how did I get here? Im almost positive ive never seen this room before. \n"
            "Hmmm I wonder if this has anything to do with Mayas research. A piece of paper is lying on one of the research tables.\n"
            " The only thing written on it is the words\n"
            "\"hezen_corrective\"\n"
            "Hmmm what could this mean? ",0,
            item("Mind_forking_device", "A colleagues side project, I wonder what it does...", NULL), NULL, NULL, NULL, NULL, NULL, NULL);


    struct Room *list[8];
    list[0] = startingRoom; //starting room
    list[1] = lab; //Omen
    list[2] = library; //first event room
    list[3] = network; //Omen
    list[4] = hallway;
    list[5] = eventRoom; //second event room
    list[6] = bedroom; //storage
    list[7] = mystery; //teleport mechanic

    struct useItems *itemkey[3];
    itemkey[0] = itemList("Notes",0);
    itemkey[1] = itemList("Radiolarian_fluid",0);
    itemkey[2] = itemList("Mind_forking_device",0);

    struct Keyword *keywords = keyword("look", keyword("go",keyword("take",
            keyword("drop", keyword("inventory",keyword("exit",keyword("hezen_corrective",NULL)))))));

    char keyword[50];
    char item[50];
    int i = 0;
    struct Player *p = player(startingRoom, NULL);

    //main game loop
    printf("======================================== Welcome to the Vault of Glass! ========================================\n\n");
    printf("During the golden age of humanity, Venus was colonized and considered a paradise. An entity named the \'traveler\' was\n"
           "able to tera-form Venus into a prosperous, ecological, and habitable planet. Although this feat was met with great\n"
           "strides within humanity, what also came as a result was the introduction of the hostile machine subspecies named the\n"
           " Vex. Without going into much detail, the Vex  are a collective intelligence of time-traveling cybernetic\n"
           "war-machines. They operate under a single mind, interconnected to each other at all times, and their minds hold\n"
           "infinite computational power...\n\n");
    printf("%s\n",list[0]->desc);

    while (possible_paths() != 0) {
        printf("\n================================================================================================================\n\n");
        printf("Enter a command: ");
        scanf("%s", keyword);
        if (strcmp(keyword, "look") == 0 || strcmp(keyword, "inventory") == 0 || strcmp(keyword, "exit") == 0 || strcmp(keyword, "hezen_corrective") == 0) {
            parse_command(keyword, "", p,list,itemkey);
            printf("\n");
        } else {
            scanf("%s", item);
            if (parse_command(keyword, item, p,list,itemkey) == 0) {
                printf("Error: That command was not recognized\n");
            }
        }
        //winning state
        if((p->currentroom == list[0] && p->omens >= 1 && amountOfItems(p->items) >= 2) || itemkey[2]->state > 0){
            printf("\n==================== You have met a winning condition of the game! ====================\n");
            printf("Here is a list of your final items:\n");
            print_items(p->items);
            printf("Thank you for playing!\n");
            //free all memory

            free(p);
            keywordsFree(keywords);
            itemFree(startingRoom->items);
            itemFree(lab->items);
            itemFree(library->items);
            itemFree(network->items);
            itemFree(eventRoom->items);
            itemFree(bedroom->items);
            itemFree(mystery->items);
            itemFree(hallway->items);
            for(i = 0;i < 8;i++){
                free(list[i]);
                if(i < 3){
                    free(itemkey[i]);
                }
            }
            return 0;
        }
    }
    printf("\n==================== You have ran out of rooms! ====================\n");
    printf("You have lost with these remaining items in your list\n");
    print_items(p->items);
    //free malloc memory
    free(p);
    keywordsFree(keywords);
    itemFree(startingRoom->items);
    itemFree(hallway->items);
    itemFree(lab->items);
    itemFree(library->items);
    itemFree(network->items);
    itemFree(eventRoom->items);
    itemFree(bedroom->items);
    itemFree(mystery->items);
    for(i = 0;i < 8;i++){
        free(list[i]);
        if(i < 3){
            free(itemkey[i]);
        }
    }
    return 0;
}
