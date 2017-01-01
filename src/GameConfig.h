#ifndef GameConfig_H
#define GameConfig_H

class GameConfig {
    public:
        bool sound;  // enable sound or not

        bool endFlag;

        int fps;  // frame per second

        GameConfig() :
            sound(true),
            endFlag(false),
            fps(30)
        {
        }
};

#endif  /* ifndef GameConfig_H */
