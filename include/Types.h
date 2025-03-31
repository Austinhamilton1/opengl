#pragma once

namespace gl {
    enum BufferType {
        STATIC,
        DYNAMIC,
    };

    enum CompileResult {
        SUCCESS,
        VERTEX_COMPILATION_ERROR,
        FRAGMENT_COMPILATION_ERROR,
        PROGRAM_LINK_ERROR,
    };
}