CC = g++ 
CC_FLAG = "-std=c++11"

all: server test 

benchmark: benchmark.cpp
	$(CC) benchmark.cpp -o benchmark $(CC_FLAG) -lcppnetlib-client-connections -lcppnetlib-uri -lboost_system-mt -lboost_thread-mt -lpthread -lssl

server: web.o mysql.o data_access.o
	$(CC)  web.o mysql.o data_access.o -ldl -ltbb -lmysqlcppconn-static -L/usr/lib64/mysql -lmysqlclient -lpthread -lboost_system -o server $(CC_FLAG)

test : test.o mysql.o
	$(CC)  test.o mysql.o -ltbb -lmysqlcppconn-static -lmysqlclient -o test $(CC_FLAG)

data_access.o: data_access.h data_access.cpp
	$(CC)  -c data_access.cpp $(CC_FLAG)

web.o: web.cpp
	$(CC)  -c web.cpp $(CC_FLAG)

test.o: test.cpp
	$(CC)  -c test.cpp $(CC_FLAG)

mysql.o: mysql.cpp mysql.h
	$(CC)  -c mysql.cpp $(CC_FLAG)

clean:
	rm *.o benchmark server test data/a.out data/html.txt 

run:
	./server
		
