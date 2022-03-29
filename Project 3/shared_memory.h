#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_
// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include <cstddef>

struct SharedMemory {
    char search_str[512];
    char file_path[512];

    char buffer[(4096 << 2) - 4 - 512 - 4 - 512];
    // Four pages of memory, minus 1024 bytes for search string and file path
    // and minus 8 bytes for their respective sizes
};


#endif  // SHARED_MEMORY_H_
