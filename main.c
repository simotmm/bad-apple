#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PROJECTNAME /*"[C Project: 'Bad Apple']"*/ "C Project - '[Touhou] Bad Apple!! PV [Shadow] - [ASCII]'"
//#define DIRECTORY "C:/Users/by_si/Desktop/Simone/07. Progetti/C/CodeBlocks/Bad Apple/Bad Apple (my project)/res"
#define DIRECTORY "res"
#define PREFISSO "/BA"
#define FILETOT "/numberOfFrames.txt"
#define FILEMUSIC "/BA.wav"
#define LEN 68
#define INIZIO 0
#define WAIT 23
#define LARGHEZZA 80
#define DEBUG 1
#define FPS 30

int getTotFrames(char *dir);
char *saveFrame(int i, char *dir);
char **saveFrames(char *dir, int totFrames);
void play(char **framse, int totFrames);
void progressBar(int corrente, int tot, int r, int frames);

int main(){
    int totFrames;
    char **frames;
    totFrames=getTotFrames(DIRECTORY);

    printf("%s\n", PROJECTNAME);
    system("PAUSE");

    if(totFrames==-1)
        return totFrames;

    frames=saveFrames(DIRECTORY, totFrames);

    printf("(PLAY) --> ");
    system("PAUSE");

    play(frames, totFrames);

    return 0;
}

void play(char **frames, int totFrames){
    int i, j;

    for(i=INIZIO;i<totFrames;i++){
        #if DEBUG
        char framesCount[100];
        sprintf(framesCount, "(frame: %d/%d) \n", i+1, totFrames);
        printf(PROJECTNAME);
        int x=LARGHEZZA-strlen(PROJECTNAME)-strlen(framesCount);
        for(j=0;j<=x;j++)
            printf(" ");
        printf("%s", framesCount);
        printf("%s", frames[i]);
        progressBar(i, totFrames, 0, 0);
        _sleep(WAIT);
        #else
        printf("%s\n", frames[i]);
        _sleep(WAIT);
        #endif
    }
}

void progressBar(int corrente, int tot, int r, int frames){
    corrente++;
    int cost, x;
    int i;
    float p = (float)((float)corrente/tot)*100;

    if(r==0){
        cost=0;
        x=(corrente*(LEN-cost))/tot;
        
        printf("[");
        for(i=0;i<=x;i++)
            printf("#");
        for(i=0;i<LEN-x;i++)
            printf("-");
        printf("](%.2f%%)\n", p);
    }
    else if(r==1 && frames==1){
        cost=25;
        x=(corrente*(LEN-cost))/tot;

        printf("saving frames: %d/%d ", corrente, tot);
        printf("[");
        for(i=0;i<=x;i++)
            printf("#");
        for(i=0;i<LEN-cost-x;i++)
            printf("-");
        printf("] (%.1f%%)\r", p);
    }
}

char **saveFrames(char *dir, int totFrames){
    int i;
    char **frames;
    frames=calloc(totFrames, sizeof(char*));

    for(i=INIZIO;i<totFrames;i++){
        frames[i]=saveFrame(i, DIRECTORY);
        #if DEBUG
        progressBar(i, totFrames, 1, 1);
        #endif // DEBUG
    }
    printf("\n");
    
    return frames;
}

char *saveFrame(int i, char *dir){
    i++;
    char fileName[200], suffix[10];
    strcpy(fileName, dir);
    strcat(fileName, PREFISSO);
    sprintf(suffix, "%d.txt", i);
    strcat(fileName, suffix);

    FILE *f = fopen(fileName, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);

    string[fsize] = '\0';
    return string;
}

int getTotFrames(char *dir){
    char fileName[200];
    strcpy(fileName, dir);
    strcat(fileName, FILETOT);
    int tot=-1;

    FILE *fin=fopen(fileName, "r");

    if(fin==NULL)
        return tot;

    fscanf(fin, "%d", &tot);
    fclose(fin);

    return tot;
}
