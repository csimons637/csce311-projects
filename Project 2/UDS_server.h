#ifndef UDS_SERVER_H_
#define UDS_SERVER_H_
// Copyright 2022 Charles Simons
// Written for Project 2 - CSCE 311 @ U of SC
// Modified from existing code by J. Lewis
// (instructor for CSCE 311, Spring 2022)

// Header file for Unix Domain Socket Server

#include "UDS.h"
#include <string>
using std::ifstream;
using std::cout;
using std::cin;
using std::cerr;
using std::clog;
using std::endl;

class DomServSock : public UnixDomSock {
 public:
  using UnixDomSock::UnixDomSock;
  size_t max_client_connects = get_nprocs_conf();  // maximum clients allowed
  const char *search_res;

  void RunServ() const {
    int socket_filedes;      // Socket file descriptor (no name)
    int client_req_filedes;  // Socket file descriptor for
                             // client connection request

    // Socket Creation
    socket_filedes = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_filedes < 0) {                       //
        cerr << strerror(errno) << endl;            // Error if socket_filedes
        exit(-1);                                   // doesn't init as it should
    }
    clog << "Server Started" << endl
         << "Max Clients: " << max_client_connects << endl;

    // Socket Binding
    unlink(socket_path_.c_str());  // Deletes file, if it exists
    int success = bind(socket_filedes,  // pointer to sock_addr_,
                                        // but cast as a sockaddr pointer
        reinterpret_cast<const sockaddr*>(&sock_addr_), sizeof(sock_addr_));
                                        // sizeof must be known to prevent
                                        // mismatch between parent and child
    if (success < 0) {
        cerr << strerror(errno) << endl;            //
                                                    // Error if socket doesn't
                                                    // bind properly
        exit(-1);
    }

    // Await Client Connection(s)
    success = listen(socket_filedes, max_client_connects);
     if (success < 0) {
        cerr << strerror(errno) << endl;  //
                                                    // Error if socket listen
                                                    // doesn't happen properly
        exit(-1);
    }

    const size_t kRead_buff_size = 32;  // 64 bytes of buffer space for reading
    char read_buff[kRead_buff_size];  // read buffer
    int bytes_read;  // number of bytes read into the buffer
    while (true) {  // one socket per client (if threaded)
        client_req_filedes = accept(socket_filedes, nullptr, nullptr);
        if (client_req_filedes  < 0) {              //
        cerr << strerror(errno) << endl;  // Error if client specifies
        continue;                                   // wrong socket name
      }

      clog << "Client Connected\n" << endl;

      // Find Client Specified File
      ifstream search_file;  // file stream in
      const size_t kFile_read = 32;
      char file_read[kFile_read];  // file read buffer
      int fBytes_read;  // num bytes read for file path
      fBytes_read = read(client_req_filedes, file_read, kFile_read);
      search_file.open(file_read);
      if (search_file.fail()) {
        //   clog << file_read << endl;
          clog << "Invalid File" << endl;
          exit(-1);
      }
      clog << "Path: " << file_read << endl;

      // Data Reception from Client
      bytes_read = read(client_req_filedes, read_buff, kRead_buff_size);
      clog << "Search Term: " << read_buff << '\n' << endl;

      // Search File for Client Request
      clog << "Sending Results to Client" << endl;
      ssize_t tBytes_written;
      ssize_t bytes_written;  // bytes sent
      std::string search = read_buff;
      std::string line;
      std::string results;
      bool found_term = false;
      while (getline(search_file, line)) {
        if (line.find(search) != std::string::npos) {
          bytes_written = write(client_req_filedes, line.c_str(),
                                sizeof(line));
          clog << "Results: " << line << endl;
          found_term = true;
          break;
        }
      }

      if (!found_term) {
        std::string not_found = "\"" + search + "\"" + " was not found";
        bytes_written = write(client_req_filedes, not_found.c_str(),
                              sizeof(not_found));
      }

      clog << '\n' << "Total Sent: " << sizeof(line) << " bytes" << endl;
    }
  }
};

#endif  // UDS_SERVER_H_
