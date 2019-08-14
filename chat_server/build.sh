
g++ *.cpp  data/*.cc logic/*.cpp logic/user/*.cpp tcp/*.cpp redis/*.cpp -g -o chat_server tinyxml/libtinyxml.a -I. -I/usr/local/protobuf/include -L/usr/local/protobuf/lib -lprotobuf -pthread -lhiredis

