# CMakeList.txt : CMake project for scc, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (scc "scc.c")
target_compile_definitions(scc PRIVATE ARM=1)
# TODO: Add tests and install targets if needed.
