cmake_minimum_required(VERSION 3.5)

project(ut_qobjectlistmodel LANGUAGES CXX)


add_executable(ut_qobjectlistmodel tst_ut_qobjectlistmodel.cpp
    ../../src/utilities/qobjectlistmodel.cpp ../../src/utilities/qobjectlistmodel.h
    ../../src/3rdparty/synchronizelists.h)
add_test(NAME ut_qobjectlistmodel COMMAND ut_qobjectlistmodel)

target_link_libraries(ut_qobjectlistmodel PRIVATE
    Qt${QT_VERSION_MAJOR}::Test
    Qt${QT_VERSION_MAJOR}::Qml)



