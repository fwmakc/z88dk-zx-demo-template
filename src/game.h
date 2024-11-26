#ifndef GAME_H
#define GAME_H

#include <input.h>
#include <stdlib.h>
#include <stdbool.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <sound.h>
#include <sound/bit.h>
#include <string.h>
#include <intrinsic.h>

#pragma output REGISTER_SP           = 0xd000    // place stack at $d000 at startup
#pragma output CRT_ENABLE_RESTART    = 1         // not returning to basic
#pragma output CRT_ENABLE_CLOSE      = 0         // do not close files on exit
#pragma output CLIB_EXIT_STACK_SIZE  = 0         // no exit stack
#pragma output CLIB_MALLOC_HEAP_SIZE = 5000      // malloc heap size (not sure what is needed exactly)
#pragma output CLIB_STDIO_HEAP_SIZE  = 0         // no memory needed to create file descriptors
#pragma output CLIB_FOPEN_MAX        = -1        // no allocated FILE structures, -1 for no file lists too
#pragma output CLIB_OPEN_MAX         = 0         // no fd table

#define SCREEN_WIDTH 32
#define SCREEN_HEIGHT 24

#endif
