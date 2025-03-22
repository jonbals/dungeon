#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

#include "enums.h"
#include "database.h"
#include "game.h"
#include "battle.h"


int main()
{
    init_database();
    init_game();

    scene_t* scene_ptr = &g_game.overworld.scene;

    clear_scene(scene_ptr);

    make_room(scene_ptr, 1, 1, 12, 8);
    make_room(scene_ptr, 17, 15, 18, 6);
    make_room(scene_ptr, 28, 5, 10, 8);
    make_room(scene_ptr, 3, 10, 12, 10);
    make_hallway(scene_ptr, 13, 4, 20, 15);
    make_hallway(scene_ptr, 22, 8, 28, 8);
    make_hallway(scene_ptr, 15, 12, 19, 12);

    set_tile(scene_ptr, 4, 4, TILE_PLAYER);
    set_tile(scene_ptr, 7, 5, TILE_ENEMY);

    // game loop
    char input = '\n';
    while(input != 'q') {

        // update
        int update_return_code;
        switch(get_current_game_state()) {
        case GAME_STATE_OVERWORLD:
            update_return_code = overworld_update(&g_game.overworld, input);
            break;
        case GAME_STATE_BATTLE:
            update_return_code = battle_update(&g_game.battle, input);
            break;
        }

        // render
        if(update_return_code == 0 || input == '\n') {
            system("cls");
            //printf("\e[1;1H\e[2J");
            switch(get_current_game_state()) {
            case GAME_STATE_OVERWORLD:
                overworld_render(&g_game.overworld);
                break;
            case GAME_STATE_BATTLE:
                battle_render(&g_game.battle);
                break;
            }
        }

        input = getch();
    }

    return 0;
}
