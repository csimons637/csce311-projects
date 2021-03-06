#ifndef NAMED_SEMAPHORE_H_
#define NAMED_SEMAPHORE_H_
// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using std::cerr;
using std::endl;

class Semaphore {
 public:
  // "name_" is a null-terminated string, beginning with a '/'
  // "count" is the starting value for the semaphore
  explicit Semaphore(const char name[]) : name_(std::string(name)),
                    sem_ptr_(nullptr) {
  }

  explicit Semaphore(const std::string& name) : name_(name), sem_ptr_(nullptr) {
  }


  void Create(int count);

  inline void Destroy() {
    ::sem_unlink(name_.c_str());
  }

  void Open();

  inline void Down() {
     ::sem_wait(sem_ptr_);
  }

  inline void Up() {
     ::sem_post(sem_ptr_);
  }

 private:
  std::string name_;
  ::sem_t* sem_ptr_;
};

#endif  // NAMED_SEMAPHORE_H_
