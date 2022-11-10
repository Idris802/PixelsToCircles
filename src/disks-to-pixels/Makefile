run: pixelize deviation
	./pixelize disk-input.dat pixel-output.dat

pixelize: charmap.o disk-vector.o pixelize.o
	g++ -g3 -std=c++17 -o pixelize charmap.o disk-vector.o pixelize.o

%.o: %.cpp
	g++ -g3 -c -std=c++17 -o $@ $<

clean:
	rm -f *.o *.zip pixelize pixel-output.dat
