// Copyright 2022 Charles Simons
// Written for Project 4 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#ifndef CLIENT_H_
#define CLIENT_H_

// Starts with one command line argument (the file path)
// Sends file path to server (via socket)
// Quad-thread and change lowercase char with uppercase version
// (1/4 of file per thread)
// If server indicates file opening failure, write: "INVALID FILE"
// (std::cerr and return 1)
// Terminate nominatively with code 0

#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "./UDS.h"

// Number of threads
#define THREAD_COUNT 4

static char *address;  // mem address
static char *path;

class ClientSocket : UnixDomSock {
 public:
  using UnixDomSock::UnixDomSock;

  void RunClient(char *file_path) {
      int sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
      if (sock_fd < 0) {
          std::cerr << strerror(errno) << std::endl;
          exit(errno);
      }

      // Connect to server socket
      std::cout << "Connecting To Server" << std::endl;
      int success = connect(sock_fd,
        reinterpret_cast<const sockaddr*>(&sock_addr_), sizeof(sock_addr_));
      if (success < 0) {
          std::cerr << strerror(errno) << std::endl;
          exit(errno);
      }

      // Send file path to server
      std::cout << "Sending File Path to Server" << std::endl;
      write(sock_fd, file_path, sizeof(file_path));

      // Open file for thread processing
      int fd = open(file_path, O_RDWR | O_CREAT, 0777);
      if (fd < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
      }
      struct stat file_info;
      size_t file_size = stat(file_path, &file_info);
      char *addr = reinterpret_cast<char *>(mmap(NULL, file_size,
                PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
      address = addr;
      if (addr == MAP_FAILED) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
      }

      // Create four threads
      pthread_t threads[THREAD_COUNT];
      int thread_args[THREAD_COUNT];
      int result;
      int i;
      for (i = 0; i < THREAD_COUNT; i++) {
          thread_args[i] = i;
          result = pthread_create(&threads[i], nullptr,
                            caseChange, &thread_args[i]);
          assert(!result);
      }

      // Wait for threads to complete
      for (i = 0; i < THREAD_COUNT; i++) {
          result = pthread_join(threads[i], nullptr);
          assert(!result);
      }

      // Nominative exit status
      exit(0);
  }

  static void *caseChange(void *ptr) {
      // id of thread; used for indexing in file
      int ind = *reinterpret_cast<int *>(ptr);
      struct stat file_info;
      int file_len = stat(path, &file_info);
      // Increment through 1/4 of file and change all lowercase to uppercase
      // File can be treated like an array of char, so
      // for char c in file, use: putchar (toupper(c))
      if (ind == 0) {  // thread 1; first 1/4 of file
        for (int i = 0; i < (1/4)*file_len; i++) {
            char c = address[i];
            putchar(toupper(c));
            address[i] = c;
        }
      } else if (ind == 1) {  // thread 2; second 1/4 of file
        for (int i = (1/4)*file_len; i < (2/4)*file_len; i++) {
            char c = address[i];
            putchar(toupper(c));
            address[i] = c;
        }

      } else if (ind == 2) {  // thread 3; third 1/4 of file
        for (int i = (2/4)*file_len; i < (3/4)*file_len; i++) {
            char c = address[i];
            putchar(toupper(c));
            address[i] = c;
        }
      } else if (ind == 3) {  // thread 4; final 1/4 of file
        for (int i = (3/4)*file_len; i < file_len; i++) {
            char c = address[i];
            putchar(toupper(c));
            address[i] = c;
        }
      }
      return nullptr;
  }
};

#endif  // CLIENT_H_
