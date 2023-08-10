#include "deck.h"

//Criar baralho
Baralho* create_baralho() {
    Baralho *novo = (Baralho*) malloc(sizeof(Baralho));
    novo->qtde = 0;
    novo->cartas = NULL;

    return novo;
}

//Criar novo jogador
Player* create_player(char *nome) {
    Player* p = (Player*) malloc (sizeof(Player));
    p->nome = nome;
    p->cartas = NULL;

    return p;
}

//Preencher o baralho
Baralho* fill_deck (Baralho *b) {
    for(int i=0; i<4; i++) {
        for(int j=0; j<10; j++) {
            b->cartas = inserir(b->cartas, j, i);
            (b->qtde)++;
        }
    }

    return b;
}

//Preencher a mao do jogador
Player* fill_hands(Player *p, Baralho *b, int qtde) {
    int i, pos;
    for(i=0; i<qtde; i++) {
        pos = rand()%b->qtde;
        p = getCards(p, b->cartas, pos);
        b->cartas = remover(b->cartas, pos);
        b->qtde--;
    }

    InsertionSort(p->cartas);

    return p;
}

//Adiciona uma carta na mao do jogador
Player* getCards(Player *p, Deck *deck, int pos) {
    Deck *aux = deck;
    while(aux != NULL && pos){
        aux = aux->next;
        pos--;
    }
    p->cartas = inserir(p->cartas, aux->carta, aux->naipe);
    
    return p;
}

//Inserir nova cartas
Deck* inserir (Deck *deck, int carta, int naipe){
    Deck *novo = (Deck*) malloc(sizeof(Deck));
    novo->carta = carta;
    novo->naipe = naipe;
    novo->next = deck;
    novo->prev = NULL;
    /* verifica se lista nao esta vazia */
    if (deck != NULL)
        deck->prev = novo;

    return novo;
}

//Remover uma carta e colocar em outro deck
Deck* remover (Deck *deck, int pos){
    Deck* prv = NULL; Deck* v = deck;

    if (!pos && v->next == NULL) { free(deck); return NULL; }

    while ((v != NULL) && pos) {
        prv = v;
        v = v->next;
        pos--;
    }

    if (prv == NULL) { 
        deck = v->next;
        if(v->next != NULL)
            deck->prev = NULL; 
    }
    else {
        prv->next = v->next;
        if(v->next != NULL)
            v->next->prev = v->prev; 
    }

    free (v);

    return deck;
}

//Imprimir Deck
void imprimir(Deck *deck) {
    Deck *aux = deck;
    while (aux != NULL) {
        printf("C: %d\tN: %d\n", aux->carta, aux->naipe);
        aux = aux->next;
    }
}

//Mostrar o nome do jogador
char* getName(Player *p) {
    return p->nome;
}

//Liberar o deck
void free_deck (Deck *deck) {
    while (deck != NULL) {
        Deck *aux = deck->next;
        free (deck);
        deck = aux;
    }
}

//Liberar baralho
void free_baralho(Baralho *b) {
    free_deck(b->cartas);
}

//Liberar jogador
void free_player(Player *p) {
    free_deck(p->cartas);
}

//Mostra as cartas do jogador
Baralho* gameTurn(Player* p, int partida, Baralho *mesa, Deck *manilha){
    system("clear");
    int escolha, i=0;
    char naipes[4][20] = {"\033[1;31m\u2666 \033[0m", "\033[0;32m\u2660 \033[0m", "\033[1;31m\u2665 \033[0m", "\033[0;32m\u2663 \033[0m"};
    char cartas[10] = {'4','5','6','7','Q', 'J', 'K', 'A', '2', '3'};

    printf("=============\n");
    printf("| PARTIDA %d |\n", partida);
    printf("=============\n\n");

    show_deck(mesa, manilha);

    printf("VEZ DE %s\n\n", p->nome);
    Deck *aux = p->cartas;
    while(aux != NULL) {
        printf("---------\n");
        printf("| %c%s   |\t(%d)\n",cartas[aux->carta], naipes[aux->naipe], i++);
        printf("|       |\n");
        printf("|       |\n");
        printf("|    %c%s|\n",cartas[aux->carta], naipes[aux->naipe]);
        printf("---------\n");

        aux = aux->next;
    }

    do {
        printf("Escolha uma carta\n> ");
        scanf("%d", &escolha);
    } while (escolha < 0 || escolha >= i);

    int pos = escolha;
    aux = p->cartas;
    while(aux != NULL && escolha){
        aux = aux->next;
        escolha--;
    }

    mesa->cartas = inserir(mesa->cartas, aux->carta, aux->naipe);
    (mesa->qtde)++;
    p->cartas = remover(p->cartas, pos);

    return mesa;
}

