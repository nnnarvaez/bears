file(GLOB HEADERS "include/bearshares/tags/*.hpp")

add_library( bearshares_tags
             tags_plugin.cpp )

target_link_libraries( bearshares_tags bearshares_chain bearshares_protocol bearshares_app )
target_include_directories( bearshares_tags
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bearshares_tags

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
