file(GLOB sources CONFIGURE_DEPENDS *.cxx)

add_executable(test_deranged ${sources})
target_link_libraries(test_deranged PUBLIC deranged)

add_test(NAME test_deranged COMMAND test_deranged --use-colour yes)
