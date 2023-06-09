cmake_minimum_required(VERSION 3.19)

project(aijika VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Network
    Widgets
)

qt_standard_project_setup()

qt_add_executable(aijika
    src/main.cpp
    src/common/globals.cpp
    src/common/globals.h
    src/common/settings.cpp
    src/common/settings.h
    src/generator/generator.cpp
    src/generator/generator.h
    src/generator/openai.cpp
    src/generator/openai.h
    src/generator/prompt.cpp
    src/generator/prompt.h
    src/model/card.cpp
    src/model/card.h
    src/model/database.cpp
    src/model/database.h
    src/model/pack.cpp
    src/model/pack.h
    src/ui/components/packcombo.cpp
    src/ui/components/packcombo.h
    src/ui/composerdialog.cpp
    src/ui/composerdialog.h
    src/ui/editordialog.cpp
    src/ui/editordialog.h
    src/ui/managerwindow.cpp
    src/ui/managerwindow.h
    src/ui/settingswindow.cpp
    src/ui/settingswindow.h
    src/ui/studywindow.cpp
    src/ui/studywindow.h
    resources/icon.icns
    resources/resources.rc
)

target_include_directories(aijika PRIVATE src)

target_link_libraries(aijika PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Widgets
)

qt_add_resources(aijika "resources" PREFIX "/" FILES
    resources/prompts.json
)

if(APPLE)
    set_source_files_properties(resources/icon.icns PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")

    set_target_properties(aijika PROPERTIES
        OUTPUT_NAME "AI 记卡"
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "AI 记卡"
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_GUI_IDENTIFIER io.github.pkupop.aijika
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
        MACOSX_BUNDLE_COPYRIGHT "Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi"
        MACOSX_BUNDLE_ICON_FILE icon.icns
    )
else()
    set_target_properties(aijika PROPERTIES
        OUTPUT_NAME Aijika
        WIN32_EXECUTABLE TRUE
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out"
    )
endif()

install(TARGETS aijika
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(DEFINED ENV{AIJIKA_TEST})
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG bc860af08783b8113005ca7697da5f5d49a8056f
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    qt_add_executable(
        aijika_test
        src/main_test.cpp
        src/common/globals.cpp
        src/common/globals_test.cpp
        src/common/settings.cpp
        src/common/settings_test.cpp
        src/generator/generator.cpp
        src/generator/generator_test.cpp
        src/generator/openai.cpp
        src/generator/openai_test.cpp
        src/generator/prompt.cpp
        src/generator/prompt_test.cpp
        src/model/card.cpp
        src/model/database.cpp
        src/model/pack.cpp
    )

    target_include_directories(aijika_test PRIVATE src)

    target_link_libraries(aijika_test PRIVATE
        Qt::Core
        Qt::Network
        GTest::gtest_main
    )

    qt_add_resources(aijika_test "resources" PREFIX "/" FILES
        resources/prompts.json
    )

    include(GoogleTest)
    gtest_discover_tests(aijika_test)
endif()
