obj = out/rect.o out/string.o out/barrel.o out/matrix.o out/wrap.o

out/debug.out: $(obj) src/lab1.cpp
	g++ -g -o out/debug.out src/lab1.cpp $(obj)

out/leaks.out: $(obj) src/lab1.cpp
	g++ -g -o out/leaks.out src/lab1.cpp $(obj) -fsanitize=address

out/test_rect_basic_methods.out: $(obj) tests/test_rect_basic_methods.cpp
	g++ -g -o out/test_rect_basic_methods.out tests/test_rect_basic_methods.cpp $(obj) -fsanitize=address

out/test_rect_properties.out: $(obj) tests/test_rect_properties.cpp
	g++ -g -o out/test_rect_properties.out tests/test_rect_properties.cpp $(obj) -fsanitize=address

out/test_rect_operations.out: $(obj) tests/test_rect_operations.cpp
	g++ -g -o out/test_rect_operations.out tests/test_rect_operations.cpp $(obj) -fsanitize=address

out/test_bounding_rect.out: $(obj) tests/test_bounding_rect.cpp
	g++ -g -o out/test_bounding_rect.out tests/test_bounding_rect.cpp $(obj) -fsanitize=address


# TODO: нужно учесть зависимость wrap.hpp от string.hpp
out/%.o: src/%.cpp src/%.hpp
	g++ -g -c -o $@ $<

debug: out/debug.out
	gdb out/debug.out

leaks: out/leaks.out
	./out/leaks.out < input.txt

test_rect_basic_methods: out/test_rect_basic_methods.out
	./out/test_rect_basic_methods.out

test_rect_properties: out/test_rect_properties.out
	./out/test_rect_properties.out

test_rect_operations: out/test_rect_operations.out
	./out/test_rect_operations.out

test_bounding_rect: out/test_bounding_rect.out
	./out/test_bounding_rect.out

tests: test_rect_basic_methods test_rect_properties test_rect_operations test_bounding_rect


.PHONY: clean

clean:
	-rm -f out/*.o out/debug.out out/leaks.out out/test_*.out
