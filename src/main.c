#include "game.h"
#include "gfx.h"
#include "levels.h"
#include "scene.h"
#include "sprites.h"
#include "tiles.h"

struct spriteStructure spriteBox = { 0, 0, 0, 0, 0, INK_BLACK | PAPER_CYAN };
struct spriteStructure spritePlayer = { 0, 0, 0, 0, 0, PLAYER_SPRITE_COLOR };

void main ()
{
    initGfxEngine();

    drawScene(Level1);

    updateGfx();

    struct objectStructure playerCoords = { 0, 0 };
    playerCoords = *getPlayerCoords();

    spriteBox.s = createSprite(spriteBox.color);
    spritePlayer.s = createSprite(spritePlayer.color);

    spriteBox.dx = 1;

    placeSprite(spriteBox.s, boxSpriteState[0], 4, 8);
    placeSprite(spritePlayer.s, playerSpriteState[0], playerCoords.tileY, playerCoords.tileX);

    while (1)
    {
        moveSprite(
            spriteBox.s,
            boxSpriteState[spriteBox.state / 10],
            spriteBox.dy,
            spriteBox.dx
        );

        spriteBox.state = (spriteBox.state > 39) ? 0 : ++spriteBox.state;

        if (spriteBox.s->row > 21)
        {
            spriteBox.dy = -spriteBox.dy;
        }
        if (spriteBox.s->col > 29)
        {
            spriteBox.dx = -spriteBox.dx;
        }

   		if (in_key_pressed(IN_KEY_SCANCODE_x))
        {
            break;
   		}

        if (in_key_pressed(IN_KEY_SCANCODE_z))
        {
            isTileWalkable(Level1, spritePlayer.s->col, spritePlayer.s->row);
        }

        if (in_key_pressed(IN_KEY_SCANCODE_o))
        {
            moveSprite(spritePlayer.s, playerSpriteState[1], 0, -1);
        }
        else if (in_key_pressed(IN_KEY_SCANCODE_p))
        {
            moveSprite(spritePlayer.s, playerSpriteState[0], 0, 1);
        }
        else if (in_key_pressed(IN_KEY_SCANCODE_q))
        {
            moveSprite(spritePlayer.s, playerSpriteState[2], -1, 0);
        }
        else if (in_key_pressed(IN_KEY_SCANCODE_a))
        {
            moveSprite(spritePlayer.s, playerSpriteState[3], 1, 0);
        }

        sp1_UpdateNow();
    }

    // all sprites dead or key pressed

    zx_border(INK_RED);
    in_pause(500);
    zx_border(INK_BLACK);
}
