cmake_minimum_required(VERSION 4.4.3)

project(md2pdf
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(md2pdf)

target_sources(md2pdf
  PRIVATE
  src/main.cpp
)

target_include_directories(md2pdf
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)

target_link_libraries(md2pdf
  PRIVATE
  hpdf
  ZLIB::ZLIB
  PNG::PNG
)

