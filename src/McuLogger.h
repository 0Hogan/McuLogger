#ifndef MCU_LOGGER_LOG_H
#define MCU_LOGGER_LOG_H

// #pragma once

#include <cstdarg>

#include <Arduino.h>

class Logger
{
public:
    static inline void addOutputFile(char* file)
    {
        for (int i = 0; i < MAX_NUM_OF_OUTPUT_FILES; i++)
        {
            if (!outputFiles[i] || file == outputFiles[i])
            {
                outputFiles[i] = file;
            }
        }
    }

    static inline void addOutputStream(Print* stream)
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

    static inline void removeOutputStream(Print*& stream)
    {
        for (int i = 0; i < MAX_NUM_OF_OUTPUT_STREAMS; i++)
        {
            if (stream == outputStreams[i])
            {
                outputStreams[i] = nullptr;
            }
        }
    }

    static inline void Log(const char* file, const unsigned int line, const char* logType, ...)
    {
        for (int i = 0; i < MAX_NUM_OF_OUTPUT_STREAMS; i++)
        {
            if (!outputStreams[i])
            {
                break;
            }
            Print* stream = outputStreams[i];
            stream->print(file);
            stream->print(":");
            stream->print(line);
            stream->print("[");
            stream->print(logType);
            stream->print("]: ");

            char buffer[MAX_BUFFER_SIZE];

            va_list args;
            va_start (args, logType);
            char* msg = va_arg(args, char*);
            vsnprintf(buffer, MAX_BUFFER_SIZE, msg, args);
            va_end (args);
            stream->println(buffer);
        }
        for (const auto& file : outputFiles)
        {
            if (!file)
            {
                break;
            }
            /// @todo Need to figure out if I open and close the file, or just leave it open. If the former, I want the file name.
            ///       If the latter, I actually want the fstream object. I've a feeling I want the latter.
        }
    }
private:
    inline static const uint8_t MAX_NUM_OF_OUTPUT_FILES = 10;
    inline static const uint8_t MAX_NUM_OF_OUTPUT_STREAMS = 10;
    inline static const uint16_t MAX_BUFFER_SIZE = 512;
    inline static char* outputFiles[MAX_NUM_OF_OUTPUT_FILES];
    inline static Print* outputStreams[MAX_NUM_OF_OUTPUT_STREAMS];
};

/**
 * @brief Logs a debug message
 *
 */
#define LOG_DEBUG(msg...) (Logger::Log(__FILE__, __LINE__, "DEBUG", msg))

/**
 * @brief Logs an informational message.
 *
 */
#define LOG_INFO(msg...) (Logger::Log(__FILE__, __LINE__, "INFO", msg))

/**
 * @brief Logs a warning message.
 *
 */
#define LOG_WARNING(msg...) (Logger::Log(__FILE__, __LINE__, "WARN", msg))

/**
 * @brief Logs an error message.
 *
 */
#define LOG_ERROR(msg...) (Logger::Log(__FILE__, __LINE__, "ERROR", msg))

#endif