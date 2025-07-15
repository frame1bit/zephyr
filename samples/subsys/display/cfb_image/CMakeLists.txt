# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
include(${ZEPHYR_BASE}/cmake/cfb.cmake NO_POLICY_SCOPE)
project(cfb_custom_font2)

FILE(GLOB app_sources *.c)
target_sources(app PRIVATE ${app_sources})

# set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)
# generate_cfb_font_for_target(app battery.png cfb_font_batt.h 60 32 --first 66 --last 66)
# generate_cfb_font_for_target(app artha.png cfb_font_artha.h 64 64 --first 67 --last 67)
# generate_cfb_font_for_target(app artha2.png cfb_font_artha2.h 64 64 --first 67 --last 67)