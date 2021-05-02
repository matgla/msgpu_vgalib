
add_library(msgpu_messages INTERFACE)

target_sources(msgpu_messages 
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/messages/info_req.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/messages/mode.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/messages/write_text.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/messages/change_mode.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/messages/info_resp.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/messages/header.hpp

)
 
target_include_directories(msgpu_messages 
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR} 
)
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/messages/info_req.th)
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/messages/mode.th)
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/messages/write_text.th)
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/messages/change_mode.th)
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/messages/info_resp.th)
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/messages/header.th)
