#ifndef BATTLE_H
#define BATTLE_H

#include "database.h"


typedef struct {
    int id;
    int num1;
} battle_action_t;


typedef struct {
    enemy_t* enemy;
    int enemy_cur_hp;
    battle_action_t enemy_ba;

    int player_cur_hp;
    battle_action_t player_ba;

    int cur_battle_stage;
    const char* msg;
} battle_t;


int battle_update(battle_t* battle, char input);
void battle_render(battle_t* battle);


#endif // BATTLE_H
