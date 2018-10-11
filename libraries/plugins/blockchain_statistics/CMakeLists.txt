file(GLOB HEADERS "include/bearshares/blockchain_statistics/*.hpp")

add_library( bearshares_blockchain_statistics
             blockchain_statistics_plugin.cpp
             blockchain_statistics_api.cpp
           )

target_link_libraries( bearshares_blockchain_statistics bearshares_chain bearshares_protocol bearshares_app )
target_include_directories( bearshares_blockchain_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bearshares_blockchain_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)