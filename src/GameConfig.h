#include "Stage.h"


#ifndef GameConfig_H
#define GameConfig_H

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


class Pair
{
    /*
     * The (x, y) pair
     */

public:
    int x = 0;
    int y = 0;

    Pair()
    {
    }

    Pair(int x, int y)
    {
        this->set(x, y);
    }

    void set(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};


class Location : public Pair
{
};


class Acce : public Pair
{
    /* acceleration */
};


class Player
{
public:
    int lives = 2; // nokori ?
    int hp = 1; // health point, hp > 0 denote alive
    Location loc;
    Acce acce;

    Player() {}

    void reset_lives()
    {
        this->lives = 2;
    }

    bool is_alive() const
    {
        if (this->hp > 0)
            return true;
        return false;
    }
};


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
