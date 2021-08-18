cmake_minimum_required(VERSION 3.0.0)

project(ALTAIR_VM_PEDANTIC
        LANGUAGES C
        VERSION 0.1.0)

add_library(altair_vm_pedantic SHARED
        src/vm.h

        src/vm.c src/virtual_machine.h src/processor.h src/physical_memory.h src/virtual_machine.c src/physical_memory.c src/processor.c)

set_target_properties(altair_vm_pedantic PROPERTIES PREFIX "")
target_link_libraries(altair_vm_pedantic PRIVATE altair_vm_base)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(altair_vm_pedantic PRIVATE -Wno-float-equal)
endif()

install(TARGETS altair_vm_pedantic
        CONFIGURATIONS Debug
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/../test/debug
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/../test/debug
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/../test/debug
        COMPONENT library)

install(TARGETS altair_vm_pedantic
        CONFIGURATIONS Release
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/../test/release
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/../test/release
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/../test/release
        COMPONENT library)
