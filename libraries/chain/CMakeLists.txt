file(GLOB HEADERS "include/bearshares/chain/*.hpp" "include/bearshares/chain/util/*.hpp")

if( MSVC )
   set( hardfork_hpp_file "${CMAKE_CURRENT_SOURCE_DIR}/include/bearshares/chain/hardfork.hpp" )
   add_custom_target( build_hardfork_hpp
      COMMAND cat-parts "${CMAKE_CURRENT_SOURCE_DIR}/hardfork.d" ${hardfork_hpp_file} )
   add_dependencies( build_hardfork_hpp cat-parts )
else( MSVC )
   set( hardfork_hpp_file "${CMAKE_CURRENT_BINARY_DIR}/include/bearshares/chain/hardfork.hpp" )
   add_custom_target( build_hardfork_hpp
      COMMAND "${CMAKE_SOURCE_DIR}/programs/build_helpers/cat_parts.py" "${CMAKE_CURRENT_SOURCE_DIR}/hardfork.d" ${hardfork_hpp_file} )
endif( MSVC )


set_source_files_properties( "${CMAKE_CURRENT_BINARY_DIR}/include/bearshares/chain/hardfork.hpp" PROPERTIES GENERATED TRUE )

## SORT .cpp by most likely to change / break compile
add_library( bearshares_chain

             # As database takes the longest to compile, start it first
             database.cpp
             fork_database.cpp
             witness_schedule.cpp

             bears_evaluator.cpp

             bears_objects.cpp
             shared_authority.cpp
             block_log.cpp

             util/reward.cpp

             ${HEADERS}
             ${hardfork_hpp_file}
             "${CMAKE_CURRENT_BINARY_DIR}/include/bearshares/chain/hardfork.hpp"
           )

add_dependencies( bearshares_chain bearshares_protocol build_hardfork_hpp )
target_link_libraries( bearshares_chain bearshares_protocol fc chainbase graphene_schema ${PATCH_MERGE_LIB} )
target_include_directories( bearshares_chain
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include" )

if(MSVC)
  set_source_files_properties( database.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

INSTALL( TARGETS
   bearshares_chain

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/bearshares/chain" )
