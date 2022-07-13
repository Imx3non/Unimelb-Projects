/* Emoticon message cleanser

Algorithms are fun!
 *
//
 *
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STAGE_NUM_ONE 1                            /* stage numbers */ 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5
#define STAGE_HEADER "Stage %d\n==========\n"  /* stage header format string */

#define MAX_MSG_LENGTH 280                      /* maximum message length */
#define MAX_NUM_MSGS 100                      /* maximum number of messages */
#define MAX_EMTCN_LENGTH 50                    /* maximum emot. line length */
#define MAX_NUM_EMTCN 50                       /* maximum number of emot. */

typedef char msg_t[MAX_MSG_LENGTH + 1];            /* a message */
typedef char emtcn_t[MAX_EMTCN_LENGTH + 1];        /* an emoticon */

/****************************************************************/

/* function prototypes */
void read_one_msg(msg_t one_msg, int max_len);
void print_stage_header(int stage_num);
int count_tokens(msg_t one_msg);

void stage_one(msg_t one_msg);
void stage_two(msg_t msgs[], int* num_msgs);
void stage_three(msg_t msgs[], int num_msgs);
void stage_four(emtcn_t emtcns[], int* num_emtcns);
void stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns);

/* add your own function prototypes here */
void removeAlphaNum(msg_t msgs[], int* num_msgs);
void removeAlphaNum_1(msg_t msgs[], int* num_msgs);
void removeTrailComma(msg_t msgs[], int* num_msgs);
void completeFilter(msg_t msgs[], int* num_msgs);
void Add_emtcns(emtcn_t emtcns[], int* num_emtcns);
void removeAlphaNumEmtcns(emtcn_t emtcns[], int* num_emtcns);
void stage_four_result(emtcn_t emtcns[], int* num_emtcns);
void removeUnknown(msg_t msgs[], int num_msgs, emtcn_t emtcns[],
                   int num_emtcns);
void string_compare2(char msg[], emtcn_t emtcns[], int num_emtcns);
/***********s*****************************************************/

/* main function controls all the action, do NOT modify this function */
int
main(int argc, char* argv[]) {
    /* to hold all input messages */
    msg_t msgs[MAX_NUM_MSGS];
    /* to hold the number of input messages */
    int num_msgs = 0;
    /* to hold all input emoticons in the dictionary */
    emtcn_t emtcns[MAX_NUM_EMTCN];
    /* to hold the number of emoticons in the dictionary */
    int num_emtcns = 0;

    /* stage 1: reading the first message */
    stage_one(msgs[num_msgs]);
    num_msgs++;
    //AddMessages(msgs);

    /* stage 2: removing alphanumeric characters */
    stage_two(msgs, &num_msgs);


    /* stage 3: removing extra commas */
    stage_three(msgs, num_msgs);

    /* stage 4: reading the dictionary and finding the longest emoticon */
    stage_four(emtcns, &num_emtcns);

    /* stage 5: removing invalid emoticons with the help of the dictionary */
    stage_five(msgs, num_msgs, emtcns, num_emtcns);

    /* all done; take some rest */
    return 0;
}

/* read a line of input into one_msg */
void
read_one_msg(msg_t one_msg, int max_len) {
    int i = 0, c;
    while (((c = getchar()) != EOF) && (c != '\n') && (c != '\r')) {
        if (i < max_len) {
            one_msg[i++] = c;
        }
        else {
            printf("Invalid input line, toooooooo long.\n");
            exit(EXIT_FAILURE);
        }
    }
    one_msg[i] = '\0';
}

/* print stage header given stage number */
void
print_stage_header(int stage_num) {
    printf(STAGE_HEADER, stage_num);
}

/****************************************************************/
/* add your code below */

/* scan a message and count the number of tokens (separated by commas) in it */
int
count_tokens(msg_t one_msg) {
    int i;
    int count = 0;
    for (i = 0; i < MAX_MSG_LENGTH + 1; i++) {

        if (one_msg[i] == ',') count++;
    }

    /* add code here to count the number commas in one_msg,
       and return the count + 1 */

    return count + 1;
}

/* stage 1: reading the first message */
void
stage_one(msg_t one_msg) {

    read_one_msg(one_msg, MAX_MSG_LENGTH);

    /* add code for stage 1 */
    /* print stage header */
    print_stage_header(STAGE_NUM_ONE);
    //printf("%s", msgs)

    /* read the first message */

    /* count and print the number of tokens */
    printf("Number of tokens: %d\n\n", count_tokens(one_msg));
}

