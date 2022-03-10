#ifndef UDS_CLIENT_H_
#define UDS_CLIENT_H_
// Copyright 2022 Charles Simons
// Written for Project 2 - CSCE 311 @ U of SC
// Modified from existing code by J. Lewis
// (instructor for CSCE 311, Spring 2022)

// Header file for Unix Domain Socket Client

#include "UDS.h"
#include <string>
using std::cout;
using std::cin;
using std::cerr;
using std::clog;
using std::endl;

class DomClntSock : public UnixDomSock {
 public:
  using UnixDomSock::UnixDomSock;
  const char *file;
  std::string file_name = file;
  const char *search;
  std::string search_term = search;

  void getFileName(const char *file_name) {
      file = file_name;
  }

  void getSearchTerm(const char *search_string) {
      search = search_string;
  }

  void RunClnt() {
      int socket_filedes;  // Socket file descriptor (no name)
      socket_filedes = socket(AF_UNIX, SOCK_STREAM, 0);
      if (socket_filedes < 0) {                   //
      cerr << strerror(errno) << endl;            // Error if socket_filedes
      exit(-1);                                   // doesn't init as it should
    }

    // Connect to Existing Server Socket
    int success = connect(socket_filedes,  // pointer to scok_addrr_,
                                           // but cast as sockaddr pointer
        reinterpret_cast<const sockaddr*>(&sock_addr_), sizeof(sock_addr_));
                                           // sizeof must be known to prevent
                                           // mismatch between parent and child
    if (success < 0) {
    cerr << strerror(errno) << endl;            //
                                                // Error if socket doesn't
                                                // connect properly
    exit(-1);
    }
    clog << "Connected to Server\n" << endl;

    // Write File Name to Server
    ssize_t fBytes_written = write(socket_filedes, file, sizeof(file_name));
    clog << "File Path Sent: " << file << endl;

    // Write Query to Server
    ssize_t sBytes_written = write(socket_filedes, search, sizeof(search_term));
    clog << "Search Query Sent: " << search << '\n' << endl;

    // Read Result from Server
    const size_t kServ_read = 64;
    char result[kServ_read];
    clog << "Results Received from Server" << endl;
    ssize_t sBytes_read = read(socket_filedes, result, kServ_read);
    std::string results = result;
    clog << results << endl;

    clog << '\n' << "Total Received: " << sBytes_read << " bytes" << endl;
  }
};

#endif  // UDS_CLIENT_H_
