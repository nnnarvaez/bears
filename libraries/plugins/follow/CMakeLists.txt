file(GLOB HEADERS "include/bearshares/follow/*.hpp")

add_library( bearshares_follow
             follow_plugin.cpp
             follow_api.cpp
             follow_operations.cpp
             follow_evaluators.cpp
           )

target_link_libraries( bearshares_follow bearshares_chain bearshares_protocol bearshares_app )
target_include_directories( bearshares_follow
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bearshares_follow

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
