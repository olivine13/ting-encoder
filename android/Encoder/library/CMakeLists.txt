cmake_minimum_required(VERSION 3.4.1)

SET(ENCODER_DIR ${PROJECT_SOURCE_DIR}/../../..)
SET(ENCODER_INCLUDE ${ENCODER_DIR}/src)
SET(JNI_DIR src/main/cpp)

FILE(GLOB JNI_DIR_SRC ${JNI_DIR}/*.cpp)
FILE(GLOB ENCODER_SRC ${ENCODER_DIR}/src/*.cpp)

MESSAGE(STATUS ${ENCODER_DIR})
MESSAGE(STATUS ${ENCODER_SRC})
INCLUDE_DIRECTORIES(${ENCODER_INCLUDE})
ADD_LIBRARY(encoder SHARED
            ${ENCODER_SRC}
            ${JNI_DIR_SRC})

target_link_libraries(encoder
                        android
                        log)