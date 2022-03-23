#ifndef SHRMEM_CLIENT_H_
#define SHRMEM_CLIENT_H_
// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Modified from code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::clog;
using std::endl;

const char mem_name[] = "shared_memory1";  // name of shared memory file

// Open shared memory


#endif  // SHRMEM_CLIENT_H_