/* stage 2: removing alphanumeric characters */
void
stage_two(msg_t msgs[], int* num_msgs) {
    /* add code for stage 2 */
    print_stage_header(STAGE_NUM_TWO);
    
    
    char temp_msg[MAX_MSG_LENGTH];                         
    while (1) {                                          
        read_one_msg(temp_msg, MAX_MSG_LENGTH);           
        if (strcmp(temp_msg, "###") == 0) break;
        strcpy(msgs[*num_msgs],temp_msg);
       
        *num_msgs += 1;
    }
    removeAlphaNum(msgs, num_msgs);

    printf("\n");
    /* print stage header */
}
/* stage 3: removing extra commas */
void
stage_three(msg_t msgs[], int num_msgs) {
    /* add code for stage 3 */
    /* print stage header */
    print_stage_header(STAGE_NUM_THREE);
    removeTrailComma(msgs, &num_msgs);
    completeFilter(msgs, &num_msgs);
    int message;
    for (message = 0; message < num_msgs; message++) {
        printf("%s\n", msgs[message]);
    } 

    printf("\n");
}

/* stage 4: reading the dictionary and finding the longest emoticon */

void stage_four(emtcn_t emtcns[], int* num_emtcns) {
    /* add code for stage 4 */
    /* print stage header */
    print_stage_header(STAGE_NUM_FOUR);
    Add_emtcns(emtcns, num_emtcns);
    removeAlphaNumEmtcns(emtcns, num_emtcns);
    stage_four_result(emtcns, num_emtcns);

    printf("\n");
}

/* stage 5: removing invalid emoticons with the help of the dictionary */
void
stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns) {
    /* add code for stage 5  */
    /* print stage header */
    print_stage_header(STAGE_NUM_FIVE);

    removeUnknown(msgs, num_msgs, emtcns, num_emtcns);

    //printf("\n");
}

void removeAlphaNum(msg_t msgs[], int* num_msgs){
    /*Function to loop through the messages and then remove the AlphaNUm 
    characters and then store them in original msgs[] and print them.*/

    int message; 
    msg_t filtered_msg[MAX_MSG_LENGTH];
    for (message = 0; message < *num_msgs; message++) {
        int characters = 0;
        int k = 0;
        //add the filtered messages to a new temp array
        while (msgs[message][characters] != '\0') { 
            // loop until the end of the array 
            
            // if 1 just increment index of second arr
            if (isalnum(msgs[message][characters])) { 
                characters++;
            }
            //printf("%d\n",j);}
            else {
                
                 // store message in the temp array
                
                filtered_msg[message][k] = msgs[message][characters];
                characters++;
                k++;
            }
        }
        memset(msgs[message],'\0',MAX_MSG_LENGTH);  
        //copy the filtered msg in the original msgs arr 
        strcpy(msgs[message], filtered_msg[message]); 
        //printf("\n");
    }
    // print the filtered msgs
    for (int i = 0; i < *num_msgs; i++) {
        printf("%s\n", msgs[i]);
    }
}

void removeTrailComma(msg_t msgs[], int* num_msgs) {
    
    /* fucntion to remove the trailling commas between 2 emojis for stage 3*/
   
   int  message; 
    
    // temp array to add filtered msg
    msg_t filtered_msg[MAX_MSG_LENGTH];
    
    for (message = 0; message < *num_msgs; message++) {
        int characters = 0; 
       // used to add the filtered messages to temp array
       int k = 0; 
        while (msgs[message][characters] != '\0') {
            if (msgs[message][characters + 1] != ',' ||         
                          msgs[message][characters] != ',') { 
                filtered_msg[message][k] = msgs[message][characters];
                k++;
                characters++;
            }
            else characters++;
        }
        filtered_msg[message][k] = '\0';
        if (filtered_msg[message][k - 1] == ','){
            filtered_msg[message][k - 1] = '\0';
        }
        memset(msgs[message],'\0',MAX_MSG_LENGTH); 
        strcpy(msgs[message], filtered_msg[message]);
        // printf("%s\n", msgs[ message])
    }
}
void completeFilter(msg_t msgs[], int* num_msgs) {

/* fuction to remove the ending comma that is left from the removeTrailComa  */

    int  message;
    msg_t filtered_msg[MAX_MSG_LENGTH];
    for (message = 0; message < *num_msgs; message++) {
        int characters = 0;
        int k = 0;
        if (msgs[message][0] == ',') characters++;
        while (msgs[message][characters] != '\0') {
            // if(msgs[i][j] == ',' && msgs[i][j + 1] == '\0') k++; break;

            filtered_msg[message][k] = msgs[message][characters];
            k++;
            characters++;
        }
        filtered_msg[message][k] = '\0';
        //if(filtered_msg[i][k - 1] == ',') filtered_msg[i][k - 1] = '\0';
        strcpy(msgs[message], filtered_msg[message]);
        //printf("%s\n", msgs[ message]);
    }
}

