cmake_minimum_required(VERSION 4.4.3)

project(md2pdf)

add_executable(md2pdf)

target_sources(md2pdf
  PRIVATE
  src/main.cpp
)

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)

target_link_libraries(md2pdf
  PRIVATE
  hpdf
  ZLIB::ZLIB
  PNG::PNG
)