//Verifica quem ganhou o round
int check_winner(Baralho *mesa, Deck *manilha, int inicio){
    system("clear");

    show_deck(mesa, manilha);

    int carta_manilha = (manilha->carta)+1;
    int naipe_manilha = 0;
    if (carta_manilha == 10) { carta_manilha = 0; }

    int ehManilha = 0, maior = mesa->cartas->carta, empate = 0, count = mesa->qtde, pos = count;
    Deck *aux = mesa->cartas;
    while(aux != NULL) {
        if(aux->carta == maior && aux->prev != NULL && !ehManilha) {
            empate = 1;
        }
        if(aux->carta > maior && !ehManilha) {
            maior = aux->carta;
            empate = 0;
            pos = count;
        }
        else if(aux->carta == carta_manilha) {
            ehManilha = 1;
            empate = 0;
            if(aux->naipe >= naipe_manilha) {
                naipe_manilha = aux->naipe;
                pos = count;
            }
        }

        count--;
        aux = aux->next;
    }

    if(empate) {
        printf("EMPATOU\n");
        return 0;
    }

    pos = (pos+inicio-2)%4 + 1;

    printf("--- JOGADOR %d GANHOU ---\n", pos);
    return pos;
}

//Menu do jogo
int menu() {
    int opcao;
    system("clear");
    printf("==================\n");
    printf("|      MENU      |\n");
    printf("------------------\n");
    printf("| 1. Novo jogo   |\n");
    printf("| 0. Sair        |\n");
    printf("------------------\n\n");
    do {
        printf("> ");
        scanf("%d", &opcao);
    } while(opcao < 0 || opcao > 1);

    return opcao;
}

//Ordenar as cartas
void InsertionSort (Deck *deck) {
    int menor_carta, menor_naipe, loop=1;
    Deck *aux = deck, *aux2;
    while(aux != NULL) {
        menor_carta = aux->carta;
        menor_naipe = aux->naipe;
        aux2 = aux;
        while(aux2->prev != NULL && (menor_carta < aux2->prev->carta || (menor_carta == aux2->prev->carta && menor_naipe < aux2->prev->naipe))) {
            aux2 = aux2->prev;
            aux2->next->carta = aux2->carta;
            aux2->next->naipe = aux2->naipe;
            
        }
        aux2->carta = menor_carta;
        aux2->naipe = menor_naipe;

        aux = aux->next;
    }
}

//Mostra a manilha e as cartas que estão na mesa
void show_deck(Baralho *mesa, Deck *manilha) {
    char naipes[4][20] = {"\033[1;31m\u2666 \033[0m", "\033[0;32m\u2660 \033[0m", "\033[1;31m\u2665 \033[0m", "\033[0;32m\u2663 \033[0m"};
    char cartas[10] = {'4','5','6','7','Q', 'J', 'K', 'A', '2', '3'};

    printf("- MANILHA -\n");
    printf("---------\n");
    printf("| %c%s   |\n",cartas[manilha->carta], naipes[manilha->naipe]);
    printf("|       |\n");
    printf("|       |\n");
    printf("|    %c%s|\n",cartas[manilha->carta], naipes[manilha->naipe]);
    printf("---------\n");
    printf("===========\n");
    printf("- MESA -\n");
    Deck *aux = mesa->cartas;
    while(aux != NULL) {
        printf("---------\n");
        printf("| %c%s   |\n",cartas[aux->carta], naipes[aux->naipe]);
        printf("|       |\n");
        printf("|       |\n");
        printf("|    %c%s|\n",cartas[aux->carta], naipes[aux->naipe]);
        printf("---------\n");
        aux = aux->next;
    }
    printf("===========\n");
}

//Sorteia uma carta para ser a manilha
Deck *getManilha(Deck *deck, Baralho *b) {
    deck = NULL;
    int pos = rand()%b->qtde;
    Deck *aux = b->cartas;
    while(aux != NULL && pos){
        aux = aux->next;
        pos--;
    }

    deck = inserir(deck, aux->carta, aux->naipe);

    return deck;
}

//Timer para mudar de tela
void troca_tela(int time) {
    printf("\nTrocando a tela em: \n");
    for(int i=time; i>0; i--) {
        printf("%d\n", i);
        sleep(1);
    }
}

//Iniciar o round
void game(Player *p1, Player *p2, Player *p3, Player *p4, int partida, Baralho *mesa, Deck *manilha) {
    mesa = gameTurn(p1, partida, mesa, manilha);
    troca_tela(3);
    mesa = gameTurn(p2, partida, mesa, manilha);
    troca_tela(3);
    mesa = gameTurn(p3, partida, mesa, manilha);
    troca_tela(3);
    mesa = gameTurn(p4, partida, mesa, manilha);
    troca_tela(3);
}