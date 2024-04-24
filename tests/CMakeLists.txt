include_directories(PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/3rdparty
    ${PROJECT_SOURCE_DIR}/src/bluetooth
    ${PROJECT_SOURCE_DIR}/src/components
    ${PROJECT_SOURCE_DIR}/src/compositor
    ${PROJECT_SOURCE_DIR}/src/notificationcategories
    ${PROJECT_SOURCE_DIR}/src/notifications
    ${PROJECT_SOURCE_DIR}/src/devicestate
    ${PROJECT_SOURCE_DIR}/src/screenlock
    ${PROJECT_SOURCE_DIR}/src/touchscreen
    ${PROJECT_SOURCE_DIR}/src/utilities
    ${PROJECT_SOURCE_DIR}/src/volume
)

enable_testing()

find_package(Qt6 ${QT_MIN_VERSION} REQUIRED
    Qml
    Test)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ut_qobjectlistmodel)
