CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)
PROJECT(MINISQL VERSION 0.0.0)

MESSAGE(STATUS "This is BINARY dir " ${MINISQL_BINARY_DIR})

SET(RE_DIR /re)
SET(LUA_DIR /thirdparts/lua)
SET(JSON_DIR /thirdparts/rapidjson)

ADD_SUBDIRECTORY(${MINISQL_SOURCE_DIR}${LUA_DIR})

INCLUDE_DIRECTORIES(
    ${MINISQL_SOURCE_DIR}/include
    ${MINISQL_SOURCE_DIR}${LUA_DIR}/src
    ${MINISQL_SOURCE_DIR}${JSON_DIR}/include

    ${MINISQL_BINARY_DIR}${LUA_DIR}
)

LINK_DIRECTORIES(
	${MINISQL_SOURCE_DIR}/libs

)

SET(MINISQL_DEPENDS main.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -DDEBUG -g")
# gen executable
ADD_EXECUTABLE(MiniSql ${MINISQL_DEPENDS})
TARGET_LINK_LIBRARIES(
	MiniSql
	liblua
)

INCLUDE(CTest)
#do test

add_test (StrEQ MiniSql living -i templateId -i name -sq name = 预言之子)
set_tests_properties (StrEQ
  PROPERTIES PASS_REGULAR_EXPRESSION "^result count is 1465")

add_test (StrNE MiniSql living -i templateId -i name -sq name != 预言之子)
set_tests_properties (StrNE
  PROPERTIES PASS_REGULAR_EXPRESSION "^result count is 3714")

add_test (StrIn MiniSql living -i templateId -i name -sq name in 预言之子,暗系兽人,智天使乌列)
set_tests_properties (StrIn
  PROPERTIES PASS_REGULAR_EXPRESSION "^result count is 1509")

add_test (NumEQ MiniSql living -i templateId -i name -nq templateId = 1005)
set_tests_properties (NumEQ
  PROPERTIES PASS_REGULAR_EXPRESSION "^result count is 1")

add_test (NumLT MiniSql living -i templateId -i name -nq templateId < 10000)
set_tests_properties (NumLT
  PROPERTIES PASS_REGULAR_EXPRESSION "^result count is 55")

add_test (NumGT MiniSql living -i templateId -i name -nq templateId > 9010016)
set_tests_properties (NumGT
  PROPERTIES PASS_REGULAR_EXPRESSION "^result count is 239")

add_test (NumGE MiniSql living -i templateId -i name -nq templateId >= 9010016)
set_tests_properties (NumGE
  PROPERTIES PASS_REGULAR_EXPRESSION "^result count is 240")

add_test (NumLE MiniSql living -i templateId -i name -nq templateId <= 100201)
set_tests_properties (NumLE
  PROPERTIES PASS_REGULAR_EXPRESSION "^result count is 118")

add_test (NumNE MiniSql living -i templateId -i name -nq templateId != 100101)
set_tests_properties (NumNE
  PROPERTIES PASS_REGULAR_EXPRESSION "^result count is 5178")

add_test (NumIn MiniSql living -i templateId -i name -nq templateId in 100101,100201)
set_tests_properties (NumIn
  PROPERTIES PASS_REGULAR_EXPRESSION "^result count is 2")

add_test (NumBT MiniSql living -i templateId -i name -nq templateId bt 100101,100201)
set_tests_properties (NumBT
  PROPERTIES PASS_REGULAR_EXPRESSION "^result count is 62")