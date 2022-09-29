# chmod +x run.sh
# ./run.sh

cmake -S . -B build && cmake --build "build" && cd build/tests && ctest