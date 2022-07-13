/*
Authorship statement:
Program Written by Rajneesh Gokool with student ID 1101512.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_CARDS 100
#define CARD_ID_LENGTH 8
#define STAGE_NUM_ONE 1                  /* stage numbers */ 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define HEADER  "=========================Stage %d=========================\n"
#define END_OF_CARDS "%%%%%%%%%%"
#define TRANSACTION_ID_LENGTH 12
#define DATE 10
#define TIME 20
#define OVER_BOTH_LIMITS "OVER_BOTH_LIMITS"
#define IN_BOTH_LIMITS "IN_BOTH_LIMITS"
#define OVER_DAILY_LIMIT "OVER_DAILY_LIMIT"
#define OVER_TRANS_LIMIT "OVER_TRANS_LIMIT"

/* Structs*/
/*=========================================================================*/
typedef struct {

    char card_ID[CARD_ID_LENGTH + 1];
    int daily_limit;
    int transaction_limit;
    
    /* used in stage four - a transaction date*/
    char date[DATE+1];
    /* used in stage four - the amount spent*/    

    int used_daily_limit;    
} card_t;

typedef struct {
    char transaction_ID[TRANSACTION_ID_LENGTH + 1];   
    char card_ID[CARD_ID_LENGTH + 1];
    char time[TIME + 1];
    int transaction_amount; 
} transaction_t;

// create a linked list of Struct
typedef struct transactions transactions_t; 
struct transactions {

    transaction_t tx_data;
    transactions_t *next;
};

// Access to the foot or head of the linked list
typedef struct {  
    transactions_t *head;
    transactions_t *foot;
} transaction_list_t;


/*=========================================================================*/
/*      Stage functions                                                    */
/*=========================================================================*/
void stage_one(card_t* cards);
void stage_two(card_t* cards, int* num_cards);
void stage_three(transaction_list_t *transactions_list, int* num_transactions);

void stage_four(card_t* cards, int num_cards, 
transaction_list_t *transactions_list);

/*=======================================================================*/
/* Healper functions                                                     */
/*=======================================================================*/
void print_stage_header(int stage_num);
void read_word(char* s);                                    
int  read_one_card(card_t* card);              
void read_cards(card_t *cards,int *num_cards); 
int  read_one_transaction(transaction_t *tx_new); 

void read_transactions(transaction_list_t *transactions_list, 
int* num_transactions); 

void limits_check(card_t *sel_card, transaction_t *tx_data);
transaction_list_t *make_empty_list(void);        
void free_list(transaction_list_t *list) ;

transaction_list_t *insert_at_foot(transaction_list_t *list, 
transaction_t value); 
/*========================================================================*/

/*******************************/
/* main and stages' function */
/*******************************/
int main(int argc, char *argv[]){
    card_t cards[MAX_CARDS]; 
    transaction_list_t *transaction_list= make_empty_list();
    
    stage_one(cards);
    
    /* At least one card is in the file.*/
    int num_cards = 1; 
    stage_two(cards, &num_cards);
    
    int num_transaction =0;
    stage_three(transaction_list, &num_transaction);   
    stage_four(cards, num_cards, transaction_list);
    free_list( transaction_list);
}

void print_stage_header(int stage_num){
    printf(HEADER, stage_num);
}

void stage_one(card_t *cards){
    /* Function to read the first card and output its contents.*/
    print_stage_header(STAGE_NUM_ONE);
   
    /* read the first card*/
    read_one_card(&cards[0]); 
    
    /* do the output needed*/
    printf("Card ID: %s\n", cards[0].card_ID);
    printf("Daily limit: %u\n", cards[0].daily_limit);
    printf("Transaction limit: %u\n\n", cards[0].transaction_limit);
}

void stage_two(card_t* cards, int* num_cards){
    /*Function to first read remaining card, loop on all the cards, 
    add all together, get the average for the 
    daily limit and card with largest transaction limit.*/
    
    double sum = 0,average_daily_limit;
    int largest = 0;
    char largest_ID[CARD_ID_LENGTH+1];
    
    print_stage_header(STAGE_NUM_TWO);
    
    read_cards(cards, num_cards); 

   /* find the max Transaction_limit (largest) and calculate 
   the avg daily limit */
    for(int i = 0; i < *num_cards; i++){  
        if(cards[i].transaction_limit > largest){
            largest = cards[i].transaction_limit;
            strcpy(largest_ID, cards[i].card_ID);
        }
        sum += cards[i].daily_limit;
    }
    average_daily_limit = sum / *num_cards;

    /* do the output needed*/
    printf("Number of credit cards: %d\n", *num_cards);
    printf("Average daily limit: %.2f\n", average_daily_limit);
    printf("Card with the largest transaction limit: %s\n\n", largest_ID);     
}

void 
stage_three(transaction_list_t *transactions_list, int* num_transactions){
    /* Function to read the transactions to a linked list requried 
    to store the transactions and do the necessary output
    */
    print_stage_header(STAGE_NUM_THREE);
    
    read_transactions(transactions_list, num_transactions);
    
    /* do the output needed*/
    transactions_t *current = transactions_list->head;
    while (current != NULL)  {
        printf("%s\n", current->tx_data.transaction_ID);
        current = current->next;
    };
    printf("\n");
}

