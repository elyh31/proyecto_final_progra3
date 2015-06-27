#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <SDL2/SDL_ttf.h>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *fondo1, *monte, *nuves1, *nuves2, *basketball, *madera, *madera2, *madera3,
            *madera4, *madera5, *madera6, *madera7, *reloj, *menu, *instrucciones, *balon_rojo, *puntuacion, *nivel;
SDL_Rect rect_fondo1, rect_monte, rect_nuves1, rect_nuves2, rect_basketball, rect_madera, rect_madera2, rect_madera3,
         rect_madera4, rect_madera5, rect_madera6, rect_madera7, rect_reloj, rect_menu, rect_instrucciones,rect_balon_rojo,
         rect_puntuacion, rect_nivel;

std::string toString(int number)
{
if (number == 0)
return "0";
if(number < 0)
return "-"+toString(-number);
std::string temp="";
std::string returnvalue="";
while (number>0)
{
temp+=number%10+48;
number/=10;
}
for (int i=0; i<(int)temp.length(); i++)
returnvalue+=temp[temp.length()-i-1];
return returnvalue;
}

void mover_nuve(int mov_nuve)
{
    if(mov_nuve > -1000)
    {
        rect_nuves1.x--;
        rect_nuves2.x--;
    }
}

void bask_salto_arriba(int salto)
{
    if(salto == 1)
        if(rect_basketball.y >= 0)
            rect_basketball.y--;
}

void bask_salto_bajada(int bajada)
{
    if(bajada==1)
    {
        rect_basketball.y++;
    }
}

void mover_madera_izq(int encender)
{
    if(encender==0 && rect_madera.x > 200 )
    {
        rect_madera.x--;
        rect_madera4.x++;
        rect_madera5.x--;
    }
}

void mover_madera23(int encender)
{
    if(encender == 0 && rect_madera2.x >= 0 )
        {
            rect_madera2.x--;
            rect_madera3.x++;
            rect_madera6.x++;
            rect_madera7.x--;
        }
}

void mover_madera_der(int encender)
{
    if(encender==1 && rect_madera.x < 700 )
    {
        rect_madera.x++;
        rect_madera4.x--;
        rect_madera5.x++;
    }
}
void mover_madera_23(int encender)
{
    if(encender == 1 && rect_madera2.x <= 200 )
        {
            rect_madera2.x++;
            rect_madera3.x--;
            rect_madera6.x--;
            rect_madera7.x++;
        }
}

