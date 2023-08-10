/*-----------------------------------------*\
| Matricula | NOME                          |
|-------------------------------------------|
|  2306379  | Murilo Brasil Cordeiro        |
\*-----------------------------------------*/

#include "deck.h"

#define PARTIDAS 12
#define CARDS 3

int main() {
    //Inicia com o menu
    while(menu()) {
        int partida = 1;
        int vitorias[2] = {0, 0};
        char jogador1[10], jogador2[10], jogador3[10], jogador4[10];

        printf("\nNome jogador 1: ");
        scanf("%s", jogador1);
        printf("Nome jogador 2: ");
        scanf("%s", jogador2);
        printf("Nome jogador 3: ");
        scanf("%s", jogador3);
        printf("Nome jogador 4: ");
        scanf("%s", jogador4);

        srand(time(NULL));

        //Roda até a primeira dupla fechar 12 pontos
        while(vitorias[0] <= PARTIDAS && vitorias[1] <= PARTIDAS) {
            //Cria o baralho e os jogadores
            Baralho *baralho = create_baralho();
            Player *p1 = create_player(jogador1);
            Player *p2 = create_player(jogador2);
            Player *p3 = create_player(jogador3);
            Player *p4 = create_player(jogador4);
            
            //Preeche o baralho, a mão do jogador e escolhe uma manilha
            baralho = fill_deck(baralho);   
            p1 = fill_hands(p1, baralho, CARDS);
            p2 = fill_hands(p2, baralho, CARDS);
            p3 = fill_hands(p3, baralho, CARDS);
            p4 = fill_hands(p4, baralho, CARDS);
            Deck *manilha = getManilha(manilha, baralho);

            //Cada round/partida inicia com os pontos zerados
            int rounds[2] = {0,0};
            //Saber em quem começa de acordo com o numero da partida
            int starts_in = (partida-1)%4 + 1;
            //Vantagem caso o jogo empate
            int vantagem = 0;

            //Roda até alguma dupla fazer 2 pontos
            while(rounds[0] <= CARDS/2 && rounds[1] <= CARDS/2) {
                //Criar o monte de descarte (cartas que estão na mesa)
                Baralho *mesa = create_baralho();
                troca_tela(5);

                //Inicia de acordo com a vez ou se venceu o round anterior
                if(starts_in == 1)
                    game(p1,p2,p3,p4, partida, mesa, manilha);
                else if(starts_in == 2)
                    game(p2,p3,p4,p1, partida, mesa, manilha);
                else if(starts_in == 3)
                    game(p3,p4,p1,p2, partida, mesa, manilha);
                else
                    game(p4,p1,p2,p3, partida, mesa, manilha);
                
                //retorna a posição para saber quem pontuou 
                int pos = check_winner(mesa, manilha, starts_in);
                if(pos) {
                    rounds[(pos-1)%2]++;
                    //Casos de primeira vitoria para gerar vantagem
                    if(pos%2 && !vantagem) {
                        vantagem = 1;
                    }
                    else if(pos%2==0 && !vantagem) {
                        vantagem = 2;
                    }
                }
                else {
                    //Caso de empate as duas duplas pontuam 
                    for(int i=0; i<2; i++) { rounds[i]++; }
                }

                starts_in = pos;

                //Libera o monte que estava sobre a mesa
                free_baralho(mesa);
            }

            printf("\nVENCEDOR DA PARTIDA %d: ", partida++);
            //Caso empate na ultima rodada
            if(rounds[0] == rounds[1] && vantagem) {
                if(vantagem == 1) {
                    printf("%s & %s\n", getName(p1), getName(p3));
                    vitorias[0]++; 
                }
                else {
                    printf("%s & %s\n", getName(p2), getName(p4));
                    vitorias[1]++; 
                }
            }
            //Primeira dupla vencedora
            else if(rounds[0] > rounds[1]){
                printf("%s & %s\n", getName(p1), getName(p3));
                vitorias[0]++; 
            }
            //Segunda dupla vencedora
            else if(rounds[1] > rounds[0]) {
                printf("%s & %s\n", getName(p2), getName(p4));
                vitorias[1]++;
            }

            sleep(2);

            //Libera todos os elementos criados
            free_deck(manilha);
            free_baralho(baralho);
            free_player(p1);
            free_player(p2);
        }
        
        printf("\nVENCEDORES DO JOGO: \n");
        if(vitorias[0] > vitorias[1]){
            printf("%s & %s\n", jogador1, jogador3);
            vitorias[0]++; 
        }
        else {
            printf("%s & %s\n", jogador2, jogador4);
            vitorias[1]++;
        }

        troca_tela(10);
    }

    printf("\nOBRIGADO POR JOGAR :)\n");
    
    return 0;
}