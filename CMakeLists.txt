cmake_minimum_required(VERSION 4.1)
project(A10)

set(CMAKE_CXX_STANDARD 14)
# These three lines are mandatory for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# This tells CMake to go find the files in the path we set in Step 2
find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(domain)
include_directories(Exceptions)
include_directories(gui)
include_directories(repository)
include_directories(services)
include_directories(ui)

add_executable(A10
        domain/domain.cpp
        domain/domain.h
        Exceptions/exceptions.cpp
        Exceptions/exceptions.h
        gui/file_gui.cpp
        gui/file_gui.h
        gui/gui.cpp
        gui/gui.h
        gui/select_gui.cpp
        gui/select_gui.h
        gui/user_gui.cpp
        gui/user_gui.h
        repository/repository.cpp
        repository/repository.h
        services/services.cpp
        services/services.h
        ui/ui.cpp
        ui/ui.h
        main.cpp
        services/undo_action.h
        gui/mymodel.h
        gui/mymodel.cpp
        gui/mywindow.h
        gui/mywindow.cpp)
# This links the libraries so the #include works
target_link_libraries(A10 PRIVATE Qt6::Widgets)