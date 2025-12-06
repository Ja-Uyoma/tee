install(
    TARGETS tee_exe
    RUNTIME COMPONENT tee_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
