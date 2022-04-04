// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)
#ifndef SHARED_MEM_H_
#define SHARED_MEM_H_

#include <cstddef>

struct SharedMemory {
    size_t buffer_size;
    char search_str[128];  // 128 bytes for search string
    char buffer[1];  // Will be extended later,
                     // since c++ doesn't do bounds checking
};

#endif  // SHARED_MEM_H_
