file(GLOB HEADERS "include/bearshares/account_statistics/*.hpp")

add_library( bearshares_account_statistics
             account_statistics_plugin.cpp
             account_statistics_api.cpp
           )

target_link_libraries( bearshares_account_statistics bearshares_chain bearshares_protocol bearshares_app )
target_include_directories( bearshares_account_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bearshares_account_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)