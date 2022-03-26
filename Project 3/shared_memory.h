#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_
// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include <cstddef>

struct SharedMemory {
    const size_t kSearch_len = 512;  // max size for search string
    char search_str[kSearch_len];
    const size_t kPath_len = 512;  // max size text file path
    char file_path[kPath_len];
    const size_t kBuffer_length = (4096 << 2) - 4 - 512 - 4 - 512;
    // Four pages of memory, minus 1024 bytes for search string and file path
    // and minus 8 bytes for their respective sizes

    char buffer[kBuffer_length];
};


#endif  // SHARED_MEMORY_H_
