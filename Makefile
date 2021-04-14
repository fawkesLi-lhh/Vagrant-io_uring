CXX = g++
CFLAGS = -std=c++14 -Wall -g

TARGET = server
OBJS = code/Vagrant/http/*.cpp \
       code/Vagrant/server/*.cpp \
       code/Vagrant/manager/*.cpp \
       code/Vagrant/config/*.cpp \
       code/Vagrant/sql/*.cpp \
       code/Vagrant/io/*.cpp \
       code/Classes/*.cpp \
       code/main.cpp

all: $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o bin/$(TARGET)  -pthread -lmysqlclient -luring

clean:
	rm -rf bin/$(OBJS) $(TARGET)




