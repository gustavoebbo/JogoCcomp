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

    SDL_Rect caiexp;
    SDL_Rect caiexp_sprite[5];
    SDL_Rect *caiexp_pointer;


    SDL_Rect inimigoa;
    SDL_Rect inimigoa_sprite[16];
    SDL_Rect *inia_pointer;

    Uint8 *keystates = SDL_GetKeyState( NULL );
    srand(time(NULL));

    int i,j;
    int tempo_passo = 0, ult_sent = 8, cmpr_sent = 8, rodador_movdn = 1, conf_bomb = 0, frac_passoy = 0, frac_passox = 0, tempo_passo_mov = 0, tempo_bomb, conf_kup = 0, rb = 1, raiobomb = 1, rodador_tbomb = 0, tempo_spritebomb = SDL_GetTicks(), colexp_a = 0, colexp_b = 0, colexp_c = 0, colexp_d = 0, tempo_rodexp = 0, rodador_animexp = 0, tempo_parexp = 0, rodador_parexp = 0, morreu_bomba = 1, rodador_temporenasc = 0, tempo_renasc = -1500, roda_blitaplayer = 1, tempo_passoinia = SDL_GetTicks(), escolhe_movinia = 0, decidido_movinia = 0, ult_sentinia = 0, rodador_animinia = 0, frac_passoinia = 1, tempo_passo_movinia = SDL_GetTicks();
    int  movimenta_x[2], movimenta_y[2], cord_animexp[2];
    char cron_bomb[50];
    char string_pontuacao[50];
    movimenta_x[0] = 1;
    movimenta_y[0] = 1;

    //O BLOCO QUE SE MOVE COMEÇA
    int yAtual = 0;
    int xAtual = 0;
    int inc_mx  = 0;
    int inc_my  = 0; 

    int xInimigoa = 16;
    int yInimigoa = 0;
    int incinia_mx  = 0;
    int incinia_my  = 0;

    int xInimigob = 16;
    int yInimigob = 10;
    int incinib_mx  = 0;
    int incinib_my  = 0; 

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
    SDL_Surface* screen = SDL_SetVideoMode(1024, 768, 16, SDL_HWSURFACE|SDL_DOUBLEBUF); //|SDL_FULLSCREEN

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

    SDL_Surface *text_contbomb = NULL;
    SDL_Surface *text_pontuacao = NULL;
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

    SDL_Surface* nulo;
    nulo = IMG_Load("nulo_game_DN.png");
    if (!nulo)
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

    SDL_Surface* imgcaiexp;
    imgcaiexp = IMG_Load("sprite_blocodes_game_DN.png");
    if (!imgcaiexp)
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

    SDL_Surface* imgpkplut;
    imgpkplut = IMG_Load("pkplut_game_DN.png");
    if (!imgpkplut)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* imgpkvida;
    imgpkvida = IMG_Load("pkvida_game_DN.png");
    if (!imgpkvida)
    {
        printf("Nem deu para carregar esse png: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* imgpkclub;
    imgpkclub = IMG_Load("pkclub_game_DN.png");
    if (!imgpkclub)
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

    theme = Mix_LoadMUS( "theme.wav" );

    if(theme == NULL)
        printf("Erro ao carregar a música tema\n");

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

     /* ----- Sprites caixa Explodindo ----- */
     caiexp_sprite[ 0 ].x = 0;
     caiexp_sprite[ 0 ].y = 0;
     caiexp_sprite[ 0 ].w = 54;
     caiexp_sprite[ 0 ].h = 54;

     caiexp_sprite[ 1 ].x = 54;
     caiexp_sprite[ 1 ].y = 0;
     caiexp_sprite[ 1 ].w = 54;
     caiexp_sprite[ 1 ].h = 54;

     caiexp_sprite[ 2 ].x = 108;
     caiexp_sprite[ 2 ].y = 0;
     caiexp_sprite[ 2 ].w = 54;
     caiexp_sprite[ 2 ].h = 54;

     caiexp_sprite[ 3 ].x = 162;
     caiexp_sprite[ 3 ].y = 0;
     caiexp_sprite[ 3 ].w = 54;
     caiexp_sprite[ 3 ].h = 54;

     caiexp_sprite[ 4 ].x = 216;
     caiexp_sprite[ 4 ].y = 0;
     caiexp_sprite[ 4 ].w = 54;
     caiexp_sprite[ 4 ].h = 54;

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

     /* ----- Fim sprites Duke Nukem ----- */


    personagem.x = 53;
    personagem.y = 119;


    inimigoa.x = 53 + (xInimigoa*54);
    inimigoa.y = 119 + (yInimigoa*54);


    exp_cent_pointer = &exp_sprite[18]; 
    exp_cim_pointer = &exp_sprite[25]; 
    exp_esq_pointer = &exp_sprite[23];
    exp_bai_pointer = &exp_sprite[21];  
    exp_dir_pointer = &exp_sprite[19]; 
    exp_cimfim_pointer = &exp_sprite[26]; 
    exp_esqfim_pointer = &exp_sprite[24];
    exp_baifim_pointer = &exp_sprite[22];  
    exp_dirfim_pointer = &exp_sprite[20]; 



    //11 LINHAS 17 COLUNAS s
  int mapa[11][17] = {
{0,3,0,0,1,0,1,0,0,1,0,0,0,1,0,0,8},
{0,13,0,3,0,11,0,1,3,0,0,0,1,0,3,3,3},
{3,0,0,1,0,3,0,0,3,0,0,1,0,0,3,3,7},
{0,14,0,3,0,3,0,3,0,0,0,0,0,11,3,3,3},
{0,0,0,1,1,0,0,3,0,3,0,0,0,0,1,1,3},
{1,3,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
{0,3,0,1,3,0,0,1,3,0,0,3,1,1,0,0,0},
{3,17,1,1,3,3,0,14,0,1,1,3,1,1,0,3,3},
{0,3,1,1,3,0,0,0,0,0,3,3,1,1,0,3,3},
{0,3,1,1,1,1,3,3,17,1,1,1,1,1,0,0,1},
{3,3,1,3,3,3,0,0,0,0,0,0,0,0,3,3,1}
};

  /*
  int mapa[11][17] = {
{0,0,3,0,3,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,3,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{17,3,0,0,3,11,0,0,0,0,0,0,0,0,0,0,0},
{0,1,14,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,14,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
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


    int jogorodando = 1;
    int emorreu = 0;
    int fimtempo = 0;
    int vidas = 3;
    int pontuacao = 0;

    int donemenu = 0;
// novo jogo, continuar, instruções, recordes, sair

int opcoes = 1;
int continuar = 1, infos = 1, recordes =1;


while(donemenu == 0)
{
    if( Mix_PlayingMusic() == 0 )
                    {
                        Mix_PlayMusic( theme, -1 );
                    }
    
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
                        infos = 1;
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
                       if(opcoes == 1){
                            jogorodando = 0;
                            Mix_PauseMusic();}
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
    if(infos == 0);
    {
        apply_surface(0,0,fundo,screen);
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
    while (jogorodando == 0 && emorreu == 0 && fimtempo == 0)
    {

    if(vidas <= 0){
        emorreu = 1;
        Mix_ResumeMusic();
    }

    /* ------- Movimentacao do Duke Nukem ------- */

    if(!(inc_my != 0 && inc_mx != 0)){
        if(rodador_movdn == 1){

            if(mapa[yAtual+inc_my][xAtual] != 1 && mapa[yAtual+inc_my][xAtual] != 4 && mapa[yAtual+inc_my][xAtual] != 11 && mapa[yAtual+inc_my][xAtual] != 12 && mapa[yAtual+inc_my][xAtual] != 14 && mapa[yAtual+inc_my][xAtual] != 15 && mapa[yAtual+inc_my][xAtual] != 17 && mapa[yAtual+inc_my][xAtual] != 18 && mapa[yAtual+inc_my][xAtual] != 3 && mapa[yAtual+inc_my][xAtual] != 5 && yAtual+inc_my >= 0 && yAtual+inc_my <= 10 && movimenta_y[0] != 1){
                if(mapa[yAtual+inc_my][xAtual] == 13){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    raiobomb += 1;
                } else if(mapa[yAtual+inc_my][xAtual] == 16){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    vidas += 1;
                } else if(mapa[yAtual+inc_my][xAtual] == 19){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    pontuacao += 200;
                }
                yAtual += inc_my;
                if(inc_my != 0){
                    movimenta_y[0] = 1;
                    movimenta_y[1] = inc_my;
                }
            }
            if(mapa[yAtual][xAtual+inc_mx] != 1 && mapa[yAtual][xAtual+inc_mx] != 4 && mapa[yAtual][xAtual+inc_mx] != 11 && mapa[yAtual][xAtual+inc_mx] != 12 && mapa[yAtual][xAtual+inc_mx] != 14 && mapa[yAtual][xAtual+inc_mx] != 15 && mapa[yAtual][xAtual+inc_mx] != 17 && mapa[yAtual][xAtual+inc_mx] != 18 && mapa[yAtual][xAtual+inc_mx] != 3 && mapa[yAtual][xAtual+inc_mx] != 5 && xAtual+inc_mx >= 0 && xAtual+inc_mx <= 16 && movimenta_x[0] != 1){
                if(mapa[yAtual][xAtual+inc_mx] == 13){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    raiobomb += 1;
                } else if(mapa[yAtual][xAtual+inc_mx] == 16){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    vidas += 1;
                } else if(mapa[yAtual][xAtual+inc_mx] == 19){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    pontuacao += 200;
                }
                xAtual += inc_mx;
                if(inc_mx != 0){
                    movimenta_x[0] = 1;
                    movimenta_x[1] = inc_mx;
                }
            }

            rodador_movdn = 0;
            tempo_passo = SDL_GetTicks();

        } else if(SDL_GetTicks() - tempo_passo > 500){

            if(mapa[yAtual+inc_my][xAtual] != 1 && mapa[yAtual+inc_my][xAtual] != 4 && mapa[yAtual+inc_my][xAtual] != 11 && mapa[yAtual+inc_my][xAtual] != 12 && mapa[yAtual+inc_my][xAtual] != 14 && mapa[yAtual+inc_my][xAtual] != 15 && mapa[yAtual+inc_my][xAtual] != 17 && mapa[yAtual+inc_my][xAtual] != 18 && mapa[yAtual+inc_my][xAtual] != 3 && mapa[yAtual+inc_my][xAtual] != 5 && yAtual+inc_my >= 0 && yAtual+inc_my <= 10){
                if(mapa[yAtual+inc_my][xAtual] == 13){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    raiobomb += 1;
                } else if(mapa[yAtual+inc_my][xAtual] == 16){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    vidas += 1;
                } else if(mapa[yAtual+inc_my][xAtual] == 19){ 
                    mapa[yAtual+inc_my][xAtual] = 0;
                    pontuacao += 200;
                }
                yAtual += inc_my;
                if(inc_my != 0){
                    movimenta_y[0] = 1;
                    movimenta_y[1] = inc_my;
                }
            }
            if(mapa[yAtual][xAtual+inc_mx] != 1 && mapa[yAtual][xAtual+inc_mx] != 4 && mapa[yAtual][xAtual+inc_mx] != 11 && mapa[yAtual][xAtual+inc_mx] != 12 && mapa[yAtual][xAtual+inc_mx] != 14 && mapa[yAtual][xAtual+inc_mx] != 15 && mapa[yAtual][xAtual+inc_mx] != 17 && mapa[yAtual][xAtual+inc_mx] != 18 && mapa[yAtual][xAtual+inc_mx] != 3 && mapa[yAtual][xAtual+inc_mx] != 5 && xAtual+inc_mx >= 0 && xAtual+inc_mx <= 16){
                if(mapa[yAtual][xAtual+inc_mx] == 13){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    raiobomb += 1;
                } else if(mapa[yAtual][xAtual+inc_mx] == 16){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    vidas += 1;
                } else if(mapa[yAtual][xAtual+inc_mx] == 19){ 
                    mapa[yAtual][xAtual+inc_mx] = 0;
                    pontuacao += 200;
                }
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
    /* ------- Fim movimentacao do Duke Nukem ------- */




    /* ------- Movimentacao do inimigo A ------- */

    /*if(!(incinia_my != 0 && incinia_mx != 0)){

        

            if(mapa[yInimigoa+incinia_my][xInimigoa] != 1 && mapa[yInimigoa+incinia_my][xInimigoa] != 4 && mapa[yInimigoa+incinia_my][xInimigoa] != 11 && mapa[yInimigoa+incinia_my][xInimigoa] != 12 && mapa[yInimigoa+incinia_my][xInimigoa] != 14 && mapa[yInimigoa+incinia_my][xInimigoa] != 15 && mapa[yInimigoa+incinia_my][xInimigoa] != 17 && mapa[yInimigoa+incinia_my][xInimigoa] != 18 && mapa[yInimigoa+incinia_my][xInimigoa] != 3 && mapa[yInimigoa+incinia_my][xInimigoa] != 5 && yInimigoa+incinia_my >= 0 && yInimigoa+incinia_my <= 10 && movimenta_y[0] != 1){
                if(mapa[yInimigoa+incinia_my][xInimigoa] == 13){ 
                    mapa[yInimigoa+incinia_my][xInimigoa] = 0;
                    raiobomb += 1;
                } else if(mapa[yInimigoa+incinia_my][xInimigoa] == 16){ 
                    mapa[yInimigoa+incinia_my][xInimigoa] = 0;
                    vidas += 1;
                } else if(mapa[yInimigoa+incinia_my][xInimigoa] == 19){ 
                    mapa[yInimigoa+incinia_my][xInimigoa] = 0;
                    pontuacao += 200;
                }
                yInimigoa += incinia_my;
                if(incinia_my != 0){
                    movimenta_y[0] = 1;
                    movimenta_y[1] = incinia_my;
                }
            }
            if(mapa[yInimigoa][xInimigoa+incinia_mx] != 1 && mapa[yInimigoa][xInimigoa+incinia_mx] != 4 && mapa[yInimigoa][xInimigoa+incinia_mx] != 11 && mapa[yInimigoa][xInimigoa+incinia_mx] != 12 && mapa[yInimigoa][xInimigoa+incinia_mx] != 14 && mapa[yInimigoa][xInimigoa+incinia_mx] != 15 && mapa[yInimigoa][xInimigoa+incinia_mx] != 17 && mapa[yInimigoa][xInimigoa+incinia_mx] != 18 && mapa[yInimigoa][xInimigoa+incinia_mx] != 3 && mapa[yInimigoa][xInimigoa+incinia_mx] != 5 && xInimigoa+incinia_mx >= 0 && xInimigoa+incinia_mx <= 16 && movimenta_x[0] != 1){
                if(mapa[yInimigoa][xInimigoa+incinia_mx] == 13){ 
                    mapa[yInimigoa][xInimigoa+incinia_mx] = 0;
                    raiobomb += 1;
                } else if(mapa[yInimigoa][xInimigoa+incinia_mx] == 16){ 
                    mapa[yInimigoa][xInimigoa+incinia_mx] = 0;
                    vidas += 1;
                } else if(mapa[yInimigoa][xInimigoa+incinia_mx] == 19){ 
                    mapa[yInimigoa][xInimigoa+incinia_mx] = 0;
                    pontuacao += 200;
                }
                xInimigoa += incinia_mx;
                if(incinia_mx != 0){
                    movimenta_x[0] = 1;
                    movimenta_x[1] = incinia_mx;
                }
            }

            rodador_movdn = 0;
            tempo_passo = SDL_GetTicks(); */

            

        if(SDL_GetTicks() - tempo_passoinia > 1100){
            escolhe_movinia = rand()%10;
            decidido_movinia = 0;
            while(decidido_movinia != 1){
                if(escolhe_movinia == 0){
                    if(mapa[yInimigoa-1][xInimigoa] != 1 && mapa[yInimigoa-1][xInimigoa] != 4 && mapa[yInimigoa-1][xInimigoa] != 11 && mapa[yInimigoa-1][xInimigoa] != 12 && mapa[yInimigoa-1][xInimigoa] != 14 && mapa[yInimigoa-1][xInimigoa] != 15 && mapa[yInimigoa-1][xInimigoa] != 17 && mapa[yInimigoa-1][xInimigoa] != 18 && mapa[yInimigoa-1][xInimigoa] != 3 && mapa[yInimigoa-1][xInimigoa] != 5 && yInimigoa-1 >= 0){
                        decidido_movinia = 1;
                        yInimigoa = yInimigoa - 1;
                        ult_sentinia = 0;
                    } else{
                        while(escolhe_movinia == 0){
                            escolhe_movinia = rand()%4;                         
                        }
                        decidido_movinia = 0;
                    }
                } else if(escolhe_movinia == 1){
                    if(mapa[yInimigoa+1][xInimigoa] != 1 && mapa[yInimigoa+1][xInimigoa] != 4 && mapa[yInimigoa+1][xInimigoa] != 11 && mapa[yInimigoa+1][xInimigoa] != 12 && mapa[yInimigoa+1][xInimigoa] != 14 && mapa[yInimigoa+1][xInimigoa] != 15 && mapa[yInimigoa+1][xInimigoa] != 17 && mapa[yInimigoa+1][xInimigoa] != 18 && mapa[yInimigoa+1][xInimigoa] != 3 && mapa[yInimigoa+1][xInimigoa] != 5 && yInimigoa+1 <= 10){
                        decidido_movinia = 1;
                        yInimigoa = yInimigoa + 1;
                        ult_sentinia = 1;
                    } else{
                        while(escolhe_movinia == 1){
                            escolhe_movinia = rand()%4;                         
                        }
                        decidido_movinia = 0;
                    }
                } else if(escolhe_movinia == 2){
                    if(mapa[yInimigoa][xInimigoa-1] != 1 && mapa[yInimigoa][xInimigoa-1] != 4 && mapa[yInimigoa][xInimigoa-1] != 11 && mapa[yInimigoa][xInimigoa-1] != 12 && mapa[yInimigoa][xInimigoa-1] != 14 && mapa[yInimigoa][xInimigoa-1] != 15 && mapa[yInimigoa][xInimigoa-1] != 17 && mapa[yInimigoa][xInimigoa-1] != 18 && mapa[yInimigoa][xInimigoa-1] != 3 && mapa[yInimigoa][xInimigoa-1] != 5 && xInimigoa-1 >= 0){
                        decidido_movinia = 1;
                        xInimigoa = xInimigoa - 1;
                        ult_sentinia = 2;
                    } else{
                        while(escolhe_movinia == 2){
                            escolhe_movinia = rand()%4;                         
                        }
                        decidido_movinia = 0;
                    }
                } else if(escolhe_movinia == 3){
                    if(mapa[yInimigoa][xInimigoa+1] != 1 && mapa[yInimigoa][xInimigoa+1] != 4 && mapa[yInimigoa][xInimigoa+1] != 11 && mapa[yInimigoa][xInimigoa+1] != 12 && mapa[yInimigoa][xInimigoa+1] != 14 && mapa[yInimigoa][xInimigoa+1] != 15 && mapa[yInimigoa][xInimigoa+1] != 17 && mapa[yInimigoa][xInimigoa+1] != 18 && mapa[yInimigoa][xInimigoa+1] != 3 && mapa[yInimigoa][xInimigoa+1] != 5 && xInimigoa+1 <= 16){
                        decidido_movinia = 1;
                        xInimigoa = xInimigoa + 1;
                        ult_sentinia = 3;
                    } else{
                        while(escolhe_movinia == 3){
                            escolhe_movinia = rand()%4;                         
                        }
                        decidido_movinia = 0;
                    }
                } else{
                    if(ult_sentinia == 0 && mapa[yInimigoa-1][xInimigoa] != 1 && mapa[yInimigoa-1][xInimigoa] != 4 && mapa[yInimigoa-1][xInimigoa] != 11 && mapa[yInimigoa-1][xInimigoa] != 12 && mapa[yInimigoa-1][xInimigoa] != 14 && mapa[yInimigoa-1][xInimigoa] != 15 && mapa[yInimigoa-1][xInimigoa] != 17 && mapa[yInimigoa-1][xInimigoa] != 18 && mapa[yInimigoa-1][xInimigoa] != 3 && mapa[yInimigoa-1][xInimigoa] != 5 && yInimigoa-1 >= 0){
                        yInimigoa = yInimigoa - 1;
                        decidido_movinia = 1;
                    } else if(ult_sentinia == 1 && mapa[yInimigoa+1][xInimigoa] != 1 && mapa[yInimigoa+1][xInimigoa] != 4 && mapa[yInimigoa+1][xInimigoa] != 11 && mapa[yInimigoa+1][xInimigoa] != 12 && mapa[yInimigoa+1][xInimigoa] != 14 && mapa[yInimigoa+1][xInimigoa] != 15 && mapa[yInimigoa+1][xInimigoa] != 17 && mapa[yInimigoa+1][xInimigoa] != 18 && mapa[yInimigoa+1][xInimigoa] != 3 && mapa[yInimigoa+1][xInimigoa] != 5 && yInimigoa+1 <= 10){
                        yInimigoa = yInimigoa + 1;
                        decidido_movinia = 1;
                    } else if(ult_sentinia == 2 && mapa[yInimigoa][xInimigoa-1] != 1 && mapa[yInimigoa][xInimigoa-1] != 4 && mapa[yInimigoa][xInimigoa-1] != 11 && mapa[yInimigoa][xInimigoa-1] != 12 && mapa[yInimigoa][xInimigoa-1] != 14 && mapa[yInimigoa][xInimigoa-1] != 15 && mapa[yInimigoa][xInimigoa-1] != 17 && mapa[yInimigoa][xInimigoa-1] != 18 && mapa[yInimigoa][xInimigoa-1] != 3 && mapa[yInimigoa][xInimigoa-1] != 5 && xInimigoa-1 >= 0){
                        xInimigoa = xInimigoa - 1;
                        decidido_movinia = 1;
                    } else if(ult_sentinia == 3 && mapa[yInimigoa][xInimigoa+1] != 1 && mapa[yInimigoa][xInimigoa+1] != 4 && mapa[yInimigoa][xInimigoa+1] != 11 && mapa[yInimigoa][xInimigoa+1] != 12 && mapa[yInimigoa][xInimigoa+1] != 14 && mapa[yInimigoa][xInimigoa+1] != 15 && mapa[yInimigoa][xInimigoa+1] != 17 && mapa[yInimigoa][xInimigoa+1] != 18 && mapa[yInimigoa][xInimigoa+1] != 3 && mapa[yInimigoa][xInimigoa+1] != 5 && xInimigoa+1 <= 16){
                        xInimigoa = xInimigoa + 1;
                        decidido_movinia = 1;
                    } else{
                        while(escolhe_movinia != 0 && escolhe_movinia != 1 && escolhe_movinia != 2 && escolhe_movinia != 3){
                            escolhe_movinia = rand()%4;
                        }
                        decidido_movinia = 0;
                    }
                }
            }


            tempo_passoinia = SDL_GetTicks();
            //.x = 53 + (xInimigoa*54);
            //inimigoa.y = 119 + (yInimigoa*54);
            //rodador_animinia = 1;
        }

        /*

            if(mapa[yInimigoa+incinia_my][xInimigoa] != 1 && mapa[yInimigoa+incinia_my][xInimigoa] != 4 && mapa[yInimigoa+incinia_my][xInimigoa] != 11 && mapa[yInimigoa+incinia_my][xInimigoa] != 12 && mapa[yInimigoa+incinia_my][xInimigoa] != 14 && mapa[yInimigoa+incinia_my][xInimigoa] != 15 && mapa[yInimigoa+incinia_my][xInimigoa] != 17 && mapa[yInimigoa+incinia_my][xInimigoa] != 18 && mapa[yInimigoa+incinia_my][xInimigoa] != 3 && mapa[yInimigoa+incinia_my][xInimigoa] != 5 && yInimigoa+incinia_my >= 0 && yInimigoa+incinia_my <= 10){
                if(mapa[yInimigoa+incinia_my][xInimigoa] == 13){ 
                    mapa[yInimigoa+incinia_my][xInimigoa] = 0;
                    raiobomb += 1;
                } else if(mapa[yInimigoa+incinia_my][xInimigoa] == 16){ 
                    mapa[yInimigoa+incinia_my][xInimigoa] = 0;
                    vidas += 1;
                } else if(mapa[yInimigoa+incinia_my][xInimigoa] == 19){ 
                    mapa[yInimigoa+incinia_my][xInimigoa] = 0;
                    pontuacao += 200;
                }
                yInimigoa += incinia_my;
                if(incinia_my != 0){
                    movimenta_y[0] = 1;
                    movimenta_y[1] = incinia_my;
                }
            }
            if(mapa[yInimigoa][xInimigoa+incinia_mx] != 1 && mapa[yInimigoa][xInimigoa+incinia_mx] != 4 && mapa[yInimigoa][xInimigoa+incinia_mx] != 11 && mapa[yInimigoa][xInimigoa+incinia_mx] != 12 && mapa[yInimigoa][xInimigoa+incinia_mx] != 14 && mapa[yInimigoa][xInimigoa+incinia_mx] != 15 && mapa[yInimigoa][xInimigoa+incinia_mx] != 17 && mapa[yInimigoa][xInimigoa+incinia_mx] != 18 && mapa[yInimigoa][xInimigoa+incinia_mx] != 3 && mapa[yInimigoa][xInimigoa+incinia_mx] != 5 && xInimigoa+incinia_mx >= 0 && xInimigoa+incinia_mx <= 16){
                if(mapa[yInimigoa][xInimigoa+incinia_mx] == 13){ 
                    mapa[yInimigoa][xInimigoa+incinia_mx] = 0;
                    raiobomb += 1;
                } else if(mapa[yInimigoa][xInimigoa+incinia_mx] == 16){ 
                    mapa[yInimigoa][xInimigoa+incinia_mx] = 0;
                    vidas += 1;
                } else if(mapa[yInimigoa][xInimigoa+incinia_mx] == 19){ 
                    mapa[yInimigoa][xInimigoa+incinia_mx] = 0;
                    pontuacao += 200;
                }
                xInimigoa += incinia_mx;
                if(incinia_mx != 0){
                    movimenta_x[0] = 1;
                    movimenta_x[1] = incinia_mx;
                }
            }
            tempo_passo = SDL_GetTicks();
        }
    }

                   

    */
    if(SDL_GetTicks() - tempo_passo_movinia > 275){
        pontuacao += 1;
        //if(rodador_animinia == 1){
            if(ult_sentinia == 0){
                if(frac_passoinia != 4){
                    inimigoa.y = 119 + ((yInimigoa+1)*54) - frac_passoinia*13;
                    inimigoa.x = inimigoa.x;
                    //dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                    frac_passoinia += 1;
                } else{
                    //dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                    frac_passoinia = 1;
                    inimigoa.y = 119 + ((yInimigoa)*54);
                    inimigoa.x = 53 + ((xInimigoa)*54);
                    inimigoa.x = inimigoa.x;
                    rodador_animinia = 0;
                }
            } else if(ult_sentinia == 1){
                if(frac_passoinia != 4){
                    inimigoa.y = 119 + ((yInimigoa-1)*54) + frac_passoinia*13;
                    inimigoa.x = inimigoa.x;
                    //dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                    frac_passoinia += 1;
                } else{
                    //dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                    frac_passoinia = 1;
                    inimigoa.y = 119 + ((yInimigoa)*54);
                    inimigoa.x = 53 + ((xInimigoa)*54);
                    inimigoa.x = inimigoa.x;
                    rodador_animinia = 0;
                }
            } else if(ult_sentinia == 2){
                if(frac_passoinia != 4){
                    inimigoa.x = 53 + ((xInimigoa+1)*54) - frac_passoinia*13;
                    inimigoa.y = inimigoa.y;
                    //dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                    frac_passoinia += 1;
                } else{
                    //dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                    frac_passoinia = 1;
                    inimigoa.x = 53 + ((yInimigoa)*54);
                    inimigoa.y = 119 + ((yInimigoa)*54);
                    rodador_animinia = 0;
                }
            } else if(ult_sentinia == 3){
                if(frac_passoinia != 4){
                    inimigoa.x = 53 + ((xInimigoa-1)*54) + frac_passoinia*13;
                    inimigoa.y = inimigoa.y;
                    //dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                    frac_passoinia += 1;
                } else{
                    //dn_pointer = &dn_sprite[ult_sent+frac_passoy-1];
                    frac_passoinia = 1;
                    inimigoa.x = 53 + ((xInimigoa)*54);
                    inimigoa.y = 119 + ((yInimigoa)*54);
                    rodador_animinia = 0;
                }
            }
        //}
        tempo_passo_movinia = SDL_GetTicks();
    }
    /* ------- Fim movimentacao do inimigo A ------- */




    /* ------- Perde vida com a bomba -------- */
    if(mapa[yAtual][xAtual] == 21 || mapa[yAtual][xAtual] == 22 || mapa[yAtual][xAtual] == 23 || mapa[yAtual][xAtual] == 24 || mapa[yAtual][xAtual] == 25 || mapa[yAtual][xAtual] == 26 || mapa[yAtual][xAtual] == 27 || mapa[yAtual][xAtual] == 28){ 
        if(morreu_bomba == 0){
            vidas -= 1;
            morreu_bomba = 1;
            rodador_temporenasc = 1;
            tempo_renasc = SDL_GetTicks();
            roda_blitaplayer = 0;
            yAtual = -100;
            xAtual = -100;
            personagem.x = -54;
            personagem.y = -54;
            SDL_BlitSurface(nulo,dn_pointer,screen,&personagem);
        }
    }
    if(rodador_temporenasc == 1 && SDL_GetTicks()-tempo_renasc > 1500){
        yAtual = 0;
        xAtual = 0;
        personagem.x = 53;
        personagem.y = 119;
        rodador_temporenasc = 0;
        roda_blitaplayer = 1;
        tempo_renasc = -1500;
    }
    /* ------ Fim perde vida pra bomba ------ */




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
                        morreu_bomba = 0;

                        for(rb=1;rb<=raiobomb;rb++){
                            if(mapa[j-rb][i] == 3 && j-rb >= 0 && colexp_a == 0){
                                pontuacao += 25;
                                mapa[j-rb][i] = 4;
                                colexp_a = 1;
                            } else if(mapa[j-rb][i] == 11 && j-rb >= 0 && colexp_a == 0){
                                pontuacao += 25;
                                mapa[j-rb][i] = 12;
                                colexp_a = 1;
                            } else if(mapa[j-rb][i] == 14 && j-rb >= 0 && colexp_a == 0){
                                pontuacao += 25;
                                mapa[j-rb][i] = 15;
                                colexp_a = 1;
                            }  else if(mapa[j-rb][i] == 17 && j-rb >= 0 && colexp_a == 0){
                                pontuacao += 25;
                                mapa[j-rb][i] = 18;
                                colexp_a = 1;
                            } else if(mapa[j-rb][i] == 1 && j-rb >= 0 && colexp_a == 0){
                                colexp_a = 1;
                            } else if(mapa[j-rb][i] == 0 && j-rb >= 0 && colexp_a == 0){
                                mapa[j-rb][i] = 21;
                                if(rb == raiobomb)
                                    mapa[j-rb][i] = 25;
                            }
                            if(mapa[j][i-rb] == 3 && i-rb >= 0 && colexp_b == 0){
                                pontuacao += 25;
                                mapa[j][i-rb] = 4;
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 11 && i-rb >= 0 && colexp_b == 0){
                                pontuacao += 25;
                                mapa[j][i-rb] = 12;
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 14 && i-rb >= 0 && colexp_b == 0){
                                pontuacao += 25;
                                mapa[j][i-rb] = 15;
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 17 && i-rb >= 0 && colexp_b == 0){
                                pontuacao += 25;
                                mapa[j][i-rb] = 18;
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 1 && i-rb >= 0 && colexp_b == 0){
                                colexp_b = 1;
                            } else if(mapa[j][i-rb] == 0 && i-rb >= 0 && colexp_b == 0){
                                mapa[j][i-rb] = 22;
                                if(rb == raiobomb)
                                    mapa[j][i-rb] = 26;
                            }
                            if(mapa[j+rb][i] == 3 && j+rb <= 10 && colexp_c == 0){
                                pontuacao += 25;
                                mapa[j+rb][i] = 4;
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 11 && j+rb <= 10 && colexp_c == 0){
                                pontuacao += 25;
                                mapa[j+rb][i] = 12;
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 14 && j+rb <= 10 && colexp_c == 0){
                                pontuacao += 25;
                                mapa[j+rb][i] = 15;
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 17 && j+rb <= 10 && colexp_c == 0){
                                pontuacao += 25;
                                mapa[j+rb][i] = 18;
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 1 && j+rb <= 10 && colexp_c == 0){
                                colexp_c = 1;
                            } else if(mapa[j+rb][i] == 0 && j+rb <= 10 && colexp_c == 0){
                                mapa[j+rb][i] = 23;
                                if(rb == raiobomb)
                                    mapa[j+rb][i] = 27;
                            }
                            if(mapa[j][i+rb] == 3 && i+rb <= 16 && colexp_d == 0){
                                pontuacao += 25;
                                mapa[j][i+rb] = 4;
                                colexp_d = 1;
                            } else if(mapa[j][i+rb] == 11 && i+rb <= 16 && colexp_d == 0){
                                pontuacao += 25;
                                mapa[j][i+rb] = 12;
                                colexp_d = 1;
                            } else if(mapa[j][i+rb] == 14 && i+rb <= 16 && colexp_d == 0){
                                pontuacao += 25;
                                mapa[j][i+rb] = 15;
                                colexp_d = 1;
                            } else if(mapa[j][i+rb] == 17 && i+rb <= 16 && colexp_d == 0){
                                pontuacao += 25;
                                mapa[j][i+rb] = 18;
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
        text_contbomb = TTF_RenderText_Solid( font, cron_bomb, textColor );
        apply_surface( 200, 20, text_contbomb, screen );

        sprintf(string_pontuacao, "%d", pontuacao);
        text_pontuacao = TTF_RenderText_Solid( font, string_pontuacao, textColor );
        apply_surface( 500, 20, text_pontuacao, screen );



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
                        } else if(mapa[j][i]==4){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[0]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==12){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[0]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==15){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[0]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==18){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[0]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
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
                        } else if(mapa[j][i]==4){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[1]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==12){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[1]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==15){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[1]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==18){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[1]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
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
                        } else if(mapa[j][i]==4){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[2]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==12){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[2]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==15){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[2]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==18){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[2]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
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
                        } else if(mapa[j][i]==4){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[3]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==12){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[3]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==15){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[3]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==18){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[3]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
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
                        } else if(mapa[j][i]==4){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[4]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==12){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[4]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==15){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[4]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
                        } else if(mapa[j][i]==18){
                            caiexp.x = 53 + (i*54);
                            caiexp.y = 119 + (j*54);
                            caiexp_pointer = &caiexp_sprite[4]; 
                            SDL_BlitSurface(imgcaiexp,caiexp_pointer,screen,&caiexp);
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
            morreu_bomba = 1;
            for(i=0;i<17;i++){
                for(j=0;j<11;j++){
                    if(mapa[j][i] == 20 || mapa[j][i] == 21 || mapa[j][i] == 22 || mapa[j][i] == 23 || mapa[j][i] == 24 || mapa[j][i] == 25 || mapa[j][i] == 26 || mapa[j][i] == 27 || mapa[j][i] == 28 || mapa[j][i] == 4){
                        mapa[j][i] = 0;
                    }
                    if(mapa[j][i] == 12){
                        mapa[j][i] = 13;
                    } else if(mapa[j][i] == 15){
                        mapa[j][i] = 16;
                    } else if(mapa[j][i] == 18){
                        mapa[j][i] = 19;
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
                else if(mapa[j][i]==3 || mapa[j][i]==11 || mapa[j][i]==14 || mapa[j][i]==17)
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
                else if(mapa[j][i]==13)
                {
                    apply_surface((53+i*54),(119+j*54),imgpkplut,screen);
                }
                else if(mapa[j][i]==16)
                {
                    apply_surface((53+i*54),(119+j*54),imgpkvida,screen);
                }
                else if(mapa[j][i]==19)
                {
                    apply_surface((53+i*54),(119+j*54),imgpkclub,screen);
                }
            }
        }
        

        // Marcador da posição na matriz
        //apply_surface((53+xAtual*54),(119+yAtual*54),posi_matriz,screen);

        if(roda_blitaplayer == 1){
            SDL_BlitSurface(player,dn_pointer,screen,&personagem);
        }

        //inimigoa.x = 53 + (xInimigoa*54);
        //inimigoa.y = 119 + (yInimigoa*54);
        SDL_BlitSurface(player,dn_pointer,screen,&inimigoa);

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
                jogorodando = 1;
                break;


                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // SE A TECLA PRESSIONADA FOR ESC

                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        jogorodando = 1;
                        Mix_ResumeMusic();
                    break;
                    }

                    if (event.key.keysym.sym == SDLK_UP){
                        inc_my = -1;
                        ult_sent = 0;
                        rodador_movdn = 1;
                        conf_kup += 1;

                        break;
                    }

                    if (event.key.keysym.sym == SDLK_DOWN){ // keystates[ SDLK_DOWN ]
                        inc_my = 1;
                        ult_sent = 8;
                        rodador_movdn = 1;
                        conf_kup += 1;

                        break;
                    }

                    if (event.key.keysym.sym == SDLK_RIGHT){
                        inc_mx = 1;
                        ult_sent = 4;
                        rodador_movdn = 1;
                        conf_kup += 1;
                            
                        break;
                    }

                    if (event.key.keysym.sym == SDLK_LEFT){
                        inc_mx = -1;
                        ult_sent = 12;
                        rodador_movdn = 1;
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

}// end menu loop;


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