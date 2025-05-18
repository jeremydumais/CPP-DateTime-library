# Changelog

All notable changes to this project will be documented in this file

## [1.0.2]
- The version of the library is now managed in the build configuration
(CMakeLists.txt)
- The library and header files are now installed in a datetime subfolder.
You may need to update your references to the datetime header files in your
project.

    Before: #include <datetime.h>

    After: #include <datetime/datetime.h>

    You should also use datetime namespace when targeting the library.

    Ex: target_link_libraries(${PROJECT_NAME} datetime::datetime)

## [1.0.1]

### Style
- Apply linting to all source files in the project (cpplint).

### CI
- Add the Github Action configuration file to the project.

## [1.0.0]

### Added

- The initial version development
