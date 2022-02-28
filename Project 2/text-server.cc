// Copyright 2022 Charles Simons
// Written for Project 2 - CSCE 311 @ U of SC



// server for demonstrating IPC using Unix Domain sockets
// processes large text files to find particular search term from the client

class UnixDomSock {
 public:
  explicit UnixDomSock(const char *sock_path) {
      sock_path_ = std::string(sock_path);

      sock_addr_ = {};
      sock_addr_.sun_family = AF_UNIX;

      strncpy(sock_addr_.sun_path + 1, sock_path,
              sizeof(sock_addr_.sun_path) - 2);
  }

 protected:
  ::sockaddr_un sock_addr_;
  std::string sock_path_;
};


// Domain Socket Server
