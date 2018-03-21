cmake_minimum_required(VERSION 3.9)
project(Assignment03_04Fixed C)

set(CMAKE_C_STANDARD 11)

add_executable(Assignment03_04Fixed main.c controller/controller.c controller/controller.h domain/country.c domain/country.h repository/repo.c repository/repo.h ui/cli.c ui/cli.h validator/validator.c validator/validator.h test/tester.c test/tester.h controller/undoController.c controller/undoController.h)