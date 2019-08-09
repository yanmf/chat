
g++ *.cpp  data/*.cc logic/*.cpp tcp/*.cpp -g -o chat_server -I. -I/usr/local/protobuf/include -L/usr/local/protobuf/lib -lprotobuf -pthread

