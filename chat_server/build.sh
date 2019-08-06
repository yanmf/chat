#g++ server.cc people.pb.cc -o s -lprotobuf  
g++ main.cpp server.cpp data/*.cc -g -o chat_server -I. -I/usr/local/protobuf/include -L/usr/local/protobuf/lib -lprotobuf -pthread

