/**
 * TP1
 * Fichier tournament.c
 * 
 * @author Yassine Hasnaoui (HASY04089702)
 */


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


/** Creates a Player with the specified name and Number.
 *
*/
typedef struct 
{
    char name[30];
    int PlayerNumber;
} player;

/** Creates an Array of Players
 * 20 of Capacity 
 * 
*/
typedef struct
{
    player Array[20];
} PlayerArray;

/** Creates a match between two Players
 * 
 * Stores the  two players and the day of the match.
 * 
*/
typedef struct
{
    //contient les joueurs qui s'affrontent et le jour du match
    player Player1;
    player Player2;
    int Day;
} Match;

/** Creates a 2D Array of Matchs 
 * Each row of this array represent a Day that 
 * will store the matchs of that day.
 * 
*/
typedef struct
{
    Match Array[20][20];
} MatchsArray;

/** Creates a Player with the list of his opponents in the tournament
 * 
*/
typedef struct
{ 
    // the actual player
    player ThePlayer;
    // the list of his opponents
    player opponentsList[20]; //verifier la limite

} PlayerOpponents;

/** Creates an Array of PlayerOpponents
 * 20 of Capacity
*/
typedef struct
{
    PlayerOpponents Array[20];

} OpponentsArray;

/** Creates an Array of all matchs of the tournament.
 * 
*/
typedef struct
{
    Match Array[200];

} ArrayMatchs;

/** Read the Input file (.in) where is stored all the players.
 * Store all the players in Array and return the number of players.
 * Adds the player Bye if necessary.
 * 
 * @param MyPlayerArray The Array of players
 * @return number of players
*/
int lectureInput(PlayerArray *MyPlayerArray)
{
    int compteur = 0;

    player newplayer;
    while (fgets(newplayer.name, sizeof newplayer.name, stdin) != NULL)
    {
        //Pour enlever le caractere entree
        char *p = newplayer.name;
        p[strlen(p) - 1] = '\0';
        //
        newplayer.PlayerNumber = compteur + 1; //+1 car compteur commence par 0
        MyPlayerArray->Array[compteur] = newplayer;

        compteur++;
    }
    if (compteur<2)
    {
        fprintf(stderr, "%s", "Error: not enough players (minimum is 2)\n");
        exit(1);        
    }else if (compteur>20)
    {
        fprintf(stderr, "%s", "Error: too many players (maximum is 20)\n");
        exit(1);      
    }
    
    
    //Si le nombre de joueurs est impair, on introduit un joueur artificiel Bye
    if (compteur % 2 != 0)
    {
        player newplayer;
        strcpy(newplayer.name, "Bye");
        newplayer.PlayerNumber = compteur + 1;
        MyPlayerArray->Array[compteur] = newplayer;
        compteur++;
    }

    return compteur;
}

