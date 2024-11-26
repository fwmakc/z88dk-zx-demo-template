#ifndef SPRITES_H
#define SPRITES_H

#include "sprites/box.h"
#include "sprites/player.h"

unsigned char *boxSpriteState[4] = {
    boxPhase0,
    boxPhase1,
    boxPhase2,
    boxPhase3
};

unsigned char *playerSpriteState[4] = {
    playerRight,
    playerLeft,
    playerUp,
    playerDown
};

// Table Holding Movement Data for Each Sprite

#endif
