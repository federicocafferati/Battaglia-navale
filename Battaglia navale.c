#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EN_MAX 5
#define DIM_MARE 5

typedef struct {
int riga; //indice di riga da 0 a DIM_MARE - 1
int colonna; //indice di colonna da 0 a DIM_MARE - 1
int energia; //da 0 a EN_MAX
} s_nave;

s_nave flotta[DIM_MARE];
int mare[DIM_MARE][DIM_MARE], contatore = 0;

void setup (int m[DIM_MARE][DIM_MARE],s_nave v[DIM_MARE]); //riceve come parametri il mare e la flotta e li "popola" con valori casuali

void stampa_mare(int m[DIM_MARE][DIM_MARE]); //visualizza dove si trovino nel mare le navi della flotta

void stampa_flotta(s_nave v[DIM_MARE]); //visualizza l'energia e le coordinate di ciascuna nave della flotta

void fuoco(int m[DIM_MARE][DIM_MARE],s_nave v[DIM_MARE]); //sceglie due coordinate casuali su cui fare fuoco ed eventualmente aggiorna l'energia di una nave della flotta se colpita

int gameover(s_nave v[DIM_MARE]); //verifica se tutte le navi sono affondate ritorna 0 per continuare, 1 per finire

int main(){
    srand(time(NULL));
    setup(mare,flotta);

    while(gameover(flotta) == 0){
        fuoco(mare, flotta);
        stampa_mare(mare);
        stampa_flotta(flotta);
        contatore ++;
    }
    printf("Il gioco e' terminato in %d mosse", contatore);
}

void setup (int m[DIM_MARE][DIM_MARE],s_nave v[DIM_MARE]){
    int i,j;

    for(i=0; i<DIM_MARE; i++){
        for(j=0;j<DIM_MARE;j++)
        {
            m[i][j] = -1;
        }
    }
    for(i=0;i<DIM_MARE;i++){
        m[rand()%5][rand()%5]=i;
    }
    for(i=0;i<DIM_MARE;i++){
        v[i].riga = rand()%5;
        v[i].colonna = rand()%5;
        v[i].energia = (rand()%5)+1;
    }
}

void stampa_mare(int m[DIM_MARE][DIM_MARE]){
    int i,j;
    for(i=0; i<DIM_MARE; i++){
        for(j=0;j<DIM_MARE;j++){
            printf("%3d", m[i][j]);
        }
        puts(" ");
    }
    puts(" ");
}

void stampa_flotta(s_nave v[DIM_MARE]){
    int i;
    for(i=0;i<DIM_MARE;i++){
        printf("NAVE %d:\n",i+1);
        printf("Energia: %d\n", v[i].energia);
    }
    puts(" ");
}

void fuoco(int m[DIM_MARE][DIM_MARE],s_nave v[DIM_MARE]){
    int x,y;
    x = rand()%DIM_MARE;
    y = rand()%DIM_MARE;

    if(m[x][y] != -1){
        if(v[m[x][y]].energia>0)
        v[m[x][y]].energia--;
    }
}

int gameover(s_nave v[DIM_MARE]){
    int i;
    int contatore_affondati = 0;
    for(i=0; i<DIM_MARE; i++){
        if (v[i].energia <= 0) contatore_affondati++;
    }
    if (contatore_affondati == 5){
            return 1;
    }
    else return 0;
}
