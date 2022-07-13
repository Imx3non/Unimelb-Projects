#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

#include "ai.h"
#include "utils.h"
#include "hashtable.h"
#include "stack.h"




struct expanded{
    node_t* node;
    struct expanded* next;
};

//linked list to free all the nodes
struct expanded* head;

void insert(node_t* node);
void free_list(struct expanded* nodes);

void copy_state(state_t* dst, state_t* src){

    //Copy field

    memcpy( dst->field, src->field, SIZE*SIZE*sizeof(int8_t) );

    dst->cursor = src->cursor;
    dst->selected = src->selected;
}


/**
 * Saves the path up to the node as the best solution found so far
*/
void save_solution( node_t* solution_node ){
    node_t* n = solution_node;
    while( n->parent != NULL ){
        copy_state( &(solution[n->depth]), &(n->state) );
        solution_moves[n->depth-1] = n->move;

        n = n->parent;
    }
    solution_size = solution_node->depth;
}




node_t* create_init_node( state_t* init_state ){
    node_t * new_n = (node_t *) malloc (sizeof(node_t));
    assert(new_n != NULL);
    new_n->parent = NULL;
    new_n->depth = 0;
    copy_state(&(new_n->state), init_state);

    return new_n;
}

/**
 * Apply an action to node n and return a new node resulting from executing the action
*/
node_t* applyAction(node_t* n, position_s* selected_peg, move_t action ){

    node_t* new_node = NULL;
    new_node = (node_t*)malloc(sizeof(node_t));
    assert(new_node != NULL);
    new_node->parent = n;
    
    copy_state(&new_node->state,&n->state);
    new_node->depth = n->depth + 1;
    new_node->move = action;
    
    new_node->state.cursor = *selected_peg;

    //FILL IN MISSING CODE

    execute_move_t( &(new_node->state), &(new_node->state.cursor), action );

    return new_node;

}

/**
 * Find a solution path as per algorithm description in the handout
 */


void find_solution(state_t *init_state) {

    HashTable table;
    // Choose initial capacity of PRIME NUMBER 
    // Specify the size of the keys and values you want to store once 
    ht_setup(&table, sizeof(int8_t) * SIZE * SIZE, sizeof(int8_t) * SIZE * SIZE, 16769023);


    // Initialize Stack
    initialize_stack();

    position_s *current_cursor = (position_s *) malloc(sizeof(position_s));
    assert(current_cursor!=NULL);

    //Add the initial node
    node_t *n = create_init_node(init_state);
    ht_insert(&table, &n->state.field, &n->state.field);

    //push initial node in stack
    stack_push(n);

    //add initial node in linked list 
    insert(n);

    int remaining_peg = num_pegs(&n->state);

    while (!is_stack_empty()) {
        n = stack_top();
        stack_pop();
        expanded_nodes++;
		
		//check if current solution is best solution
        if (num_pegs(&n->state) < remaining_peg) {
            save_solution(n);
            remaining_peg = num_pegs(&n->state);
        }
        
        //line 12 of algorithm 
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j <= SIZE; j++) {
                for (int direction = left; direction <= down; direction++) {

                    current_cursor->x = i;
                    current_cursor->y = j;
                    
                    //check for legal moves
                    if (can_apply(&n->state, current_cursor, direction)) {
                        node_t *new_node = NULL;
                        new_node = applyAction(n, current_cursor, direction);
                        insert(new_node);
                        generated_nodes += 1;
						
                        //check if game won
                        if (won(&new_node->state)) {
                            save_solution(new_node);
                            remaining_peg = num_pegs(&new_node->state);
                            ht_destroy(&table);
                            free_list(head);
                            free(current_cursor);
                            return;
                        }   
                        //check for duplicate states
                        if ((ht_contains(&table, new_node->state.field)) == false) {
                            ht_insert(&table, &new_node->state, &new_node->state);
                            stack_push(new_node);

                        }

                    }

                }

            }
        }
        //check if budget is reached
        if (expanded_nodes >= budget) {
            ht_destroy(&table);
            free_list(head);
            free(current_cursor);
            return;
        }
    }

    ht_destroy(&table);
    free_list(head);
    free(current_cursor);
    
}

void insert(node_t* node){
    
    struct expanded* temp = (struct expanded*)malloc(sizeof(struct expanded));
    assert(temp != NULL);
    temp->node = node;
    temp->next = head;
    head = temp;
}


void free_list(struct expanded* nodes){
    struct expanded* temp = NULL;


    while(nodes != NULL){

        temp = nodes->next;
        free(nodes->node);
        free(nodes);
        nodes = temp;
    }

}