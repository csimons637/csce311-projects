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
#include "./UDS.h"

// Number of threads
#define THREAD_COUNT 4

static int file_position = 0;

class ClientSocket : UnixDomSock {
 public:
  using UnixDomSock::UnixDomSock;
  const char *file_path;

  void RunClient(const char file_path[]) {
      int sock_fd;
      sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
      if (sock_fd < 0) {
          std::cerr << strerror(errno) << std::endl;
          exit(-1);
      }

      // Connect to server socket
      int success = connect(sock_fd,
        reinterpret_cast<const sockaddr*>(&sock_addr_), sizeof(sock_addr_));
      if (success < 0) {
          std::cerr << strerror(errno) << std::endl;
          exit(-1);
      }

      // Send file path to server
      std::cout << "Sending File Path to Server" << std::endl;
      write(sock_fd, file_path, sizeof(file_path));

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
      // Increment through 1/4 of file and change all lowercase to uppercase
      // File can be treated like an array of char, so
      // for char c in file, use: putchar (toupper(c))
      // Then, increment file_position by 1/4 of file size
      return nullptr;  // Returns null after completing operation
  }
};

#endif  // CLIENT_H_