void Add_emtcns(emtcn_t emtcns[], int* num_emtcns) {
  /* Add the emoticons to emtcns[] */  
  
    int x = 0;
    while (1) {

        if (*emtcns[*num_emtcns] == EOF) break;

        // printf("%s\n",emtcns[*num_emtcns]);
        read_one_msg(emtcns[*num_emtcns], MAX_EMTCN_LENGTH);
        x = strlen(emtcns[*num_emtcns]);
        if (x == 0) break;
        // printf("%d, %s, %d \n",x, emtcns[*num_emtcns], *num_emtcns);
        *num_emtcns += 1;
    }
}

void removeAlphaNumEmtcns(emtcn_t emtcns[], int* num_emtcns) {
    
    /* remove Alphanum from the emotions */
    
    emtcn_t temparr[MAX_EMTCN_LENGTH];
    int i;
    for (i = 0; i < *num_emtcns; i++) {
        int characters = 0;
        int k = 0;
        while (emtcns[i][characters] != ',') {
            if (isalpha(emtcns[i][characters])) characters++;

            else {
                temparr[i][k] = emtcns[i][characters];
                characters++; k++;
            }
        }
        memset(emtcns[i],'\0',MAX_EMTCN_LENGTH); 
        strcpy(emtcns[i], temparr[i]);
        
    }
}
void stage_four_result(emtcn_t emtcns[], int* num_emtcns) {
    
    /* Fucntion to search for the longest emoticon record the length and
    print it with the total number of emotiocons*/
    
    int i;
    int emtcn_length = 0;
    int longest;
    int x = 0;
    for (i = 0; i < *num_emtcns; i++) {
        x = strlen(emtcns[i]);
        if (x > emtcn_length) {
            emtcn_length = strlen(emtcns[i]);
            longest = i;
            //longest[0] = emtcns[i];            
        }
    }
    printf("Emoticon total: %d\n", *num_emtcns);
    printf("Longest: %s\n", emtcns[longest]);
    printf("Length: %d\n", emtcn_length);
}

void removeUnknown(msg_t msgs[], int num_msgs, emtcn_t emtcns[], 
                   int num_emtcns) {
   
    /*Function to remove the invalid emoticons from the messages using the 
    the dictionaries by comparing each characters from the filtered message
    to the emoticons each at a time*/
    
    for  (int lmsg = 0; lmsg < num_msgs; lmsg++){
        int i = 0;        
    
        int At_Least_One_Msg_OK  = 0;
        while (msgs[lmsg][i] != '\0') {
         // find ',' to isolate the sequence
            int s = 0;
            char currentMsgToCompare[10];
            //printf("num caractere msg: %d", i);
            while  (msgs[lmsg][i] != '\0' && msgs[lmsg][i] != ',') {
                currentMsgToCompare[s]=msgs[lmsg][i];
                i++;
                s++;
            }
            if (s>0){
                
                // terminate the currentmsgtocompare by \0
                currentMsgToCompare[s]='\0';
            } 
            //# now we have one sequence in currentMsgToCompare 
        //  fetch the emtcns to find if currentMsgToCompare is in there
            for (int j = 0; j < num_emtcns; j++) {
               // # here we fetch thru the list of emtcns
                int k = 0;
                int ok = 0;
                while (currentMsgToCompare[k]!= '\0') {
                   // # here we go thru the character of one emtcn
                        ok = 1;
                 
                        if (currentMsgToCompare[k] != emtcns[j][k] || 
                            emtcns[j][k] == '\0') {
                        //# if one character is not Ok, then we can to
                            ok = 0; 
                            break;
                        }
                        k++;
                }                   
                if (ok==1) {  
                    int l=0;
                    At_Least_One_Msg_OK = 1;
                    printf("%s", currentMsgToCompare);
                    while (currentMsgToCompare[l]!= '\0'){
                        currentMsgToCompare[l]='\0';  
                        l++;
                    }
                    break;    
                } // end of the OK==1
                
            } // end of loop for emtcns
            
            if (msgs[lmsg][i] != '\0') {
                printf(",");
                i++;
            }
         } // end of the while for a line in lmsg
         if (At_Least_One_Msg_OK) printf("\n") ;
           
    }    // end of loop through all messages
}

