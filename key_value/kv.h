#ifndef KV_H
#define KV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_FILE "./database.txt"
#define MAX_VALUE_LENGTH 1024

// Structure for key-value pairs
typedef struct KVNode {
    int key;
    char value[MAX_VALUE_LENGTH];
    struct KVNode* next;
} KVNode;

// Function declarations
void load_database();
void save_database();
void put(int key, const char* value);
void get(int key);
void delete_f(int key);
void clear();
void print_all();
void free_list();
KVNode* find_node(int key);

#endif // KV_H

