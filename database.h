#ifndef DATABASE_H
#define DATABASE_H

#include "stdbool.h"

#include "enums.h"


typedef struct {
    const char* icon; // 2 chars wide
    int text_color;
    int bg_color;
    bool bold;
} tile_t;


typedef struct {
    bool large_sprite;
    const char* rows[8];
} enemy_sprite_t;


typedef struct {
    const char* name;
    enemy_sprite_t sprite;
    int hp;
    int atk;
} enemy_t;


typedef struct {
    tile_t tiles[NUM_TILES];
    enemy_t enemies[NUM_ENEMIES];
} database_t;

database_t g_database;

void database_setup_tile(int tile_id, char icon, int color);
void init_database();
tile_t* get_tile(int tile_id);
enemy_t* get_enemy(int enemy_id);


#endif // DATABASE_H
