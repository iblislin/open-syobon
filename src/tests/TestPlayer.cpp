#include <UnitTest++/UnitTest++.h>

#include "../Player.h"


SUITE(PlayerTest)
{
    TEST(flip_pose)
    {
        Player p;
        auto expect_pose = !(p.pose);

        p.pose_interval = 42;
        p.move_trace = 50;
        p.flip_pose();

        CHECK_EQUAL(expect_pose, p.pose);
        CHECK_EQUAL(8, p.move_trace);
    }
}
