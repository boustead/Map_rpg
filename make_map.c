/*
** EPITECH PROJECT, 2020
** map
** File description:
** make_map.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <SFML/Graphics.h>

typedef struct Cellule_t cell;
struct Cellule_t
{
    sfVector2f pos;
    int type;
};

void my_putchar(char c)
{
    write(1, &c, 1);
}

void draw(cell **screen, int height, int width)
{
    int j = 0;

    for (int i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            //printf("|%.1f,%.1f|", screen[i][j].pos.x, screen[i][j].pos.y);
            printf("%i", screen[i][j].type);
        }
        //if (i != height-1)
        my_putchar('\n');
    }
}

cell **init(int width, int height)
{
    cell **res;
    int i = 0;
    int j = 0;
    sfVector2f x = {0, 0};

    res = malloc(sizeof(cell *) * (height+1));
    while (i <= height) {
        res[i] = malloc(sizeof(cell) * (width+1));
        i++;
    }
    for (int i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            res[i][j].type = 0;
            res[i][j].pos = x;
            x.y += 20;
        }
        x.y = 0;
        x.x += 20;
    }
    return res;
}

void create_view(sfVector2f center)
{
    // center.x -= 500;
    // center.y -= 500;
    sfFloatRect rec = {0, 0, 50, 50};
    sfView *view = sfView_create();
    view = sfView_createFromRect(rec);
    sfView_setCenter(view, center);
    //sfView_zoom(view, 0.5);
}

void mk_win(cell **screen)
{
    sfRenderWindow *window;
    sfVideoMode mode = {800, 600, 32};
    window = sfRenderWindow_create(mode, "vidéo gayme",
sfResize | sfClose, NULL);
    //view
    //sfVector2f size = {100, 100};
    sfFloatRect rec = {0, 0, 320, 320};
    sfView *view = sfView_create();
    view = sfView_createFromRect(rec);
    //sfView_setSize(view, size);
    //create texture sprite ect..
    sfTexture *tbg = sfTexture_createFromFile("sky.png", NULL);
    sfSprite *sbg = sfSprite_create();
    sfSprite_setTexture(sbg, tbg, sfTrue);
    sfSprite_setPosition(sbg, screen[0][0].pos);
    sfTexture *tplayer = sfTexture_createFromFile("aim.png", NULL);
    sfSprite *splayer = sfSprite_create();
    sfSprite_setTexture(splayer, tplayer, sfTrue);
    int x = 10;
    int y = 10;
    sfVector2f pplayer = screen[x][y].pos;
    sfSprite_setPosition(splayer, pplayer);
    //sfView_zoom(view, 0.1);
    //create_view(pplayer);

    while (sfRenderWindow_isOpen(window)) {
        //create_view(pplayer);
        sfView_setCenter(view, pplayer);
        //sfView_zoom(view, 0.1);
        pplayer = screen[x][y].pos;
        sfSprite_setPosition(splayer, pplayer);
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyS)
                y++;
                if (event.key.code == sfKeyZ && y > 0)
                y--;
                if (event.key.code == sfKeyD)
                x++;
                if (event.key.code == sfKeyQ && x > 0)
                x--;
            sfSprite_setPosition(splayer, pplayer);
            }
        }
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_setView(window, view);
        sfRenderWindow_drawSprite(window, sbg, NULL);
        sfRenderWindow_drawSprite(window, splayer, NULL);
        sfRenderWindow_display(window);
    }
}

int main(int argc, char const *argv[])
{
    cell **screen;
    screen = init(50, 50);
    mk_win(screen);
    draw(screen, 50, 50);
    return 0;
}
