// Copyright 2022 Charles Simons
// Written for Project 4 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#ifndef SERVER_H_
#define SERVER_H_

// Prints opening message: "SERVER STARTED"
// Receives file path from client (via socket)
// then writes: "CLIENT REQUEST RECEIVED"

// Create a semaphore to control access to file-backed mem
// Lock semaphore and attempt to access it
// (effectively blocking until client unlocks the semaphore)

// Opens the file and writes: "/tOPENING: <file_path>"
// If opening fails, indicate failure to client (via socket)
// Otherwise, map file to shared mem and write: "\tFILE MAPPED TO SHARED MEMORY"
// Close file when finished, and write: "\tFILE CLOSED"

// Wait for further client activity

#include "./UDS.h"

class ServerSocket : public UnixDomSock {
 public:
  using UnixDomSock::UnixDomSock;
  size_t max_client_connects = get_nprocs_conf();  // max client connections

  void RunServer() const {
      int sock_fd;
      int client_req_fd;

      // Socket creation
      if ((sock_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
          std::cerr << strerror(errno) << std::endl;
          exit(-1);
      }
    std::cout << "Client Request Received" << std::endl
              << "Maximum CLient Connections: "
              << max_client_connects << std::endl;

    unlink(socket_path_.c_str());  // Deletes, if it already exists

    // Bind the server socket
    if (bind(sock_fd, reinterpret_cast<const sockaddr*>(&sock_addr_),
            sizeof(sock_addr_)) < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(-1);
    }

    // Listen for clients
    // If max num of clients, refuse connection
    if (listen(sock_fd, max_client_connects) < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(-1);
    }

    // Read buffer for server socket
    const size_t kRead = 64;
    char read_buffer[kRead];

    // Accept client request
    while (true) {
        client_req_fd = accept(sock_fd, nullptr, nullptr);
        if (client_req_fd < 0) {
            std::cerr << strerror(errno) << std::endl;
            continue;
        }

        std::cout << "Client Connected" << std::endl;
    }

    // Read file path from client
    read(client_req_fd, read_buffer, kRead);

    // Open file into shared memory
  }
};













#endif  // SERVER_H_
