#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <sys/time.h>
#include <SDL/SDL_mixer.h>


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;

    //PASSANDO OS DESTINOS;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}
/*
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}
*/

/*
void blita_tudo(int mapa[][], SDL_Surface* blocoind, SDL_Surface* blocodes, SDL_Surface* imgbomb, SDL_Surface* screen){
    int i,j;
    for(i=0;i<17;i++){
        for(j=0;j<11;j++){
            if(mapa[j][i]==1){
                apply_surface((53+i*54),(119+j*54),blocoind,screen);
            }
            else if(mapa[j][i]==3){
                apply_surface((53+i*54),(119+j*54),blocodes,screen);
            }
                 // else if(mapa[j][i]==2)
                 // {
                 //     apply_surface((68+i*64),(164+j*64),sprite_dn_bai3_game_DN,screen);
                 // }
             else if(mapa[j][i]==5){
                apply_surface((53+i*54),(119+j*54),imgbomb,screen);
             }
         }
     }
}
*/


int main ( int argc, char** argv )
{
    SDL_Rect personagem;
    SDL_Rect dn_sprite[16];
    SDL_Rect *dn_pointer;

    SDL_Rect bomb;
    SDL_Rect bomb_sprite[2];
    SDL_Rect *bomb_pointer;

    SDL_Rect exp_cent;
    SDL_Rect exp_cim;
    SDL_Rect exp_esq;
    SDL_Rect exp_bai;
    SDL_Rect exp_dir;
    SDL_Rect exp_cimfim;
    SDL_Rect exp_esqfim;
    SDL_Rect exp_baifim;
    SDL_Rect exp_dirfim;
    SDL_Rect exp_sprite[18];
    SDL_Rect *exp_cent_pointer;
    SDL_Rect *exp_cim_pointer;
    SDL_Rect *exp_esq_pointer;
    SDL_Rect *exp_bai_pointer;
    SDL_Rect *exp_dir_pointer;
    SDL_Rect *exp_cimfim_pointer;
    SDL_Rect *exp_esqfim_pointer;
    SDL_Rect *exp_baifim_pointer;
    SDL_Rect *exp_dirfim_pointer;


    Uint8 *keystates = SDL_GetKeyState( NULL );

    int i,j;
    int tempo_passo = 0, ult_sent = 8, cmpr_sent = 8, rodador = 1, conf_bomb = 0, frac_passoy = 0, frac_passox = 0, tempo_passo_mov = 0, tempo_bomb, conf_kup = 0, rb = 1, raiobomb = 2, rodador_tbomb = 0, tempo_spritebomb = SDL_GetTicks(), colexp_a = 0, colexp_b = 0, colexp_c = 0, colexp_d = 0, tempo_rodexp = 0, rodador_animexp = 0, tempo_parexp = 0, rodador_parexp = 0;
    int  movimenta_x[2], movimenta_y[2], cord_animexp[2];
    char cron_bomb[50];
    movimenta_x[0] = 1;
    movimenta_y[0] = 1;

    //O BLOCO QUE SE MOVE COMEÇA
    int yAtual = 0;
    int xAtual = 0;

    int inc_mx  = 0;
    int inc_my  = 0; 


    int xInimigo = 2;
    int yInimigo = 2;
    int movimento = 0;

    //xAtual está relacionado com a coluna.
    //yAtual está relacionado com a linha.


    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
        return 0;
    }

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

     //Initialize SDL_ttf
    if( TTF_Init() == -1 ) {
        return 0;
    }

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return 0;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(1024, 768, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

    if ( !screen )
    {
        printf("Nao deu pra por 1024x768 de tamanho: %s\n", SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption( "Duke Nukem - Nuke Time", NULL );

    SDL_Surface* posi_matriz;
    posi_matriz = IMG_Load("posi_matriz.png");
    if (!posi_matriz)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *mens_contbomb = NULL;
    TTF_Font *font = NULL;
    SDL_Color textColor = {255,255,255};
    
    //Open the font
    font = TTF_OpenFont( "arial.ttf", 28 );

    //If there was an error in loading the font
    if( font == NULL ) {
        return 0;
    }

    // load an image
    SDL_Surface* blocoind;
    blocoind = IMG_Load("blocoindes_game_DN_2.png");
    if (!blocoind)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* player;
    player = IMG_Load("sprite_dn_game_DN.png");
    if (!player)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* blocodes;
    blocodes = IMG_Load("blocodes_game_DN.png");
    if (!blocodes)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* imgbomb;
    imgbomb = IMG_Load("sprite_bomb_game_DN.png");
    if (!imgbomb)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* imgexp;
    imgexp = IMG_Load("sprite_explosion_game_DN.png");
    if (!imgexp)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* menu;
    menu = IMG_Load("bg_menu_DN.png");
    if (!menu)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Surface* bola;
    bola = IMG_Load("selec_menu_DN.png");
    if (!bola)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    // LOAD MÚSICA.
    Mix_Music *theme = NULL;
    // LOAD FALAS.
    Mix_Chunk *diesob = NULL;
    Mix_Chunk *gameover = NULL;
    Mix_Chunk *hail = NULL;
    Mix_Chunk *kickuass = NULL;
    Mix_Chunk *letgod = NULL;
    Mix_Chunk *myname = NULL;
    Mix_Chunk *hell = NULL;
    Mix_Chunk *yipie = NULL;
    Mix_Chunk *pissin = NULL;
    Mix_Chunk *faceass = NULL;
    Mix_Chunk *bubble = NULL;
    Mix_Chunk *quit = NULL;
    Mix_Chunk *hurts = NULL;
    // LOAD EXPLOSAO
    Mix_Chunk *explosao = NULL;

    //theme = Mix_LoadMUS( "theme.wav" );

    //if(theme== NULL)
        //printf("Erro ao carregar a música\n");

    diesob = Mix_LoadWAV( "diesob.wav" );
    gameover = Mix_LoadWAV( "gameover.wav" );
    hail = Mix_LoadWAV( "hail.wav" );
    kickuass = Mix_LoadWAV( "kickuass.wav" );
    letgod = Mix_LoadWAV( "letgod.wav" );
    myname = Mix_LoadWAV( "myname.wav" );
    hell = Mix_LoadWAV( "hell.wav" );
    yipie = Mix_LoadWAV( "yipie.wav" );
    pissin = Mix_LoadWAV( "pissin.wav" );
    faceass = Mix_LoadWAV( "faceass.wav" );
    bubble = Mix_LoadWAV( "bubble.wav" );
    explosao = Mix_LoadWAV( "explosao.wav" );
    quit = Mix_LoadWAV ("quit.wav");
    hurts = Mix_LoadWAV ("hurts.wav");

    if (diesob == NULL || gameover == NULL || hail == NULL || kickuass == NULL || letgod == NULL || myname == NULL || hell == NULL || yipie == NULL || pissin == NULL || faceass == NULL || bubble == NULL || explosao == NULL || quit == NULL || hurts == NULL)
        printf("Erro ao carregar os efeitos sonoros / falas \n");




    SDL_Surface *fundo;
    fundo = IMG_Load("bg_game_DN.png");

     /* ----- Sprites bomba ----- */
     bomb_sprite[ 0 ].x = 0;
     bomb_sprite[ 0 ].y = 0;
     bomb_sprite[ 0 ].w = 54;
     bomb_sprite[ 0 ].h = 54;

     bomb_sprite[ 1 ].x = 54;
     bomb_sprite[ 1 ].y = 0;
     bomb_sprite[ 1 ].w = 54;
     bomb_sprite[ 1 ].h = 54;

     /* ----- Sprites explosao ----- */
     exp_sprite[ 0 ].x = 0;
     exp_sprite[ 0 ].y = 0;
     exp_sprite[ 0 ].w = 54;
     exp_sprite[ 0 ].h = 54;
     
     exp_sprite[ 1 ].x = 54;
     exp_sprite[ 1 ].y = 0;
     exp_sprite[ 1 ].w = 54;
     exp_sprite[ 1 ].h = 54;
     
     exp_sprite[ 2 ].x = 108;
     exp_sprite[ 2 ].y = 0;
     exp_sprite[ 2 ].w = 54;
     exp_sprite[ 2 ].h = 54;
     
     exp_sprite[ 3 ].x = 162;
     exp_sprite[ 3 ].y = 0;
     exp_sprite[ 3 ].w = 54;
     exp_sprite[ 3 ].h = 54;
     
     exp_sprite[ 4 ].x = 216;
     exp_sprite[ 4 ].y = 0;
     exp_sprite[ 4 ].w = 54;
     exp_sprite[ 4 ].h = 54;
     
     exp_sprite[ 5 ].x = 270;
     exp_sprite[ 5 ].y = 0;
     exp_sprite[ 5 ].w = 54;
     exp_sprite[ 5 ].h = 54;
     
     exp_sprite[ 6 ].x = 324;
     exp_sprite[ 6 ].y = 0;
     exp_sprite[ 6 ].w = 54;
     exp_sprite[ 6 ].h = 54;
     
     exp_sprite[ 7 ].x = 378;
     exp_sprite[ 7 ].y = 0;
     exp_sprite[ 7 ].w = 54;
     exp_sprite[ 7 ].h = 54;
     
     exp_sprite[ 8 ].x = 432;
     exp_sprite[ 8 ].y = 0;
     exp_sprite[ 8 ].w = 54;
     exp_sprite[ 8 ].h = 54;
     
     exp_sprite[ 9 ].x = 0;
     exp_sprite[ 9 ].y = 54;
     exp_sprite[ 9 ].w = 54;
     exp_sprite[ 9 ].h = 54;
     
     exp_sprite[ 10 ].x = 54;
     exp_sprite[ 10 ].y = 54;
     exp_sprite[ 10 ].w = 54;
     exp_sprite[ 10 ].h = 54;
     
     exp_sprite[ 11 ].x = 108;
     exp_sprite[ 11 ].y = 54;
     exp_sprite[ 11 ].w = 54;
     exp_sprite[ 11 ].h = 54;

     exp_sprite[ 12 ].x = 162;
     exp_sprite[ 12 ].y = 54;
     exp_sprite[ 12 ].w = 54;
     exp_sprite[ 12 ].h = 54;
     
     exp_sprite[ 13 ].x = 216;
     exp_sprite[ 13 ].y = 54;
     exp_sprite[ 13 ].w = 54;
     exp_sprite[ 13 ].h = 54;
     
     exp_sprite[ 14 ].x = 270;
     exp_sprite[ 14 ].y = 54;
     exp_sprite[ 14 ].w = 54;
     exp_sprite[ 14 ].h = 54;
     
     exp_sprite[ 15 ].x = 324;
     exp_sprite[ 15 ].y = 54;
     exp_sprite[ 15 ].w = 54;
     exp_sprite[ 15 ].h = 54;
     
     exp_sprite[ 16 ].x = 378;
     exp_sprite[ 16 ].y = 54;
     exp_sprite[ 16 ].w = 54;
     exp_sprite[ 16 ].h = 54;
     
     exp_sprite[ 17 ].x = 432;
     exp_sprite[ 17 ].y = 54;
     exp_sprite[ 17 ].w = 54;
     exp_sprite[ 17 ].h = 54;
     
     exp_sprite[ 18 ].x = 0;
     exp_sprite[ 18 ].y = 108;
     exp_sprite[ 18 ].w = 54;
     exp_sprite[ 18 ].h = 54;
     
     exp_sprite[ 19 ].x = 54;
     exp_sprite[ 19 ].y = 108;
     exp_sprite[ 19 ].w = 54;
     exp_sprite[ 19 ].h = 54;
     
     exp_sprite[ 20 ].x = 108;
     exp_sprite[ 20 ].y = 108;
     exp_sprite[ 20 ].w = 54;
     exp_sprite[ 20 ].h = 54;

     exp_sprite[ 21 ].x = 162;
     exp_sprite[ 21 ].y = 108;
     exp_sprite[ 21 ].w = 54;
     exp_sprite[ 21 ].h = 54;
     
     exp_sprite[ 22 ].x = 216;
     exp_sprite[ 22 ].y = 108;
     exp_sprite[ 22 ].w = 54;
     exp_sprite[ 22 ].h = 54;
     
     exp_sprite[ 23 ].x = 270;
     exp_sprite[ 23 ].y = 108;
     exp_sprite[ 23 ].w = 54;
     exp_sprite[ 23 ].h = 54;
     
     exp_sprite[ 24 ].x = 324;
     exp_sprite[ 24 ].y = 108;
     exp_sprite[ 24 ].w = 54;
     exp_sprite[ 24 ].h = 54;
     
     exp_sprite[ 25 ].x = 378;
     exp_sprite[ 25 ].y = 108;
     exp_sprite[ 25 ].w = 54;
     exp_sprite[ 25 ].h = 54;
     
     exp_sprite[ 26 ].x = 432;
     exp_sprite[ 26 ].y = 108;
     exp_sprite[ 26 ].w = 54;
     exp_sprite[ 26 ].h = 54;

     /* ----- Sprites Duke Nukem ----- */
     dn_sprite[ 0 ].x = 0;
     dn_sprite[ 0 ].y = 0;
     dn_sprite[ 0 ].w = 54;
     dn_sprite[ 0 ].h = 54;

     dn_sprite[ 1 ].x = 54;
     dn_sprite[ 1 ].y = 0;
     dn_sprite[ 1 ].w = 54;
     dn_sprite[ 1 ].h = 54;

     dn_sprite[ 2 ].x = 108;
     dn_sprite[ 2 ].y = 0;
     dn_sprite[ 2 ].w = 54;
     dn_sprite[ 2 ].h = 54;

     dn_sprite[ 3 ].x = 162;
     dn_sprite[ 3 ].y = 0;
     dn_sprite[ 3 ].w = 54;
     dn_sprite[ 3 ].h = 54;

     dn_sprite[ 4 ].x = 0;
     dn_sprite[ 4 ].y = 54;
     dn_sprite[ 4 ].w = 54;
     dn_sprite[ 4 ].h = 54;

     dn_sprite[ 5 ].x = 54;
     dn_sprite[ 5 ].y = 54;
     dn_sprite[ 5 ].w = 54;
     dn_sprite[ 5 ].h = 54;

     dn_sprite[ 6 ].x = 108;
     dn_sprite[ 6 ].y = 54;
     dn_sprite[ 6 ].w = 54;
     dn_sprite[ 6 ].h = 54;

     dn_sprite[ 7 ].x = 162;
     dn_sprite[ 7 ].y = 54;
     dn_sprite[ 7 ].w = 54;
     dn_sprite[ 7 ].h = 54;

     dn_sprite[ 8 ].x = 0;
     dn_sprite[ 8 ].y = 108;
     dn_sprite[ 8 ].w = 54;
     dn_sprite[ 8 ].h = 54;

     dn_sprite[ 9 ].x = 54;
     dn_sprite[ 9 ].y = 108;
     dn_sprite[ 9 ].w = 54;
     dn_sprite[ 9 ].h = 54;

     dn_sprite[ 10 ].x = 108;
     dn_sprite[ 10 ].y = 108;
     dn_sprite[ 10 ].w = 54;
     dn_sprite[ 10 ].h = 54;

     dn_sprite[ 11 ].x = 162;
     dn_sprite[ 11 ].y = 108;
     dn_sprite[ 11 ].w = 54;
     dn_sprite[ 11 ].h = 54;

     dn_sprite[ 12 ].x = 0;
     dn_sprite[ 12 ].y = 162;
     dn_sprite[ 12 ].w = 54;
     dn_sprite[ 12 ].h = 54;

     dn_sprite[ 13 ].x = 54;
     dn_sprite[ 13 ].y = 162;
     dn_sprite[ 13 ].w = 54;
     dn_sprite[ 13 ].h = 54;

     dn_sprite[ 14 ].x = 108;
     dn_sprite[ 14 ].y = 162;
     dn_sprite[ 14 ].w = 54;
     dn_sprite[ 14 ].h = 54;

     dn_sprite[ 15 ].x = 162;
     dn_sprite[ 15 ].y = 162;
     dn_sprite[ 15 ].w = 54;
     dn_sprite[ 15 ].h = 54;

    personagem.x = 53;
    personagem.y = 119;


    exp_cent_pointer = &exp_sprite[18]; 
    exp_cim_pointer = &exp_sprite[25]; 
    exp_esq_pointer = &exp_sprite[23];
    exp_bai_pointer = &exp_sprite[21];  
    exp_dir_pointer = &exp_sprite[19]; 
    exp_cimfim_pointer = &exp_sprite[26]; 
    exp_esqfim_pointer = &exp_sprite[24];
    exp_baifim_pointer = &exp_sprite[22];  
    exp_dirfim_pointer = &exp_sprite[20]; 



    //11 LINHAS 17 COLUNAS

  int mapa[11][17] = {
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,14,0,3,0,3,0,3,0,3,0,3,0,3,0,3,3},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,14,0,3,0,3,0,3,0,3,0,3,0,3,0,3,3},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,14,0,3,0,3,0,3,0,3,0,3,0,3,0,3,3},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,14,0,3,0,3,0,3,0,3,0,3,0,3,0,3,9},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,14,0,3,0,3,0,3,0,3,0,3,0,3,0,3,3},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
  /*
    int mapa[11][17] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
*/




