all:server client
server:server.c
	gcc $^ -o $@ -pthread
client:client.c
	gcc $^ -o $@ -pthread
.PHONY:
clean:
	rm server client
