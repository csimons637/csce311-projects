#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_
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

class Semaphore {
 public:
  // "name" is a null-terminated string, beginning with a '/'
  // "count" is the starting value for the semaphore
  explicit Semaphore(const char name[]) : name(std::string(name)),
                    sem_ptr_(nullptr) {
  }

  explicit Semaphore(const std::string& name) : name(name), sem_ptr_(nullptr) {
  }


  void Create(int count);

  inline void Destroy() {
  }

  void Open();

  inline void Down() {
     ::sem_wait(sem_ptr_);
  }

  inline void Up() {
     ::sem_post(sem_ptr_);
  }

 private:
  std::string name;
  ::sem_t* sem_ptr_;
};

#endif  // SEMAPHORE_H_
