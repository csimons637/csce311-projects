#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_
// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include <cstddef>

struct SharedMemory {
    size_t buffer_size;
    char search_str[128];  // 128 bytes for search string
    char file_path[128];  // 128 bytes for file_path (overly generous)
    char buffer[1];  // size will expand later; c++ doesn't check bounding
};


#endif  // SHARED_MEMORY_H_
