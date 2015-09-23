CC_FLAG = -std=c++11 -O2

server: web.o mysql.o data_access.o
	clang++ web.o mysql.o data_access.o -ltbb -lmysqlcppconn-static -lmysqlclient -lpthread -lboost_system -o server $(CC_FLAG)

test : test.o mysql.o
	clang++ test.o mysql.o -ltbb -lmysqlcppconn-static -lmysqlclient -o test $(CC_FLAG)

data_access.o: data_access.h data_access.cpp
	clang++ -c data_access.cpp $(CC_FLAG)

web.o: web.cpp
	clang++ -c web.cpp $(CC_FLAG)

test.o: test.cpp
	clang++ -c test.cpp $(CC_FLAG)

mysql.o: mysql.cpp mysql.h
	clang++ -c mysql.cpp $(CC_FLAG)

clean:
	rm *.o server test

run:
	./server
		
