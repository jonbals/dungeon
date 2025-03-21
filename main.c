#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>


#define GRID_WIDTH 40
#define GRID_HEIGHT 24
#define GRID_SIZE (GRID_WIDTH * GRID_HEIGHT)

#define MAX_TILE_ACTIONS 1024


enum ENUM_GAME_STATES
{
    GAME_STATE_OVERWORLD,
    GAME_STATE_FIGHT,
    NUM_GAME_STATES
};


enum ENUM_TILES
{
    TILE_AIR,
    TILE_WALL,
    TILE_PLAYER,
    TILE_ENEMY,
    NUM_TILES
};


enum ENUM_ENEMIES
{
    ENEMY_CAT,
    ENEMY_BAT,
    ENEMY_GUNTER,
    ENEMY_ORGALORG,
    NUM_ENEMIES
};


enum ENUM_BATTLE_ACTIONS
{
    BA_ATTACK,
    BA_DEFEND,
    BA_RUN,
    NUM_BATTLE_ACTIONS
};


typedef struct {
    const char* icon;
} tile_t;


typedef struct {
    int data[GRID_SIZE];
} scene_t;


typedef struct {
    int tile_x;
    int tile_y;
    int move_x;
    int move_y;
    int change_tile_id;
} tile_action_t;


typedef struct {
    bool large_sprite;
    const char* row1;
    const char* row2;
    const char* row3;
    const char* row4;
    const char* row5;
    const char* row6;
    const char* row7;
    const char* row8;
} enemy_sprite_t;


typedef struct {
    const char* name;
    enemy_sprite_t sprite;
    int hp;
    int atk;
} enemy_t;


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
    const char* msg;
} battle_t;


void clearScene(scene_t* scene)
{
    for(int i = 0; i < GRID_SIZE; i++)
    {
        scene->data[i] = TILE_AIR;
    }
}


int getTileId(scene_t* scene, int x, int y)
{
    return scene->data[x + (GRID_WIDTH * y)];
}


void setTile(scene_t* scene, int x, int y, int tile_id)
{
    scene->data[x + (GRID_WIDTH * y)] = tile_id;
}


void renderScene(scene_t* scene, tile_t* tiles)
{
    for(int y = 0; y < GRID_HEIGHT; y++)
    {
        for(int x = 0; x < GRID_WIDTH; x++)
        {
            printf(tiles[getTileId(scene, x, y)].icon);
        }
        printf("\n");
    }
}


void makeRoom(scene_t* scene, int pos_x, int pos_y, int width, int height)
{
    for(int y = pos_y; y < pos_y + height; y++)
    {
        for(int x = pos_x; x < pos_x + width; x++)
        {
            if(x == pos_x || x == pos_x + width - 1 || y == pos_y || y == pos_y + height - 1)
            {
                setTile(scene, x, y, TILE_WALL);
            }
        }
    }
}


void makeHallway(scene_t* scene, int from_x, int from_y, int to_x, int to_y)
{
    int stage = 0;
    while(stage < 2)
    {
        int cur_x = from_x;
        int cur_y = from_y;

        int d_x = 0;
        int d_y = 0;

        while(cur_x != to_x || cur_y != to_y)
        {
            if(cur_x < to_x) {
                d_x = 1;
                d_y = 0;
            } else if(cur_x > to_x) {
                d_x = -1;
                d_y = 0;
            } else if(cur_y < to_y) {
                d_x = 0;
                d_y = 1;
            } else if(cur_y > to_y) {
                d_x = 0;
                d_y = -1;
            }

            if(stage == 0)
            {
                for(int i = -1; i <= 1; i++)
                {
                    for(int j = -1; j <= 1; j++)
                    {
                        setTile(scene, cur_x + i, cur_y + j, TILE_WALL);
                    }
                }
                if(cur_x == from_x && cur_y == from_y) {
                    setTile(scene, cur_x - d_x, cur_y - d_y, TILE_AIR);
                } else if((cur_x + d_x) == to_x && (cur_y + d_y) == to_y) {
                    setTile(scene, cur_x + d_x, cur_y + d_y, TILE_AIR);
                }
            }
            else if(stage == 1)
            {
                setTile(scene, cur_x, cur_y, TILE_AIR);
            }

            cur_x += d_x;
            cur_y += d_y;
        }
        stage++;
    }
}


