#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct deck {
    int carta;
    int naipe;
    struct deck *next;
    struct deck *prev;
} Deck;

typedef struct {
    char* nome;
    Deck* cartas;
} Player;

typedef struct {
    int qtde;
    Deck* cartas;
} Baralho;

//Criar baralho
Baralho* create_baralho();

//Criar novo jogador
Player* create_player(char *nome);

//Preencher o baralho
Baralho* fill_deck (Baralho *b);

//Preencher a mao do jogador
Player* fill_hands(Player *p, Baralho *b, int qtde);

//Adiciona uma carta na mao do jogador
Player* getCards(Player *p, Deck *deck, int pos);

//Inserir nova cartas
Deck* inserir (Deck *deck, int carta, int naipe);

//Remover uma carta e colocar em outro deck
Deck* remover (Deck *deck, int pos);

//Imprimir Deck
void imprimir (Deck *deck);

//Mostrar o nome do jogador
char* getName(Player *p);

//Liberar o deck
void free_deck (Deck *deck);

//Liberar baralho
void free_baralho(Baralho *b);

//Liberar jogador
void free_player(Player *p);

//Mostra as cartas do jogador
Baralho* gameTurn(Player* p, int round, Baralho *mesa, Deck *manilha);

//Verifica quem ganhou o round
int check_winner(Baralho *mesa, Deck *manilha, int inicio);

//Menu do jogo
int menu();

//Ordenar as cartas
void InsertionSort (Deck *deck);

//Mostra a manilha e as cartas que estão na mesa
void show_deck(Baralho *mesa, Deck *manilha);

//Sorteia uma carta para ser a manilha
Deck *getManilha(Deck *deck, Baralho *b);

//Timer para mudar de tela
void troca_tela(int time);

//Iniciar o round
void game(Player *p1, Player *p2, Player *p3, Player *p4, int partida, Baralho *mesa, Deck *manilha);