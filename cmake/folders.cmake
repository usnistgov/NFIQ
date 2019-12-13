# derive dist path from build path
# 1st
get_filename_component( tmp ${BUILD_PATH}/.. ABSOLUTE   )
get_filename_component( tmp ${tmp} NAME  )
set( DIST_PATH  ${ROOT_PATH}/dist/${tmp} )
# 2nd
get_filename_component( tmp ${BUILD_PATH} ABSOLUTE   )
get_filename_component( tmp ${tmp} NAME  )
set( DIST_PATH  ${DIST_PATH}/${tmp} )

# configure cmake folders
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${DIST_PATH} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DIST_PATH} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIST_PATH} )

