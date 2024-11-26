#include "game.h"
#include "gfx.h"
#include "scene.h"
#include "tiles.h"

struct objectStructure playerCoords = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

struct objectStructure *getPlayerCoords () {
    return playerCoords;
}

void drawScene (
    const char *scene
)
{
    // memcpy(currentLevel, Level1, sizeof(Level1));
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            char tile = scene[y * SCREEN_WIDTH + x];
            switch (tile)
            {
                case '#':
                    sp1_PrintAt(y, x, WALL_TILE_COLOR, (int) wallTile);
                    break;
                case '*':
                    sp1_PrintAt(y, x, DOT_TILE_COLOR, (int) dotTile);
                    break;
                case 'P':
                    playerCoords.tileX = (int) x;
                    playerCoords.tileY = (int) y;
                default:
                    sp1_PrintAt(y, x, EMPTY_TILE_COLOR, (int) emptyTile);
                    break;
            }
            // ++tile;
        }
    }
}

bool isTileWalkable(
    const char *scene,
    int tileX,
    int tileY
)
{
    char tile = scene[(tileY * 32) + tileX];
    switch (tile)
    {
        case '#':
            return false;

        case '*':
            sp1_PrintAt(tileY, tileX, EMPTY_TILE_COLOR, (int) emptyTile);
            // from sdcc/sound/bit.h
            bit_beepfx_fastcall(BEEPFX_GRAB_1);
            tile = ' ';

        default:
            return true;
    }

    return false;
}
