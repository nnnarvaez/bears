file(GLOB HEADERS "include/bearshares/plugins/block_info/*.hpp")

add_library( bearshares_block_info
             ${HEADERS}
             block_info_plugin.cpp
             block_info_api.cpp
           )

target_link_libraries( bearshares_block_info bearshares_app bearshares_chain bearshares_protocol fc )
target_include_directories( bearshares_block_info
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
