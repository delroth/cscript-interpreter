add_executable(cscript-interpreter
               main.cc
               skit-backend.cc
               skit-backend.hh)

target_link_libraries(cscript-interpreter cscript ${Boost_LIBRARIES})
