#----------------------------------------
# GENERAL:

CC=g++
LD=g++

#----------------------------------------
# GO:

TARGET=Go
SRC=main go game goban pawn pawn_black pawn_white field history event player
#game
#game interface player goban field history event

LIBS=-lncurses
FLAGS=-Wall -I "./header"

#----------------------------------------
# UNIT TESTS:

TSRC=ExampleTest MyTest
TUNIT=CuTest

TLIBS= 
TFLAGS=-I "./test"

#----------------------------------------

CFLAGS=$(FLAGS)
LDFLAGS=$(FLAGS) $(LIBS)

TCFLAGS=$(FLAGS) $(TFLAGS)
TLDFLAGS=$(FLAGS) $(LIBS) $(TFLAGS) $(TLIBS)

SRCS=$(addsuffix .cpp, $(SRC)) 
OBJS=$(addprefix object/, $(addsuffix .o, $(SRCS)))

TSRCS=$(addsuffix .cpp, $(SRC) $(TSRC) $(TUNIT)) 
TOBJS=$(addprefix object/, $(addsuffix .o, $(TSRCS)))

test: $(TOBJS)
	$(LD) $(TOBJS) $(TLDFLAGS) -o $(TARGET)

$(TARGET): $(OBJS) 
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET)

object/%.cpp.o: source/%.cpp header/%.hpp
	$(CC) -c $< $(TCFLAGS) -o $@
object/%.cpp.o: test/%.cpp test/AllTests.hpp test/CuTest.hpp test/test.hpp
	$(CC) -c $< $(TCFLAGS) -o $@

make debug: debug.c
	g++ debug.c -o debug
clean:
	rm -f $(TOBJS) $(TARGET) object/*