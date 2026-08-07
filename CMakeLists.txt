cmake_minimum_required(VERSION 3.12)
include(GenerateExportHeader)

project(YNoitaPatcher VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC编码选项
if(MSVC)
    add_compile_options(/utf-8)
# else()
#     add_compile_options(-Wall)
#     add_compile_options(-Wextra)
#     add_compile_options(-pedantic)
#     add_compile_options(-Wuninitialized)
#     add_compile_options(-Wstrict-aliasing)
endif()

file(GLOB_RECURSE YNoitaPatcherSrc
    CONFIGURE_DEPENDS
    "src/*.cpp" 
)

add_library(YNoitaPatcher 
    ${YNoitaPatcherSrc}
)

# 清理可能过时的文件
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES ${EXPORT_HEADER_PATH})
# 构建数据生成
set(EXPORT_HEADER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/YNoitaPatcher/detail/auto/")
# 生成导出头
generate_export_header(YNoitaPatcher
    EXPORT_FILE_NAME ${EXPORT_HEADER_PATH}YNoitaPatcher_export.h
)

# 设置头文件搜索路径
target_include_directories(YNoitaPatcher PUBLIC
    # $<BUILD_INTERFACE:...> 只有在同一个构建系统中编译时，才使用这个路径
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>                          # 安装后
)

# 命名空间别名
add_library(YNoitaPatcher::YNoitaPatcher ALIAS YNoitaPatcher)

# 统一输出路径
set_target_properties(YNoitaPatcher PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

add_subdirectory(minhook)
target_link_libraries(YNoitaPatcher PRIVATE minhook)