int done = 1, donemenu = 0;
// novo jogo, continuar, instruções, recordes, sair

int opcoes = 1;
int continuar = 1, infos = 1, recordes =1;


while(donemenu == 0)
{
    apply_surface(0,0,menu,screen);

    SDL_Event menu;
        while (SDL_PollEvent(&menu))
        {
            // check for messages
            switch (menu.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                donemenu = 1;
                break;


                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // SE A TECLA PRESSIONADA FOR ESC

                    if (menu.key.keysym.sym == SDLK_ESCAPE){
                        donemenu = 0;
                    break;
                    }

                    if (menu.key.keysym.sym == SDLK_UP){
                        opcoes--;
                        if(opcoes<1)
                            opcoes = 1;



                        break;
                    }

                    if (menu.key.keysym.sym == SDLK_DOWN){ // keystates[ SDLK_DOWN ]
                        
                        opcoes++;
                        if(opcoes>5)
                            opcoes = 5;

                        break;
                    }


                    if (menu.key.keysym.sym == SDLK_RETURN){
                       if(opcoes == 1)
                            done = 0;
                        else if(opcoes == 2)
                            continuar = 0;
                        else if(opcoes == 3)
                            infos = 0;
                        else if(opcoes == 4)
                            recordes = 0;
                        else if (opcoes==5)
                            donemenu = 1;
                        break;

                    }
                }
            case SDL_KEYUP:
                {
                    
                }


            } // end switch
        }

    if(opcoes == 1)
        apply_surface(660,275,bola,screen);
    else if(opcoes == 2)
        apply_surface(670,328,bola,screen);
    else if(opcoes == 3)
        apply_surface(692,382,bola,screen);
    else if(opcoes == 4)
        apply_surface(716,432,bola,screen);
    else if(opcoes == 5)
        apply_surface(848,480,bola,screen);
        


