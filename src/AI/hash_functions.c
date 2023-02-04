#include "hash_functions.h"
#include "hash_nodes.h"

void add_node_to_hashmap(HashNode *hashnode) {
    /* commented for speed, for now we assume no double mapping
    HASH_FIND_INT(get_hashmap(), &(node->id), node);  
    if (node==NULL) {
        HASH_ADD_INT( get_hashmap(), node->id, node );
    }
    */
    HASH_ADD_INT( hashmap, id, hashnode );
}

HashNode* find_node_in_hashmap(uint64_t id){
    /*
        returns pointer to node, if found
        returns NULL if key wasn't found in hashmap
    */

    HashNode *hashnode;
    HASH_FIND_INT( hashmap, &id, hashnode ); 
    return hashnode;
}

void delete_node_from_hashmap(HashNode *hashnode) {
    HASH_DEL( hashmap, hashnode );
    free(hashnode); //optional, comment out for speed          
}

uint64_t hash_node(Node* node){
    uint64_t hash = 14695981039346656037;
    char octet_of_data;

    for(char i = 0; i <= 7; ++i){
        octet_of_data = (node->sw >> (8*i)) & 0xff;
        hash = hash ^ octet_of_data;
        hash = hash * 1099511628211;
    }

    for(char i = 0; i <= 7; ++i){
        octet_of_data = (node->sb >> (8*i)) & 0xff;
        hash = hash ^ octet_of_data;
        hash = hash * 1099511628211;
    }

    for(char i = 0; i <= 7; ++i){
        octet_of_data = (node->dw >> (8*i)) & 0xff;
        hash = hash ^ octet_of_data;
        hash = hash * 1099511628211;
    }

    for(char i = 0; i <= 7; ++i){
        octet_of_data = (node->db >> (8*i)) & 0xff;
        hash = hash ^ octet_of_data;
        hash = hash * 1099511628211;
    }

    for(char i = 0; i <= 7; ++i){
        octet_of_data = (node->mw >> (8*i)) & 0xff;
        hash = hash ^ octet_of_data;
        hash = hash * 1099511628211;
    }

    for(char i = 0; i <= 7; ++i){
        octet_of_data = (node->mb >> (8*i)) & 0xff;
        hash = hash ^ octet_of_data;
        hash = hash * 1099511628211;
    }
    
    hash = hash ^ node->player;
    hash = hash * 1099511628211;

    return hash;
}

HashNode *create_hashnode(Node* current, char* next_move){

    HashNode *hashnode = malloc(sizeof(HashNode));
    hashnode->current = current;
    strcpy(hashnode->next_move, next_move);
    hashnode->id = hash_node(current);

    return hashnode;
}

void populate_hashmap(){
    for (int i=0; i <numberOfNodes; ++i){
        Node *node = &(nodes_for_hashpopulation[i]);
        char *move = next_move_string[i];
        HashNode *hashnode = create_hashnode(node, move);
        add_node_to_hashmap(hashnode);
    }
}