test.out:test.cpp
	gcc -o test.out test.cpp -lstdc++

.PHONY:clean
clean:
	rm -f test.out

