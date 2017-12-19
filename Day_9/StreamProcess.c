// Author: MKozuch
// Date: 2017-12-19

#include <stdio.h>

struct State{
    int cancelState;
    int garbageState;
    int openedGroups;
    int totalScore;
    int garbageCount;
};

void character(struct State* state){
    if(state->cancelState)
        state->cancelState = 0;
    else if(state->garbageState)
        state->garbageCount++;
}

void groupOpen(struct State *state){
    if(!state->cancelState && !state->garbageState )
        state->openedGroups++;
    character(state);

}

void groupClose(struct State *state){
    if(!state->cancelState && !state->garbageState ){
        state->totalScore += state->openedGroups;
        state->openedGroups--;
    }
    character(state);
}

void garbageOpen(struct State *state){
    if(!state->cancelState && !state->garbageState)
        state->garbageState = 1;
    else
        character(state);
}

void garbageClose(struct State *state){
    if(!state->cancelState && state->garbageState)
        state->garbageState = 0;
    else
        character(state);
}

void cancel(struct State *state){
    if(state->cancelState)
        state->cancelState = 0;
    else
        state->cancelState = 1;
}


int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Bad args");
        return -1;
    }

    const char* fname = argv[1];
    FILE *file = fopen(fname, "r");
    if(file == NULL){
        perror("File error");
        return -1;
    }

    char chr;
    struct State state;
    state.cancelState = 0;
    state.garbageState = 0;
    state.openedGroups = 0;
    state.totalScore = 0;
    state.garbageCount = 0;

    while(!feof(file)){
        chr = getc(file);

        switch(chr){
            case '{':
                groupOpen(&state);
                break;

            case '}':
                groupClose(&state);
                break;

            case '<':
                garbageOpen(&state);
                break;

            case '>':
                garbageClose(&state);
                break;

            case '!':
                cancel(&state);
                break;

            default:
                character(&state);
                break;
        }
    }

    printf("Total score: %d\n", state.totalScore);
    printf("Garbage count: %d\n", state.garbageCount);
    printf("Open groups: %d\n", state.openedGroups);
    fclose(file);
    return 0;
}