# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
include(${ZEPHYR_BASE}/cmake/cfb.cmake NO_POLICY_SCOPE)
project(cfb_custom_font2)

FILE(GLOB app_sources *.c font/*.c)
target_sources(app PRIVATE ${app_sources})

# set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)
# generate_cfb_font_for_target(app fonts/dice.png ${gen_dir}/cfb_font_dice.h 32 32 --first 49 --last 54)
