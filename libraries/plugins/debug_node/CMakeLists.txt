file(GLOB HEADERS "include/bearshares/plugins/debug_node/*.hpp")

add_library( bearshares_debug_node
             ${HEADERS}
             debug_node_plugin.cpp
             debug_node_api.cpp
           )

target_link_libraries( bearshares_debug_node bearshares_app bearshares_chain bearshares_protocol fc )
target_include_directories( bearshares_debug_node
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS bearshares_debug_node
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
       )
INSTALL( FILES ${HEADERS} DESTINATION "include/bearshares/plugins/debug_node" )
