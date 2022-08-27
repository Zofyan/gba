cmake_minimum_required(VERSION 3.21)
project(GBE)
project(GBETEST)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR sdl/include)
set(SDL2_LIB_DIR sdl/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(GBE include/cpu.h include/bus.h include/rom.h include/instructions/instruction.h
        source/main.cpp source/bus.cpp source/instructions/instruction.cpp source/rom.cpp source/cpu.cpp source/clock.cpp include/clock.h source/emu.cpp include/emu.h test/test.cpp source/instructions/thumb_instruction.cpp include/instructions/thumb_instruction.h source/instructions/arm_instruction.cpp include/instructions/arm_instruction.h source/instructions/condition.cpp include/instructions/condition.h include/helpers.h source/helpers.cpp test/test.h)

add_executable(GBETEST test/test.cpp test/doctest/doctest.h include/cpu.h include/bus.h include/rom.h include/instructions/instruction.h
        source/main.cpp source/bus.cpp source/instructions/instruction.cpp source/rom.cpp source/cpu.cpp source/clock.cpp include/clock.h source/emu.cpp include/emu.h test/test.cpp source/instructions/thumb_instruction.cpp include/instructions/thumb_instruction.h source/instructions/arm_instruction.cpp include/instructions/arm_instruction.h source/instructions/condition.cpp include/instructions/condition.h include/helpers.h source/helpers.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
