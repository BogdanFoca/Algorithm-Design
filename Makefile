build:
	g++ p3.cpp -o p3
	g++ -std=c++11 p1.cpp -o p1
	g++ -std=c++11 p2.cpp -o p2
run-p3:
	./p3
run-p2:
	./p2
run-p1:
	./p1
clean:
	rm -f p1 p2 p3
