file(GLOB HEADERS "include/bearshares/delayed_node/*.hpp")

add_library( bearshares_delayed_node
             delayed_node_plugin.cpp
           )

target_link_libraries( bearshares_delayed_node bearshares_chain bearshares_protocol bearshares_app )
target_include_directories( bearshares_delayed_node
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

if(MSVC)
  set_source_files_properties( delayed_node_plugin.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

install( TARGETS
   bearshares_delayed_node

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
