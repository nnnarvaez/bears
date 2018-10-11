file(GLOB HEADERS "include/bearshares/witness/*.hpp")

add_library( bearshares_witness
             witness_plugin.cpp
             witness_evaluators.cpp
             witness_operations.cpp
           )

target_link_libraries( bearshares_witness bearshares_chain bearshares_protocol bearshares_app )
target_include_directories( bearshares_witness
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bearshares_witness

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
