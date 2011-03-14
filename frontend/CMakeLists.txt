add_executable(cscript-interpreter
               main.cc)

target_link_libraries(cscript-interpreter cscript ${Boost_LIBRARIES})
