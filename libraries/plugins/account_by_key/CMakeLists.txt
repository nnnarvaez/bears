file(GLOB HEADERS "include/bearshares/account_by_key/*.hpp")

add_library( bearshares_account_by_key
             account_by_key_plugin.cpp
             account_by_key_api.cpp
           )

target_link_libraries( bearshares_account_by_key bearshares_chain bearshares_protocol bearshares_app )
target_include_directories( bearshares_account_by_key
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bearshares_account_by_key

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