SDL_Flip(screen);
/*----------------------------------Main Loop------------------------------*/
    while (done == 0)
    {

    if(!(inc_my != 0 && inc_mx != 0)){
        if(rodador == 1){

            if(mapa[yAtual+inc_my][xAtual] != 1 && mapa[yAtual+inc_my][xAtual] != 3 && mapa[yAtual+inc_my][xAtual] != 5 && yAtual+inc_my >= 0 && yAtual+inc_my <= 10 && movimenta_y[0] != 1){
                yAtual += inc_my;
                if(inc_my != 0){
                    movimenta_y[0] = 1;
                    movimenta_y[1] = inc_my;
                }
            }
            if(mapa[yAtual][xAtual+inc_mx] != 1 && mapa[yAtual][xAtual+inc_mx] != 3 && mapa[yAtual][xAtual+inc_mx] != 5 && xAtual+inc_mx >= 0 && xAtual+inc_mx <= 16 && movimenta_x[0] != 1){
                xAtual += inc_mx;
                if(inc_mx != 0){
                    movimenta_x[0] = 1;
                    movimenta_x[1] = inc_mx;
                }
            }

            rodador = 0;
            tempo_passo = SDL_GetTicks();

        } else if(SDL_GetTicks() - tempo_passo > 500){

            if(mapa[yAtual+inc_my][xAtual] != 1 && mapa[yAtual+inc_my][xAtual] != 3 && mapa[yAtual+inc_my][xAtual] != 5 && yAtual+inc_my >= 0 && yAtual+inc_my <= 10){
                yAtual += inc_my;
                if(inc_my != 0){
                    movimenta_y[0] = 1;
                    movimenta_y[1] = inc_my;
                }
            }
            if(mapa[yAtual][xAtual+inc_mx] != 1 && mapa[yAtual][xAtual+inc_mx] != 3 && mapa[yAtual][xAtual+inc_mx] != 5 && xAtual+inc_mx >= 0 && xAtual+inc_mx <= 16){
                xAtual += inc_mx;
                if(inc_mx != 0){
                    movimenta_x[0] = 1;
                    movimenta_x[1] = inc_mx;
                }
            }
            tempo_passo = SDL_GetTicks();
        }
    }
    if(SDL_GetTicks() - tempo_passo_mov > 115){
        if(movimenta_y[0] == 1){
            if(frac_passoy != 4){
                personagem.y = 119 + ((yAtual-movimenta_y[1])*54) + movimenta_y[1]*frac_passoy*13;
                dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                frac_passoy += 1;
            } else{
                dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                frac_passoy = 1;
                personagem.y = 119 + ((yAtual)*54);
                movimenta_y[0] = 0;
            }
        }

        if(movimenta_x[0] == 1){
            if(frac_passox != 4){
                personagem.x = 53 + ((xAtual-movimenta_x[1])*54) + movimenta_x[1]*frac_passox*13;
                dn_pointer = &dn_sprite[ult_sent+frac_passox-1];
                frac_passox += 1;
            } else{
                dn_pointer = &dn_sprite[ult_sent+frac_passox-1];
                frac_passox = 1;
                personagem.x = 53 + ((xAtual)*54);
                movimenta_x[0] = 0;
            }
        }
        tempo_passo_mov = SDL_GetTicks();
    }

    if(rodador_tbomb == 0){
        tempo_bomb = SDL_GetTicks();
    }
    if(SDL_GetTicks() - tempo_bomb > 3000){
        for(i=0;i<17;i++){
            for(j=0;j<11;j++){
                if(mapa[j][i]==5){
                        mapa[j][i] = 20;
                        rodador_animexp = 1;
                        tempo_rodexp = 0;

                        for(rb=1;rb<=raiobomb;rb++){
                            if(mapa[j-rb][i] == 3 && j-rb >= 0 && colexp_a == 0){
                                mapa[j-rb][i] = 0;
                                colexp_a = 1;
                            } else if(mapa[j-rb][i] == 1 && j-rb >= 0 && colexp_a == 0){
                                colexp_a = 1;
                            } else if(mapa[j-rb][i] == 0 && j-rb >= 0 && colexp_a == 0){
                                mapa[j-rb][i] = 21;
                                if(rb == raiobomb)
                                    mapa[j-rb][i] = 25;
                            }
                            if(mapa[j][i-rb] == 3 && i-rb >= 0 && colexp_b == 0){
                                mapa[j][i-rb] = 0;
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 1 && i-rb >= 0 && colexp_b == 0){
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 0 && i-rb >= 0 && colexp_b == 0){
                                mapa[j][i-rb] = 22;
                                if(rb == raiobomb)
                                    mapa[j][i-rb] = 26;
                            }
                            if(mapa[j+rb][i] == 3 && j+rb <= 10 && colexp_c == 0){
                                mapa[j+rb][i] = 0;
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 1 && j+rb <= 10 && colexp_c == 0){
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 0 && j+rb <= 10 && colexp_c == 0){
                                mapa[j+rb][i] = 23;
                                if(rb == raiobomb)
                                    mapa[j+rb][i] = 27;
                            }
                            if(mapa[j][i+rb] == 3 && i+rb <= 16 && colexp_d == 0){
                                mapa[j][i+rb] = 0;
                                colexp_d = 1;
                            } else if(mapa[j][i+rb] == 1 && i+rb <= 16 && colexp_d == 0){
                                colexp_d = 1;
                            } else if(mapa[j][i+rb] == 0 && i+rb <= 16 && colexp_d == 0){
                                mapa[j][i+rb] = 24;
                                if(rb == raiobomb)
                                    mapa[j][i+rb] = 28;
                            }
                        }
                    }
                }
            }
            rodador_tbomb = 0;
        }


        sprintf(cron_bomb, "%d", SDL_GetTicks()-tempo_bomb);
        mens_contbomb = TTF_RenderText_Solid( font, cron_bomb, textColor );
        apply_surface( 200, 20, mens_contbomb, screen );



        if(rodador_animexp == 1){  
        Mix_VolumeChunk(explosao,10);
        Mix_PlayChannel(-1,explosao,0);  
            for(i=0;i<17;i++){
                for(j=0;j<11;j++){
                    if(SDL_GetTicks()-tempo_parexp < 200){

                        if(mapa[j][i]==20){
                            exp_cent.x = 53 + (i*54);
                            exp_cent.y = 119 + (j*54);
                            exp_cent_pointer = &exp_sprite[0]; 
                            SDL_BlitSurface(imgexp,exp_cent_pointer,screen,&exp_cent);
                        } else if(mapa[j][i]==21){
                            exp_cim.x = 53 + (i*54);
                            exp_cim.y = 119 + (j*54);
                            exp_cim_pointer = &exp_sprite[7]; 
                            SDL_BlitSurface(imgexp,exp_cim_pointer,screen,&exp_cim);
                        } else if(mapa[j][i]==22){
                            exp_esq.x = 53 + (i*54);
                            exp_esq.y = 119 + (j*54);
                            exp_esq_pointer = &exp_sprite[5]; 
                            SDL_BlitSurface(imgexp,exp_esq_pointer,screen,&exp_esq);
                        } else if(mapa[j][i]==23){
                            exp_bai.x = 53 + (i*54);
                            exp_bai.y = 119 + (j*54);
                            exp_bai_pointer = &exp_sprite[3]; 
                            SDL_BlitSurface(imgexp,exp_bai_pointer,screen,&exp_bai);
                        } else if(mapa[j][i]==24){
                            exp_dir.x = 53 + (i*54);
                            exp_dir.y = 119 + (j*54);
                            exp_dir_pointer = &exp_sprite[1]; 
                            SDL_BlitSurface(imgexp,exp_dir_pointer,screen,&exp_dir);
                        } else if(mapa[j][i]==25){
                            exp_cimfim.x = 53 + (i*54);
                            exp_cimfim.y = 119 + (j*54);
                            exp_cimfim_pointer = &exp_sprite[8]; 
                            SDL_BlitSurface(imgexp,exp_cimfim_pointer,screen,&exp_cimfim);
                        } else if(mapa[j][i]==26){
                            exp_esqfim.x = 53 + (i*54);
                            exp_esqfim.y = 119 + (j*54);
                            exp_esqfim_pointer = &exp_sprite[6]; 
                            SDL_BlitSurface(imgexp,exp_esqfim_pointer,screen,&exp_esqfim);
                        } else if(mapa[j][i]==27){
                            exp_baifim.x = 53 + (i*54);
                            exp_baifim.y = 119 + (j*54);
                            exp_baifim_pointer = &exp_sprite[4]; 
                            SDL_BlitSurface(imgexp,exp_baifim_pointer,screen,&exp_baifim);
                        } else if(mapa[j][i]==28){
                            exp_dirfim.x = 53 + (i*54);
                            exp_dirfim.y = 119 + (j*54);
                            exp_dirfim_pointer = &exp_sprite[2]; 
                            SDL_BlitSurface(imgexp,exp_dirfim_pointer,screen,&exp_dirfim);
                        }
                        
                    } else if(SDL_GetTicks()-tempo_parexp >= 200 && SDL_GetTicks()-tempo_parexp < 400){
                        if(mapa[j][i]==20){
                            exp_cent.x = 53 + (i*54);
                            exp_cent.y = 119 + (j*54);
                            exp_cent_pointer = &exp_sprite[9]; 
                            SDL_BlitSurface(imgexp,exp_cent_pointer,screen,&exp_cent);
                        } else if(mapa[j][i]==21){
                            exp_cim.x = 53 + (i*54);
                            exp_cim.y = 119 + (j*54);
                            exp_cim_pointer = &exp_sprite[16]; 
                            SDL_BlitSurface(imgexp,exp_cim_pointer,screen,&exp_cim);
                        } else if(mapa[j][i]==22){
                            exp_esq.x = 53 + (i*54);
                            exp_esq.y = 119 + (j*54);
                            exp_esq_pointer = &exp_sprite[14]; 
                            SDL_BlitSurface(imgexp,exp_esq_pointer,screen,&exp_esq);
                        } else if(mapa[j][i]==23){
                            exp_bai.x = 53 + (i*54);
                            exp_bai.y = 119 + (j*54);
                            exp_bai_pointer = &exp_sprite[12]; 
                            SDL_BlitSurface(imgexp,exp_bai_pointer,screen,&exp_bai);
                        } else if(mapa[j][i]==24){
                            exp_dir.x = 53 + (i*54);
                            exp_dir.y = 119 + (j*54);
                            exp_dir_pointer = &exp_sprite[10]; 
                            SDL_BlitSurface(imgexp,exp_dir_pointer,screen,&exp_dir);
                        } else if(mapa[j][i]==25){
                            exp_cimfim.x = 53 + (i*54);
                            exp_cimfim.y = 119 + (j*54);
                            exp_cimfim_pointer = &exp_sprite[17]; 
                            SDL_BlitSurface(imgexp,exp_cimfim_pointer,screen,&exp_cimfim);
                        } else if(mapa[j][i]==26){
                            exp_esqfim.x = 53 + (i*54);
                            exp_esqfim.y = 119 + (j*54);
                            exp_esqfim_pointer = &exp_sprite[15]; 
                            SDL_BlitSurface(imgexp,exp_esqfim_pointer,screen,&exp_esqfim);
                        } else if(mapa[j][i]==27){
                            exp_baifim.x = 53 + (i*54);
                            exp_baifim.y = 119 + (j*54);
                            exp_baifim_pointer = &exp_sprite[13]; 
                            SDL_BlitSurface(imgexp,exp_baifim_pointer,screen,&exp_baifim);
                        } else if(mapa[j][i]==28){
                            exp_dirfim.x = 53 + (i*54);
                            exp_dirfim.y = 119 + (j*54);
                            exp_dirfim_pointer = &exp_sprite[11]; 
                            SDL_BlitSurface(imgexp,exp_dirfim_pointer,screen,&exp_dirfim);
                        }
                    } else if(SDL_GetTicks()-tempo_parexp >= 400 && SDL_GetTicks()-tempo_parexp < 600){
                        if(mapa[j][i]==20){
                            exp_cent.x = 53 + (i*54);
                            exp_cent.y = 119 + (j*54);
                            exp_cent_pointer = &exp_sprite[9]; 
                            SDL_BlitSurface(imgexp,exp_cent_pointer,screen,&exp_cent);
                        } else if(mapa[j][i]==21){
                            exp_cim.x = 53 + (i*54);
                            exp_cim.y = 119 + (j*54);
                            exp_cim_pointer = &exp_sprite[16]; 
                            SDL_BlitSurface(imgexp,exp_cim_pointer,screen,&exp_cim);
                        } else if(mapa[j][i]==22){
                            exp_esq.x = 53 + (i*54);
                            exp_esq.y = 119 + (j*54);
                            exp_esq_pointer = &exp_sprite[14]; 
                            SDL_BlitSurface(imgexp,exp_esq_pointer,screen,&exp_esq);
                        } else if(mapa[j][i]==23){
                            exp_bai.x = 53 + (i*54);
                            exp_bai.y = 119 + (j*54);
                            exp_bai_pointer = &exp_sprite[12]; 
                            SDL_BlitSurface(imgexp,exp_bai_pointer,screen,&exp_bai);
                        } else if(mapa[j][i]==24){
                            exp_dir.x = 53 + (i*54);
                            exp_dir.y = 119 + (j*54);
                            exp_dir_pointer = &exp_sprite[10]; 
                            SDL_BlitSurface(imgexp,exp_dir_pointer,screen,&exp_dir);
                        } else if(mapa[j][i]==25){
                            exp_cimfim.x = 53 + (i*54);
                            exp_cimfim.y = 119 + (j*54);
                            exp_cimfim_pointer = &exp_sprite[17]; 
                            SDL_BlitSurface(imgexp,exp_cimfim_pointer,screen,&exp_cimfim);
                        } else if(mapa[j][i]==26){
                            exp_esqfim.x = 53 + (i*54);
                            exp_esqfim.y = 119 + (j*54);
                            exp_esqfim_pointer = &exp_sprite[15]; 
                            SDL_BlitSurface(imgexp,exp_esqfim_pointer,screen,&exp_esqfim);
                        } else if(mapa[j][i]==27){
                            exp_baifim.x = 53 + (i*54);
                            exp_baifim.y = 119 + (j*54);
                            exp_baifim_pointer = &exp_sprite[13]; 
                            SDL_BlitSurface(imgexp,exp_baifim_pointer,screen,&exp_baifim);
                        } else if(mapa[j][i]==28){
                            exp_dirfim.x = 53 + (i*54);
                            exp_dirfim.y = 119 + (j*54);
                            exp_dirfim_pointer = &exp_sprite[11]; 
                            SDL_BlitSurface(imgexp,exp_dirfim_pointer,screen,&exp_dirfim);
                        }
                    } else if(SDL_GetTicks()-tempo_parexp >= 600 && SDL_GetTicks()-tempo_parexp < 800){
                        if(mapa[j][i]==20){
                            exp_cent.x = 53 + (i*54);
                            exp_cent.y = 119 + (j*54);
                            exp_cent_pointer = &exp_sprite[9]; 
                            SDL_BlitSurface(imgexp,exp_cent_pointer,screen,&exp_cent);
                        } else if(mapa[j][i]==21){
                            exp_cim.x = 53 + (i*54);
                            exp_cim.y = 119 + (j*54);
                            exp_cim_pointer = &exp_sprite[16]; 
                            SDL_BlitSurface(imgexp,exp_cim_pointer,screen,&exp_cim);
                        } else if(mapa[j][i]==22){
                            exp_esq.x = 53 + (i*54);
                            exp_esq.y = 119 + (j*54);
                            exp_esq_pointer = &exp_sprite[14]; 
                            SDL_BlitSurface(imgexp,exp_esq_pointer,screen,&exp_esq);
                        } else if(mapa[j][i]==23){
                            exp_bai.x = 53 + (i*54);
                            exp_bai.y = 119 + (j*54);
                            exp_bai_pointer = &exp_sprite[12]; 
                            SDL_BlitSurface(imgexp,exp_bai_pointer,screen,&exp_bai);
                        } else if(mapa[j][i]==24){
                            exp_dir.x = 53 + (i*54);
                            exp_dir.y = 119 + (j*54);
                            exp_dir_pointer = &exp_sprite[10]; 
                            SDL_BlitSurface(imgexp,exp_dir_pointer,screen,&exp_dir);
                        } else if(mapa[j][i]==25){
                            exp_cimfim.x = 53 + (i*54);
                            exp_cimfim.y = 119 + (j*54);
                            exp_cimfim_pointer = &exp_sprite[17]; 
                            SDL_BlitSurface(imgexp,exp_cimfim_pointer,screen,&exp_cimfim);
                        } else if(mapa[j][i]==26){
                            exp_esqfim.x = 53 + (i*54);
                            exp_esqfim.y = 119 + (j*54);
                            exp_esqfim_pointer = &exp_sprite[15]; 
                            SDL_BlitSurface(imgexp,exp_esqfim_pointer,screen,&exp_esqfim);
                        } else if(mapa[j][i]==27){
                            exp_baifim.x = 53 + (i*54);
                            exp_baifim.y = 119 + (j*54);
                            exp_baifim_pointer = &exp_sprite[13]; 
                            SDL_BlitSurface(imgexp,exp_baifim_pointer,screen,&exp_baifim);
                        } else if(mapa[j][i]==28){
                            exp_dirfim.x = 53 + (i*54);
                            exp_dirfim.y = 119 + (j*54);
                            exp_dirfim_pointer = &exp_sprite[11]; 
                            SDL_BlitSurface(imgexp,exp_dirfim_pointer,screen,&exp_dirfim);
                        }
                    } else if(SDL_GetTicks()-tempo_parexp >= 800){
                        if(mapa[j][i]==20){
                            exp_cent.x = 53 + (i*54);
                            exp_cent.y = 119 + (j*54);
                            exp_cent_pointer = &exp_sprite[0]; 
                            SDL_BlitSurface(imgexp,exp_cent_pointer,screen,&exp_cent);
                        } else if(mapa[j][i]==21){
                            exp_cim.x = 53 + (i*54);
                            exp_cim.y = 119 + (j*54);
                            exp_cim_pointer = &exp_sprite[7]; 
                            SDL_BlitSurface(imgexp,exp_cim_pointer,screen,&exp_cim);
                        } else if(mapa[j][i]==22){
                            exp_esq.x = 53 + (i*54);
                            exp_esq.y = 119 + (j*54);
                            exp_esq_pointer = &exp_sprite[5]; 
                            SDL_BlitSurface(imgexp,exp_esq_pointer,screen,&exp_esq);
                        } else if(mapa[j][i]==23){
                            exp_bai.x = 53 + (i*54);
                            exp_bai.y = 119 + (j*54);
                            exp_bai_pointer = &exp_sprite[3]; 
                            SDL_BlitSurface(imgexp,exp_bai_pointer,screen,&exp_bai);
                        } else if(mapa[j][i]==24){
                            exp_dir.x = 53 + (i*54);
                            exp_dir.y = 119 + (j*54);
                            exp_dir_pointer = &exp_sprite[1]; 
                            SDL_BlitSurface(imgexp,exp_dir_pointer,screen,&exp_dir);
                        } else if(mapa[j][i]==25){
                            exp_cimfim.x = 53 + (i*54);
                            exp_cimfim.y = 119 + (j*54);
                            exp_cimfim_pointer = &exp_sprite[8]; 
                            SDL_BlitSurface(imgexp,exp_cimfim_pointer,screen,&exp_cimfim);
                        } else if(mapa[j][i]==26){
                            exp_esqfim.x = 53 + (i*54);
                            exp_esqfim.y = 119 + (j*54);
                            exp_esqfim_pointer = &exp_sprite[6]; 
                            SDL_BlitSurface(imgexp,exp_esqfim_pointer,screen,&exp_esqfim);
                        } else if(mapa[j][i]==27){
                            exp_baifim.x = 53 + (i*54);
                            exp_baifim.y = 119 + (j*54);
                            exp_baifim_pointer = &exp_sprite[4]; 
                            SDL_BlitSurface(imgexp,exp_baifim_pointer,screen,&exp_baifim);
                        } else if(mapa[j][i]==28){
                            exp_dirfim.x = 53 + (i*54);
                            exp_dirfim.y = 119 + (j*54);
                            exp_dirfim_pointer = &exp_sprite[2]; 
                            SDL_BlitSurface(imgexp,exp_dirfim_pointer,screen,&exp_dirfim);
                        }
                    }
                }
            }
            rodador_parexp = 1;
        }
        if(rodador_parexp == 0){
            tempo_parexp = SDL_GetTicks();
        }
        if(SDL_GetTicks()-tempo_parexp > 1000){
            rodador_parexp = 0;
            rodador_animexp = 0;
            for(i=0;i<17;i++){
                for(j=0;j<11;j++){
                    if(mapa[j][i] == 20 || mapa[j][i] == 21 || mapa[j][i] == 22 || mapa[j][i] == 23 || mapa[j][i] == 24 || mapa[j][i] == 25 || mapa[j][i] == 26 || mapa[j][i] == 27 || mapa[j][i] == 28){
                        mapa[j][i] = 0;
                    }
                }
            }
        }

        //DESENHO TODOS OS ELEMENTOS DO MAPA
        // SE MAPA[Y(LINHA)][X(COLUNA)].
        for(i=0;i<17;i++){

            for(j=0;j<11;j++){

                if(mapa[j][i]==1){
                    apply_surface((53+i*54),(119+j*54),blocoind,screen);
                }
                else if(mapa[j][i]==3)
                {
                    apply_surface((53+i*54),(119+j*54),blocodes,screen);
                }
               // else if(mapa[j][i]==2)
               // {
               //     apply_surface((68+i*64),(164+j*64),sprite_dn_bai3_game_DN,screen);
               // }
                else if(mapa[j][i]==5)
                {
                    bomb.x = 53 + (i*54);
                    bomb.y = 119 + (j*54);

                    if(SDL_GetTicks() - tempo_spritebomb > 300){
                        if(bomb_pointer == &bomb_sprite[0]){
                            bomb_pointer = &bomb_sprite[1];
                        } else{
                            bomb_pointer = &bomb_sprite[0];                            
                        }
                        tempo_spritebomb = SDL_GetTicks();
                    }
                    SDL_BlitSurface(imgbomb,bomb_pointer,screen,&bomb);
                }
            }
        }
        

        // Marcador da posição na matriz
        //apply_surface((53+xAtual*54),(119+yAtual*54),posi_matriz,screen);
        
        SDL_BlitSurface(player,dn_pointer,screen,&personagem);
        SDL_Flip(screen);
        apply_surface(0,0,fundo,screen);

        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = 1;
                break;


                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // SE A TECLA PRESSIONADA FOR ESC

                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        done = 1;
                    break;
                    }

                    if (event.key.keysym.sym == SDLK_UP){
                        inc_my = -1;
                        ult_sent = 0;
                        rodador = 1;
                        conf_kup += 1;


                        break;
                    }

                    if (event.key.keysym.sym == SDLK_DOWN){ // keystates[ SDLK_DOWN ]
                        inc_my = 1;
                        ult_sent = 8;
                        rodador = 1;
                        conf_kup += 1;

                        break;
                    }

                    if (event.key.keysym.sym == SDLK_RIGHT){
                        inc_mx = 1;
                        ult_sent = 4;
                        rodador = 1;
                        conf_kup += 1;
                            
                        break;
                    }

                    if (event.key.keysym.sym == SDLK_LEFT){
                        inc_mx = -1;
                        ult_sent = 12;
                        rodador = 1;
                        conf_kup += 1;
                        
                        break;
                    }

                    if (event.key.keysym.sym == SDLK_SPACE){
                        rodador_tbomb = 1;
                        conf_bomb = 0;
                        for(i=0;i<11;i++){
                            for(j=0;j<17;j++){
                                if(mapa[i][j] == 5){
                                    conf_bomb += 1;
                                }
                            }
                        }
                        if(conf_bomb < 1){
                            mapa[yAtual][xAtual] = 5;
                        }

                        colexp_a = 0;
                        colexp_b = 0;
                        colexp_c = 0;
                        colexp_d = 0;

                        conf_kup += 1;
                        break;
                    }
                }
            case SDL_KEYUP:
                {
                    /*
                    */
                    if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_SPACE) {
                        if(conf_kup == 1){
                            inc_my = 0;
                            inc_mx = 0;
                        } else {
                            if(ult_sent == 4 || ult_sent == 12){
                                inc_my = 0;
                            }
                            if(ult_sent == 0 || ult_sent == 8){
                                inc_mx = 0;
                            }
                        }
                        conf_kup--;
                    }

                            //inc_my = 0;
                            //inc_mx = 0;
                }


            } // end switch
        } // end of message processing

        /*
        movimento = rand()%20;

        mapa[yInimigo][xInimigo] = 0;
        switch(movimento){
            case 0:
            if(mapa[yInimigo][xInimigo+1]==1){
                break;
            }
            xInimigo+=1;
            break;

            case 1:
            if(mapa[yInimigo][xInimigo-1]==1){
                break;
            }
            xInimigo-=1;
            break;

            case 2:
            if(mapa[yInimigo+1][xInimigo]==1){
                break;
            }
            yInimigo+=1;
            break;

            case 3:
            if(mapa[yInimigo-1][xInimigo+1]==1){
                break;
            }
            yInimigo-=1;
            break;
        }

        mapa[yInimigo][xInimigo] = 2;
        */



        //LOCAL ATUAL DO PERSONAGEM = 2.
         //mapa[yAtual][xAtual] = 2;
    } // end main loop
}

    // free loaded bitmap
    /*
    SDL_FreeSurface( posi_matriz );
    SDL_FreeSurface( blocoind );
    SDL_FreeSurface( player );
    SDL_FreeSurface( blocodes );
    SDL_FreeSurface( imgbomb );
    SDL_FreeSurface( imgexp );
    SDL_FreeSurface( fundo );
    */
    // all is well ;)
    printf("Fechamento do Jogo\n");
    return 0;
}