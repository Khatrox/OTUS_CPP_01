cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
	set(PATCH $ENV{TRAVIS_BUILD_NUMBER})
else()
	set(PATCH 26)
endif()
 
project(Try VERSION 0.0.${PATCH})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(Doxygen COMPONENTS dot REQUIRED)

configure_file(TakeCMakeVars.h.in TakeCMakeVars.h ESCAPE_QUOTES)

add_executable(MainTarget main.cpp)
add_library(ProjectVersionLibTarget STATIC lib.cpp)
add_executable(TestTarget test.cpp)

set_target_properties(MainTarget TestTarget ProjectVersionLibTarget 
			PROPERTIES
			CXX_STANDARD 17
			CXX_STANDARD_REQUIRED ON
		      )

set_target_properties(TestTarget PROPERTIES
			COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
			INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
		      )
			

target_include_directories(ProjectVersionLibTarget PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(TestTarget ${Boost_LIBRARIES} ProjectVersionLibTarget)



##### DOCUMENTATION #####

configure_file(Doxyfile.in Doxyfile)

add_custom_target(
		   doc 
		   ${DOXYGEN_EXECUTABLE} Doxyfile
		   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}  
		   COMMENT "Creating documentation" VERBATIM
		  )

#########################

install(TARGETS MainTarget RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_CONTACT masteryilerki@yandex.ru)

include(CPack)

enable_testing()

add_test(test TestTarget)
