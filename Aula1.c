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
 
    // Inicializamos a biblioteca
    al_init();
    al_init_font_addon();
 

    font = al_create_builtin_font();

    // Criamos a nossa janela - dimensões de 640x480 px
    janela = al_create_display(640, 480);
 
    // Preenchemos a janela de branco
    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_draw_text(font,al_map_rgb(0,0,0),100,100,ALLEGRO_ALIGN_CENTER,"ola Mundo");
 
    // Atualiza a tela
    al_flip_display();
 
    // Segura a execução por 10 segundos
    al_rest(5.0);
 
    // Finaliza a janela
    al_destroy_display(janela);
 
    return 0;
}