file(GLOB HEADERS "include/bearshares/app/*.hpp")

add_library( bearshares_app
             database_api.cpp
             api.cpp
             application.cpp
             impacted.cpp
             plugin.cpp
             ${HEADERS}
           )

target_link_libraries( bearshares_app bearshares_chain bearshares_protocol bearshares_tags bearshares_follow bearshares_witness bearshares_mf_plugins fc graphene_net graphene_utilities )
target_include_directories( bearshares_app
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

if(MSVC)
  set_source_files_properties( application.cpp api.cpp database_api.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

INSTALL( TARGETS
   bearshares_app

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/bearshares/app" )
