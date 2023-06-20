CC = `curl-config --cc`
LIBS = `curl-config --libs`

test: test.o
	$(CC) -g -o target/$@ $< $(LIBS)

# test.o: test-version.c
test.o: resolve.c
	$(CC) -g -c $< -o target/$@

clean:
	rm -f test.o test
