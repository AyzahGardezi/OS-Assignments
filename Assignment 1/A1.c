#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// memory should be freed after no longer in use as it can cause issues
bool str_contains(const char* s, char c) {
    int i = 0;

    while (s[i]) {
        if (s[i] == c)
            return true;
        i++;
    }
    return false;
}

void str_append(char** append_to, const char* to_append) {
    int append_to_len = strlen(*append_to);
    int to_append_len = strlen(to_append);
    int total_len = append_to_len + to_append_len;

    char* ret = malloc(sizeof(char) * total_len + 1); // adding 1 here to create space for null character/ recall strings are null terminated in c

    int i = 0;
    while ((*append_to)[i]) {
        ret[i] = (*append_to)[i];
        i++;
    }

    int j = 0;
    while (to_append[j]) {
        ret[i] = to_append[j];
        i++;
        j++;
    }
    ret[i] = '\0'; // after all the characters have been added to the string we have to add a null character.

    *append_to = realloc(*append_to, total_len + 1);
    strcpy(*append_to, ret);
    free(ret);
}

int str_unique(const char* s) {
    int len = strlen(s);
    int count = 0;
    char* uniq_vals = malloc(sizeof(char) * len + 1); // adding 1 again for null character
    uniq_vals[0] = '\0';

    for (int i = 0; i < len; i++) {
        bool unique = true;
        int uniq_vals_len = strlen(uniq_vals);
        for (int k = 0; k < uniq_vals_len && unique; k++) {
            if (s[i] == uniq_vals[k])
                unique = false;
        }

        char* ptr = malloc(sizeof(char) * 2);
        ptr[0] = s[i];
        ptr[1] = '\0';

        if (unique) {
            count++;
            str_append(&uniq_vals, ptr);
        }
        free(ptr);
    }
    free(uniq_vals);
    return count;
}

char * str_strip ( const char *s)
{
    int i = 0;
    while (*(s+i) == ' ' || *(s+i) == '\t' || *(s+i) == '\n')
        i++;
    
    int new_s_len = strlen(s) - i; //without terminating character

    char *heading_rem = malloc(sizeof(char)*((new_s_len) + 1)); //heading spaces removed
    strcpy(heading_rem, s+i);

    i = new_s_len; //without terminating character

    i--;

    while(*(heading_rem+i) == ' ' || *(heading_rem+i) == '\t' || *(heading_rem+i) == '\n')
        i--;

    char *stripped = malloc(sizeof(char)*(i + 1));

    int j;

    for(j = 0; j < i+1; j++){
        stripped[j] = heading_rem[j];
    }

    stripped[j] = '\0';

    free(heading_rem);
    return stripped;

}


int main() {
    const char* string = "hello";
    printf("\n\n%s\n\n", string);

    bool val;
    val = str_contains(string, 'i');
    printf("\ne is present in hello: %d", val);

    val = str_contains(string, 'e');
    printf("\ne is present in hello: %d", val);

    int unique = str_unique("teeth");
    printf("\nunique characters in teeth: %d\n", unique);

    unique = str_unique("cart");
    printf("\nunique characters in cart: %d\n", unique);

    char *stripped = str_strip("      This is a cat\t\t\t");
    printf("\n'      This is a cat\t\t\t\n' stripped: '%s'\n", stripped);
    return 0;
}