#ifndef PLAYER_H
#define PLAYER_H

#define ORIE_LEFT  0
#define ORIE_RIGHT 1


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

    /* pose related vars */
    int pose = 0; // for walking animation, value should be 0 or 1
    unsigned int pose_interval = 2000;  // the pose changing interval
    /* the acumulative movement counter, for changing pose */
    unsigned int move_trace = 0;

    /* is the player on the ground ? */
    bool ground = false;

    /* orientation: ORIE_LEFT or ORIE_RIGHT */
    unsigned short int orie = ORIE_RIGHT;

    Player() {}

    void reset_lives();

    bool is_alive() const;

    void flip_pose();

    void render();
};
#endif  /* ifndef PLAYER_H */