/** Creates all the matchs of the tournament and store them in the tournament.
 * 
 * @param NombreJoueurs the number of players
 * @param MyplayerArray The players
 * @param Tournament The empty array of matchs of the tournament
 * @param AllMatchs The empty Array of matchs of the tournament
 * 
*/
void StoreData(int NombreJoueurs, PlayerArray *MyplayerArray, MatchsArray *Tournament,ArrayMatchs *AllMatchs)
{
    player Player1, Player2;
    int Day;
    int numberOfMatchs=0;
       //Represente le nombre de jours du tournois (nombre de lignes)
    //represente le nombre de colonne pour chaque jours du tournois
    //lecture sur la liste des joueurs
    for (int i = 0; i < NombreJoueurs; i++)
    {
        for (int j = i + 1; j < NombreJoueurs; j++)
        {
            //creation d'un nouveau match
            Match NewMatch;
            //Identification des joueurs du match
            Player1 = MyplayerArray->Array[i];
            Player2 = MyplayerArray->Array[j];
            //Calcul du jour ou les joueurs 1 et 2 saffrontents

            // *notation i et j venant de wikipedia, represente les joueurs 1 et 2 dans la formule*
            //Cas où i≠n et j≠n
            if (Player1.PlayerNumber != NombreJoueurs && Player2.PlayerNumber != NombreJoueurs)
            {
                //si i+j-1 < n
                if (Player1.PlayerNumber + Player2.PlayerNumber - 1 < NombreJoueurs)
                {
                    Day = Player1.PlayerNumber + Player2.PlayerNumber - 1;
                }
                //si i+j-1 ≥ n
                else if (Player1.PlayerNumber + Player2.PlayerNumber - 1 >= NombreJoueurs)
                {
                    Day = Player1.PlayerNumber + Player2.PlayerNumber - NombreJoueurs;
                }
            }
            else if (Player2.PlayerNumber == NombreJoueurs) //Cas où j=n
            {
                //si 2i ≤ n
                if (2 * Player1.PlayerNumber <= NombreJoueurs)
                {
                    Day = 2 * Player1.PlayerNumber - 1;
                }
                else if (2 * Player1.PlayerNumber > NombreJoueurs) //si 2i > n
                {
                    Day = 2 * Player1.PlayerNumber - NombreJoueurs;
                }
            }

            //Need a 2d array to store multiple matchs in a sinsgle day
            NewMatch.Day = Day;
            NewMatch.Player1 = Player1;
            NewMatch.Player2 = Player2;
            AllMatchs->Array[numberOfMatchs]=NewMatch;
            numberOfMatchs++;
            //representre le iem match de la journee
           // int MatchNumber = 0;
            //tant qu'il y a des matchs dans cette journee, on incremenete le numeros du prochain match
          //  while (Tournament->Array[Day][MatchNumber].Day != 0)
          //  {
        //        MatchNumber++;
          //  }
            //store the new match in the tournament
            //le nouveau match se passera a la journee Day et il est placé apres tout les autres matchs
            //de la meme journee avant lui (MatchNumber)
           // Tournament->Array[Day][MatchNumber] = NewMatch;
        }
    }
    //
    for (int i = 0; i < numberOfMatchs; i++)
    {
        //representre le iem match de la journee
        int MatchNumber = 0;
            //tant qu'il y a des matchs dans cette journee, on incremenete le numeros du prochain match
        while (Tournament->Array[AllMatchs->Array[i].Day][MatchNumber].Day != 0)
        {
               MatchNumber++;
        }
        Tournament->Array[AllMatchs->Array[i].Day][MatchNumber] = AllMatchs->Array[i];
       
    }
    
 
 
    


}
/** Creates the List of opponents of each players for easier Display.
 * @param Tournament The tournament
 * @param playerOpponents the empty 2d Array where we store the opponents.
 * @param NombreJoueurs the number of players
 * 
*/
void GenerateOpponents(MatchsArray *Tournament, OpponentsArray *playerOpponents, int nombreJoueurs)
{
    int PlayerID = 1;

    //Represente le nombre de jours du tournois (nombre de lignes)
    int NumberOfDays = nombreJoueurs - 1;
    //represente le nombre de colonne pour chaque jours du tournois
    int MatchsPerDay = nombreJoueurs / 2;

    while (PlayerID <= nombreJoueurs)
    {
        //represente le nombre d'adversaire du joueur
        int OpponentsNumber = 0;
        //Pour tout les jours du tournois
        for (int Day = 0; Day < NumberOfDays + 1; Day++)
        {
            //on parcours tout les matchs du jour
            for (int Match = 0; Match < MatchsPerDay + 1; Match++)
            {
                //si le numeros du joueurs actuelle correspond au joueur1 du match
                if (PlayerID == Tournament->Array[Day][Match].Player1.PlayerNumber)
                {

                    //On l'ajoure comme joueur dans la liste
                    playerOpponents->Array[PlayerID].ThePlayer = Tournament->Array[Day][Match].Player1;
                    //son adversaire sera le joueur 2
                    playerOpponents->Array[PlayerID].opponentsList[OpponentsNumber] = Tournament->Array[Day][Match].Player2;
                    OpponentsNumber++;
                }
                //si le numeros du joueurs actuelle correspond au joueur2 du match
                else if (PlayerID == Tournament->Array[Day][Match].Player2.PlayerNumber)
                {

                    //On l'ajoure comme joueur dans la liste
                    playerOpponents->Array[PlayerID].ThePlayer = Tournament->Array[Day][Match].Player2;
                    //son adversaire sera le joueur 1
                    playerOpponents->Array[PlayerID].opponentsList[OpponentsNumber] = Tournament->Array[Day][Match].Player1;
                    OpponentsNumber++;
                }
            }
        }
        PlayerID++;
    }
}

