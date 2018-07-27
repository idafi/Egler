#include "Egler.Test.hpp"

int main(int argc, char **argv)
{
    _set_error_mode(_OUT_TO_STDERR);

    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}