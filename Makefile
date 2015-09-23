CC = g++ 
CC_FLAG = "-std=c++11"

proxy: proxy.o
	$(CC) proxy.o -o proxy $(CC_FLAG) -lboost_system -lboost_thread-mt -lcppnetlib-client-connections -lcppnetlib-uri -lpthread -lssl -undefined dynamic_lookup

proxy.o: proxy.cpp config.h util.h	
	$(CC) -c proxy.cpp $(CC_FLAG)

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
	rm *.o server test

run:
	./server
		
