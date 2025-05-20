#include <stdio.h>
#include "board.h"

/**
 * @file main.c
 * @brief a simple game using a library name board.h and a compile file name board.o
 * @author Ilhan Mary and Willelm Delacoudre
 */


//Function to set up the different settings//

bool select_game_hexa() /*The function test if the player want to play with a normal grid or a hexa grid*/
{
    bool is_hexa = false;
    char hexa[1];
    printf("Voulez-vous lancer le jeu dans sa version hexa (O - N) : ");
    scanf("%c", hexa);
    if (hexa[0] == 'O' || hexa[0] == 'o')
    {
        is_hexa = true;
    }
    else if (hexa[0] == 'N' || hexa[0] == 'n')
    {
        is_hexa = false;
    }
    else
    {
        printf("\033[1;31mSaisie non valide ! Veuillez réessayer !\033[00m\n\n");
        while ((hexa[0] = getchar()) != '\n')
            ;
        select_game_hexa();
    }
    while ((hexa[0] = getchar()) != '\n')
        ;
    return is_hexa;
}

bool select_game_range() /*The function test if the player wants to play with a range system or a normal system*/
{
    bool us_range = false;
    char range[1];
    printf("Voulez-vous lancer le jeu dans sa version range (O - N) : ");
    scanf("%c", range);
    if (range[0] == 'O' || range[0] == 'o')
    {
        us_range = true;
    }
    else if (range[0] == 'N' || range[0] == 'n')
    {
        us_range = false;
    }
    else
    {
        printf("\033[1;31mSaisie non valide ! Veuillez réessayer !\033[00m\n\n");
        while ((range[0] = getchar()) != '\n')
            ;
        select_game_range();
    }
    while ((range[0] = getchar()) != '\n')
        ;
    return us_range;
}

void select_name(char name_player_1[32], char name_player_2[32]) /*Allows the two players to select a name for one game*/
{
    printf("\n\033[1;36mJoueur 1\033[00m veuillez choisir votre nom : ");
    scanf("%s", name_player_1);

    printf("\033[1;35mJoueur 2\033[00m veuillez choisir votre nom : ");
    scanf("%s", name_player_2);
}



//Function so the game can work noramlly//



void get_player_location(board game, int tab[2]) /*The function allows the game to get the location of a specific player*/
{
    player whos_playing = current_player(game);
    for (int l = 0; l < NB_LINES; l++)
    {
        for (int c = 0; c < NB_COLS; c++)
        {
            if (whos_playing == 1 && get_content(game, l, c) == NORTH_KING)
            {
                tab[0] = l;
                tab[1] = c;
            }
            else if (whos_playing == 2 && get_content(game, l, c) == SOUTH_KING)
            {
                tab[0] = l;
                tab[1] = c;
            }
        }
    }
}

