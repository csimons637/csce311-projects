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

    const size_t kRead_buff_size = 64;  // 64 bytes of buffer space for reading
    char read_buff[kRead_buff_size];  // read buffer
    int bytes_read;  // number of bytes read into the buffer
    while (true) {  // one socket per client (if threaded)
        client_req_filedes = accept(socket_filedes, nullptr, nullptr);
        if (client_req_filedes  < 0) {              //
        cerr << strerror(errno) << endl;  // Error if client specifies
        continue;                                   // wrong socket name
      }

      clog << "Client Connected" << endl;

      // Find Client Specified File
      ifstream search_file;
      ssize_t kFile_read = 32;
      char file_read[kFile_read];
      read(client_req_filedes, file_read, kRead_buff_size);
      search_file.open(file_read);
      if (search_file.fail()) {
          clog << "Invalid File" << endl;
          exit(-1);
      }
      clog << "Path: " << file_read << endl;

      // Data Reception from Client
      bytes_read = read(client_req_filedes, read_buff, kRead_buff_size);
      const char kKill_mesg[] = "Quit";
      const char kEOT = '\004';  // end-of-transmission
      const char kUS = '\037';  // universal separator

      while (bytes_read > 0) {
        if (strcmp(read_buff, kKill_mesg) == 0) {     // On kill msg receipt
          cout << "Shutting Down Server..." << endl;  // print closing message
          bytes_read = 0;                             // set bytes_read to 0
          break;
        }

        cout << "Read " << bytes_read << " bytes: " << endl;
        cout.write(read_buff, bytes_read) << endl;
      }

      // Search File for Client Request
      std::string search = read_buff;
      std::string temp = "";
      std::string found = "";
      while (!search_file.eof()) {
          getline(search_file, temp);
          for (int i = 0; i < search.size(); i++) {
              if (search[i] == temp[i])
                  found += temp[i];
          }
      }

      bytes_read = read(client_req_filedes, read_buff, kRead_buff_size);
    }

    // Send Data to Client
    ssize_t kWrite_buff_size = 64;  // 64 bytes of buffer space for writing
    char write_buff[kWrite_buff_size];  // write buffer
    int bytes_written;  // number of bytes written from buffer

    while (true) {
        cin.getline(write_buff, kWrite_buff_size);  // reads 64 bytes
                                                    // & stores in write buffer
        while (cin.gcount() > 0) {
            if (cin.gcount() == kWrite_buff_size - 1 && cin.fail())
                cin.clear();
            bytes_written = write(socket_filedes, write_buff, cin.gcount());
            cout << "Sent " << bytes_written << " bytes" << endl;
            if (bytes_written == 0) {
                clog << "Client dropped connection" << endl;
                break;
            } else if (bytes_written < 0) {
                cerr << strerror(errno) << endl;
                exit(-1);
            }

            // cin.getline(write_buff, kWrite_buff_size);
        }
    }

    if (bytes_read == 0) {
        cout << "Client disconnected" << endl;
        close(client_req_filedes);
        clog << "Bytes Sent: " << bytes_written << endl;
    } else if (bytes_read < 0) {
        cerr << strerror(errno) << endl;
        exit(-1);
    }
  }
};

#endif  // UDS_SERVER_H_
