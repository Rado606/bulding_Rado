FROM ubuntu:19.10

RUN apt-get update
RUN apt-get install -y libcpprest-dev
RUN apt-get install -y g++ git libboost-atomic-dev libboost-thread-dev libboost-system-dev libboost-date-time-dev libboost-regex-dev libboost-filesystem-dev libboost-random-dev libboost-chrono-dev libboost-serialization-dev libwebsocketpp-dev openssl libssl-dev ninja-build



WORKDIR /
ADD BasicController.cpp BasicController.cpp
ADD BasicController.h BasicController.h
ADD budynek_private.h budynek_private.h
ADD main.cpp main.cpp
ADD Service.cpp Service.cpp
ADD Service.h Service.h
RUN g++ *.cpp --std=c++11 -o main.o -lcpprest -lpthread -lboost_system -lssl -lcrypto -lboost_chrono
EXPOSE 8080
CMD ./main.o