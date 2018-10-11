file(GLOB HEADERS "include/bearshares/market_history/*.hpp")

add_library( bearshares_market_history
             market_history_plugin.cpp
             market_history_api.cpp
           )

target_link_libraries( bearshares_market_history bearshares_chain bearshares_protocol bearshares_app )
target_include_directories( bearshares_market_history
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bearshares_market_history

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)