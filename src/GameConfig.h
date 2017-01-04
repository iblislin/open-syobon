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


class Location
{
public:
    int x = 0;
    int y = 0;

    Location()
    {
    }

    Location(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

class StageInfo
{
public:
    unsigned int series    = 1;
    unsigned int level     = 1;
    unsigned int sub_level = 0;

    bool changed = false;

    StageInfo()
    {
        /*
         * (0, 0, 0) -> a random generated stage
         */
    }

    void set(unsigned int series, unsigned int level, unsigned int sub_level)
    {
        this->series = series;
        this->level = level;
        this->sub_level = sub_level;
        this->changed = true;
    }

    bool check(unsigned int series, unsigned int level,
               unsigned int sub_level) const
    {
        if (this->series != series)
            return false;
        else if (this->level != level)
            return false;
        else if (this->sub_level != sub_level)
            return false;
        return true;
    }

    bool is_random() const
    {
        if (!(this->series || this->level || this-> sub_level))
            return true;
        return false;
    }
};


class Player
{
public:
    int lives = 2; // nokori ?
    int hp = 1; // health point, hp > 0 denote alive
    Location loc;

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
