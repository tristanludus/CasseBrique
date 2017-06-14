#include "header.h"
void InitBalle(balle *Balle){

    Balle->position.x=SCREEN_WIDTH/2-24;
    Balle->position.y=SCREEN_HEIGHT/2-24;
    Balle->vitesse=6;
    Balle->hauteur=24;
    Balle->largeur=24;
    Balle->haut_bas=0;
    Balle->gauche_droite=0;


}

void AfficheBalle(game *myGame,gameState state,balle *Balle){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        myGame->g_surface = IMG_Load("./assets/ball.png");//Chargement de l'image bitmap

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
                    rectangleSource.w=Balle->largeur;
                    rectangleSource.h=Balle->hauteur;



                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=Balle->position.x;//debut x
                    rectangleDest.y=Balle->position.y;//debut y
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


void DeplacementBalle(balle *Balle){

    if (Balle->haut_bas==1){

        Balle->position.y+=Balle->vitesse; //la balle va vers le bas

    }
    else if (Balle->haut_bas==0){

        Balle->position.y-=Balle->vitesse; //la balle va vers le haut

    }

    if (Balle->gauche_droite==1){

        Balle->position.x+=Balle->vitesse; //la balle va vers la droite
    }
    else if (Balle->gauche_droite==0){

        Balle->position.x-=Balle->vitesse; //la balle va vers la gauche
    }

}


void Collision(balle *Balle, raquette *joueur){

    if (Balle->position.x>=SCREEN_WIDTH-40){

        Balle->gauche_droite=0; //empêche la balle d'aller plus loin que le mur droit et la renvoie vers la gauche

    }else if (Balle->position.x<=16){

        Balle->gauche_droite=1; //empêche la balle d'aller plus loin que le mur gauche et la renvoie vers la droite
    }

    if ((Balle->position.y+24>=joueur->position.y) && (Balle->position.x>=joueur->position.x) && (Balle->position.x+24<=joueur->position.x+128)){

        Balle->haut_bas=0; // la balle rebondit sur la raquette

    }else if (Balle->position.y<=0){

        Balle->haut_bas=1; //empêche la balle d'aller plus loin que le mur du haut
    }



}
