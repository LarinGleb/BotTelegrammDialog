get_property(LIST_FILES GLOBAL PROPERTY LIST_FILES)
add_custom_target(
    clang-format
    COMMAND /usr/bin/clang-format -style=webkit -i ${LIST_FILES}
)

