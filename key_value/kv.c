#include "./kv.h"

int main(int argc, char* argv[]) {
    // Load existing database
    load_database();

    // If no arguments, just exit
    if (argc == 1) {
        return 0;
    }

    // Process each command
    for (int i = 1; i < argc; i++) {
        char* cmd = strdup(argv[i]);
        if (!cmd) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(1);
        }

        char* saveptr = NULL;
        char* command = strtok_r(cmd, ",", &saveptr);
        
        if (!command) {
            printf("bad command\n");
            free(cmd);
            continue;
        }

        switch (command[0]) {
            case 'p': { // put
                char* key_str = strtok_r(NULL, ",", &saveptr);
                char* value = strtok_r(NULL, "", &saveptr);
                if (!key_str || !value) {
                    printf("bad command\n");
                    free(cmd);
                    continue;
                }
                int key = atoi(key_str);
                put(key, value);
                break;
            }
            case 'g': { // get
                char* key_str = strtok_r(NULL, "", &saveptr);
                if (!key_str) {
                    printf("bad command\n");
                    free(cmd);
                    continue;
                }
                int key = atoi(key_str);
                get(key);
                break;
            }
            case 'd': { // delete
                char* key_str = strtok_r(NULL, "", &saveptr);
                if (!key_str) {
                    printf("bad command\n");
                    free(cmd);
                    continue;
                }
                int key = atoi(key_str);
                delete_f(key);
                break;
            }
            case 'c': // clear
                clear();
                break;
            case 'a': // all
                print_all();
                break;
            default:
                printf("bad command\n");
                break;
        }
        free(cmd);
    }

    // Save database before exiting
    save_database();
    
    // Clean up
    free_list();
    
    return 0;
}
