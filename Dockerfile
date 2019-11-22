FROM ubuntu:19.10

RUN apt-get update
RUN apt-get install -y libcpprest-dev
RUN apt-get install -y gcc
RUN apt-get install -y g++


WORKDIR /
ADD * /
RUN g++ *.cpp -o main.o -lcpprest -lpthread -lboost_system -lssl -lcrypto
EXPOSE 8080
CMD ./main.o