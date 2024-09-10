#include "pch.h"
#include "LoggerStrategy.h"
#include "Logger.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "TimedFileLogger.h"
#include "Parser.h"
#include "CompareFormat.h"

class MemoryLeakDetector {
public:


    MemoryLeakDetector() {
        _CrtMemCheckpoint(&memState_);
    }

    ~MemoryLeakDetector() {
        _CrtMemState stateNow, stateDiff;
        _CrtMemCheckpoint(&stateNow);
        int diffResult = _CrtMemDifference(&stateDiff, &memState_, &stateNow);
        if (diffResult)
            reportFailure(stateDiff.lSizes[1]);
    }
private:
    void reportFailure(size_t unfreedBytes) {
        FAIL() << "Memory leak of " << unfreedBytes << " byte(s) detected.";
    }
    _CrtMemState memState_;
};


TEST(Console, LogMessage) {
    MemoryLeakDetector leakDetector;

    std::shared_ptr<LoggerStrategy> log = std::make_shared<ConsoleLogger>();
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(log);

    logger->logMessage("Hello, world!");
}

TEST(SimpleFile, LogMessageEmpty) {
    MemoryLeakDetector leakDetector;

    std::string fileName = "SimpleLogEmpty.txt";
    std::string message = "";

    std::shared_ptr<LoggerStrategy> log = std::make_shared<FileLogger>(fileName);
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(log);
    logger->logMessage(message);

    std::ifstream is{ fileName };
    Parser parser{};

    parser.read(is);
    std::vector<std::string> data = parser.getLines();

    EXPECT_EQ(data.size(), 1);
    EXPECT_EQ(message, data[0]);
}

TEST(SimpleFile, LogMessageOneLine) {
    MemoryLeakDetector leakDetector;

    std::string fileName = "SimpleLog.txt";
    std::string message = "Hello, world!";

    std::shared_ptr<LoggerStrategy> log = std::make_shared<FileLogger>(fileName);
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(log);
    logger->logMessage(message);

    std::ifstream is{fileName};
    Parser parser{};

    parser.read(is);
    std::vector<std::string> data = parser.getLines();

    EXPECT_EQ(data.size(), 1);
    EXPECT_EQ(message, data[0]);
}

TEST(SimpleFile, LogMessageManyLine) {
    MemoryLeakDetector leakDetector;

    std::string fileName = "SimpleLog.txt";
    std::string message = "Hello, world!";
    std::string message2 = "I am here";
    std::string message3 = "Test";

    std::shared_ptr<LoggerStrategy> log = std::make_shared<FileLogger>(fileName);
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(log);
    logger->logMessage(message);
    logger->logMessage(message2);
    logger->logMessage(message3);

    std::ifstream is{ fileName };
    Parser parser{};

    parser.read(is);
    std::vector<std::string> data = parser.getLines();

    EXPECT_EQ(data.size(), 3);
    EXPECT_EQ(message, data[0]);
    EXPECT_EQ(message2, data[1]);
    EXPECT_EQ(message3, data[2]);
}

TEST(TimedFileLogger, LogMessageOneLine) {
    MemoryLeakDetector leakDetector;

    std::string fileName = "TimeFileLog.txt";
    std::string message = "Hello, world!";

    std::shared_ptr<LoggerStrategy> log = std::make_shared<TimedFileLogger>(fileName);
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(log);
    logger->logMessage(message);

    std::ifstream is{ fileName };
    Parser parser{};

    parser.read(is);
    std::vector<std::string> data = parser.getLines();

    std::vector<std::string> words = getWords(data[0], ' ');
    std::string str = words[2] + ' ' + words[3];

    EXPECT_EQ(data.size(), 1);
    EXPECT_EQ(message, str);

    EXPECT_TRUE(compareFormat(data[0]));
}

TEST(TimedFileLogger, LogMessageManyLine) {
    MemoryLeakDetector leakDetector;

    std::string fileName = "TimeFileLog.txt";
    std::string message = "Hello, world!";
    std::string message2 = "Test";

    std::shared_ptr<LoggerStrategy> log = std::make_shared<TimedFileLogger>(fileName);
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(log);
    logger->logMessage(message);
    logger->logMessage(message2);

    std::ifstream is{ fileName };
    Parser parser{};

    parser.read(is);
    std::vector<std::string> data = parser.getLines();

    std::vector<std::string> words = getWords(data[0], ' ');
    std::string str = words[2] + ' ' + words[3];

    EXPECT_EQ(data.size(), 2);
    EXPECT_EQ(message, str);

    EXPECT_TRUE(compareFormat(data[0]));

    words = getWords(data[1], ' ');
    str = words[2];

    EXPECT_EQ(message2, str);

    EXPECT_TRUE(compareFormat(data[1]));
}

TEST(TimedFileLogger, LogMessageEmpty) {
    MemoryLeakDetector leakDetector;

    std::string fileName = "TimeFileLogEmpty.txt";
    std::string message = "";

    std::shared_ptr<LoggerStrategy> log = std::make_shared<TimedFileLogger>(fileName);
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(log);
    logger->logMessage(message);

    std::ifstream is{ fileName };
    Parser parser{};

    parser.read(is);
    std::vector<std::string> data = parser.getLines();

    std::vector<std::string> words = getWords(data[0], ' ');

    EXPECT_EQ(data.size(), 1);

    EXPECT_TRUE(compareFormat(data[0]));
}

TEST(SetStrategy, LogMessage) {
    MemoryLeakDetector leakDetector;

    std::string message = "new Hello world!";

    std::shared_ptr<LoggerStrategy> log = std::make_shared<FileLogger>("SimpleLog2.txt");
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(log);
    logger->logMessage(message);

    std::ifstream is{ "SimpleLog2.txt" };
    Parser parser{};

    parser.read(is);
    std::vector<std::string> data = parser.getLines();

    EXPECT_EQ(data.size(), 1);
    EXPECT_EQ(message, data[0]);

    is.close();

    std::shared_ptr<LoggerStrategy> log2 = std::make_shared<TimedFileLogger>("TimeLog2.txt");
    logger->setStrategy(log2);
    logger->logMessage(message);

    is.open("TimeLog2.txt");

    Parser parser2{};

    parser2.read(is);
    std::vector<std::string> data2 = parser2.getLines();

    std::vector<std::string> words = getWords(data2[0], ' ');
    std::string str = words[2] + ' ' + words[3] + ' ' + words[4];

    EXPECT_EQ(data2.size(), 1);
    EXPECT_EQ(message, str);

    EXPECT_TRUE(compareFormat(data2[0]));
}