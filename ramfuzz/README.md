1. `r.sh` runs the RamFuzz code generator
2. RamFuzz-powered test sources are in `../src/tests/ramfuzz/`, which needs
   three more files to work properly:
   * symlink to `fuzz.cpp` in this directory
   * symlink to `missimpl.cpp` in this directory
   * symlink to `ramfuzz-rt.cpp`, wherever it lives
3. There is a bug in protobuf-3.3.0 that prevents compilation of `fuzz.cpp`.  To
   fix it, apply `./repeated_field.h.patch` to the file
   `build/3rdparty/protobuf-3.3.0/src/google/protobuf/repeated_field.h`.
4. `../src/Makefile.am` has new targets `ramfuzz-tests` (to build RamFuzz tests)
   and `check-ramfuzz` (to run them)
   * assumes RamFuzz source is in a directory `ramfuzz` sibling to top-level
     `mesos` to set include paths properly
   * if you're building with `-Werror` (the default), you will need to manually
     delete some unused variables from `fuzz.?pp`; otherwise, you'll see an
     error similar to `fuzz.hpp:759:17: error: private field 'g' is not used`.
