#ifndef UDS_SERVER_H_
#define UDS_SERVER_H_
// Copyright 2022 Charles Simons
// Written for Project 2 - CSCE 311 @ U of SC
// Modified from existing code by J. Lewis
// (instructor for CSCE 311, Spring 2022)

// Header file for Unix Domain Socket Server

#include <./UDS.h>
using std::cout;
using std::cerr;
using std::endl;

class DomServSock : public UnixDomSock {
 public:
  using ::UnixDomSock::UnixDomSock;

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
    size_t max_client_connects = get_nprocs_conf();  // maximum clients allowed
    success = listen(socket_filedes, max_client_connects);
     if (success < 0) {
        cerr << strerror(errno) << endl;  //
                                                    // Error if socket listen
                                                    // doesn't happen properly
        exit(-1);
    }

    const size_t kRead_buff_size = 32;  // 32 bytes of buffer space for reading
    char read_buff[kRead_buff_size];  // read buffer
    int bytes_read;  // number of bytes read into the buffer
    while (true) {  // one socket per client (if threaded)
        client_req_filedes = accept(socket_filedes, nullptr, nullptr);
        if (client_req_filedes  < 0) {              //
        cerr << strerror(errno) << endl;  // Error if client specifies
        continue;                                   // wrong socket name
      }

      cout << "Client connectd" << endl;

      // Data Reception from Client
      bytes_read = read(client_req_filedes, read_buff, kRead_buff_size);
      const char kKill_mesg[] = "quit";
      const char kEOT = '\004';  // end-of-transmission
      const char kUS = '\037';  // universal separator
      cout << "Read " << bytes_read << " bytes: ";
      cout.write(read_buff, bytes_read) << endl;
      bytes_read = read(client_req_filedes, read_buff, kRead_buff_size);
    }
    if (bytes_read == 0) {
        cout << "Client disconnected" << endl;
        close(client_req_filedes);
    } else if (bytes_read < 0) {
        cerr << strerror(errno) << endl;
        exit(-1);
    }
  }
};

#endif  // UDS_SERVER_H_
