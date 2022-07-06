// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
 
// Nossa conhecida função main...
int main(void)
{
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT    *font = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
 
    // Inicializamos a biblioteca
    al_init();
    al_init_font_addon();
    
    font = al_create_builtin_font();
    fila_eventos = al_create_event_queue();
    // Criamos a nossa janela - dimensões de 640x480 px
    janela = al_create_display(640, 480);
    
    //avisamos para a fila de eventos que vamos prestar atenção em eventos da tela
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    while (true)
    {
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);
        al_wait_for_event_until(fila_eventos,&evento,&timeout);
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        
        
        // Preenchemos a janela dse branco
        al_clear_to_color(al_map_rgb(255, 255, 255));

        al_draw_text(font,al_map_rgb(0,0,0),100,100,ALLEGRO_ALIGN_CENTER,"ola Mundo");
    
        // Atualiza a tela
        al_flip_display();

        al_rest(2);
        // mudamos a tela de cor
        al_clear_to_color(al_map_rgb(56, 123, 155));

        al_draw_text(font,al_map_rgb(0,0,0),250,250,ALLEGRO_ALIGN_CENTER,"ola Mundo");
    
        // Atualiza a tela
        al_flip_display();
        al_rest(2);

        
        
        
    }
    
 
 
    // Finaliza a janela
    al_destroy_display(janela);
 
    return 0;
}