# Copyright 2022 Charles Simons
# Written for Project 3 - CSCE 311 @ U of SC
cc = g++

flags = -std=c++17
flags += -Wall
flags += -g
flags += -pthread
# flags += lpthread

link = $(cc) $(flags) -o
compile = $(cc) $(flags) -c

# for executables (used in clean)
obj = text-client text-server

# client compilation
text-client : text-client.cc named_semaphore.cc
			$(link) $@ $^ -lrt

# server compilation
text-server : text-server.cc named_semaphore.cc
			$(link) $@ $^ -lrt

# directory clean-up
.PHONY : clean
clean :
		$(RM) $(obj)
