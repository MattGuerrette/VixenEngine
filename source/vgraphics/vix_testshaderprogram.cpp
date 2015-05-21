#include <vix_testshaderprogram.h>

namespace Vixen {

    TestShaderProgram::TestShaderProgram(const UString path)
    {

    }

    TestShaderProgram::~TestShaderProgram(void)
    {
        glDeleteProgram(m_programID);
    }

    void TestShaderProgram::Bind(void)
    {
        //bind program: pass ID value m_programID
        glUseProgram(m_programID);
    }

    void TestShaderProgram::Unbind(void)
    {
        //unbind program: pass ID value ZERO
        glUseProgram(0);
    }

}

