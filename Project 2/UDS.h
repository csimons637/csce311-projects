#ifndef UDS_H_
// Copyright 2022 Charles Simons
// Modified from existing code by J. Lewis (instructor for CSCE 311, Spring 2022)
// Written for Project 2 - CSCE 311 @ U of SC

// Header for Unix Domain Socket Constructor

// includes
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <cassert>
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <string>
#include <iostream>
// end inludes

class UnixDomainSocket {
 public:
  explicit UnixDomainSocket(const char *socket_path) {
    socket_path_ = std::string(socket_path);  // std::string manages char *

    sock_addr_ = {};  // init struct (replaces memset)
    sock_addr_.sun_family = AF_UNIX;  // set to Unix domain socket (e.g. instead
                                      //   of internet domain socket)
    // leaving leading null char sets abstract socket
    strncpy(sock_addr_.sun_path + 1,  // use strncpy to limit copy for
            socket_path,              //   portability
            sizeof(sock_addr_.sun_path) - 2);  // -2 for leading/trailing \0s
  }

 protected:
  ::sockaddr_un sock_addr_;  // socket address from sys/un.h

  std::string socket_path_;  // let std::string manage char *
};

#endif
