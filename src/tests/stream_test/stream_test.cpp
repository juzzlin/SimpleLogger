// MIT License
//
// Copyright (c) 2020 Jussi Lind <jussi.lind@iki.fi>
//
// https://github.com/juzzlin/SimpleLogger
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "../../simple_logger.hpp"

// Don't compile asserts away
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <cstdlib>
#include <sstream>

namespace juzzlin::StreamTest {

void assertMessage(std::stringstream & stream, std::string message, std::string timestampSeparator)
{
    assert(stream.str().find(message) != std::string::npos);
    assert(stream.str().find(timestampSeparator) != std::string::npos);
}

void assertNotMessage(std::stringstream & stream, std::string message, std::string timestampSeparator)
{
    assert(stream.str().find(message) == std::string::npos);
    assert(stream.str().find(timestampSeparator) == std::string::npos);
}

void testFatal_noneLoggingLevel_shouldNotPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    L::setLoggingLevel(L::Level::None);
    std::stringstream ss;
    L::setStream(L::Level::Fatal, ss);
    L().fatal() << message;
    assertNotMessage(ss, message, timestampSeparator);
}

void testFatal_fatalLoggingLevel_shouldPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    std::stringstream ss;
    L::setStream(L::Level::Fatal, ss);
    L::setLoggingLevel(L::Level::Fatal);
    L().fatal() << message;
    assertMessage(ss, message, timestampSeparator);
}

void testError_higherLoggingLevel_shouldNotPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    L::setLoggingLevel(L::Level::Fatal);
    std::stringstream ss;
    L::setStream(L::Level::Error, ss);
    L().error() << message;
    assertNotMessage(ss, message, timestampSeparator);
}

void testError_errorLoggingLevel_shouldPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    std::stringstream ss;
    L::setStream(L::Level::Error, ss);
    L::setLoggingLevel(L::Level::Error);
    L().error() << message;
    assertMessage(ss, message, timestampSeparator);
}

void testWarning_higherLoggingLevel_shouldNotPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    L::setLoggingLevel(L::Level::Error);
    std::stringstream ss;
    L::setStream(L::Level::Warning, ss);
    L().warning() << message;
    assertNotMessage(ss, message, timestampSeparator);
}

void testWarning_warningLoggingLevel_shouldPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    std::stringstream ss;
    L::setStream(L::Level::Warning, ss);
    L::setLoggingLevel(L::Level::Warning);
    L().warning() << message;
    assertMessage(ss, message, timestampSeparator);
}

void testInfo_higherLoggingLevel_shouldNotPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    L::setLoggingLevel(L::Level::Warning);
    std::stringstream ss;
    L::setStream(L::Level::Info, ss);
    L().info() << message;
    assertNotMessage(ss, message, timestampSeparator);
}

void testInfo_infoLoggingLevel_shouldPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    std::stringstream ss;
    L::setStream(L::Level::Info, ss);
    L::setLoggingLevel(L::Level::Info);
    L().info() << message;
    assertMessage(ss, message, timestampSeparator);
}

void testDebug_higherLoggingLevel_shouldNotPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    L::setLoggingLevel(L::Level::Info);
    std::stringstream ss;
    L::setStream(L::Level::Debug, ss);
    L().debug() << message;
    assertNotMessage(ss, message, timestampSeparator);
}

void testDebug_debugLoggingLevel_shouldPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    std::stringstream ss;
    L::setStream(L::Level::Debug, ss);
    L::setLoggingLevel(L::Level::Debug);
    L().debug() << message;
    assertMessage(ss, message, timestampSeparator);
}

void testTrace_higherLoggingLevel_shouldNotPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    L::setLoggingLevel(L::Level::Debug);
    std::stringstream ss;
    L::setStream(L::Level::Trace, ss);
    L().trace() << message;
    assertNotMessage(ss, message, timestampSeparator);
}

void testTrace_traceLoggingLevel_shouldPrintMessage(const std::string & message, const std::string & timestampSeparator)
{
    std::stringstream ss;
    L::setStream(L::Level::Trace, ss);
    L::setLoggingLevel(L::Level::Trace);
    L().trace() << message;
    assertMessage(ss, message, timestampSeparator);
}

void initializeLogger(const std::string & timestampSeparator)
{
    L::enableEchoMode(true);
    L::setTimestampMode(L::TimestampMode::DateTime, timestampSeparator);
}

} // namespace juzzlin::StreamTest

int main(int, char **)
{
    const std::string timestampSeparator = " ## ";
    juzzlin::StreamTest::initializeLogger(timestampSeparator);

    const std::string message = "Hello, world!";

    juzzlin::StreamTest::testFatal_noneLoggingLevel_shouldNotPrintMessage(message, timestampSeparator);

    juzzlin::StreamTest::testFatal_fatalLoggingLevel_shouldPrintMessage(message, timestampSeparator);

    juzzlin::StreamTest::testError_higherLoggingLevel_shouldNotPrintMessage(message, timestampSeparator);

    juzzlin::StreamTest::testError_errorLoggingLevel_shouldPrintMessage(message, timestampSeparator);

    juzzlin::StreamTest::testWarning_higherLoggingLevel_shouldNotPrintMessage(message, timestampSeparator);

    juzzlin::StreamTest::testWarning_warningLoggingLevel_shouldPrintMessage(message, timestampSeparator);

    juzzlin::StreamTest::testInfo_higherLoggingLevel_shouldNotPrintMessage(message, timestampSeparator);

    juzzlin::StreamTest::testInfo_infoLoggingLevel_shouldPrintMessage(message, timestampSeparator);

    juzzlin::StreamTest::testDebug_higherLoggingLevel_shouldNotPrintMessage(message, timestampSeparator);

    juzzlin::StreamTest::testDebug_debugLoggingLevel_shouldPrintMessage(message, timestampSeparator);

    juzzlin::StreamTest::testTrace_higherLoggingLevel_shouldNotPrintMessage(message, timestampSeparator);

    juzzlin::StreamTest::testTrace_traceLoggingLevel_shouldPrintMessage(message, timestampSeparator);

    return EXIT_SUCCESS;
}
