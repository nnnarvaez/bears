file(GLOB HEADERS "include/bearshares/account_history/*.hpp")

add_library( bearshares_account_history
             account_history_plugin.cpp
           )

target_link_libraries( bearshares_account_history bearshares_chain bearshares_protocol bearshares_app )
target_include_directories( bearshares_account_history
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bearshares_account_history

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
