cmake_minimum_required(VERSION 3.10.0)

project(gdrender)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(INSTALL_MANPAGES OFF)
# add_subdirectory(external/flac)

# add_subdirectory(external/vorbis)
# add_subdirectory(external/zlib)

# add_subdirectory(external/curl)

add_subdirectory(external/openal-soft)

add_subdirectory(external/cpr)

set(BUILD_SHARED_LIBS TRUE)
add_subdirectory(external/SFML)

set(SFML_LIBRARIES sfml-network sfml-system sfml-window sfml-graphics sfml-audio)

if(WIN32)
    set(FMOD_LIBRARIES ${CMAKE_SOURCE_DIR}/external/FMOD/windows/fmod.dll)
elseif(UNIX)
    set(FMOD_LIBRARIES_PATH ${CMAKE_SOURCE_DIR}/external/FMOD/linux)
    set(FMOD_LIBRARIES ${FMOD_LIBRARIES_PATH}/libfmodL.so.13)
endif()
message(NOTICE ${SFML_LIBRARIES} " & " ${SFML_DEPEDENCIES})
message(NOTICE "FMOD : " ${FMOD_LIBRARIES})

# add_subdirectory(external/imgui-sfml)

file(GLOB base_src CONFIGURE_DEPENDS "GD/*.cpp" "GD/*.h" "GD/*.hpp")
# file(GLOB imgui_base_src CONFIGURE_DEPENDS "external/imgui/*.cpp")
# file(GLOB imgui_sfml_src CONFIGURE_DEPENDS "external/imgui-sfml/*.cpp")

add_executable(gdrender ${base_src} ${imgui_base_src} ${imgui_sfml_src})

target_include_directories(gdrender PUBLIC
    GD/include 
    GD/include/boost
    external/cpr/include
    external/curl/include
    GD/include/fmod
    external/flac/include
    # external/imgui/
    # external/imgui/backends
    # external/imgui-sfml
    external/openal-soft/include
    external/SFML/include
    external/zlib
)

target_link_libraries(gdrender ${SFML_LIBRARIES} ${FMOD_LIBRARIES} cpr::cpr)