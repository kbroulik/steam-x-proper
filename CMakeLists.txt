cmake_minimum_required(VERSION 3.0)

project(steamgameproper)

# Not sure how high those must be but I'm pretty sure not very high
set(QT_MIN_VERSION "5.9.0")
set(KF5_MIN_VERSION "5.40.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui X11Extras)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS Service WindowSystem)
find_package(XCB REQUIRED COMPONENTS XCB)

set(STEAMGAMEXPROPER_SRCS
    main.cpp
    steamxproper.cpp
)

add_executable(steamgamexproper ${STEAMGAMEXPROPER_SRCS})

target_link_libraries(steamgamexproper
    Qt5::Core
    Qt5::X11Extras
    KF5::Service
    KF5::WindowSystem
    XCB::XCB
)

# TODO install?

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
