#include "game.h"


void init_game()
{
    srand(time(NULL));
    g_game.cur_game_state = GAME_STATE_OVERWORLD;
}


int get_current_game_state()
{
    return g_game.cur_game_state;
}


void start_battle()
{
    enemy_t* enemy = get_enemy(randint(NUM_ENEMIES));

    g_game.battle.msg = "";
    g_game.battle.enemy = enemy;
    g_game.battle.enemy_cur_hp = enemy->hp;
    g_game.battle.player_cur_hp = 10;
    g_game.cur_game_state = GAME_STATE_BATTLE;
}
