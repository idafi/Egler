#include "../Egler.Test.hpp"

namespace Egler::Logging
{
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
        ASSERT_THROW(log.Write(LogLevel::Note, nullptr), NullPtrException);
    }

    TEST_F(LogTest, TestHandlesNoLogs)
    {
        ASSERT_NO_THROW(log.Write(LogLevel::Note, msg));
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

    TEST_F(LogTest, TestMacros)
    {
        Log::AddDefaultLogger(&logger, LogLevel::Debug);

        EXPECT_CALL(logger, Write(LogLevel::Debug, testing::HasSubstr("hello !!")));
        LogDebug("hello !!");

        EXPECT_CALL(logger, Write(LogLevel::Note, testing::HasSubstr("hello !!")));
        LogNote("hello !!");

        EXPECT_CALL(logger, Write(LogLevel::Warning, testing::HasSubstr("hello !!")));
        LogWarning("hello !!");

        EXPECT_CALL(logger, Write(LogLevel::Error, testing::HasSubstr("hello !!")));
        LogError("hello !!");

        EXPECT_CALL(logger, Write(LogLevel::Failure, testing::HasSubstr("hello !!")));
        LogFailure("hello !!");
    }
}