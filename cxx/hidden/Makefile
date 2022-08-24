CXXFLAGS := -fvisibility=hidden -fvisibility-inlines-hidden -g
CXXFLAGS := -g
LDFLAGS := '-Wl,-rpath,$$ORIGIN' -pthread -L.
LDLIBS := -lopenvdb
OBJS := main.o Module.o
LIB := libopenvdb.so

vdb_view: $(OBJS) $(LIB)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
Module.o: Tree.h
$(LIB): openvdb.cc Tree.h
	#$(CXX) $(CXXFLAGS) -DVIS -fvisibility=hidden -fvisibility-inlines-hidden -fPIC -shared -Wl,-soname,$@ -o $@ $<
	$(CXX) $(CXXFLAGS) -fPIC -shared -Wl,-soname,$@ -o $@ $<
clean:
	rm -f $(OBJS) $(LIB)
