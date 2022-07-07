
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


#define TAMANHO_TELA_X 640
#define TAMANHO_TELA_Y 480
#define pi 3.1415


void rotate(float angle, float *x, float *y, float innerAngle, float size, float offsetX, float offsetY) {
    *x = cos((innerAngle + angle) * pi/180) * size/2 + offsetX;
    *y = sin((innerAngle + angle) * pi/180) * size/2 + offsetY;
}


int main(void) {
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    // Inicializamos a biblioteca
    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();

    font = al_create_builtin_font();
    fila_eventos = al_create_event_queue();

    janela = al_create_display(TAMANHO_TELA_X, TAMANHO_TELA_Y);

    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    al_register_event_source(fila_eventos, al_get_mouse_event_source()); // registrando mouse

    al_register_event_source(fila_eventos, al_get_keyboard_event_source()); // registrando teclado

    float p0x, p0y, p1x, p1y, p2x, p2y; // pontos do triângulo
    
    float p3x = 500, p3y = 250, p4x = 600, p4y = 400; // pontos do retângulo

    double lastTempo = 0, tempo = 0; // tempos para controle do fps

    int rodando = 1, mouseX = 0, mouseY = 0;

    float x = -100, y = 460; // cordenadas do texto

    float angle = 0; // guardamos o angulo de rotação (em graus) aqui

    float tamanho_triangulo = 100;

    bool incrementa_angulo = false, triangulo_segue = false;

    int incrementa_tamanho = 0;

    while (rodando) {

        lastTempo = tempo;
        tempo = al_get_time();

        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                rodando = 0;
            }

            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
                mouseX = evento.mouse.x;
                mouseY = evento.mouse.y;
            }

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (false) { // desafio
                    puts("Clicou no retângulo!");
                }
            }

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (evento.keyboard.keycode) {

                    case ALLEGRO_KEY_R:
                        incrementa_angulo = true;
                        break;

                    case ALLEGRO_KEY_UP:
                        incrementa_tamanho = 1;
                        break;
                    
                    case ALLEGRO_KEY_DOWN:
                        incrementa_tamanho = -1;
                        break;

                    case ALLEGRO_KEY_T:
                        triangulo_segue = !triangulo_segue;
                }
            }

            if (evento.type == ALLEGRO_EVENT_KEY_UP) {
                switch (evento.keyboard.keycode) {

                    case ALLEGRO_KEY_R:
                        incrementa_angulo = false;
                        break;

                    case ALLEGRO_KEY_UP:
                        incrementa_tamanho = 0;
                        break;
                    
                    case ALLEGRO_KEY_DOWN:
                        incrementa_tamanho = 0;
                        break;
                }
            }

        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        

        rotate(angle, &p0x, &p0y, 0,   tamanho_triangulo, triangulo_segue ? mouseX : 320, triangulo_segue ? mouseY : 240); // primeiro ponto, angulo 0
        rotate(angle, &p1x, &p1y, 120, tamanho_triangulo, triangulo_segue ? mouseX : 320, triangulo_segue ? mouseY : 240); // segundo ponto, angulo 120
        rotate(angle, &p2x, &p2y, 240, tamanho_triangulo, triangulo_segue ? mouseX : 320, triangulo_segue ? mouseY : 240); // terceiro ponto, angulo 240

        al_draw_triangle(p0x, p0y, p1x, p1y, p2x, p2y, al_map_rgb(255,255,255), 3);

        // calculo do incremento independente do fps
        // x aumenta em 100 pixels a cada segundo
        x += 100 * (tempo - lastTempo);

        // angulo incrementa 240 graus por segundo
        if (incrementa_angulo) {
            angle += 240 * (tempo - lastTempo);
        }

        if (incrementa_tamanho) {
            tamanho_triangulo += incrementa_tamanho * 400 * (tempo - lastTempo);
        }


        al_draw_filled_rectangle(p3x, p3y, p4x, p4y, al_map_rgb(255,255,255));


        al_draw_text(font, al_map_rgb(255,255,255), x, y, ALLEGRO_ALIGN_LEFT, "BOTTOM TEXT");

        if (x > TAMANHO_TELA_X)
            x = -al_get_text_width(font, "BOTTOM TEXT"); // função que retorna a largura de um texto, comentado na aula 3

        // atualiza tela
        al_flip_display();

    }


    // Finaliza a janela
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
