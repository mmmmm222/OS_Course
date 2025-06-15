#include "./kv.h"


// Global head of the linked list
KVNode* head = NULL;


// Load database from file
void load_database() {
    FILE* file = fopen(DATABASE_FILE, "r");
    if (!file) {
        // If file doesn't exist, that's okay - we'll create it later
        return;
    }

    char line[MAX_VALUE_LENGTH + 20]; // Extra space for key and comma
    while (fgets(line, sizeof(line), file)) {
        char* saveptr = NULL;
        char* key_str = strtok_r(line, ",", &saveptr);
        if (!key_str) continue;
        
        // Remove newline if present
        char* newline = strchr(key_str, '\n');
        if (newline) *newline = '\0';
        
        char* value = strtok_r(NULL, "\n", &saveptr);
        if (!value) continue;
        
        int key = atoi(key_str);
        put(key, value);
    }
    
    fclose(file);
}

// Save database to file
void save_database() {
    FILE* file = fopen(DATABASE_FILE, "w");
    if (!file) {
        fprintf(stderr, "Error: Could not open database file for writing\n");
        exit(1);
    }

    KVNode* current = head;
    while (current) {
        fprintf(file, "%d,%s\n", current->key, current->value);
        current = current->next;
    }

    fclose(file);
}

// Put a key-value pair
void put(int key, const char* value) {
    KVNode* existing = find_node(key);
    if (existing) {
        strncpy(existing->value, value, MAX_VALUE_LENGTH - 1);
        existing->value[MAX_VALUE_LENGTH - 1] = '\0';
        return;
    }

    KVNode* new_node = malloc(sizeof(KVNode));
    if (!new_node) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    new_node->key = key;
    strncpy(new_node->value, value, MAX_VALUE_LENGTH - 1);
    new_node->value[MAX_VALUE_LENGTH - 1] = '\0';
    new_node->next = head;
    head = new_node;
}

// Get a value by key
void get(int key) {
    KVNode* node = find_node(key);
    if (node) {
        printf("%d,%s\n", node->key, node->value);
    } else {
        printf("%d not found\n", key);
    }
}

// Delete a key-value pair
void delete_f(int key) {
    if (!head) {
        printf("%d not found\n", key);
        return;
    }

    if (head->key == key) {
        KVNode* temp = head;
        head = head->next;
        free(temp);
        return;
    }

    KVNode* current = head;
    while (current->next) {
        if (current->next->key == key) {
            KVNode* temp = current->next;
            current->next = temp->next;
            free(temp);
            return;
        }
        current = current->next;
    }

    printf("%d not found\n", key);
}

// Clear all key-value pairs
void clear() {
    free_list();
    head = NULL;
}

// Print all key-value pairs
void print_all() {
    KVNode* current = head;
    while (current) {
        printf("%d,%s\n", current->key, current->value);
        current = current->next;
    }
}

// Free the linked list
void free_list() {
    KVNode* current = head;
    while (current) {
        KVNode* temp = current;
        current = current->next;
        free(temp);
    }
}

// Find a node by key
KVNode* find_node(int key) {
    KVNode* current = head;
    while (current) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
