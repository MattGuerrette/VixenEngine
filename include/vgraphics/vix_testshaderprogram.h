#ifndef VIX_TESTSHADERPROGRAM_H
#define VIX_TESTSHADERPROGRAM_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_gl.h>

#define SHADER_GLOBAL_PROJECTION "gProjection"
#define SHADER_GLOBAL_WORLD      "gWorld"
#define SHADER_GLOBAL_VIEW       "gView"

namespace Vixen {

    /**
    *   class TestShaderProgram
    *
    *   Test bed for new GLSL shader loading
    *   The idea is to load all possible shader types:
    *   VERTEX, TESS_CONTROL, TESS_EVAL, GEOMETRY, FRAGMENT
    *   from a single .glsl file.
    *
    *   This way we reduce the amount of file we have to keep track of, and the rewrite
    *   should solve previous shader issues brought to light by Valgrind.
    */
    class VIX_API TestShaderProgram
    {
    public:
        TestShaderProgram(const UString path);

        ~TestShaderProgram(void);

        void Bind(void);
        void Unbind(void);

    private:
        GLuint  m_programID;
    };

}

#endif // VIX_TESTSHADERPROGRAM_H
