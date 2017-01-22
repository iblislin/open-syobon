#include "Player.h"


void Player::reset_lives()
{
    this->lives = 2;
}


bool Player::is_alive() const
{
    return (this->hp > 0);
}


void Player::flip_pose()
{
    if (this->move_trace < this->pose_interval)
        return;

    this->move_trace -= this->pose_interval;
    this->pose = !(this->pose);
}