/** Default Printing. (-f id et -s compact)
 * @param nombreJoueurs 
 * @param MyplayerArray 
 * @param playerOpponents 
 * 
*/
void AffichageDefaut(int nombreJoueurs, PlayerArray *MyplayerArray, OpponentsArray *playerOpponents)
{
    //Represente le nombre de jours du tournois (nombre de lignes)
    int NumberOfDays = nombreJoueurs - 1;

    for (int i = 0; i < nombreJoueurs; i++)
    {
        printf("%d:%s", MyplayerArray->Array[i].PlayerNumber, MyplayerArray->Array[i].name);
        printf("\n");
    }
    // i need a new type of array here
    for (int playerID = 1; playerID <= nombreJoueurs; playerID++)
    {
        printf("%d:", playerOpponents->Array[playerID].ThePlayer.PlayerNumber);
        for (int Opponent = 0; Opponent < NumberOfDays; Opponent++)
        {
            if (Opponent < NumberOfDays - 1)
            {
                printf("%d,", playerOpponents->Array[playerID].opponentsList[Opponent].PlayerNumber);
            }
            else if (Opponent < NumberOfDays)
            {
                printf("%d", playerOpponents->Array[playerID].opponentsList[Opponent].PlayerNumber);
            }
        }
        printf("\n");
    }
}
/**  Printing with names
 *  @param nombreJoueurs 
 *  @param playerOpponents 
 * 
*/
void AffichageNoms(int nombreJoueurs, OpponentsArray *playerOpponents)
{
    //Represente le nombre de jours du tournois (nombre de lignes)
    int NumberOfDays = nombreJoueurs - 1;

    for (int playerID = 1; playerID <= nombreJoueurs; playerID++)
    {
        printf("%s:", playerOpponents->Array[playerID].ThePlayer.name);
        for (int Opponent = 0; Opponent < NumberOfDays; Opponent++)
        {
            if (Opponent < NumberOfDays - 1)
            {
                printf("%s,", playerOpponents->Array[playerID].opponentsList[Opponent].name);
            }
            else if (Opponent < NumberOfDays)
            {
                printf("%s", playerOpponents->Array[playerID].opponentsList[Opponent].name);
            }
        }
        printf("\n");
    }
}
/** Display the tournament in a table with id of players
 * @param nombreJoueurs 
 * @param playerOpponents 
 * 
*/
void AffichageTableID(int nombreJoueurs, OpponentsArray *playerOpponents)
{
    //Represente le nombre de jours du tournois (nombre de lignes)
    int NumberOfDays = nombreJoueurs - 1;
  
    //table header
    printf("ID  ");
    printf("Player    ");
    for (int i = 0; i < NumberOfDays; i++)
    {
        printf("Day %d   ", i + 1);
    }
    printf("\n");
    printf("--  --------  ");
    for (int i = 0; i < NumberOfDays; i++)
    {
        printf("------  ");
    }
    printf("\n");

    for (int playerID = 1; playerID <= nombreJoueurs; playerID++)
    {
        if (strlen(playerOpponents->Array[playerID].ThePlayer.name) > 8)
        {
            char *ThePlayerName = playerOpponents->Array[playerID].ThePlayer.name;
            printf(" %d  ", playerOpponents->Array[playerID].ThePlayer.PlayerNumber);
            printf("%.8s%*s  ", ThePlayerName, 0, "");
        }
        else
        {
            char *ThePlayerName = playerOpponents->Array[playerID].ThePlayer.name;
            printf(" %d  ", playerOpponents->Array[playerID].ThePlayer.PlayerNumber);
            printf("%.8s%*s  ", ThePlayerName, (int)(8 - strlen(playerOpponents->Array[playerID].ThePlayer.name)), "");
        }
        for (int Opponent = 0; Opponent < NumberOfDays; Opponent++)
        {
            printf("%d       ", playerOpponents->Array[playerID].opponentsList[Opponent].PlayerNumber);
        }
        printf("\n");
    }
}
/** Display the tournament in a table with names of players
 * @param nombreJoueurs 
 * @param playerOpponents
 * 
*/
void AfficherTableName(int nombreJoueurs, OpponentsArray *playerOpponents)
{
    //Represente le nombre de jours du tournois (nombre de lignes)
    int NumberOfDays = nombreJoueurs - 1;
   
    //table header
    printf("ID  ");
    printf("Player    ");
    for (int i = 0; i < NumberOfDays; i++)
    {
        printf("Day %d     ", i + 1);
    }
    printf("\n");
    printf("--  --------  ");
    for (int i = 0; i < NumberOfDays; i++)
    {
        printf("--------  ");
    }
    printf("\n");

    for (int playerID = 1; playerID <= nombreJoueurs; playerID++)
    {
        if (strlen(playerOpponents->Array[playerID].ThePlayer.name) > 8)
        {
            char *ThePlayerName = playerOpponents->Array[playerID].ThePlayer.name;
            printf(" %d  ", playerOpponents->Array[playerID].ThePlayer.PlayerNumber);
            printf("%.8s%*s  ", ThePlayerName, 0, "");
        }
        else
        {
            char *ThePlayerName = playerOpponents->Array[playerID].ThePlayer.name;
            printf(" %d  ", playerOpponents->Array[playerID].ThePlayer.PlayerNumber);
            printf("%.8s%*s  ", ThePlayerName, (int)(8 - strlen(playerOpponents->Array[playerID].ThePlayer.name)), "");
        }
        for (int Opponent = 0; Opponent < NumberOfDays; Opponent++)
        {
            if (strlen(playerOpponents->Array[playerID].opponentsList[Opponent].name) > 8)
            {
                char *TheOpponentName = playerOpponents->Array[playerID].opponentsList[Opponent].name;
                printf("%.8s%*s  ", TheOpponentName, 0, "");
            }
            else
            {
                char *TheOpponentName = playerOpponents->Array[playerID].opponentsList[Opponent].name;
                printf("%.8s%*s  ", TheOpponentName, (int)(8 - strlen(playerOpponents->Array[playerID].opponentsList[Opponent].name)), "");
            }
        }
        printf("\n");
    }
}

