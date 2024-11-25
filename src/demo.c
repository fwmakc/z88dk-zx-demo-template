// By szeliga @ worldofspectrum.org forums
// while running press any key to reset screen

#include <input.h>
#include <sound.h>
#include <stdlib.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <intrinsic.h>
#include "sprites.h"

#pragma output REGISTER_SP           = 0xd000    // place stack at $d000 at startup
#pragma output CRT_ENABLE_RESTART    = 1         // not returning to basic
#pragma output CRT_ENABLE_CLOSE      = 0         // do not close files on exit
#pragma output CLIB_EXIT_STACK_SIZE  = 0         // no exit stack
#pragma output CLIB_MALLOC_HEAP_SIZE = 5000      // malloc heap size (not sure what is needed exactly)
#pragma output CLIB_STDIO_HEAP_SIZE  = 0         // no memory needed to create file descriptors
#pragma output CLIB_FOPEN_MAX        = -1        // no allocated FILE structures, -1 for no file lists too
#pragma output CLIB_OPEN_MAX         = 0         // no fd table

// Clipping Rectangle for Sprites
 
struct sp1_Rect cr = {0, 0, 32, 24};            // rectangle covering the full screen
 
// Table Holding Movement Data for Each Sprite
 
struct sprentry
{
   struct sp1_ss  	*s;                     // sprite handle returned by sp1_CreateSpr()
   char           	dx;                     // signed horizontal speed in pixels
   char           	dy;                     // signed vertical speed in pixels
   unsigned char     state;                  // frame state (MSS)
};

// здесь мы задаем направление движения и скорость
// 0, 0, 1, 0 - вниз
// 0, 0,-1, 0 - вверх
// 0, 1, 0, 0 - вправо
// 0,-1, 0, 0 - влево
struct sprentry sprtbl = {0,1,1,0};
 
// Спрайт для фона
unsigned char hash[] = {
	0b11111110,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11101111,
	0b11111111,
	0b11111111,
	0b11111111
};
 
// Callback Function to Colour Sprites Using sp1_IterateSprChar()
 
unsigned char colour;
unsigned char cmask;
 
void colourSpr(unsigned int count, struct sp1_cs *c)
{
   c->attr_mask = cmask;
   c->attr = colour;
}

main()
{
   static unsigned char i, j;
   static struct sp1_ss *s;
   static struct sprentry *se;
 
   // Initialize SP1.LIB
 
   zx_border(INK_BLACK);
 
   sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE, INK_BLACK | PAPER_WHITE, ' ');
   sp1_TileEntry(' ', hash);   // redefine graphic associated with space character
 
   sp1_Invalidate(&cr);        // invalidate entire screen so that it is all initially drawn
   sp1_UpdateNow();            // draw screen area managed by sp1 now
 
   // Создаем спрайт и колоризируем его
 
   s = sprtbl.s = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE,  3,  0,  0);
   sp1_AddColSpr(s, SP1_DRAW_MASK2, 0, 48, 0);
   sp1_AddColSpr(s, SP1_DRAW_MASK2RB, 0, 0, 0);

   colour = INK_BLACK | PAPER_CYAN;
   cmask = SP1_AMASK_INK & SP1_AMASK_PAPER;

   sp1_IterateSprChar(s, colourSpr);
 
   // Main Loop
 
   // Move Sprite to Initial Location
   // sp1_MoveSprAbs(sprtbl[i].s, &cr, sprite01, (rand() & 0x0f) + 4, (rand() & 0x0f) + 8, 0, 4);
   // 4 - знакоместо по x
   // 8 - знакоместо по y
   sp1_MoveSprAbs(sprtbl.s, &cr, boxSpriteState[0], 4, 8, 0, 4);
   sprtbl.state = 0;

   while (1)
   {
      sp1_UpdateNow();

      // move sprite
      sp1_MoveSprRel(
         sprtbl.s,
         &cr,
         boxSpriteState[sprtbl.state / 10],
         0,
         0,
         sprtbl.dy,
         sprtbl.dx
      );
      sprtbl.state = (sprtbl.state > 39) ? 0 : ++sprtbl.state;

      // if sprite went off screen reverse direction
      if (s->row > 21) {
         sprtbl.dy = - sprtbl.dy;
      }
      if (s->col > 29) {
         sprtbl.dx = - sprtbl.dx;
      }
   }

   // all sprites dead or key pressed

   zx_border(INK_RED);

   in_pause(500);

   zx_border(INK_BLACK);
}
