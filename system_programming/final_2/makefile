all:server client
server:server.c
	g++ $^ -o $@ -lpthread
client:client.c
	g++ $^ -o $@ -pthread
.PHONY:
clean:
	rm server client LOGFILES
