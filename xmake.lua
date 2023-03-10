set_project("redis")
set_languages("c11")
set_warnings("allextra")
--set_warnings("all", "error")

-- set_config("cxxflags", "-Wno-attributes")
set_config("cc", "clang")
set_config("cxx", "clang++")
set_config("ld", "clang++")

add_rules("mode.debug", "mode.release")

add_includedirs("./base")
add_includedirs("./data")
add_includedirs("./net")
add_includedirs("./server")
add_includedirs("./util")
add_includedirs("./event")
add_includedirs("./struct")
add_includedirs("./deps/fpconv")

target("redis")
    set_kind("binary")
    add_files("./base/*.c")
    add_files("./data/*.c")
    add_files("./net/*.c")
    add_files("./server/*.c")
    add_files("./util/*.c")
    add_files("./struct/*.c")
    add_files("./event/*.c")
    add_files("./deps/fpconv/*.c")

-- test
add_includedirs("./fuck_redis/monotime")
target("monotime")
    set_kind("binary")
    add_files("./fuck_redis/monotime/*.c")

target("sds")
    set_kind("binary")
    add_files("./fuck_redis/sds/sds.c")

target("ll2str")
    set_kind("binary")
    add_files("./fuck_redis/sds/ll2str.c")

target("vsnprintf_test")
    set_kind("binary")
    add_files("./fuck_redis/anet/vsnprintf_test.c")