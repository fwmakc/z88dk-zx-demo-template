#ifndef SCENE_H
#define SCENE_H

struct objectStructure
{
    int tileX;
    int tileY;
};

struct objectStructure *getPlayerCoords();

void drawScene(
    const char *scene
);

bool isTileWalkable(
    const char *scene,
    int tileX,
    int tileY
);

#endif
