include Makefile

.cpp.o:
	${CXX} ${CXXFLAGS} -o $@ -c $<

.erl.beam:
	erlc ${ERLCFLAGS} $<
