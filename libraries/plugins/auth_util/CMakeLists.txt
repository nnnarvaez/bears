file(GLOB HEADERS "include/bearshares/plugins/auth_util/*.hpp")

add_library( bearshares_auth_util
             ${HEADERS}
             auth_util_plugin.cpp
             auth_util_api.cpp
           )

target_link_libraries( bearshares_auth_util bearshares_app bearshares_chain bearshares_protocol fc )
target_include_directories( bearshares_auth_util
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
