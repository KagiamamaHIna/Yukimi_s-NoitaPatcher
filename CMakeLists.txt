cmake_minimum_required(VERSION 3.12)
include(GenerateExportHeader)

project(NVFSPatcher VERSION 1.0.0)

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

file(GLOB_RECURSE NVFSPatcherSrc
    CONFIGURE_DEPENDS
    "src/*.cpp" 
)

add_library(NVFSPatcher 
    ${NVFSPatcherSrc}
)

# 清理可能过时的文件
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES ${EXPORT_HEADER_PATH})
# 构建数据生成
set(EXPORT_HEADER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/NVFSPatcher/detail/auto/")
# 生成导出头
generate_export_header(NVFSPatcher
    EXPORT_FILE_NAME ${EXPORT_HEADER_PATH}NVFSPatcher_export.h
)

# 设置头文件搜索路径
target_include_directories(NVFSPatcher PUBLIC
    # $<BUILD_INTERFACE:...> 只有在同一个构建系统中编译时，才使用这个路径
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>                          # 安装后
)

# 命名空间别名
add_library(NVFSPatcher::NVFSPatcher ALIAS NVFSPatcher)

# 统一输出路径
set_target_properties(NVFSPatcher PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

add_subdirectory(minhook)
target_link_libraries(NVFSPatcher PRIVATE minhook)