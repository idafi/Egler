#include "../Egler.Test.hpp"

class MockLogger : public ILogger
{
    public:
        MOCK_METHOD2(Write, void(LogLevel level, const char * const msg));
};

class LogTest : public testing::Test
{
    protected:
        const char * const msg = "hello !!";
        MockLogger logger;
        Log log;
};

TEST_F(LogTest, TestAddLogger)
{
    log.AddLogger(&logger, LogLevel::Debug);

    EXPECT_CALL(logger, Write(LogLevel::Note, testing::HasSubstr(msg)));
    log.Write(LogLevel::Note, msg);
}

TEST_F(LogTest, TestDoesNotLogBelowMinLevel)
{
    log.AddLogger(&logger, LogLevel::Warning);

    EXPECT_CALL(logger, Write(testing::_, testing::_)).Times(0);
    log.Write(LogLevel::Note, msg);
}

TEST_F(LogTest, TestRemoveLogger)
{
    log.AddLogger(&logger, LogLevel::Debug);
    log.RemoveLogger(&logger);

    EXPECT_CALL(logger, Write(testing::_, testing::_)).Times(0);
    log.Write(LogLevel::Note, msg);
}

TEST_F(LogTest, TestChangeMinLevel)
{
    log.AddLogger(&logger, LogLevel::Warning);
    log.ChangeMinLevel(&logger, LogLevel::Debug);

    EXPECT_CALL(logger, Write(LogLevel::Note, testing::HasSubstr(msg)));
    log.Write(LogLevel::Note, msg);
}

TEST_F(LogTest, TestWriteFailsOnNullMsg)
{
    ASSERT_DEATH(log.Write(LogLevel::Note, nullptr), ".*");
}

TEST_F(LogTest, TestHandlesNoLogs)
{
    ASSERT_NO_FATAL_FAILURE(log.Write(LogLevel::Note, msg));
}

TEST_F(LogTest, TestDefaultLogger)
{
    Log::AddDefaultLogger(&logger, LogLevel::Warning);

    EXPECT_CALL(logger, Write(LogLevel::Warning, testing::HasSubstr(msg)));
    Log::WriteToDefault(LogLevel::Warning, msg);

    EXPECT_CALL(logger, Write(testing::_, testing::_)).Times(0);
    Log::WriteToDefault(LogLevel::Note, msg);

    Log::ChangeDefaultMinLevel(&logger, LogLevel::Note);
    EXPECT_CALL(logger, Write(LogLevel::Note, testing::HasSubstr(msg)));
    Log::WriteToDefault(LogLevel::Note, msg);

    Log::RemoveDefaultLogger(&logger);
    EXPECT_CALL(logger, Write(testing::_, testing::_)).Times(0);
    Log::WriteToDefault(LogLevel::Warning, msg);
}