void stage_four(card_t* cards, int num_cards, 
transaction_list_t *transactions_list){
    
    /*Function to search the corresponding card of a transaction from   
    the linked list to the cards struct using binary search  
    then we check if the limits  are exceeded or not.*/
    
    print_stage_header(STAGE_NUM_FOUR);
    
    card_t * sel_card;
    char card_id[CARD_ID_LENGTH+1];

    transactions_t *current = transactions_list->head;
    while (current != NULL)  {
        /* go thru the transaction linked list*/
        /* get the card_id to search*/
        strcpy(card_id,current->tx_data.card_ID); 

        /* search using bsearch of “stdlib.h”*/
        sel_card = bsearch(&card_id, cards, 
        num_cards, sizeof(card_t), (int(*)(const void*, const void*))strcmp);

        printf("%s             " , current->tx_data.transaction_ID);
        limits_check(sel_card, &current->tx_data);
        current = current->next;
    }
}

/* ======================= */
/* Linked list functions
These functions are modified versions of that of Alistair Mofatt.
 
 Program written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
*/
/* ======================= */
transaction_list_t *make_empty_list(void) {
    // create an empty linked list
    transaction_list_t *list;
    list = (transaction_list_t*)malloc(sizeof(*list));
    assert(list!=NULL);
    list->head = list->foot = NULL;
    return list;
}

void free_list(transaction_list_t *list) {
    // free a  linked list
    transactions_t *curr, *prev;
    assert(list!=NULL);
    curr = list->head;
    while (curr) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(list);
}

transaction_list_t *
insert_at_foot(transaction_list_t *list, transaction_t value) {
    /* Add a new element at the foot of a linked list*/
    transactions_t *new;
    new = (transactions_t*)malloc(sizeof(*new));
    assert(list!=NULL && new!=NULL);
    new->tx_data = value;
    new->next = NULL;
    if (list->foot==NULL) {
        /* this is the first insertion into the list */
        list->head = list->foot = new;
    } else {
        list->foot->next = new;
        list->foot = new;
    }
    return list;
}

/* ======================= */

/* Other functions         */
/* ======================= */
void read_word(char* s){
     /*Function to read from stdin and get one string.*/
    
    int j = 0;
    char c;
    for (unsigned int i=0; i <sizeof(s);i++) {
        s[i]='\0';
    }
    while (((c = getchar()) != EOF) ){
          if ((c==' ') | (c == '\n') | (c == '\r')) {
              s[j]='\0';
              break;
          } 
          s[j] = c ;
          j++;      
    }
}

int read_one_card(card_t* card){  
    /*Function to call read_word() to get one card details and then store 
    the data from it in the respective data fields*/
    
    int cnt_word=0;
    while (1) {

        /*Array to store one component of card with maximum size of the Date*/       
        char word[DATE + 1];

        read_word(word);
        if (cnt_word==0){
           if ((word[0]=='%') | (word[0]=='\0') ) return 1;
           strcpy(card->card_ID, word);
           cnt_word++;
        } else if (cnt_word==1){   
           card->daily_limit =atoi(word);
           cnt_word++;
        } else {
           card->transaction_limit = atoi(word);
           return 0;
        }
    }
}

void read_cards(card_t* cards,int *num_cards){  
    /*
     read all cards from the input*/  
    int check;
    while(1){
        check = read_one_card(&cards[*num_cards]);

        /*Check if we reached end of cards*/
        if (check) break;
        *num_cards = *num_cards + 1;
    }
}

int read_one_transaction(transaction_t *tx_new){
    /*Function to call read_word() to get one transaction details 
    and then store the data from it in the respective data fields*/
    
    /*variable cnt_word used to count number of spaces to know in which field
    should data be put*/
    int cnt_word=0;
    while (1) {
        /*Array to store one component of a transaction 
        with maxinum size be that of date-time*/
        char word[TIME + 1];

        read_word(word);
        if (cnt_word==0){
           if ((word[0]=='%') | (word[0]=='\0') ) return 1;
           strcpy(tx_new->transaction_ID, word);
           cnt_word++;
        } else if (cnt_word==1){   
           strcpy(tx_new->card_ID, word);
           cnt_word++;
        } 
        else if (cnt_word==2){   
           strcpy(tx_new->time, word);
           cnt_word++;
        } else {
           tx_new->transaction_amount = atoi(word);
           return 0;
        }
    }
}

void read_transactions(transaction_list_t *transactions_list, 
int* num_transactions){ 
    
   /*function to read all transactions from the input and put it in the
   linked list.*/
    
    while (1){
        transaction_t tx_new;
        if (read_one_transaction(&tx_new)) break;
        insert_at_foot(transactions_list, tx_new);
        *num_transactions+=1;                
    }
}



void limits_check(card_t *sel_card, transaction_t *tx_data){
    /* Function to check if 
    1. the transaction amount has exceed limit or not.
    2. if not then we store the amount used to keep track if daily limit is 
    used up for a particular date.*/
    
    char date[DATE+1];
    
    /* get the transactions's date*/
    strncpy(date,tx_data->time, DATE); 
    date[DATE]='\0';

    /*check if a card already has a transaction recorded*/
    if (strcmp(sel_card->date, date)!=0){
        strcpy(sel_card->date, date);
        sel_card->used_daily_limit=0;
    }

    sel_card->used_daily_limit += tx_data->transaction_amount;

    if (tx_data->transaction_amount > sel_card->transaction_limit) {
        if (sel_card->used_daily_limit > sel_card->daily_limit){
            printf("%s\n",  OVER_BOTH_LIMITS  );    
        } else {
            printf("%s\n", OVER_TRANS_LIMIT );
        }    
    } 
    else{
        if(sel_card->used_daily_limit > sel_card->daily_limit){
            printf("%s\n", OVER_DAILY_LIMIT );
        }
        else{
            printf("%s\n", IN_BOTH_LIMITS );

        }
    }
       
}



/* For stage 4 we go through the list of transaction (n) and we use bsearch
through the list of cards(m) since the are already sorted,hence, log m
so the time complexity is O(nlogm)*/

/*Algorithms are fun!*/
