cmake_minimum_required(VERSION 3.12.0)

set(OA_ENABLE_EXCEPTIONS OFF CACHE BOOL "If true C++ Exceptions will be enabled when compiling.")

project(oasisEngine)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(OA_MAIN_DIR  ${PROJECT_SOURCE_DIR})

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OA_BINARY_OUTPUT_DIR   ${OA_MAIN_DIR}/bin/x64)
    set(OA_LIBRARY_OUTPUT_DIR  ${OA_MAIN_DIR}/lib/x64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(OA_BINARY_OUTPUT_DIR   ${OA_MAIN_DIR}/bin/x86)
    set(OA_LIBRARY_OUTPUT_DIR  ${OA_MAIN_DIR}/lib/x86)
endif()

#set(OA_BINARY_OUTPUT_DIR   ${OA_MAIN_DIR}/bin)
#set(OA_LIBRARY_OUTPUT_DIR  ${OA_MAIN_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG             ${OA_BINARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL        ${OA_BINARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO    ${OA_BINARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE           ${OA_BINARY_OUTPUT_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG             ${OA_LIBRARY_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL        ${OA_LIBRARY_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO    ${OA_LIBRARY_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE           ${OA_LIBRARY_OUTPUT_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG             ${OA_LIBRARY_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL        ${OA_LIBRARY_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO    ${OA_LIBRARY_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE           ${OA_LIBRARY_OUTPUT_DIR})

if(WIN32)
    add_compile_options(/W4)
endif()

if (MSVC AND NOT BOO_ENABLE_EXCEPTIONS)
    if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
	    string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "$(CMAKE_CXX_FLAGS)")
	endif()
endif()

string(REPLACE "/GR" "/GR-" CMAKE_CXX_FLAGS "$(CMAKE_CXX_FLAGS)")

if (CMAKE_GENERATOR STREQUAL "Ninja")
    check_cxx_compiler_flag("-fdiagnostics-color=always" F_DIAGNOSTIC_COLOR_ALWAYS)
	if (F_DIAGNOSTIC_COLOR_ALWAYS)
	    add_compile_options(-fdiagnostics-color=always)
    endif()
endif()

find_path(UTILITIES_SUBMODULE_SOURCES "oaUtilities/Include/booPrerequisitesUtilities.h")
if (NOT UTILITIES_SUBMODULE_SOURCES)
    include(FetchContent)
  	FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/heads/master.zip)
	
	#For Windows: Prevent overriding the parent project's compiler/linker settings.
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	#FetchContent_MakeAvailable(googletest)
endif()

#FILTER CREATION FUNCTION
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

add_subdirectory(oaUtilities)
add_subdirectory(oaUtilitiesTest)
add_subdirectory(oaCore)
add_subdirectory(oaDX11Graphics)
add_subdirectory(oaOglGrafics)
add_subdirectory(oaRenderer)
add_subdirectory(oaGaInput)
add_subdirectory(oaFmodAudio)

if(MSVC)
    target_compile_options(oaUtilities PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/GR->)
    target_compile_options(oaUtilitiesTest PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/GR->)
    target_compile_options(oaCore PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/GR->)
    target_compile_options(oaDX11Graphics PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/GR->)
    target_compile_options(oaOglGrafics PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/GR->)
    target_compile_options(oaRenderer PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/GR->)
    target_compile_options(oaGaInput PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/GR->)
    target_compile_options(oaFmodAudio PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/GR->)
endif()
