/*
****************** INTEGRANTES ******************

ANDREW SANTOS MACHADO / MATRÍCULA: 202110132
PEDRO ENGER GLUSZCZUK / MATRÍCULA: 202210792
PEDRO HENRIQUE DIAS COELHO / MATRÍCULA: 202212663

*************************************************
*/

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/timer.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    //VARIAVÉIS DO JOGO
    const int largura_t = 591, altura_t = 443;
    const float FPS = 90;
    float cx=0,cy=0,nx=largura_t,speed=7.0,vento=speed-1.5,larg=1329;
    float pos_scootery = 330;
    float pos_scooterx = 25;
    float enemy=310,enemx=largura_t+800;
    float copoy=350,copox=0-largura_t;
    int score=0;
    int imune=0;
    int hi=0;

    bool fim = false;
    bool inicio = false;
    bool gameover = false;
    bool jump=false;
    bool agachado=false;
    bool vilao=false;

    ALLEGRO_EVENT_QUEUE *event = NULL;

    //INICIALIZAÇÕES
    al_init();
    if(!al_init())

    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    ALLEGRO_TIMER *tempo = al_create_timer(1.0/FPS);
    if(!tempo)
    {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    ALLEGRO_DISPLAY *display;
    display = al_create_display(largura_t,altura_t);
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(tempo);
        return -1;
    }

    //INSTALAÇÕES DOS ADDONS
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(16);
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_set_window_title(display, "A SCOOTER ODISSEY");

      if (!al_install_audio())
    {
        fprintf(stderr, "Falha ao inicializar áudio.\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        return -1;
    }

    if (!al_init_acodec_addon())
    {
        fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        return -1;
    }

    if (!al_reserve_samples(16))
    {
        fprintf(stderr, "Falha ao alocar canais de áudio.\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        return -1;
    }

    if(!al_install_keyboard())

    {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        return -1;
    }

    if(!al_init_image_addon())
    {
        fprintf(stderr, "failed to initialize the image addon!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        return -1;
    }

    if(!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        return -1;
    }

    //INICIALIZAÇÃO DAS IMAGENS
    ALLEGRO_SAMPLE* song = al_load_sample("sons/song.wav");
    ALLEGRO_SAMPLE* deathsong = al_load_sample("sons/deathsound.wav");
    ALLEGRO_SAMPLE* drinkingsound = al_load_sample("sons/drinkingsound.wav");
    ALLEGRO_SAMPLE* jumpsound = al_load_sample("sons/jumpsound.wav");
    ALLEGRO_BITMAP *scooter = al_load_bitmap("imagens/scooter.png");
    ALLEGRO_BITMAP *scooter1 = al_load_bitmap("imagens/scooter1.png");
    ALLEGRO_BITMAP *scooterjump = al_load_bitmap("imagens/scooterjump.png");
    ALLEGRO_BITMAP *scootersic = al_load_bitmap("imagens/scootersic.png");
    ALLEGRO_BITMAP *fundo = al_load_bitmap("imagens/fundo.png");
    ALLEGRO_BITMAP *fundo2 = al_load_bitmap("imagens/fundo2.png");
    ALLEGRO_BITMAP *fundo3 = al_load_bitmap("imagens/fundo3.png");
    ALLEGRO_BITMAP *badassscooter = al_load_bitmap("imagens/badassscooter.png");
    ALLEGRO_BITMAP *nuvens = al_load_bitmap("imagens/nuvens.png");
    ALLEGRO_BITMAP *covid = al_load_bitmap("imagens/covid.png");
    ALLEGRO_BITMAP *copo = al_load_bitmap("imagens/copo.png");
    ALLEGRO_BITMAP *desenvolvedores = al_load_bitmap("imagens/desenvolvedores.png");

    if(!song)
    {
        fprintf(stderr, "falhou ao criar som de fundo!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        return -1;
    }

    if(!drinkingsound)
    {
        fprintf(stderr, "falhou ao criar drinkingsound!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        return -1;
    }

    if(!deathsong)
    {
        fprintf(stderr, "falhou ao criar deathsong!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(drinkingsound);
        return -1;
    }

    if(!jumpsound)
    {
        fprintf(stderr, "falhou ao criar o som de pulo!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        return -1;
    }

    if(!scooter)
    {
        fprintf(stderr, "falhou ao criar o scooter bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        return -1;
    }

    if(!scooter1)
    {
        fprintf(stderr, "falhou ao criar o scooter1 bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        return -1;
    }

    if(!scooterjump)
    {
        fprintf(stderr, "falhou ao criar o scooterjump bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        return -1;
    }

    if(!scootersic)
    {
        fprintf(stderr, "falhou ao criar o scootersic bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        return -1;
    }

    if(!badassscooter)
    {
        fprintf(stderr, "falhou ao criar o badassscooter bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        al_destroy_bitmap(scootersic);
        return -1;
    }

    if(!fundo)
    {
        fprintf(stderr, "falhou ao criar o fundo bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        al_destroy_bitmap(scootersic);
        al_destroy_bitmap(badassscooter);
        return -1;
    }

    if(!fundo2)
    {
        fprintf(stderr, "falhou ao criar o fundo2 bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        al_destroy_bitmap(scootersic);
        al_destroy_bitmap(badassscooter);
        al_destroy_bitmap(fundo);
        return -1;
    }

    if(!fundo3)
    {
        fprintf(stderr, "falhou ao criar o fundo3 bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        al_destroy_bitmap(scootersic);
        al_destroy_bitmap(badassscooter);
        al_destroy_bitmap(fundo);
        al_destroy_bitmap(fundo2);
        return -1;
    }

    if(!nuvens)
    {
        fprintf(stderr, "falhou ao criar as nuvens!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        al_destroy_bitmap(scootersic);
        al_destroy_bitmap(badassscooter);
        al_destroy_bitmap(fundo);
        al_destroy_bitmap(fundo2);
        al_destroy_bitmap(fundo3);
        return -1;
    }

    if(!covid)
    {
        fprintf(stderr, "falhou ao criar os covids, scooter pode chegar tranquilamente em seu destino!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        al_destroy_bitmap(scootersic);
        al_destroy_bitmap(badassscooter);
        al_destroy_bitmap(fundo);
        al_destroy_bitmap(fundo2);
        al_destroy_bitmap(fundo3);
        al_destroy_bitmap(nuvens);
        return -1;
    }

    if(!copo)
    {
        fprintf(stderr, "falhou ao criar os copos, scooter não conseguiu ter energia sem seu cafézinho!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        al_destroy_bitmap(scootersic);
        al_destroy_bitmap(badassscooter);
        al_destroy_bitmap(fundo);
        al_destroy_bitmap(fundo2);
        al_destroy_bitmap(fundo3);
        al_destroy_bitmap(nuvens);
        al_destroy_bitmap(covid);
        return -1;
    }

    if(!desenvolvedores)
    {
        fprintf(stderr, "falhou ao criar o bitmap dos desenvolvedores!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        al_destroy_bitmap(scootersic);
        al_destroy_bitmap(badassscooter);
        al_destroy_bitmap(fundo);
        al_destroy_bitmap(fundo2);
        al_destroy_bitmap(fundo3);
        al_destroy_bitmap(nuvens);
        al_destroy_bitmap(covid);
        al_destroy_bitmap(copo);
        return -1;
    }

    //CRIAR FONTES
    ALLEGRO_FONT *fonteTITLE = al_load_font("fonte/fonte.ttf",20,NULL);
    ALLEGRO_FONT *fontemenu = al_load_font("fonte/fonte.ttf",10,NULL);

    if(!fonteTITLE)
    {
        fprintf(stderr, "falhou ao criar fonteTITLE!\n");
         al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        al_destroy_bitmap(scootersic);
        al_destroy_bitmap(badassscooter);
        al_destroy_bitmap(fundo);
        al_destroy_bitmap(fundo2);
        al_destroy_bitmap(fundo3);
        al_destroy_bitmap(nuvens);
        al_destroy_bitmap(covid);
        al_destroy_bitmap(copo);
        al_destroy_bitmap(desenvolvedores);
        return -1;
    }

    if(!fontemenu)
    {
        fprintf(stderr, "falhou ao criar fontemenu!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        al_destroy_bitmap(scootersic);
        al_destroy_bitmap(badassscooter);
        al_destroy_bitmap(fundo);
        al_destroy_bitmap(fundo2);
        al_destroy_bitmap(fundo3);
        al_destroy_bitmap(nuvens);
        al_destroy_bitmap(covid);
        al_destroy_bitmap(copo);
        al_destroy_bitmap(desenvolvedores);
        al_destroy_font(fonteTITLE);
        return -1;
    }

    //CRIAÇÃO DOS ELEMENTOS DO MENU
    al_play_sample(song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    al_draw_bitmap(fundo, cx, cy, 0);
    al_draw_text (fonteTITLE,al_map_rgb(255,255,255),120,100,NULL,"A SCOOTER ODYSSEY");
    al_draw_text (fontemenu,al_map_rgb(0,0,0),140,170,NULL,"PRESSIONE ENTER PARA INICIAR");
    al_draw_bitmap(scooter,pos_scooterx,pos_scootery,0);

    //FUNÇÕES DE EVENTO
    event = al_create_event_queue();
    al_register_event_source(event,al_get_keyboard_event_source());
    al_register_event_source(event,al_get_display_event_source(display));
    al_register_event_source(event, al_get_timer_event_source(tempo));

    if(!event)
    {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(tempo);
        al_destroy_sample(song);
        al_destroy_sample(deathsong);
        al_destroy_sample(drinkingsound);
        al_destroy_sample(jumpsound);
        al_destroy_bitmap(scooter);
        al_destroy_bitmap(scooter1);
        al_destroy_bitmap(scooterjump);
        al_destroy_bitmap(scootersic);
        al_destroy_bitmap(badassscooter);
        al_destroy_bitmap(fundo);
        al_destroy_bitmap(fundo2);
        al_destroy_bitmap(fundo3);
        al_destroy_bitmap(nuvens);
        al_destroy_bitmap(covid);
        al_destroy_bitmap(copo);
        al_destroy_bitmap(desenvolvedores);
        al_destroy_font(fonteTITLE);
        al_destroy_font(fontemenu);
        return -1;
    }

    srand(time(NULL));
    al_flip_display();
    al_start_timer(tempo);

//LÓGICA DO JOGO
while(!fim)
{
    score++;
    ALLEGRO_EVENT ev;

    //LÓGICA DO MENU
    while (!inicio)
{
    al_wait_for_event(event,&ev);

    {switch (ev.keyboard.keycode)
    {case ALLEGRO_KEY_ENTER:
        {al_play_sample(deathsong, 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); inicio = true; break;}
     case ALLEGRO_EVENT_DISPLAY_CLOSE:
        {fim=true; break;}}
    }
}

        if(rand()%50==0)
            vilao=true;

        //PULO
        if(jump==false&&pos_scootery<330){
            pos_scootery+=10;}
        else if(jump==true){
            pos_scootery-=5; if (pos_scootery==180) jump=false;}

        //MOVIMENTO DAS IMAGENS
        cx-=speed;
        nx-=vento;
        copox-=speed-1.0;

        //RESET DAS IMAGENS
        if(cx<-(4*largura_t+150))
            cx=0;

        if (nx<-largura_t-800)
            nx=largura_t;

        if (enemx<-largura_t){
            enemx=largura_t; vilao=false;}

        if (copox<-largura_t-1000)
            copox=largura_t+1000;

        //DESENHO DAS IMAGENS
        al_draw_bitmap(fundo, cx, cy, 0);
        al_draw_bitmap(fundo2, cx+largura_t, cy+5, 0);
        al_draw_bitmap(fundo3, cx+largura_t+larg, cy, 0);
        al_draw_bitmap(fundo, cx+(2*largura_t)+larg, cy, 0);
        al_draw_bitmap(nuvens,nx,-220,0);
        al_draw_bitmap(nuvens,nx+800,-220,0);
        al_draw_bitmap(copo,copox,copoy,0);

        if(vilao){
        al_draw_bitmap(covid,enemx,enemy,0); enemx-=speed+2.0;}

        //DESENHO DO PRINCIPAL CONFORME QTD DE CAFÉS
        if(jump&&imune<3)
        {al_draw_bitmap(scooterjump,pos_scooterx,pos_scootery,0);}
        else if (imune>0&&imune<3)
        al_draw_bitmap(scooter1,pos_scooterx,pos_scootery,0);
        else if (imune>=3||jump)
        al_draw_bitmap(badassscooter,pos_scooterx,pos_scootery,0);
        else if (imune<0)
        al_draw_bitmap(scootersic,pos_scooterx,pos_scootery,0);
        else
        al_draw_bitmap(scooter,pos_scooterx,pos_scootery,0);

        //EASTER-EGG
        if(score>20000&&score<20500)
            al_draw_bitmap(desenvolvedores,150,100,0);

        //INPUT
        al_wait_for_event(event,&ev);{{
        switch(ev.type)
        {case ALLEGRO_EVENT_KEY_DOWN:
            {if(ev.keyboard.keycode == ALLEGRO_KEY_UP&&pos_scootery>=325)
                {al_play_sample(jumpsound, 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); jump=true; speed+=0.05;}
        break;}


        case ALLEGRO_EVENT_DISPLAY_CLOSE:
        {fim = true;
        break;}}}
        }

        //COLISÕES
         if(copox<=pos_scooterx&&copox>18)
            if(pos_scootery>=300||pos_scootery>=copoy-35)
                {imune+=1; al_play_sample(drinkingsound, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); copox=largura_t+10000;}

        if(enemx<=pos_scooterx&&enemx>15)
            {if(pos_scootery>=300||pos_scootery>=enemy-50)
                imune-=1;}

        if(imune<-1)
        {if(enemx<=pos_scooterx&&enemx>15)
            if(pos_scootery>=300||pos_scootery>=enemy-50)
             gameover=true; al_play_sample(deathsong, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);}


        //DESENHO DA QTD DE CAFÉS NA TELA
        if(imune>3)
            imune=3;

        {if (imune>0)
            al_draw_bitmap(copo,22,25,0);
        if (imune>1)
            al_draw_bitmap(copo,72,25,0);
        if (imune>=3)
            al_draw_bitmap(copo,122,25,0);}

        //DESENHO DO SCORE
        al_draw_textf(fonteTITLE,al_map_rgb(255,255,255),480,45,0,"%d",score);
        al_draw_textf(fonteTITLE,al_map_rgb(255,255,0),245,45,0,"HS: %d",hi);

        //LÓGICA DO GAMEOVER
        while(gameover)
        {
            al_flip_display();

            al_draw_text (fonteTITLE,al_map_rgb(255,0,0),200,100,NULL,"GAME OVER");
            al_draw_text (fontemenu,al_map_rgb(255,0,0),115,170,NULL,"PRESSIONE ENTER PARA REINICIAR!");

            if(score>hi)
                hi=score;

            score=0;
            cx=0;
            nx=largura_t;
            enemx=largura_t+800;
            copox=largura_t+1000;
            imune=0;
            speed=7.0;

            al_wait_for_event(event,&ev);

        {switch (ev.keyboard.keycode)
        {case ALLEGRO_KEY_ENTER:
            gameover = false; break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
        {gameover=false; fim=true;
        break;}}}
        }

    al_flip_display();
}

    al_destroy_display(display);
    al_destroy_timer(tempo);
    al_destroy_sample(song);
    al_destroy_sample(deathsong);
    al_destroy_sample(drinkingsound);
    al_destroy_sample(jumpsound);
    al_destroy_bitmap(scooter);
    al_destroy_bitmap(scooter1);
    al_destroy_bitmap(scooterjump);
    al_destroy_bitmap(scootersic);
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(fundo2);
    al_destroy_bitmap(fundo3);
    al_destroy_bitmap(badassscooter);
    al_destroy_bitmap(covid);
    al_destroy_bitmap(copo);
    al_destroy_bitmap(nuvens);
    al_destroy_bitmap(desenvolvedores);
    al_destroy_font(fontemenu);
    al_destroy_font(fonteTITLE);
    al_destroy_event_queue(event);

return 0;
}
