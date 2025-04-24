# .PHONY: test
# CC = gcc
# CFLAGS=-I ../src -Wall -g #-DSENTINEL

# test: test-rbtree
# 	./test-rbtree
# 	valgrind ./test-rbtree

# test-rbtree: test-rbtree.o ../src/rbtree.o

# ../src/rbtree.o:
# 	$(MAKE) -C ../src rbtree.o

# clean:
# 	rm -f test-rbtree *.o

.PHONY: test clean

CC = gcc
CFLAGS = -I ../src -Wall -g -DSENTINEL

test: test-rbtree
	./test-rbtree.exe

# valgrind 부분은 Windows 환경에서는 보통 작동하지 않음
# 필요한 경우 WSL에서 실행하거나 주석 처리하세요
#	valgrind ./test-rbtree.exe

test-rbtree: test-rbtree.o ../src/rbtree.o
	$(CC) $(CFLAGS) -o test-rbtree.exe test-rbtree.o ../src/rbtree.o

test-rbtree.o: test-rbtree.c
	$(CC) $(CFLAGS) -c test-rbtree.c

../src/rbtree.o:
	$(MAKE) -C ../src rbtree.o

clean:
	@echo Cleaning up...
	@rm -f test-rbtree.exe *.o || del test-rbtree.exe *.o 2>nul
