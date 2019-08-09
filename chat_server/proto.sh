
mv ./data/*.cc ./data/*.h ./cs/*.cs ./dataCopy

protoc --proto_path=./proto --cpp_out=./data --csharp_out=./cs ./proto/*.proto

