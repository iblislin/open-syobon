#ifndef GameConfig_H
#define GameConfig_H

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

    Player() {}

    void reset_lives()
    {
        this->lives = 2;
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

    int fps = 30;  // frame per second

    GameConfig() {}
};

// BGM
#define BGM_FIELD    1
#define BGM_DUNGEON  2
#define BGM_STAR4    3
#define BGM_CASTLE   4
#define BGM_PUYO     5

#endif  /* ifndef GameConfig_H */
