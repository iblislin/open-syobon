#include <UnitTest++/UnitTest++.h>

#include "../GameConfig.h"


SUITE(StageInfoTest)
{
    TEST(is_random)
    {
        StageInfo s;

        s.set(0, 0, 0);
        CHECK_EQUAL(true, s.is_random());

        s.set(1, 0, 0);
        CHECK_EQUAL(false, s.is_random());

        s.set(0, 1, 0);
        CHECK_EQUAL(false, s.is_random());

        s.set(0, 0, 1);
        CHECK_EQUAL(false, s.is_random());
    }
}


SUITE(Player)
{
    TEST(is_alive)
    {
        Player p;

        CHECK_EQUAL(1, p.hp);

        p.hp = 0;
        CHECK_EQUAL(false, p.is_alive());

        p.hp = -1;
        CHECK_EQUAL(false, p.is_alive());

        p.hp = 42;
        CHECK_EQUAL(true, p.is_alive());

        p.hp = 1;
        CHECK_EQUAL(true, p.is_alive());
    }
}


SUITE(Pair)
{
    TEST(set)
    {
        Pair p;

        p.set(-4, 3);
        CHECK_EQUAL(-4, p.x);
        CHECK_EQUAL(3,  p.y);

        p.set(0, 42);
        CHECK_EQUAL(0,  p.x);
        CHECK_EQUAL(42, p.y);
    }
}
