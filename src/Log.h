/**
 * @file Log.h
 * @brief Credit where credit is due - most of this was taken from 
 *        https://stackoverflow.com/q/19415845, but some modifications were necessary to get it to
 *        work as desired on Arduino-style platforms and include different logging levels.
 */

#ifndef MCU_LOGGER_LOG_H
#define MCU_LOGGER_LOG_H

#include <Arduino.h>

// #include <cstdint>
// #include <utility>
// #include <ostream>
// #include <vector>
namespace Logger
{
    static const uint8_t MAX_NUM_OF_OUTPUT_FILES = 10;
    static const uint8_t MAX_NUM_OF_OUTPUT_STREAMS = 10;

    // #define LOG(msg) (Log(__FILE__, __LINE__, LogData<None>() << msg))


    static char* outputFiles[MAX_NUM_OF_OUTPUT_FILES] = {};
    static Print* outputStreams[MAX_NUM_OF_OUTPUT_STREAMS] = {};

    void addOutputFile(char* file)
    {
        for (int i = 0; i < MAX_NUM_OF_OUTPUT_FILES; i++)
        {
            if (!outputFiles[i] || file == outputFiles[i])
            {
                outputFiles[i] = file;
            }
        }
    }

    void addOutputStream(Print* stream)
    {
        for (int i = 0; i < MAX_NUM_OF_OUTPUT_STREAMS; i++)
        {
            if (!outputStreams[i] || stream == outputStreams[i])
            {
                outputStreams[i] = stream;
                break;
            }
        }
    }

    void removeOutputStream(Print* stream)
    {
        for (int i = 0; i < MAX_NUM_OF_OUTPUT_STREAMS; i++)
        {
            if (stream == outputStreams[i])
            {
                outputStreams[i] = nullptr;
            }
        }
    }

    /**
     * @brief 
     * 
     * @param file 
     * @param line 
     * @param logType 
     * @param msg
     * 
     * @todo Add a timestamp field/macro 
     */
    void Log(const char* file, const unsigned int line, const char* logType, const char* msg)
    {
        for (const auto& stream : outputStreams)
        {
            if (!stream)
            {
                break;
            }
            stream->printf("%s:%u [%s]: %s\n", file, line, logType, msg);
        }
        for (const auto& file : outputFiles)
        {
            if (!file)
            {
                break;
            }
            /// @todo Need to figure out if I open and close the file, or just leave it open. If the former, I want the file name.
            ///       If the latter, I actually want the fstream object.
        }
    }
}

/**
 * @brief Logs a debug message
 * 
 */
#define LOG_DEBUG(msg) (Logger::Log(__FILE__, __LINE__, "DEBUG", msg))

/**
 * @brief Logs an informational message.
 * 
 */
#define LOG_INFO(msg) (Logger::Log(__FILE__, __LINE__, "INFO", msg))

/**
 * @brief Logs a warning message.
 * 
 */
#define LOG_WARNING(msg) (Logger::Log(__FILE__, __LINE__, "WARN", msg))

/**
 * @brief Logs an error message.
 * 
 */
#define LOG_ERROR(msg) (Logger::Log(__FILE__, __LINE__, "ERROR", msg))


// #define WHERESTR "[FILE : %s, FUNC : %s, LINE : %d]: "
// #define WHEREARG __FILE__,__func__,__LINE__
// #define DEBUG(...)  fprintf(stderr, __VA_ARGS__)
// #define DEBUG_PRINT(_fmt, ...) DEBUG(WHERESTR _fmt, WHEREARG,__VA_ARGS__)

// class Logger
// {
// public:
//     Log(char* msg)
// };





// // Workaround GCC 4.7.2 not recognizing noinline attribute
// #ifndef NOINLINE_ATTRIBUTE
//   #ifdef __ICC
//     #define NOINLINE_ATTRIBUTE __attribute__(( noinline ))
//   #else
//     #define NOINLINE_ATTRIBUTE
//   #endif // __ICC
// #endif // NOINLINE_ATTRIBUTE


// static std::vector<Print*> logDestinations;

// template<typename List>
// void Log(const char* file, int line, 
//          LogData<List>&& data) NOINLINE_ATTRIBUTE
// {
//     std::cout << file << ":" << line << ": ";
//     output(std::cout, std::move(data.list));
//     std::cout << std::endl;
// }

// struct None { };

// template<typename List>
// struct LogData {
//     List list;
// };

// template<typename Begin, typename Value>
// constexpr LogData<std::pair<Begin&&, Value&&>> operator<<(LogData<Begin>&& begin, 
//                                                           Value&& value) noexcept
// {
//     return {{ std::forward<Begin>(begin.list), std::forward<Value>(value) }};
// }

// template<typename Begin, size_t n>
// constexpr LogData<std::pair<Begin&&, const char*>> operator<<(LogData<Begin>&& begin, 
//                                                               const char (&value)[n]) noexcept
// {
//     return {{ std::forward<Begin>(begin.list), value }};
// }

// typedef std::ostream& (*PfnManipulator)(std::ostream&);

// template<typename Begin>
// constexpr LogData<std::pair<Begin&&, PfnManipulator>> operator<<(LogData<Begin>&& begin, 
//                                                                  PfnManipulator value) noexcept
// {
//     return {{ std::forward<Begin>(begin.list), value }};
// }

// template <typename Begin, typename Last>
// void output(std::ostream& os, std::pair<Begin, Last>&& data)
// {
//     output(os, std::move(data.first));
//     os << data.second;
// }

// inline void output(std::ostream& os, None)
// { }

#endif