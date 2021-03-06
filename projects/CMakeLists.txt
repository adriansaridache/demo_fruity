cmake_minimum_required(VERSION 3.8)
project(fruitymesh)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        config/adv_packets.h
        config/board_ars100748.h
        config/board_ars100748_adapter.h
        config/board_ars100748_cable.h
        config/board_ars101693.h
        config/board_ars101694.h
        config/board_pca10031.h
        config/board_pca10036.h
        config/board_pca10040.h
        config/Config.h
        config/conn_packets.h
        config/nrf_drv_config.h
        config/nrf_drv_config_validation.h
        config/pstorage_platform.h
        config/SEGGER_RTT_Conf.h
        config/types.h
        inc/AdvertisingController.h
        inc/AdvertisingModule.h
        inc/ButtonListener.h
        inc/Connection.h
        inc/ConnectionManager.h
        inc/DebugModule.h
        inc/EnrollmentModule.h
        inc/GAPController.h
        inc/GATTController.h
        inc/IoModule.h
        inc/LedWrapper.h
        inc/Logger.h
        inc/Main.h
        inc/Module.h
        inc/NewStorage.h
        inc/Node.h
        inc/PacketQueue.h
        inc/ScanController.h
        inc/ScanningModule.h
        inc/SimpleBuffer.h
        inc/SimplePushStack.h
        inc/SimpleQueue.h
        inc/StatusReporterModule.h
        inc/Storage.h
        inc/SystemTest.h
        inc/Terminal.h
        inc/TestBattery.h
        inc/Testing.h
        inc/Utility.h
        inc_c/crc16.h
        inc_c/SEGGER_RTT.h
        inc_c/simple_uart.h
        src/base/AdvertisingController.cpp
        src/base/GAPController.cpp
        src/base/GATTController.cpp
        src/base/ScanController.cpp
        src/mesh/Connection.cpp
        src/mesh/ConnectionManager.cpp
        src/mesh/Node.cpp
        src/modules/AdvertisingModule.cpp
        src/modules/DebugModule.cpp
        src/modules/EnrollmentModule.cpp
        src/modules/IoModule.cpp
        src/modules/Module.cpp
        src/modules/ScanningModule.cpp
        src/modules/StatusReporterModule.cpp
        src/nrf/crc16.c
        src/nrf/simple_uart.c
        src/segger_rtt/RTT_Syscalls_GCC.c
        src/segger_rtt/SEGGER_RTT.c
        src/test/SystemTest.cpp
        src/test/TestBattery.cpp
        src/test/Testing.cpp
        src/utility/ButtonListener.cpp
        src/utility/LedWrapper.cpp
        src/utility/Logger.cpp
        src/utility/NewStorage.cpp
        src/utility/PacketQueue.cpp
        src/utility/SimpleBuffer.cpp
        src/utility/SimplePushStack.cpp
        src/utility/SimpleQueue.cpp
        src/utility/Storage.cpp
        src/utility/Terminal.cpp
        src/utility/Utility.cpp
        src/Config.cpp
        src/Main.cpp
        src_examples/PingModule.cpp
        src_examples/PingModule.h
        src_examples/TemplateModule.cpp
        src_examples/TemplateModule.h)

add_executable(fruitymesh ${SOURCE_FILES})