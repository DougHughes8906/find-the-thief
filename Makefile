
CXX = g++
CXXFLAGS = -std=c++0x

OBJS = Menu.o intValid.o Backpack.o Clue.o FireworksBox.o Floor.o
OBJS += Person.o Space.o Stereo.o ThiefGame.o TruthCandyBox.o thiefMain.o
OBJS += Launcher.o

SRCS = Menu.cpp intValid.cpp Backpack.cpp Clue.cpp FireworksBox.cpp
SRCS += Floor.cpp Person.cpp Space.cpp Stereo.cpp ThiefGame.cpp
SRCS += TruthCandyBox.cpp thiefMain.cpp Launcher.cpp

HEADERS = Menu.hpp intValid.hpp Backpack.hpp Clue.hpp FireworksBox.hpp
HEADERS += Floor.hpp Person.hpp Space.hpp Stereo.hpp ThiefGame.hpp
HEADERS += TruthCandyBox.hpp Launcher.hpp

output: ${OBJS} ${HEADERS}
	${CXX} ${OBJS} -o output

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm *.o output