void battle_update(battle_t* battle, char input)
{
    battle->msg = "";

    // player action
    switch(input)
    {
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
            return;
    }

    // enemy action
    battle->enemy_ba.id = BA_ATTACK;
    battle->enemy_ba.num1 = battle->enemy->atk;

    // evaluation
    switch(battle->player_ba.id)
    {
        case BA_ATTACK:
            battle->enemy_cur_hp -= battle->enemy_ba.id == BA_DEFEND ? 1 : battle->player_ba.num1;
            break;
        case BA_DEFEND:
            break;
        case BA_RUN:
            battle->msg = "Tried to run... but failed!";
            break;
    }

    switch(battle->enemy_ba.id)
    {
        case BA_ATTACK:
            battle->player_cur_hp -= battle->player_ba.id == BA_DEFEND ? 1 : battle->enemy_ba.num1;
            break;
        case BA_DEFEND:
            break;
        case BA_RUN:
            break;
    }
}


int main()
{
    int cur_game_state = GAME_STATE_OVERWORLD;

    // overworld stuff

    tile_t tiles[NUM_TILES];
    tiles[TILE_AIR].icon = "  ";
    tiles[TILE_WALL].icon = "[]";
    tiles[TILE_PLAYER].icon = "$@";
    tiles[TILE_ENEMY].icon = "#%%";

    scene_t scene;
    clearScene(&scene);

    makeRoom(&scene, 1, 1, 12, 8);
    makeRoom(&scene, 17, 15, 18, 6);
    makeRoom(&scene, 28, 5, 10, 8);
    makeRoom(&scene, 3, 10, 12, 10);
    makeHallway(&scene, 13, 4, 20, 15);
    makeHallway(&scene, 22, 8, 28, 8);
    makeHallway(&scene, 15, 12, 19, 12);

    setTile(&scene, 4, 4, TILE_PLAYER);
    setTile(&scene, 7, 5, TILE_ENEMY);

    // fight stuff

    enemy_t enemies[NUM_ENEMIES];

    enemies[ENEMY_CAT].name = "Cat";
    enemies[ENEMY_CAT].sprite.large_sprite = false;
    enemies[ENEMY_CAT].sprite.row1 = " ^-^   \\";
    enemies[ENEMY_CAT].sprite.row2 = "(O,O)_||";
    enemies[ENEMY_CAT].sprite.row3 = " | ___ |";
    enemies[ENEMY_CAT].sprite.row4 = " ||   ||";
    enemies[ENEMY_CAT].hp = 9;
    enemies[ENEMY_CAT].atk = 4;

    enemies[ENEMY_BAT].name = "Bat";
    enemies[ENEMY_BAT].sprite.large_sprite = false;
    enemies[ENEMY_BAT].sprite.row1 = "\\ ^__^ /";
    enemies[ENEMY_BAT].sprite.row2 = "=\\|..|/=";
    enemies[ENEMY_BAT].sprite.row3 = "\"=/vv\\=\"";
    enemies[ENEMY_BAT].sprite.row4 = " _\\^^/_ ";
    enemies[ENEMY_BAT].hp = 4;
    enemies[ENEMY_BAT].atk = 3;

    enemies[ENEMY_GUNTER].name = "Gunter";
    enemies[ENEMY_GUNTER].sprite.large_sprite = false;
    enemies[ENEMY_GUNTER].sprite.row1 = " ,4###\\ ";
    enemies[ENEMY_GUNTER].sprite.row2 = "|#/O  >0";
    enemies[ENEMY_GUNTER].sprite.row3 = "|v|    Y";
    enemies[ENEMY_GUNTER].sprite.row4 = "|#|_   |";
    enemies[ENEMY_GUNTER].hp = 12;
    enemies[ENEMY_GUNTER].atk = 6;

    enemies[ENEMY_ORGALORG].name = "Orgalorg";
    enemies[ENEMY_ORGALORG].sprite.large_sprite = true;
    enemies[ENEMY_ORGALORG].sprite.row1 = " ,4###\\  ,4###\\ ";
    enemies[ENEMY_ORGALORG].sprite.row2 = "|#/O  >0|#/O  >0";
    enemies[ENEMY_ORGALORG].sprite.row3 = "|v|    Y|v|    Y";
    enemies[ENEMY_ORGALORG].sprite.row4 = "|#|_   ||#|_   |";
    enemies[ENEMY_ORGALORG].sprite.row5 = " ,4###\\  ,4###\\ ";
    enemies[ENEMY_ORGALORG].sprite.row6 = "|#/O  >0|#/O  >0";
    enemies[ENEMY_ORGALORG].sprite.row7 = "|v|    Y|v|    Y";
    enemies[ENEMY_ORGALORG].sprite.row8 = "|#|_   ||#|_   |";
    enemies[ENEMY_ORGALORG].hp = 100;
    enemies[ENEMY_ORGALORG].atk = 20;

    battle_t battle;
    battle.msg = "";

    // game loop

    char input = ' ';
    while(input != 'q')
    {

        // update

        if(cur_game_state == GAME_STATE_OVERWORLD)
        {
            tile_action_t tile_actions[MAX_TILE_ACTIONS];
            int tile_action_counter = 0;
            for(int i = 0; i < MAX_TILE_ACTIONS; i++)
            {
                tile_actions[i].tile_x = -1;
                tile_actions[i].tile_y = -1;
                tile_actions[i].move_x = 0;
                tile_actions[i].move_y = 0;
                tile_actions[i].change_tile_id = -1;
            }

            int p_x = 0;
            int p_y = 0;

            switch(input)
            {
                case 'w':
                    p_y = -1;
                    break;
                case 'a':
                    p_x = -1;
                    break;
                case 's':
                    p_y = 1;
                    break;
                case 'd':
                    p_x = 1;
                    break;
            }

            for(int y = 0; y < GRID_HEIGHT; y++)
            {
                for(int x = 0; x < GRID_WIDTH; x++)
                {
                    if(getTileId(&scene, x, y) == TILE_PLAYER)
                    {
                        tile_actions[tile_action_counter].tile_x = x;
                        tile_actions[tile_action_counter].tile_y = y;
                        tile_actions[tile_action_counter].move_x = p_x;
                        tile_actions[tile_action_counter].move_y = p_y;
                    }
                }
            }

            for(int i = 0; i < MAX_TILE_ACTIONS; i++)
            {
                tile_action_t* ta = &tile_actions[i];
                if(ta->tile_x == -1 || ta->tile_y == -1)
                {
                    break;
                }

                if(ta->move_x != 0 || ta->move_y != 0)
                {
                    int tile_id = getTileId(&scene, ta->tile_x, ta->tile_y);
                    int new_x = ta->tile_x + ta->move_x;
                    int new_y = ta->tile_y + ta->move_y;

                    int colliding_tile_id = getTileId(&scene, new_x, new_y);
                    if(colliding_tile_id == TILE_WALL) continue;
                    else if(colliding_tile_id == TILE_ENEMY)
                    {
                        battle.enemy = &enemies[ENEMY_ORGALORG];
                        battle.enemy_cur_hp = battle.enemy->hp;
                        battle.player_cur_hp = 10;
                        cur_game_state = GAME_STATE_FIGHT;
                    }

                    setTile(&scene, new_x, new_y, tile_id);
                    setTile(&scene, ta->tile_x, ta->tile_y, TILE_AIR);
                }
            }
        }
        else if(cur_game_state == GAME_STATE_FIGHT)
        {
            battle_update(&battle, input);
        }

        // render
        if(cur_game_state == GAME_STATE_OVERWORLD)
        {
            renderScene(&scene, tiles);
        }
        else if(cur_game_state == GAME_STATE_FIGHT)
        {
            printf("\n\n");
            // enemy sprite
            if(battle.enemy->sprite.large_sprite)
            {
                printf(
                    "\t%s\n"
                    "\t%s\n"
                    "\t%s\n"
                    "\t%s\n"
                    "\t%s\n"
                    "\t%s\n"
                    "\t%s\n"
                    "\t%s\n",
                    battle.enemy->sprite.row1,
                    battle.enemy->sprite.row2,
                    battle.enemy->sprite.row3,
                    battle.enemy->sprite.row4,
                    battle.enemy->sprite.row5,
                    battle.enemy->sprite.row6,
                    battle.enemy->sprite.row7,
                    battle.enemy->sprite.row8
                );
            }
            else
            {
                printf(
                    "\t\t%s\n"
                    "\t\t%s\n"
                    "\t\t%s\n"
                    "\t\t%s\n",
                    battle.enemy->sprite.row1,
                    battle.enemy->sprite.row2,
                    battle.enemy->sprite.row3,
                    battle.enemy->sprite.row4
                );
            }

            printf(
               "\n"
               "\t\t%s  HP:%d\n"
               "\n\n"
               "\t\tYOUR HP:%d\n"
               "\n"
               "\t[A]ttack  [D]efend  [R]un\n"
               "\n%s\n",
               battle.enemy->name,
               battle.enemy_cur_hp,
               battle.player_cur_hp,
               battle.msg
            );

        }

        input = getch();
        system("cls");
    }

    return 0;
}
