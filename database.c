#include "database.h"


void setup_tile(int tile_id, const char* icon, int text_color, int bg_color, bool bold)
{
    tile_t* t = &g_database.tiles[tile_id];
    t->icon = icon;
    t->text_color = text_color;
    t->bg_color = bg_color;
    t->bold = bold;
}


void init_database()
{
    setup_tile(TILE_AIR, "  ", COLOR_WHITE, COLOR_BLACK, false);
    setup_tile(TILE_WALL, "[]", COLOR_BLACK, COLOR_WHITE, false);
    setup_tile(TILE_PLAYER, "$@", COLOR_GREEN, COLOR_BLACK, true);
    setup_tile(TILE_ENEMY, "@!", COLOR_RED, COLOR_BLACK, true);

    g_database.enemies[ENEMY_CAT].name = "Cat";
    g_database.enemies[ENEMY_CAT].sprite.large_sprite = false;
    g_database.enemies[ENEMY_CAT].sprite.rows[0] = " ^-^   \\";
    g_database.enemies[ENEMY_CAT].sprite.rows[1] = "(O,O)_||";
    g_database.enemies[ENEMY_CAT].sprite.rows[2] = " | ___ |";
    g_database.enemies[ENEMY_CAT].sprite.rows[3] = " ||   ||";
    g_database.enemies[ENEMY_CAT].hp = 9;
    g_database.enemies[ENEMY_CAT].atk = 4;

    g_database.enemies[ENEMY_BAT].name = "Bat";
    g_database.enemies[ENEMY_BAT].sprite.large_sprite = false;
    g_database.enemies[ENEMY_BAT].sprite.rows[0] = "\\ ^__^ /";
    g_database.enemies[ENEMY_BAT].sprite.rows[1] = "=\\|..|/=";
    g_database.enemies[ENEMY_BAT].sprite.rows[2] = "\"=/vv\\=\"";
    g_database.enemies[ENEMY_BAT].sprite.rows[3] = " _\\^^/_ ";
    g_database.enemies[ENEMY_BAT].hp = 4;
    g_database.enemies[ENEMY_BAT].atk = 3;

    g_database.enemies[ENEMY_GUNTER].name = "Gunter";
    g_database.enemies[ENEMY_GUNTER].sprite.large_sprite = false;
    g_database.enemies[ENEMY_GUNTER].sprite.rows[0] = " ,4###\\ ";
    g_database.enemies[ENEMY_GUNTER].sprite.rows[1] = "|#/O  >0";
    g_database.enemies[ENEMY_GUNTER].sprite.rows[2] = "|v|    Y";
    g_database.enemies[ENEMY_GUNTER].sprite.rows[3] = "|#|_   |";
    g_database.enemies[ENEMY_GUNTER].hp = 12;
    g_database.enemies[ENEMY_GUNTER].atk = 6;

    g_database.enemies[ENEMY_ORGALORG].name = "Orgalorg";
    g_database.enemies[ENEMY_ORGALORG].sprite.large_sprite = true;
    g_database.enemies[ENEMY_ORGALORG].sprite.rows[0] = " ,4###\\  ,4###\\ ";
    g_database.enemies[ENEMY_ORGALORG].sprite.rows[1] = "|#/O  >0|#/O  >0";
    g_database.enemies[ENEMY_ORGALORG].sprite.rows[2] = "|v|    Y|v|    Y";
    g_database.enemies[ENEMY_ORGALORG].sprite.rows[3] = "|#|_   ||#|_   |";
    g_database.enemies[ENEMY_ORGALORG].sprite.rows[4] = " ,4###\\  ,4###\\ ";
    g_database.enemies[ENEMY_ORGALORG].sprite.rows[5] = "|#/O  >0|#/O  >0";
    g_database.enemies[ENEMY_ORGALORG].sprite.rows[6] = "|v|    Y|v|    Y";
    g_database.enemies[ENEMY_ORGALORG].sprite.rows[7] = "|#|_   ||#|_   |";
    g_database.enemies[ENEMY_ORGALORG].hp = 100;
    g_database.enemies[ENEMY_ORGALORG].atk = 20;
}


enemy_t* get_enemy(int enemy_id)
{
    return &g_database.enemies[enemy_id];
}


tile_t* get_tile(int tile_id)
{
    return &g_database.tiles[tile_id];
}
