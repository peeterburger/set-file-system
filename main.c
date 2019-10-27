#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dynarray {
    int capacity;
    int entryCount;
    void **entries;
};

struct set {
    char *identifier;
    struct set *superset;
    struct dynarray *elements;
};

int addEntry(struct dynarray *dynarray, void *entry) {
    void **tmp = malloc((dynarray->entryCount+1) * sizeof(void *));

    for(int i = 0; i < dynarray->entryCount; i++) {
        tmp[i] = dynarray->entries[i];
    }

    tmp[dynarray->entryCount] = entry;

    dynarray->entryCount++;
    dynarray->entries = tmp;
}

void *getEntry(struct dynarray *dynarray, int index) {
    return dynarray->entries[index];
}

int setEntry(struct dynarray *dynarray, int index, void *entry) {
    dynarray->entries[index] = entry;
}

int getEntryCount(struct dynarray *dynarray) {
    return dynarray->entryCount;
}

int getCapacity(struct dynarray *dynarray) {
    return dynarray->capacity;
}

struct dynarray *newDynArray(int capacity) {
    struct dynarray *newDynArray = malloc(sizeof(struct dynarray));

    newDynArray->capacity = capacity;
    newDynArray->entryCount = 0;
    newDynArray->entries = malloc(capacity * sizeof(void *));

    return newDynArray;
}

int printSet(struct set *set) {
    // TODO: make this dynamic
    char buffer[80] = "";
    
    if (getEntryCount(set->elements) <= 0) {
        strcat(buffer, "[ ]");
    } else {
        strcat(buffer, "[\n");
        for(int i = 0; i < getEntryCount(set->elements); i++) {

            //TODO: make this dynamic
            char tmp[80] = "";
            sprintf(tmp, "\t\t%p\n", (struct set *) getEntry(set->elements, 0));
            strcat(buffer, tmp);
        }
        strcat(buffer, "\t]");
    }

    printf("struct set {\n\taddress:\t%p\n\tidentifier:\t%s\n\tsuperset:\t%p\n\telements:\t%s\n}\n",
        set, set->identifier, set->superset,  buffer);

    return 0;
}

int mkset(struct set *currentSet, char *identifier) {
    struct set *subset = malloc(sizeof(struct set));

    subset->identifier = identifier;
    subset->superset = currentSet;
    subset->elements = newDynArray(0);

    addEntry(currentSet->elements, subset);
}

int ps(struct set *currentSet) {
    printf("%s\n", currentSet->identifier);
}

struct set *cs(struct set *currentSet, char *subsetIdentifier) {
    for(int i = 0; i < getEntryCount(currentSet->elements); i++) {
        struct set *tmp = (struct set *) getEntry(currentSet->elements, i);

        printf("loop: %s\n", tmp->identifier);

        if(strcmp(tmp->identifier, subsetIdentifier) == 0) {
            printf("%s = %s\n", tmp->identifier, subsetIdentifier);

            return tmp;
        }
    }
}

struct set *currentSet;

int main(void) {
    currentSet = malloc(sizeof(struct set));

    currentSet->identifier = "/";
    currentSet->superset = NULL;
    currentSet->elements = newDynArray(0);

    mkset(currentSet, "/home");
    mkset(currentSet, "/bin");
    mkset(currentSet, "/usr");

    ps(currentSet);

    currentSet = cs(currentSet, "/bin");
    ps(currentSet);
}