//recuperer les arguments du main pour determiner le format d'affichage
int main(int argc, char *argv[])
{
    //creation de la liste des joueurs
    PlayerArray MyPlayerArray;
    ArrayMatchs AllMatchs;
    //creation du tournois
    MatchsArray Tournament;
    OpponentsArray playerOpponents;
    int NombreJoueurs;

    //lecture des joueurs du tournois
    NombreJoueurs = lectureInput(&MyPlayerArray);
    //Stockage des donnees concernant les matchs du tournois
    StoreData(NombreJoueurs, &MyPlayerArray, &Tournament,&AllMatchs);
    //Generate Opponents list
    GenerateOpponents(&Tournament, &playerOpponents, NombreJoueurs);
    ////////////////////////////////////////////////////////
    //GESTION DES ERREURS
    if (argc != 1 && argc != 3 && argc != 5)
    {
        //nombre d'arguments, en plus du nom du programme, doit être 0, 2 ou 4.
        fprintf(stderr, "%s", "Error: wrong number of arguments\n");
        exit(1);
    }
    else
        //Si l'utilisateur entre des options d'affichage
        if (argc > 1)
    {
        // Affichage Selon le format et le style
        // Dans le cas ou l'utilisateur choisi de rentre le format en premier
        if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--format") == 0)
        {
            if (strcmp(argv[2], "id") == 0)
            {

                if (argc > 3 && strcmp(argv[3], "-s") == 0)
                {
                    if (strcmp(argv[4], "compact") == 0)
                    {
                        AffichageDefaut(NombreJoueurs, &MyPlayerArray, &playerOpponents);
                    }
                    else if (strcmp(argv[4], "table") == 0)
                    {
                        /* code */
                        AffichageTableID(NombreJoueurs, &playerOpponents);
                    }
                    else
                    {
                        fprintf(stderr, "Error: unknown format (%s)\n", argv[4]);
                        exit(1);
                    }
                }
                else if (argc == 3)
                {
                    printf("Affichage court avec id\n");
                    AffichageDefaut(NombreJoueurs, &MyPlayerArray, &playerOpponents);
                }
                else
                {
                    //erreur
                    fprintf(stderr, "%s", "Error: unknown option ()\n");
                    exit(1);
                }
            }
            else if (strcmp(argv[2], "name") == 0)
            {
                AffichageNoms(NombreJoueurs, &playerOpponents);
            }
            else
            {
                fprintf(stderr, "Error: unknown format (%s)\n", argv[2]);
                exit(1);
            }

            //Si l'utilisateur entre le style
        }
        //Dans le cas ou l'utilisateur decide de rentrer le style en premier
        else if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--style") == 0)
        {
            if (strcmp(argv[2], "table") == 0)
            {
                //si l'utilisateur entre le format
                if (argc > 3 && strcmp(argv[3], "-f") == 0)
                {
                    if (strcmp(argv[4], "name") == 0)
                    {
                        //Table avec Name
                        AfficherTableName(NombreJoueurs, &playerOpponents);
                    }
                    else if (strcmp(argv[4], "id") == 0)
                    {
                        //table avec id
                        AffichageTableID(NombreJoueurs, &playerOpponents);
                    }
                    else
                    {
                        /* code */
                        fprintf(stderr, "%s", "Error: unknown format (<valeur>)\n");
                        exit(1);
                    }
                }
                else if (argc == 3)
                {
                    //table avec id
                    AffichageTableID(NombreJoueurs, &playerOpponents);
                }
            }
            else if (strcmp(argv[2], "compact") == 0)
            {
                // -s compact
            }
            else
            {
                fprintf(stderr, "Error: unknown style (%s)\n", argv[2]);
                exit(1);
            }

            //sinon
        }
        else
        {
            //Erreur
            fprintf(stderr, "Error: unknown option (%s)\n", argv[1]);
            exit(1);
        }
    }
    //Affichage Par defaut
    else
    {
        AffichageDefaut(NombreJoueurs, &MyPlayerArray, &playerOpponents);
    }

    return 0;
}