int main(int argc, char* args[] )
{
    int mov_nuve=1000;
    int mov_nuve2=0;
    int velocidad=0;
    int velocidad2=0;
    int salto=0;
    int encendido=0;
    int posicion_actual=0;
    int posicion_anterior=0;
    int bajada=0;
    int encender=0, encender2=0;
    int imagen_actual=0;
    int segundos = 0;
    int minutos = 120;
    int microsegundos = 0;
    int num = rand() % 10;
    int puntos = 0;
    int niveles = 1;
    int velCamPelRoj = 20;


    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
     if((window = SDL_CreateWindow("Image Loading", 200, 100, 1000/*WIDTH*/, 483/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    if(TTF_Init() == -1)
    {
        return 40;
    }

    int w=0,h=0;
    fondo1 = IMG_LoadTexture(renderer,"imagenes/fondo1.png");
    SDL_QueryTexture(fondo1,NULL,NULL,&w,&h);
    rect_fondo1.x=0; rect_fondo1.y=0; rect_fondo1.w=w; rect_fondo1.h=h;

    monte = IMG_LoadTexture(renderer,"imagenes/monte.png");
    SDL_QueryTexture(monte,NULL,NULL,&w,&h);
    rect_monte.x=0; rect_monte.y=0; rect_monte.w=w; rect_monte.h=h;

    nuves1 = IMG_LoadTexture(renderer,"imagenes/nuves1.png");
    SDL_QueryTexture(nuves1,NULL,NULL,&w,&h);
    rect_nuves1.x=0; rect_nuves1.y=0; rect_nuves1.w=w; rect_nuves1.h=h;

    nuves2 = IMG_LoadTexture(renderer,"imagenes/nuves2.png");
    SDL_QueryTexture(nuves2,NULL,NULL,&w,&h);
    rect_nuves2.x=1000; rect_nuves2.y=0; rect_nuves2.w=w; rect_nuves2.h=h;

    basketball = IMG_LoadTexture(renderer,"imagenes/basketball.png");
    SDL_QueryTexture(basketball,NULL,NULL,&w,&h);
    rect_basketball.x=500; rect_basketball.y=440; rect_basketball.w=w; rect_basketball.h=h;

    madera = IMG_LoadTexture(renderer,"imagenes/madera.png");
    SDL_QueryTexture(madera,NULL,NULL,&w,&h);
    rect_madera.x=700; rect_madera.y=400; rect_madera.w=w; rect_madera.h=h;

    madera2 = IMG_LoadTexture(renderer,"imagenes/madera2.png");
    SDL_QueryTexture(madera2,NULL,NULL,&w,&h);
    rect_madera2.x=200; rect_madera2.y=340; rect_madera2.w=w; rect_madera2.h=h;

    madera3 = IMG_LoadTexture(renderer,"imagenes/madera3.png");
    SDL_QueryTexture(madera3,NULL,NULL,&w,&h);
    rect_madera3.x=700; rect_madera3.y=350; rect_madera3.w=w; rect_madera3.h=h;

    madera4 = IMG_LoadTexture(renderer,"imagenes/madera4.png");
    SDL_QueryTexture(madera4,NULL,NULL,&w,&h);
    rect_madera4.x=200; rect_madera4.y=260; rect_madera4.w=w; rect_madera4.h=h;

    madera5 = IMG_LoadTexture(renderer,"imagenes/madera5.png");
    SDL_QueryTexture(madera5,NULL,NULL,&w,&h);
    rect_madera5.x=700; rect_madera5.y=190; rect_madera5.w=w; rect_madera5.h=h;

    madera6 = IMG_LoadTexture(renderer,"imagenes/madera6.png");
    SDL_QueryTexture(madera6,NULL,NULL,&w,&h);
    rect_madera6.x=170; rect_madera6.y=110; rect_madera6.w=w; rect_madera6.h=h;

    madera7 = IMG_LoadTexture(renderer,"imagenes/madera7.png");
    SDL_QueryTexture(madera7,NULL,NULL,&w,&h);
    rect_madera7.x=730; rect_madera7.y=90; rect_madera7.w=w; rect_madera7.h=h;

    balon_rojo = IMG_LoadTexture(renderer,"imagenes/balon_rojo.png");
    SDL_QueryTexture(balon_rojo,NULL,NULL,&w,&h);
    rect_balon_rojo.x=0; rect_balon_rojo.y=0; rect_balon_rojo.w=w; rect_balon_rojo.h=h;

    reloj = IMG_LoadTexture(renderer,"imagenes/reloj.png");
    SDL_QueryTexture(reloj,NULL,NULL,&w,&h);
    rect_reloj.x=470; rect_reloj.y=5; rect_reloj.w=50; rect_reloj.h=40;

    puntuacion = IMG_LoadTexture(renderer,"imagenes/puntuacion.png");
    SDL_QueryTexture(puntuacion,NULL,NULL,&w,&h);
    rect_puntuacion.x=950; rect_puntuacion.y=5; rect_puntuacion.w=30; rect_puntuacion.h=40;

    nivel = IMG_LoadTexture(renderer,"imagenes/nivel.png");
    SDL_QueryTexture(nivel,NULL,NULL,&w,&h);
    rect_nivel.x=10; rect_nivel.y=5; rect_nivel.w=10; rect_nivel.h=30;

    menu = IMG_LoadTexture(renderer,"imagenes/menu.png");
    SDL_QueryTexture(menu,NULL,NULL,&w,&h);
    rect_menu.x=0; rect_menu.y=0; rect_menu.w=w; rect_menu.h=h;

    bool menu1 = true;
    bool activar_juego = false;

    instrucciones = IMG_LoadTexture(renderer,"imagenes/instrucciones.png");
    SDL_QueryTexture(instrucciones,NULL,NULL,&w,&h);
    rect_instrucciones.x=0; rect_instrucciones.y=0; rect_instrucciones.w=w; rect_instrucciones.h=h;

    bool instrucciones2 = false;
    bool opcion1 = true;
    bool opcion2 = true;
    bool opcion3 = false;
    bool opcion4 = true;
    bool salir = false;

    vector<SDL_Texture*>texturas;
    texturas.push_back(IMG_LoadTexture(renderer,"imagenes/mar1.png"));
    texturas.push_back(IMG_LoadTexture(renderer,"imagenes/mar2.png"));
    texturas.push_back(IMG_LoadTexture(renderer,"imagenes/mar3.png"));
    texturas.push_back(IMG_LoadTexture(renderer,"imagenes/mar4.png"));
    texturas.push_back(IMG_LoadTexture(renderer,"imagenes/mar5.png"));
    texturas.push_back(IMG_LoadTexture(renderer,"imagenes/mar6.png"));
    SDL_Rect rect_mar;
    SDL_QueryTexture(texturas[0],NULL,NULL,&w,&h);
    rect_mar.x=0; rect_mar.y=0; rect_mar.w=w; rect_mar.h=h;

    SDL_Color textColor = {255,0,0};
    TTF_Font *gFont = TTF_OpenFont("04B_30__.TTF", 100);
    SDL_Surface* temp = TTF_RenderText_Solid(gFont, toString(10).c_str(), textColor);
    SDL_Texture* texto = SDL_CreateTextureFromSurface(renderer, temp);

    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYUP)
                {
                    if(Event.key.keysym.sym == SDLK_SPACE)
                    {
                    if(salto == 0 && bajada == 0)
                        if(rect_basketball.y > 0)
                        {
                            salto = salto + 1;
                            posicion_actual = rect_basketball.y;
                            posicion_anterior = rect_basketball.y;
                        }
                    }
                }
            if(Event.type == SDL_KEYDOWN)
            {
             //jugar
             if(opcion1)
             {
                if(Event.key.keysym.sym == SDLK_KP_1)
                {
                    menu1 = false;
                    activar_juego = true;
                    opcion1 = false;
                    opcion2 = false;
                    opcion3 = false;
                    opcion4 = false;
                }
             }

            //instrucciones
            if(opcion2)
            {
            if(Event.key.keysym.sym == SDLK_KP_2)
                {
                    instrucciones2 = true;
                    menu1 = false;
                    opcion1 = false;
                    opcion2 = false;
                    opcion3 = true;
                    opcion4 = false;
                }
            }

            if(opcion3)
            {
            // volver al menu
            if(Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    instrucciones2 = false;
                    menu1 = true;
                    opcion1 = true;
                    opcion2 = true;
                    opcion3 = false;
                    opcion4 = true;
                }
            }

            if(opcion4)
            {
            // salir del juego
            if(Event.key.keysym.sym == SDLK_KP_3)
                {
                   return 0;
                }
            }

            if(activar_juego)
            {
                if(Event.key.keysym.sym == SDLK_RIGHT)
                    if(rect_basketball.x < 960)
                        rect_basketball.x = rect_basketball.x + 5;

                if(Event.key.keysym.sym == SDLK_LEFT)
                    if(rect_basketball.x > 0)
                        rect_basketball.x = rect_basketball.x - 5;
               }
            }
          }
    if(activar_juego)
    {
        //movimiento de nuves
        if(velocidad == 30)
        {
        mover_nuve(mov_nuve);
        mov_nuve++;
        mov_nuve2++;
        velocidad = 0;
        }

        if(mov_nuve == 2000)
        {
        rect_nuves1.x = 1000;
        mov_nuve = 0;
        }
        if(mov_nuve2 == 2000)
        {
        rect_nuves2.x = 1000;
        mov_nuve2 = 0;
          }

        //colision de polota con madera abajo
        bask_salto_arriba(salto);
        if(rect_basketball.y == posicion_actual - 100
        || rect_basketball.x+30 >= rect_madera.x
        && rect_basketball.x <= rect_madera.x +100 && rect_basketball.y == rect_madera.y +15
        //madera 2
        || rect_basketball.x+30 >= rect_madera2.x
        && rect_basketball.x <= rect_madera2.x +100 && rect_basketball.y == rect_madera2.y +15
        //madera 3
        || rect_basketball.x+30 >= rect_madera3.x
        && rect_basketball.x <= rect_madera3.x +100 && rect_basketball.y == rect_madera3.y +15
        //madera 4
        || rect_basketball.x+30 >= rect_madera4.x
        && rect_basketball.x <= rect_madera4.x +100 && rect_basketball.y == rect_madera4.y +15
        //madera 5
        || rect_basketball.x+30 >= rect_madera5.x
        && rect_basketball.x <= rect_madera5.x +100 && rect_basketball.y == rect_madera5.y +15
        //madera 6
        || rect_basketball.x+30 >= rect_madera6.x
        && rect_basketball.x <= rect_madera6.x +100 && rect_basketball.y == rect_madera6.y +15
        //madera 7
        || rect_basketball.x+30 >= rect_madera7.x
        && rect_basketball.x <= rect_madera7.x +100 && rect_basketball.y == rect_madera7.y +15)
        {
            salto = 0;
            bajada = 1;
            posicion_anterior = 440;
        }

        // colision pelota madera arriba
        if(rect_basketball.x+30 >= rect_madera.x && rect_basketball.x <= rect_madera.x +100
        && rect_basketball.y +41 == rect_madera.y
        //madera 2
        || rect_basketball.x+30 >= rect_madera2.x && rect_basketball.x <= rect_madera2.x +100
        && rect_basketball.y +41 == rect_madera2.y
        //madera 3
        || rect_basketball.x+30 >= rect_madera3.x && rect_basketball.x <= rect_madera3.x +100
        && rect_basketball.y +41 == rect_madera3.y
        //madera 4
        || rect_basketball.x+30 >= rect_madera4.x && rect_basketball.x <= rect_madera4.x +100
        && rect_basketball.y +41 == rect_madera4.y
        //madera 5
        || rect_basketball.x+30 >= rect_madera5.x && rect_basketball.x <= rect_madera5.x +100
        && rect_basketball.y +41 == rect_madera5.y
        //madera 6
        || rect_basketball.x+30 >= rect_madera6.x && rect_basketball.x <= rect_madera6.x +100
        && rect_basketball.y +41 == rect_madera6.y
        //madera 7
        || rect_basketball.x+30 >= rect_madera7.x && rect_basketball.x <= rect_madera7.x +100
        && rect_basketball.y +41 == rect_madera7.y)
        {
        bajada = 0;
            if(rect_basketball.x +30 <= rect_madera.x  && rect_basketball.y +41 == rect_madera.y
            || rect_basketball.x >= rect_madera.x +100  && rect_basketball.y +41 == rect_madera.y
            || rect_basketball.x +30 <= rect_madera2.x  && rect_basketball.y +41 == rect_madera2.y
            || rect_basketball.x >= rect_madera2.x +100  && rect_basketball.y +41 == rect_madera2.y
            || rect_basketball.x +30 <= rect_madera3.x  && rect_basketball.y +41 == rect_madera3.y
            || rect_basketball.x >= rect_madera3.x +100  && rect_basketball.y +41 == rect_madera3.y
            || rect_basketball.x +30 <= rect_madera4.x  && rect_basketball.y +41 == rect_madera4.y
            || rect_basketball.x >= rect_madera4.x +100  && rect_basketball.y +41 == rect_madera4.y
            || rect_basketball.x +30 <= rect_madera5.x  && rect_basketball.y +41 == rect_madera5.y
            || rect_basketball.x >= rect_madera5.x +100  && rect_basketball.y +41 == rect_madera5.y
            || rect_basketball.x +30 <= rect_madera6.x  && rect_basketball.y +41 == rect_madera6.y
            || rect_basketball.x >= rect_madera6.x +100  && rect_basketball.y +41 == rect_madera6.y
            || rect_basketball.x +30 <= rect_madera7.x  && rect_basketball.y +41 == rect_madera7.y
            || rect_basketball.x >= rect_madera7.x +100  && rect_basketball.y +41 == rect_madera7.y)
            {
                bajada = 1;
                posicion_anterior = 440;
            }
        }

        if(rect_basketball.y == 0)
        {
         salto = 0;
         bajada = 1;
        }

        bask_salto_bajada(bajada);

        if(rect_basketball.y == posicion_anterior || rect_basketball.y == 440)
        {
            bajada = 0;
        }
        velocidad++;

        // movimoento de madera
        if(velocidad % 2 == 0)
        {
        mover_madera_der(encender);
        if(rect_madera.x==700)
            encender=0;
        mover_madera_izq(encender);
        if(rect_madera.x==200)
            encender=1;
        }

        if(velocidad % 3 == 0)
        {
        mover_madera23(encender2);
        if(rect_madera2.x==200 && rect_madera3.x==700)
            encender2=0;
        mover_madera_23(encender2);
        if(rect_madera2.x==0 && rect_madera3.x==900)
            encender2=1;
        }

        velocidad2++;
        if(velocidad2 == 70)
            velocidad2=0;

        //cronometro
        if(microsegundos == 180)
        {
            segundos = segundos + 1;
            microsegundos = 0;
            if(segundos = 120)
            {
                minutos = minutos - 1;
                segundos = 0;
                if(minutos % velCamPelRoj == 0)
                {
                    num = rand() % 10;
                }
            }
        }
        if(rect_basketball.x+30 >= rect_balon_rojo.x && rect_basketball.x <= rect_balon_rojo.x+20
        && rect_basketball.y == rect_balon_rojo.y+20)
        {
            num = rand() % 10;
            puntos = puntos + 10;
            if(puntos % 50 == 0)
            {
                niveles = niveles + 1;
                velCamPelRoj = velCamPelRoj - 5;
            }
        }
        microsegundos++;
    }

    if(minutos == 0)
    {
        minutos = 120;
        puntos = 0;
        niveles = 1;
        instrucciones2 = false;
        menu1 = true;
        activar_juego = false;
        opcion1 = true;
        opcion2 = true;
        opcion3 = false;
        opcion4 = true;

    }
        SDL_RenderCopy(renderer,fondo1,NULL,&rect_fondo1);
        SDL_RenderCopy(renderer,texturas[imagen_actual],NULL,&rect_mar);
        if(velocidad2 % 70 == 0)
        {
        imagen_actual++;
        if(imagen_actual == 5)
            imagen_actual = 0;
        }

        SDL_RenderCopy(renderer,monte,NULL,&rect_monte);
        SDL_RenderCopy(renderer,nuves1,NULL,&rect_nuves1);
        SDL_RenderCopy(renderer,nuves2,NULL,&rect_nuves2);
        SDL_RenderCopy(renderer,basketball,NULL,&rect_basketball);
        SDL_RenderCopy(renderer,madera,NULL,&rect_madera);
        SDL_RenderCopy(renderer,madera2,NULL,&rect_madera2);
        SDL_RenderCopy(renderer,madera3,NULL,&rect_madera3);
        SDL_RenderCopy(renderer,madera4,NULL,&rect_madera4);
        SDL_RenderCopy(renderer,madera5,NULL,&rect_madera5);
        SDL_RenderCopy(renderer,madera6,NULL,&rect_madera6);
        SDL_RenderCopy(renderer,madera7,NULL,&rect_madera7);
        if(num==0)
        {
            rect_balon_rojo.x = 200;
            rect_balon_rojo.y = 30;
            SDL_RenderCopy(renderer,balon_rojo,NULL,&rect_balon_rojo);
        }
        if(num==1)
        {
            rect_balon_rojo.x = 730;
            rect_balon_rojo.y = 50;
            SDL_RenderCopy(renderer,balon_rojo,NULL,&rect_balon_rojo);
        }
        if(num==2)
        {
            rect_balon_rojo.x = 560;
            rect_balon_rojo.y = 155;
            SDL_RenderCopy(renderer,balon_rojo,NULL,&rect_balon_rojo);
        }
        if(num==3)
        {
            rect_balon_rojo.x = 210;
            rect_balon_rojo.y = 210;
            SDL_RenderCopy(renderer,balon_rojo,NULL,&rect_balon_rojo);
        }
        if(num==4)
        {
            rect_balon_rojo.x = 710;
            rect_balon_rojo.y = 170;
            SDL_RenderCopy(renderer,balon_rojo,NULL,&rect_balon_rojo);
        }
        if(num==5)
        {
            rect_balon_rojo.x = 320;
            rect_balon_rojo.y = 280;
            SDL_RenderCopy(renderer,balon_rojo,NULL,&rect_balon_rojo);
        }
        if(num==6)
        {
            rect_balon_rojo.x = 890;
            rect_balon_rojo.y = 290;
            SDL_RenderCopy(renderer,balon_rojo,NULL,&rect_balon_rojo);
        }
        if(num==7)
        {
            rect_balon_rojo.x = 160;
            rect_balon_rojo.y = 355;
            SDL_RenderCopy(renderer,balon_rojo,NULL,&rect_balon_rojo);
        }
        if(num==8)
        {
            rect_balon_rojo.x = 980;
            rect_balon_rojo.y = 400;
            SDL_RenderCopy(renderer,balon_rojo,NULL,&rect_balon_rojo);
        }
        if(num==9)
        {
            rect_balon_rojo.x = 100;
            rect_balon_rojo.y = 420;
            SDL_RenderCopy(renderer,balon_rojo,NULL,&rect_balon_rojo);
        }

        temp = TTF_RenderText_Solid(gFont, toString(minutos).c_str(), textColor);
        texto = SDL_CreateTextureFromSurface(renderer, temp);
        SDL_RenderCopy(renderer,texto,NULL,&rect_reloj);

        temp = TTF_RenderText_Solid(gFont, toString(puntos).c_str(), textColor);
        texto = SDL_CreateTextureFromSurface(renderer, temp);
        SDL_RenderCopy(renderer,texto,NULL,&rect_puntuacion);

        temp = TTF_RenderText_Solid(gFont, toString(niveles).c_str(), textColor);
        texto = SDL_CreateTextureFromSurface(renderer, temp);
        SDL_RenderCopy(renderer,texto,NULL,&rect_nivel);

        if(menu1)
        {
        SDL_RenderCopy(renderer,menu,NULL,&rect_menu);
        }

        if(instrucciones2)
        {
        SDL_RenderCopy(renderer,instrucciones,NULL,&rect_instrucciones);
        }
        SDL_RenderPresent(renderer);

        delete temp;
        SDL_DestroyTexture(texto);
        SDL_DestroyTexture(reloj);
        SDL_DestroyTexture(nivel);
        SDL_DestroyTexture(puntuacion);

    }

    return 0;
}
