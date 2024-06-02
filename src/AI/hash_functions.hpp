#include "Node.h"
#include "stdint.h"
#include <stdio.h>
#include "hashing_struct.h"
//#include "hash_nodes.h"

HashNode *hashmap;

uint64_t hash_node(Node* node);
void delete_node_from_hashmap(HashNode *node);
HashNode* find_node_in_hashmap(uint64_t id);
void add_node_to_hashmap(HashNode *node);
HashNode *create_hashnode(Node* node, char* next_move);
void populate_hashmap();