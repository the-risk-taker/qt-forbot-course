# Client
set(CLIENT_APP_NAME Client)

set(CLIENT_SOURCES
    client/client.h
    client/main.cpp
    client/qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${CLIENT_APP_NAME} MANUAL_FINALIZATION ${CLIENT_SOURCES})
else()
    if(ANDROID)
        add_library(${CLIENT_APP_NAME} SHARED ${CLIENT_SOURCES})
    else()
        add_executable(${CLIENT_APP_NAME} ${CLIENT_SOURCES})
    endif()
endif()

target_link_libraries(${CLIENT_APP_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Network)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(${CLIENT_APP_NAME})
    qt_finalize_executable(${CLIENT_APP_NAME})
endif()

# Server
set(SERVER_APP_NAME Server)

set(SERVER_SOURCES
    server/main.cpp
    server/qml.qrc
    server/server.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${SERVER_APP_NAME} MANUAL_FINALIZATION ${SERVER_SOURCES})
else()
    if(ANDROID)
        add_library(${SERVER_APP_NAME} SHARED ${SERVER_SOURCES})
    else()
        add_executable(${SERVER_APP_NAME} ${SERVER_SOURCES})
    endif()
endif()

target_link_libraries(${SERVER_APP_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Network)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(${SERVER_APP_NAME})
    qt_finalize_executable(${SERVER_APP_NAME})
endif()
