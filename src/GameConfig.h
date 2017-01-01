#ifndef GameConfig_H
#define GameConfig_H

class StageInfo
{
    public:
        unsigned int series;
        unsigned int level;
        unsigned int sub_level;

        StageInfo() :
            series(1),
            level(1),
            sub_level(0)
        {
        }

        void set(unsigned int series, unsigned int level, unsigned int sub_level)
        {
            this->series = series;
            this->level = level;
            this->sub_level = sub_level;
        }

        bool check(unsigned int series, unsigned int level, unsigned int sub_level){
            if (this->series != series)
                return false;
            else if (this->level != level)
                return false;
            else if (this->sub_level != sub_level)
                return false;
            return true;
        }
};

class GameConfig
{
    public:
        bool sound;  // enable sound or not

        // stage
        bool init_stage;  // init stage or not
        StageInfo stage_info;

        bool endFlag;

        int fps;  // frame per second

        GameConfig() :
            sound(true),
            init_stage(true),
            endFlag(false),
            fps(30)
        {
        }
};

// BGM
#define BGM_FIELD    1
#define BGM_DUNGEON  2
#define BGM_STAR4    3
#define BGM_CASTLE   4
#define BGM_PUYO     5

#endif  /* ifndef GameConfig_H */
