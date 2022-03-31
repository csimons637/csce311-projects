#ifndef SHARED_MEM_SERVER_H_
#define SHARED_MEM_SERVER_H_
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
#include <vector>

#include "./shared_memory.h"
#include "./named_semaphore.h"

using std::string;
using std::cout;
using std::clog;
using std::cerr;
using std::endl;
using std::vector;

// Server manages semaphore

class SharedMemServer {
 public:
  explicit SharedMemServer(const char sem_name[]);

  ~SharedMemServer();

  int ToFromClient();  // comms to and from client (shared mem)

  static void* searchFile(void* ptr);

 private:
  string mem_name_;  // name of shared memory file

  string mem_sem_;  // name of semaphore

  SharedMemory *storage;  // shared memory file
};

#endif  // SHARED_MEM_SERVER_H_
