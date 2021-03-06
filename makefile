CC = g++

s2n.so : s2n.cpp S2Daemon.cpp CnC.cpp CmdProcessor.cpp CmdHandler.cpp User.cpp util.cpp Config.cpp
	$(CC) -g -lpthread -Wall -O2 -fpic -shared -o s2n.so s2n.cpp S2Daemon.cpp CnC.cpp CmdProcessor.cpp CmdHandler.cpp User.cpp util.cpp Config.cpp -ldl

clean:
	$(RM) s2n.so *.o
