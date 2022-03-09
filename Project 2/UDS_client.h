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

  void getFile(const char *file_name) {
      file = file_name;
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

    // Write File Name to Server
    ssize_t fBytes_written = write(socket_filedes, file, sizeof(file));

    // Write Query to Server
    const char kEOT = '\004';  // end-of-transmission
    const char kUS = '\037';  // universal separator
    ssize_t kWrite_buff_size = 64;  // 64 bytes of buffer space for writing
    char write_buff[kWrite_buff_size];  // write buffer
    ssize_t bytes_written;  // number of bytes written from buffer

    while (true) {
        if (sizeof(write_buff) <= kWrite_buff_size) {
            write_buff[sizeof(write_buff) + 1] = kEOT;
        }

        cin.getline(write_buff, kWrite_buff_size);  // reads 64 bytes
                                                    // & stores in write buffer
        while (cin.gcount() > 0) {
            if (cin.gcount() == kWrite_buff_size - 1 && cin.fail())
                cin.clear();
            bytes_written = write(socket_filedes, write_buff, cin.gcount());
            cout << "Sent " << bytes_written << " bytes" << endl;
            if (bytes_written == 0) {
                clog << "Server dropped connection" << endl;
                break;
            } else if (bytes_written < 0) {
                cerr << strerror(errno) << endl;
                exit(-1);
            }

            cin.getline(write_buff, kWrite_buff_size);
        }
    }
  }
};

#endif  // UDS_CLIENT_H_
