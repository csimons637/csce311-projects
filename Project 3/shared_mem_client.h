#ifndef SHARED_MEM_CLIENT_H_
#define SHARED_MEM_CLIENT_H_
// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
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

#include "./shared_memory.h"
#include "./named_semaphore.h"

using std::string;
using std::cout;
using std::clog;
using std::cerr;
using std::endl;

// Client should create shared memory

class SharedMemClient {
 public:
  SharedMemClient(const char mem_name[], const char sem_name[]);

  ~SharedMemClient();

  // send to server

 private:
  string mem_name_;  // name of shared memory file

  SharedMemory *storage;  // shared memory file

  Semaphore mem_sem_;  // memory semaphore
};

#endif  // SHARED_MEM_CLIENT_H_
