cmake_minimum_required(VERSION 3.5)

project(ut_categorydefinitionstore LANGUAGES CXX)


add_executable(ut_categorydefinitionstore
    ut_categorydefinitionstore.cpp
    ut_categorydefinitionstore.h
    ../../src/notifications/categorydefinitionstore.cpp
    ../../src/notifications/categorydefinitionstore.h
    ../stubs/stubbase.cpp
    ../stubs/stubbase.h
)
add_test(NAME ut_categorydefinitionstore COMMAND ut_categorydefinitionstore)

target_link_libraries(ut_categorydefinitionstore PRIVATE
    Qt${QT_VERSION_MAJOR}::Test
    Qt${QT_VERSION_MAJOR}::Qml)



