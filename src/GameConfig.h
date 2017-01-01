#ifndef GameConfig_H
#define GameConfig_H

class GameConfig {
    public:
        bool sound;  // enable sound or not

        bool init_stage;  // init stage or not

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
