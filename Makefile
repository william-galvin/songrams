CXX = g++
OBJS = src/main.o src/Trie.o src/StrUtils.o src/Objective.o
EXE  = songrams
HEADERS = src/Vector.h src/StrUtils.h src/Objective.h
CPPFLAGS = -Wall -g -std=c++17 -Ofast

$(EXE): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(EXE) $(OBJS)


%.o: src/%.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -rf $(EXE) src/*.o src/*~ src/*.dSYM

