#ifndef GameConfig_H
#define GameConfig_H

#include "Player.h"
#include "Stage.h"

// BGM
#define BGM_FIELD    1
#define BGM_DUNGEON  2
#define BGM_STAR4    3
#define BGM_CASTLE   4
#define BGM_PUYO     5

// scene
#define SCENE_TITLE       1
#define SCENE_STAGE       2
#define SCENE_LIVE_PANEL  3
#define SCENE_STAFF_ROLL  4


class GameConfig
{
public:
    bool sound = true;  // enable sound or not

    // stage
    bool init_stage = true;  // init stage or not
    StageInfo stage_info;

    Player player;

    bool endFlag = false;

    int cur_scene = SCENE_TITLE;  // current scene

    GameConfig() {}
};

#endif  /* ifndef GameConfig_H */
