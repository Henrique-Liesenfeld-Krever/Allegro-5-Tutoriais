// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#define FPS 30
// Nossa conhecida função main...
int main(void)
{
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT    *font = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_TIMER *timer;

    double tempo;
 
    // Inicializamos a biblioteca
    al_init();
    al_init_font_addon();
    al_install_keyboard();
    timer = al_create_timer(0.01);

    
    font = al_create_builtin_font();
    fila_eventos = al_create_event_queue();
    // Criamos a nossa janela - dimensões de 640x480 px
    janela = al_create_display(640, 480);
    al_start_timer(timer);
    
    //avisamos para a fila de eventos que vamos prestar atenção em eventos da tela
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    //agora o keyboard
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

    int rodando=1, situacao=1, frame;

    while (rodando)
    {
        tempo = al_get_time();
        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos,&evento);
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                rodando = 0;
            }
            if (evento.type == ALLEGRO_EVENT_TIMER)
            {
                frame++;
                if (frame%240==0)
                {
                    situacao= !situacao;
                }
                
            }
            
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(evento.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:
                    {

                        situacao = 1;
                        break;
                    }
                    case ALLEGRO_KEY_DOWN:
                    {
                        situacao = 2;
                        break;

                    }
                }
            }
            
        }
        if (situacao==1)
        {
            /* code */
            // Preenchemos a janela dse branco
            al_clear_to_color(al_map_rgb(255, 255, 255));

            al_draw_text(font,al_map_rgb(0,0,0),100,100,ALLEGRO_ALIGN_CENTER,"ola Mundo");
        
            // Atualiza a tela

        }
        else if (situacao==2)
        {
            al_clear_to_color(al_map_rgb(56, 123, 155));

            al_draw_text(font,al_map_rgb(0,0,0),250,250,ALLEGRO_ALIGN_CENTER,"ola Mundo");
        
            // Atualiza a tela

            
        }
        al_draw_textf(font,al_map_rgb(0,0,0),250,250, ALLEGRO_ALIGN_CENTER,"os frames sao ");
        al_flip_display();
    }
    
 
 
    // Finaliza a janela
    al_destroy_display(janela);
 
    return 0;
}