void display_grid(board game) /*Show the current grid with the players, empty cells and dead cells*/
{
    printf("\n");
    int i = 0;
    printf("\t   ");
    for (i = 0; i < NB_COLS * 2; i++)
    {
        if (i % 2 == 1)
        {
            printf("%d ", i / 2 + 1);
        }
        else
        {
            printf("  ");
        }
    }
    printf("\n");
    for (i = 0; i <= NB_LINES * 2; i++)
    {
        if (i % 2 == 1)
        {
            printf("\t%d  ", i / 2 + 1);
        }
        else
        {
            printf("\t   ");
        }
        for (int j = 0; j <= NB_COLS * 2; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
            {
                printf("+ ");
            }
            else if (i % 2 == 0 && j % 2 == 1)
            {
                printf("- ");
            }
            else if (i % 2 == 1 && j % 2 == 0)
            {
                printf("| ");
            }
            else if (i % 2 == 1 && j % 2 == 1)
            {
                cell cellule = get_content(game, i / 2, j / 2);
                if (cellule == 1)
                {
                    printf("\033[1;36mN \033[00m");
                }
                else if (cellule == 2)
                {
                    printf("\033[1;35mS \033[00m");
                }
                else if (cellule == 3)
                {
                    printf("\033[1;47m#\033[00m ");
                }
                else
                {
                    printf("  ");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void view_direction(board game) /*Allows the player to see in witch direction he can go*/
{
    int tab_player_location[2];
    get_player_location(game, tab_player_location);
    int tab_possible_directions[3][3] = {{6, 7, 8}, {4, 0, 5}, {1, 2, 3}};

    int verif_coordonate_l = -1;
    int verif_coordonate_c = -1;
    for (int l = 0; l < 3; l++)
    {
        printf("\t");
        for (int c = 0; c < 3; c++)
        {
            if (tab_possible_directions[l][c] == 0)
            {
                player joueur = current_player(game);
                if (joueur == 1)
                {
                    printf("\033[1;36mN \033[00m");
                }
                else
                {
                    printf("\033[1;35mS \033[00m");
                }
                verif_coordonate_c += 1;
            }
            else if (get_content(game, tab_player_location[0] + verif_coordonate_l, tab_player_location[1] + verif_coordonate_c) < 1)
            {
                printf("\033[1;32m%d \033[00m", tab_possible_directions[l][c]);
                verif_coordonate_c += 1;
            }
            else
            {
                printf("\033[1;31mX \033[00m");
                verif_coordonate_c += 1;
            }
        }
        verif_coordonate_l += 1, verif_coordonate_c = -1;
        printf("\n");
    }
    printf("\n");
}

void player_move(board game) /*A function that treat the player input move and see if it work or if something is wrong*/
{
    int i = -1;
    view_direction(game);
    printf("Choisissez la direction que vous souhaitez prendre : ");
    scanf("%d", &i);

    direction movewhere = i - 1;
    while ((i = getchar()) != '\n')
        ;
    enum return_code result = move_toward(game, movewhere);
    if (result == OK)
    {
        printf("\033[1;32mDéplacement réussi !\033[00m\n\n");
    }
    else if (result == BUSY)
    {
        printf("\033[1;31mDéplacement impossible, cellule déjà occupé\033[00m\n\n");
        player_move(game);
    }
    else if (result == OUT)
    {
        printf("\033[1;31mDéplacement impossible, vous souhaitez vous déplacé hors du jeu\033[00m\n\n");
        player_move(game);
    }
    else if (result == RULES)
    {
        printf("\033[1;31mERREUR !!! La direction que vous avez selectionnez est incorrect\nVeuillez réessayer\033[00m\n\n");
        player_move(game);
    }
}

void player_kill(board game) /*A function that ask the player which cell he wants to kill and if something is wrong, it tells him*/
{
    int l, c;
    printf("Quelle est la ligne de la cellule que vous voulez tuez : ");
    scanf("%d", &l);
    printf("Quelle est la colonne de la cellule que vous voulez tuez : ");
    scanf("%d", &c);

    l -= 1, c -= 1;
    enum return_code result = kill_cell(game, l, c);
    if ((l < 0 || l > NB_LINES) || (c < 0 || c > NB_COLS))
    {
        while ((l = getchar()) != '\n')
            ;
        while ((c = getchar()) != '\n')
            ;
    }

    if (result == OK)
    {
        printf("\033[1;32mLa cellule à été tué avec succès !\033[00m\n\n");
    }
    else if (result == BUSY)
    {
        printf("\033[1;31mLa cellule que vous voulez tuez est déjà en possession d'un des deux rois !\nVeuillez réessayer\033[00m\n\n");
        player_kill(game);
    }
    else if (result == OUT)
    {
        printf("\033[1;31mLa cellule que vous voulez tuez n'est pas dans le terrain ou est déjà morte !\nVeuillez réessayer\033[00m\n\n");
        player_kill(game);
    }
    else if (result == RULES)
    {
        printf("\033[1;31mImpossible, vous ne respectez pas les règles !!!\nVeuillez réessayer\033[00m\n\n");
        player_kill(game);
    }
}

int player_action(board game, bool is_hexa, bool use_range, char name_player_1[32], char name_player_2[32]) /*Play a player's turn*/
{
    player whos_playing = current_player(game);
    if (whos_playing == 1)
    {
        printf("\033[1;36m%s\033[00m, c'est ton tour ! \n\n", name_player_1);
    }
    else if (whos_playing == 2)
    {
        printf("\033[1;35m%s\033[00m, c'est ton tour ! \n\n", name_player_2);
    }

    player_move(game);
    display_grid(game);
    player_kill(game);

    return 0;
}

int victory_test(board game, char name_player_1[32], char name_player_2[32]) /*A function that test if a player won the game and show the winner*/
{
    player victory_condition = get_winner(game);
    if (victory_condition == 1)
    {
        view_direction(game);
        printf("\033[5;40mBravo \033[1;36m%s\033[00m ! Tu as gagné !\33[00m\n\n", name_player_1);
        return 1;
    }
    if (victory_condition == 2)
    {
        view_direction(game);
        printf("\033[5;40mBravo \033[1;35m%s\033[00m ! Tu as gagné !\33[00m\n\n", name_player_2);
        return 1;
    }
    return 0;
}

void special_display_game(board game) /*A function that show and hexa grid (work in progress)*/
{
    int largeur = 5;
    for (int i = 0; i <= HEX_SIDE * 2; i++)
    {
        for (int k = 0; k < HEX_SIDE * 2 - i; k++)
        {
            printf(" ");
        }
        for (int j = 0; j < largeur; j++)
        {
            if (i % 2 == 0)
            {
                printf(" / \\");
            }
            else if (i % 2 == 1)
            {
                printf(" |  ");
            }
        }
        if (i % 2 == 0)
        {
            largeur += 1;
        }

        printf("\n");
    }
    largeur -= 1;
    for (int i = 0; i < HEX_SIDE * 2; i++)
    {
        for (int k = HEX_SIDE; k <= HEX_SIDE * 2 + i; k++)
        {
            printf(" ");
        }
        for (int j = 0; j < largeur * 2; j++)
        {
            if (i % 2 == 0)
            {
                printf(" \\ /");
            }
            else if (i % 2 == 1)
            {
                printf(" |  ");
            }
        }
        if (i % 2 == 1)
        {
            largeur -= 1;
        }

        printf("\n");
    }
}


// the next function treat all the functions above and assemble them so the game can work//


void game_structure() /*this is the main structur of the game*/
{
    printf("\033[1;44mBienvenue dans ce jeu, votre objectif est de faire en sorte que votre adversaire ne puisse plus bouger.\033[00m\n\n");
    bool is_hex = select_game_hexa();
    bool use_range = select_game_range();
    board game = new_special_game(is_hex, use_range);

    char name_player_1[32], name_player_2[32];
    select_name(name_player_1, name_player_2);
    printf("\033[1;44mAttention : Si vous avez séléctionné le mode range alors la distance maximal est de 3 cellules\033[00m\n");
    printf("\033[1;44mBonne chance et bon jeu !\033[00m\n");
    if (is_hex == true)
    {
        while (victory_test(game, name_player_1, name_player_2) == 0)
        {
            special_display_game(game);
            player_action(game, is_hex, use_range, name_player_1, name_player_2);
        }
    }
    else
    {
        while (victory_test(game, name_player_1, name_player_2) == 0)
        {
            display_grid(game);
            player_action(game, is_hex, use_range, name_player_1, name_player_2);
        }
    }
    destroy_game(game);
}

int main()
{
    game_structure();
    return 0;
}