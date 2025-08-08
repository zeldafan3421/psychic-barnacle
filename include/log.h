#pragma once

#include <print>
#include <format>
#include <vector>
#include <cstdio>
#include <stdexcept>
#include <exception>
#include <memory>
#include "raylib.h"

/**
 * @brief Wrap va_copy for raii
 * 
 */
struct va_list_guard {
    va_list ap;
    va_list_guard(va_list args)
    {
        va_copy(ap, args);
    }
    va_list_guard(const va_list_guard&) = delete;
    va_list_guard& operator=(const va_list_guard&) = delete;
    ~va_list_guard() { va_end(ap); }
};

static const char* GetMessagePreamble(int msgType)
{
    switch (msgType)
    {
        case LOG_INFO:  return "[INFO] :";
        case LOG_ERROR: return "[ERROR] :";
        case LOG_WARNING: return "[WARN] :";
        case LOG_DEBUG: return "[DEBUG] :";
        case LOG_FATAL: return "[FATAL] :";
        default: throw std::runtime_error("Invalid msgType.");
    }
}

/**
 * @brief CustomLog Design to be used as TraceLogCallback
 * 
 * @param msgType enum LogLevel (note: c style for raylib compatibility)
 * @param text Format Text 
 * @param args c style variadic args for raylib compatiblity
 * 
 * @exception runtime_error If failure occures runtime_error is thrown
 */
void CustomLog(int msgType, const char* text, va_list args)
{
    va_list_guard args_copy(args);

    const int logLength = std::vsnprintf(NULL, 0, text, args) + 1;

    if (logLength < 0) 
        throw std::runtime_error("Could not determine message length.");

    std::vector<char> message_buffer(logLength);

    std::vsnprintf(message_buffer.data(), message_buffer.size(), text, args_copy.ap);

    const char* preamble = GetMessagePreamble(msgType);
    
    if (msgType == LOG_FATAL)
        throw std::runtime_error(std::string(preamble) + " " + message_buffer.data());

    std::println("{} {}", preamble, message_buffer.data());
}