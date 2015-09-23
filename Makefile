CC_FLAG = -std=c++11 -O2

proxy: proxy.o
	clang++ proxy.o -o proxy $(CC_FLAG) -lboost_system -lboost_thread-mt -lcppnetlib-client-connections -lcppnetlib-uri -lpthread -lssl -undefined dynamic_lookup

proxy.o: proxy.cpp config.h util.h	
	clang++ -c proxy.cpp $(CC_FLAG)

server: web.o mysql.o
	clang++ web.o mysql.o -lmysqlcppconn-static -lmysqlclient -lpthread -lboost_system -o server $(CC_FLAG)

test : test.o mysql.o
	clang++ test.o mysql.o -ltbb -lmysqlcppconn-static -lmysqlclient -o test $(CC_FLAG)

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
		
