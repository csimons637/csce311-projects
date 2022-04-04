// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)
#ifndef SHM_CLIENT_H_
#define SHM_CLIENT_H_

#include <sys/mman.h>
#include <sys/unistd.h>
#include <cassert>
#include <cerrno>
#include <csignal>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

#include "./named_semaphore.h"
#include "./shared_mem.h"


class Client {
 public:
  Client(const char* search_str, const char* file_name);

  // Destroys memory access semaphore
  ~Client();

  void writeFileToMem();

  void readFromMem();

 private:
  const char* search_str_;

  const char* file_path_;

  const char* shm_name_;

  SharedMemory *storage_;

  NamedSemaphore shm_semaphore_;
};

#endif  // SHM_CLIENT_H_
