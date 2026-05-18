obj = out/point.o

# out/rect.o out/string.o out/barrel.o out/matrix.o out/wrap.o 

out/debug.out: $(obj) src/lab4.cpp
	g++ -g -o out/debug.out src/lab4.cpp $(obj)

out/leaks.out: $(obj) src/lab4.cpp
	g++ -g -o out/leaks.out src/lab4.cpp $(obj) -fsanitize=address

out/%.o: src/%.cpp src/%.hpp
	g++ -g -c -o $@ $<

debug: out/debug.out
	gdb out/debug.out

leaks: out/leaks.out
	./out/leaks.out

.PHONY: clean

clean:
	-rm -f out/*.o out/debug.out out/leaks.out out/test_*.out *.bin
	-rm -f $(filter-out data.txt,$(wildcard *.txt))