add_executable( bearsd main.cpp )
if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling bearsd with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

if( BEARS_STATIC_BUILD )
   target_link_libraries( bearsd PRIVATE
      "-static-libstdc++ -static-libgcc"
      bearshares_plugins
      bearshares_mf_plugins
      bearshares_app
      bearshares_witness
      bearshares_account_history
      bearshares_chain
      bearshares_protocol
      fc
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
else( BEARS_STATIC_BUILD )
   target_link_libraries( bearsd PRIVATE
      bearshares_plugins
      bearshares_mf_plugins
      bearshares_app
      bearshares_witness
      bearshares_account_history
      bearshares_chain
      bearshares_protocol
      fc
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
endif( BEARS_STATIC_BUILD )

install( TARGETS
   bearsd

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
