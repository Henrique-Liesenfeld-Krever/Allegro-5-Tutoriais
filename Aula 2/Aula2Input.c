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
    al_install_keyboard();

    font = al_create_builtin_font();
    fila_eventos = al_create_event_queue();
    // Criamos a nossa janela - dimensões de 640x480 px
    janela = al_create_display(640, 480);

    //avisamos para a fila de eventos que vamos prestar atenção em eventos da tela
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    //agora o keyboard
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    int rodando = 1, situacao = 1;

    char v[21];
    for (int i = 0; i < 21; i++) v[i] = '\0';
    int indice_v = 0;

    while (rodando) {
        while (!al_is_event_queue_empty(fila_eventos)) {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                rodando = 0;
            }

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (evento.keyboard.keycode) {

                    case ALLEGRO_KEY_UP:
                        situacao = 1;
                        break;

                    case ALLEGRO_KEY_DOWN:
                        situacao = 2;
                        break;

                    case ALLEGRO_KEY_A:
                        if (indice_v < 21)
                            v[indice_v++] = evento.keyboard.keycode+64;
                        break;
                }
            }
        }

        if (situacao == 1) {
            // Preenchemos a janela de branco
            al_clear_to_color(al_map_rgb(255, 255, 255));

            al_draw_text(font, al_map_rgb(0,0,0), 100, 100, ALLEGRO_ALIGN_CENTER, "ola Mundo");
        }

        else if (situacao == 2) {
            al_clear_to_color(al_map_rgb(56, 123, 155));

            al_draw_text(font, al_map_rgb(0,0,0), 250, 250, ALLEGRO_ALIGN_CENTER, "ola Mundo");
        }

        // Atualiza a tela
        al_flip_display();
    }


    // Finaliza a janela
    al_destroy_display(janela);

    return 0;
}
