#include "battle.h"


int battle_update(battle_t* battle, char input)
{
    battle->msg = "";

    // player action
    switch(input) {
    case 'a': // attack
        battle->player_ba.id = BA_ATTACK;
        battle->player_ba.num1 = 3;
        break;

    case 'd': // defend
        battle->player_ba.id = BA_DEFEND;
        break;

    case 'r': // run
        battle->player_ba.id = BA_RUN;
        break;

    case '\r': // continue
        battle->enemy_cur_hp = -1000;
        break;

    default:
        return 1;
    }

    // enemy action
    battle->enemy_ba.id = BA_ATTACK;
    battle->enemy_ba.num1 = battle->enemy->atk;

    // evaluation
    switch(battle->player_ba.id) {
    case BA_ATTACK:
        battle->enemy_cur_hp -= battle->enemy_ba.id == BA_DEFEND ? 1 : battle->player_ba.num1;
        break;
    case BA_DEFEND:
        break;
    case BA_RUN:
        battle->msg = "Tried to run... but failed!";
        break;
    }

    switch(battle->enemy_ba.id) {
    case BA_ATTACK:
        battle->player_cur_hp -= battle->player_ba.id == BA_DEFEND ? 1 : battle->enemy_ba.num1;
        break;
    case BA_DEFEND:
        break;
    case BA_RUN:
        break;
    }

    return 0;
}


void battle_render(battle_t* battle)
{
    printf("\n\n");

    // enemy sprite
    if(battle->enemy->sprite.large_sprite) {
        for(int i = 0; i < 8; i++) {
            printf("\t%s\n", battle->enemy->sprite.rows[i]);
        }
    } else {
        for(int i = 0; i < 4; i++) {
            printf("\t\t%s\n", battle->enemy->sprite.rows[i]);
        }
    }

    printf(
        "\n"
        "\t\t%s  HP:%d\n"
        "\n\n"
        "\t\tYOUR HP:%d\n"
        "\n"
        "\t[A]ttack  [D]efend  [R]un\n"
        "\n%s\n",
        battle->enemy->name,
        battle->enemy_cur_hp,
        battle->player_cur_hp,
        battle->msg
    );
}
