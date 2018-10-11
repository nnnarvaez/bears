file(GLOB HEADERS "include/bearshares/private_message/*.hpp")

add_library( bearshares_private_message
             private_message_plugin.cpp
           )

target_link_libraries( bearshares_private_message bearshares_chain bearshares_protocol bearshares_app )
target_include_directories( bearshares_private_message
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bearshares_private_message

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
