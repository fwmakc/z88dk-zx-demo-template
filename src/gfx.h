#ifndef GFX_H
#define GFX_H

struct spriteStructure
{
    struct sp1_ss   *s;      // sprite handle returned by sp1_CreateSpr()
    int             dx;     // signed horizontal speed in pixels
    int             dy;     // signed vertical speed in pixels
    int             state;  // state as sprite number in spritesheet
    int             frame;  // frame as animation number
    unsigned char   color;
};

void initGfxEngine();

void updateGfx();

void colorizeSprites (
    unsigned int frame,
    struct sp1_cs *c
);

struct sp1_ss *createSprite (
    unsigned char color
);

void placeSprite (
    struct sp1_ss *s,
    unsigned char *spriteState,
    int tileY,
    int tileX
);

void moveSprite (
    struct sp1_ss *s,
    unsigned char *spriteState,
    int dirY,
    int dirX
);

#endif
