include Makefile

.cpp.o:
	${CXX} ${CXXFLAGS} -o $@ -c $<

.o:
	${CXX} ${CXXFLAGS} -o $@ $^ ${LDFLAGS}

.erl.beam:
	erlc ${ERLCFLAGS} $<
