#include "header.h"

void InitRaq(raquette *joueur){

    joueur->position.x=SCREEN_WIDTH/2-64;
    joueur->position.y=SCREEN_HEIGHT-32;
    joueur->vitesse=5;
    joueur->hauteur=32;
    joueur->largeur=128;


}

void AfficheRaq(game *myGame,gameState state, raquette *joueur){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        myGame->g_surface = IMG_Load("./assets/paddle.png");//Chargement de l'image bitmap

         if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", SDL_GetError());
            // handle error
        }

        if(myGame->g_surface){

                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){

                    //gestion des animations
                    rectangleSource.x=0;
                    rectangleSource.y=0;
                    rectangleSource.w=joueur->largeur;
                    rectangleSource.h=joueur->hauteur;



                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=joueur->position.x;//debut x
                    rectangleDest.y=joueur->position.y;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

    destroyTexture(myGame);


}

void DeplacementRaq(int touches[2],raquette *joueur){

    if ((touches[0]==1) && (CollisionRaq(joueur)!=gauche)){ //utilisation de la touche pour bouger la raquette vers la gauche

        joueur->position.x-=joueur->vitesse;

    }
    else if ((touches[1]==1) && (CollisionRaq(joueur)!=droite)){ //utilisation de la touche pour bouger la raquette vers la droite
        joueur->position.x+=joueur->vitesse;
    }

}

int CollisionRaq(raquette *joueur){

    if (joueur->position.x>=SCREEN_WIDTH-144){

        return droite; //empêche d'aller plus loin que le mur droit

    }else if (joueur->position.x<=16){

        return gauche; //empêche d'aller plus loin que le mur gauche
    }

    return 0;

}
