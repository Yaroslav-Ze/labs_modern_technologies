obj = out/string.o out/base.o

# out/rect.o out/string.o out/barrel.o out/matrix.o out/wrap.o 

out/debug.out: $(obj) src/lab2.cpp
	g++ -g -o out/debug.out src/lab2.cpp $(obj)

out/leaks.out: $(obj) src/lab2.cpp
	g++ -g -o out/leaks.out src/lab2.cpp $(obj) -fsanitize=address

out/%.o: src/%.cpp src/%.hpp
	g++ -g -c -o $@ $<

debug: out/debug.out
	gdb out/debug.out

leaks: out/leaks.out
	./out/leaks.out

out/test_%.out: tests/test_%.cpp $(obj)
	g++ -g -o $@ $< $(obj) -fsanitize=address

test_%: out/test_%.out
	./$<

tests: \
	test_BF \
	test_B32 \
	test_RLE \
	test_B32_2 \
	test_RLE_2 \
	test_COMP1 \
	test_COMP2

.PHONY: clean

clean:
	-rm -f out/*.o out/debug.out out/leaks.out out/test_*.out *.bin
	-rm -f $(filter-out data.txt,$(wildcard *.txt))