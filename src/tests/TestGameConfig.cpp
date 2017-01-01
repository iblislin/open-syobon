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
