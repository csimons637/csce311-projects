// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)
#ifndef SHM_SERVER_H_
#define SHM_SERVER_H_

#include <pthread.h>
#include <sys/mman.h>
#include <sys/unistd.h>
#include <cassert>
#include <cerrno>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "./named_semaphore.h"
#include "./shared_mem.h"

class Server {
 public:
  Server();

  void readMemBuffers();

  int writeResultsToMem(std::string reults);  // Writes search results to memory

  void searchForMatches();

  std::string GetStdoutFromCommand(std::string cmd);

 private:
  const char* shm_name_;

  char* search_str_;

  char* file_path_;

  SharedMemory *storage_;

  NamedSemaphore shm_semaphore_;
};

#endif  // SHM_SERVER_H_
