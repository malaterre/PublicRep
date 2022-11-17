#include <cstdio>
#include <optional>
#include <string>

class Sink {
public:
  virtual void writesome(std::string const &s) = 0;
};

class Source {
public:
  virtual std::optional<std::string> readsome() = 0;
};

class Filter {
  virtual void filter(std::string const &s) = 0;
};
class Pipe /*: public Source, public Sink*/ {
  Source &source;
  Sink &sink;

public:
  Pipe(Source &source, Sink &sink) : source(source), sink(sink) {}
  void run() {
    auto item = source.readsome();
    if (item) {
      sink.writesome(*item);
    }
  }
};

class Stdin : public Source {
public:
  std::optional<std::string> readsome() {
    char buf[4096];
    size_t nread = fread(buf, 1, sizeof buf, stdin);
    return std::string(buf, nread);
  }
};

class Stdout : public Sink {
public:
  void writesome(std::string const &s) {
    fwrite(s.c_str(), 1, s.size(), stdout);
  }
};

class Tr : public Filter {
  const char From;
  const char To;

public:
  Tr(char from, char to) : From(from), To(to) {}
  //  std::string readsome() { return ""; }
  std::optional<std::string> readsome() { throw ""; }
  void writesome(std::string const &s) { throw ""; }
};

int main(int argc, char *argv[]) {
#if 0
  Stdin in;
  Stdout out;
  out.writesome(in.readsome());
  Pipe p;

  Tr('a', 'A');
#endif
  Stdin in;
  //  Tr tr('a', 'A');
  Stdout out;
  Pipe pipe(in, out);
  pipe.run();

  //  in.setSink(&pipe);
  //  pipe.setSink(&tr);
  //  tr.setSink(&out);
  //
  //  while (true) {
  //    in.process();
  //  }
  return 0;
}
