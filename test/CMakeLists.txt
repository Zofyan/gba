cmake_minimum_required(VERSION 3.21)
project(GBATEST)

set(CMAKE_CXX_STANDARD 17)


add_executable(GBATEST test.cpp doctest/doctest.h ../include/cpu.h ../include/bus.h ../include/rom.h ../include/instructions/instruction.h
        ../source/bus.cpp ../source/instructions/instruction.cpp ../source/rom.cpp ../source/cpu.cpp ../source/clock.cpp ../include/clock.h ../source/emu.cpp ../include/emu.h test.cpp ../source/instructions/thumb_instruction.cpp
        ../include/instructions/thumb_instruction.h ../source/instructions/arm_instruction.cpp ../include/instructions/arm_instruction.h ../source/instructions/condition.cpp ../include/instructions/condition.h ../include/helpers.h ../source/helpers.cpp
        doctest/extensions/doctest_mpi.h doctest/extensions/doctest_util.h doctest/extensions/mpi_reporter.h doctest/extensions/mpi_sub_comm.h doctest/parts/doctest.cpp doctest/parts/doctest_fwd.h
        mul_instructions.cpp)


add_test(NAME GBATEST
        COMMAND GBATEST)