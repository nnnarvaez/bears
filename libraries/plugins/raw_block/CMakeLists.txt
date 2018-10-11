file(GLOB HEADERS "include/bearshares/plugins/raw_block/*.hpp")

add_library( bearshares_raw_block
             ${HEADERS}
             raw_block_plugin.cpp
             raw_block_api.cpp
           )

target_link_libraries( bearshares_raw_block bearshares_app bearshares_chain bearshares_protocol fc )
target_include_directories( bearshares_raw_block
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
