# Copyright 2022 Charles Simons
# Written for Project 4 - CSCE 311 @ U of SC
cc = g++

flags = -std=c++17
flags += -Wall
flags += -g
flags += -pthread

link = $(cc) $(flags) -o
compile = $(cc) $(flags) -c

# for executables (used in clean)
obj = text-client text-server

# compile both client and server
all : clean text-client text-server

# client compilation
text-client : client.cc
			$(link) $@ $^ -lrt

# server compilation
text-server : server.cc
			$(link) $@ $^ -lrt

# directory clean-up
.PHONY : clean
clean :
		$(RM) $(obj)
