#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_
// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include <cstddef>

struct SharedMemory {
    size_t buffer_length;
    char buffer[1];
};


#endif  // SHARED_MEMORY_H_
