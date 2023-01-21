set_project("fuck_redis")
set_languages("c11")
set_warnings("allextra")
--set_warnings("all", "error")

-- set_config("cxxflags", "-Wno-attributes")
set_config("cc", "clang")
set_config("cxx", "clang++")
set_config("ld", "clang++")

add_rules("mode.debug", "mode.release")

add_includedirs("./monotime")

target("monotime")
    set_kind("binary")
    add_files("./monotime/*.c")
