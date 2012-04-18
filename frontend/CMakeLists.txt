add_executable(cscript-interpreter
               main.cc
               tog-skit-backend.cc
               tog-skit-backend.hh
               tos2-skit-backend.cc
               tos2-skit-backend.hh)

target_link_libraries(cscript-interpreter cscript ${Boost_LIBRARIES})
