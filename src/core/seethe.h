//https://github.com/jnguyen1098/seethe/blob/master/seethe.h

#ifndef SEETHE_H
#define SEETHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default level */
#ifndef LOG_LEVEL
#define LOG_LEVEL   LEVEL_DEBUG
#endif

/* Colour customization */
#define DEBUG_COLOUR    ""
#define INFO_COLOUR     "\x1B[36m"
#define NOTICE_COLOUR   "\x1B[32;1m"
#define WARNING_COLOUR  "\x1B[33m"
#define ERROR_COLOUR    "\x1B[31m"
#define CRITICAL_COLOUR "\x1B[41;1m"

/* Do not change this. */
#define RESET_COLOUR    "\x1B[0m"

/* Formatting prefs. */
#define MSG_ENDING      "\n"
#define TIME_FORMAT     "%T"
#define BORDER          "-"

/* Enabler flags */
#define DISPLAY_COLOUR  1
#define DISPLAY_TIME    1
#define DISPLAY_LEVEL   1
#define DISPLAY_FUNC    0
#define DISPLAY_FILE    0
#define DISPLAY_LINE    0
#define DISPLAY_BORDER  1
#define DISPLAY_MESSAGE 1
#define DISPLAY_ENDING  1
#define DISPLAY_RESET   1

/* Log to screen */
#define emit_log(colour, level, file, func, line, ...) do {                         \
                                                                                    \
    /* notate the time */                                                           \
    time_t raw_time = time(NULL);                                                   \
    struct tm time_info;                                                            \
    char time_buffer[80];                                                           \
                                                                                    \
    if (localtime_s(&time_info, &raw_time) == 0) {                                  \
        strftime(time_buffer, sizeof(time_buffer), TIME_FORMAT, &time_info);        \
    }                                                                               \
    else {                                                                          \
        fprintf(stderr, "Failed to get local time.\n");                             \
    }                                                                               \
                                                                                    \
    /* enable colour */                                                             \
    printf("%s", DISPLAY_COLOUR ? colour : "");                                     \
                                                                                    \
    /* display the time */                                                          \
    printf("%s%s", DISPLAY_TIME ? time_buffer : "", DISPLAY_TIME ? " " : "");       \
                                                                                    \
    /* display the level */                                                         \
    printf("%10s%s", DISPLAY_LEVEL ? level : "", DISPLAY_LEVEL ? " " : "");         \
                                                                                    \
    /* display the function doing the logging */                                    \
    printf("%s%s", DISPLAY_FUNC ? func : "", DISPLAY_FUNC ? " " : "");              \
                                                                                    \
    /* display the file and/or the line number */                                   \
    printf(                                                                         \
        "%s%s%s%.d%s%s",                                                            \
        DISPLAY_FUNC && (DISPLAY_FILE || DISPLAY_LINE) ? "(" : "",                  \
        DISPLAY_FILE ? file : "",                                                   \
        DISPLAY_FILE && DISPLAY_LINE ? ":" : "",                                    \
        DISPLAY_LINE ? line : 0,                                                    \
        DISPLAY_FUNC && (DISPLAY_FILE || DISPLAY_LINE) ? ") " : "",                 \
        !DISPLAY_FUNC && (DISPLAY_FILE || DISPLAY_LINE) ? " " : ""                  \
    );                                                                              \
                                                                                    \
    /* display message border */                                                    \
    printf("%s%s", DISPLAY_BORDER ? BORDER : "", DISPLAY_BORDER ? " " : "");        \
                                                                                    \
    /* display the callee's message */                                              \
    if (DISPLAY_MESSAGE) printf(__VA_ARGS__);                                       \
                                                                                    \
    /* add the message ending (usually '\n') */                                     \
    printf("%s", DISPLAY_ENDING ? MSG_ENDING : "");                                 \
                                                                                    \
    /* reset the colour */                                                          \
    printf("%s", DISPLAY_RESET ? RESET_COLOUR : "");                                \
                                                                                    \
} while (0)

/* Level enum */
#define LEVEL_DEBUG       0
#define LEVEL_INFO        1
#define LEVEL_NOTICE      2
#define LEVEL_WARNING     3
#define LEVEL_ERROR       4
#define LEVEL_CRITICAL    5
#define LEVEL_SILENT      6

/* DEBUG LOG */
#define log_debug(...) do {                                                             \
    if (LOG_LEVEL == LEVEL_DEBUG) {                                                       \
        emit_log(                                                                   \
            DEBUG_COLOUR, "[DEBUG]", __FILE__, __func__, __LINE__, __VA_ARGS__      \
        );                                                                          \
    }                                                                               \
} while (0)

/* INFO LOG */
#define log_info(...) do {                                                              \
    if (LOG_LEVEL <= LEVEL_INFO) {                                                        \
        emit_log(                                                                   \
            INFO_COLOUR, "[INFO]", __FILE__, __func__, __LINE__, __VA_ARGS__        \
        );                                                                          \
    }                                                                               \
} while (0)

/* NOTICE LOG */
#define log_notice(...) do {                                                            \
    if (LOG_LEVEL <= LEVEL_NOTICE) {                                                      \
        emit_log(                                                                   \
            NOTICE_COLOUR, "[NOTICE]", __FILE__, __func__, __LINE__, __VA_ARGS__    \
        );                                                                          \
    }                                                                               \
} while (0)

/* WARNING LOG */
#define log_warning(...) do {                                                           \
    if (LOG_LEVEL <= LEVEL_WARNING) {                                                     \
        emit_log(                                                                   \
            WARNING_COLOUR, "[WARNING]", __FILE__, __func__, __LINE__, __VA_ARGS__  \
        );                                                                          \
    }                                                                               \
} while (0)

/* ERROR LOG */
#define log_error(...) do {                                                             \
    if (LOG_LEVEL <= LEVEL_ERROR) {                                                       \
        emit_log(                                                                   \
            ERROR_COLOUR, "[ERROR]", __FILE__, __func__, __LINE__, __VA_ARGS__      \
        );                                                                          \
    }                                                                               \
} while (0)

/* CRITICAL LOG */
#define log_critical(...) do {                                                          \
    if (LOG_LEVEL <= LEVEL_CRITICAL) {                                                    \
        emit_log(                                                                   \
            CRITICAL_COLOUR, "[CRITICAL]", __FILE__, __func__, __LINE__, __VA_ARGS__\
        );                                                                          \
    }                                                                               \
} while (0)

#endif // seethe.h