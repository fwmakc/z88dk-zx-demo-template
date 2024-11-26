#include "game.h"
#include "gfx.h"
#include "tiles.h"

const struct sp1_Rect screen = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

// char currentLevel[SCREEN_WIDTH * SCREEN_HEIGHT];

unsigned char spriteColor;

void initGfxEngine ()
{
    zx_border(INK_BLACK);

    sp1_Initialize(
        SP1_IFLAG_MAKE_ROTTBL | // генерируем таблицы для попиксельного вывода
        SP1_IFLAG_OVERWRITE_TILES | // первые 256 тайлов - символы из шрифта ROM
        SP1_IFLAG_OVERWRITE_DFILE, // стандартный маппинг знакомест на экран
        EMPTY_TILE_COLOR, ' ' // заполняем экран пробелами белый на черном
    );
    // назначаем фоновый тайл на символ пробела
    sp1_TileEntry(' ', emptyTile);
}

void updateGfx ()
{
    // Запрашиваем перерисовку всего экрана
    sp1_Invalidate(&screen);
    sp1_UpdateNow();
}

void colorizeSprite (
    unsigned int frame,
    struct sp1_cs *c
)
{
    (void) frame;

    unsigned char cmask;
    cmask = SP1_AMASK_INK & SP1_AMASK_PAPER;

    c->attr_mask = cmask;
    c->attr = spriteColor;
}

struct sp1_ss *createSprite (
    unsigned char color
)
{
    struct sp1_ss *spr = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE,  3,  0,  0);

    sp1_AddColSpr(spr, SP1_DRAW_MASK2, 0, 48, 0);
    sp1_AddColSpr(spr, SP1_DRAW_MASK2RB, 0, 0, 0);

    spriteColor = color;
    sp1_IterateSprChar(spr, colorizeSprite);

    return spr;
}

void placeSprite (
    struct sp1_ss *s,
    unsigned char *spriteState,
    int tileY,
    int tileX
)
{
    sp1_MoveSprAbs(s, &screen, spriteState, tileY, tileX, 0, 0);
}

void moveSprite (
    struct sp1_ss *s,
    unsigned char *spriteState,
    int dirY,
    int dirX
)
{
    sp1_MoveSprRel(s, &screen, spriteState, 0, 0, dirY, dirX);
}
