#include <fstream>
#include "../Egler.Test.hpp"

namespace Egler::IO
{
    class IOTest : public testing::Test
    { };

    TEST_F(IOTest, TestReadAllText)
    {
        char const * const fileName = "test_file.txt";
        char const * const msg = "hello !!\nand a good day to you !!";

        std::ofstream out(fileName);
        out << msg;
        out.close();

        std::string in = ReadAllText(fileName);
        ASSERT_STREQ(msg, in.c_str());
        remove("test_file.txt");
    }

    TEST_F(IOTest, TestReadAllTextThrowsOnNullFilename)
    {
        ASSERT_THROW(ReadAllText(nullptr), NullPtrException);
    }

    TEST_F(IOTest, TestReadAllTextThrowsOnNoFile)
    {
        ASSERT_THROW(ReadAllText("nonexistent"), FailureException);
    }
}