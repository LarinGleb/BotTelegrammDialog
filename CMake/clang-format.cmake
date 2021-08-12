set_property(GLOBAL PROPERTY LIST_FILES)

function (add_to_target_clang TARGET) 
    set_property(GLOBAL APPEND PROPERTY LIST_FILES ${TARGET})
    
endfunction(add_to_target_clang)
