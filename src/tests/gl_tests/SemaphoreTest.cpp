//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// SemaphoreTest.cpp : Tests of the GL_EXT_semaphore extension.

#include "test_utils/ANGLETest.h"

#include "test_utils/gl_raii.h"

namespace angle
{

class SemaphoreTest : public ANGLETest
{
  protected:
    SemaphoreTest()
    {
        setWindowWidth(1);
        setWindowHeight(1);
        setConfigRedBits(8);
        setConfigGreenBits(8);
        setConfigBlueBits(8);
        setConfigAlphaBits(8);
    }
};

// glIsSemaphoreEXT must identify semaphores.
TEST_P(SemaphoreTest, SemaphoreShouldBeSemaphore)
{
    ANGLE_SKIP_TEST_IF(!EnsureGLExtensionEnabled("GL_EXT_semaphore"));

    constexpr GLsizei kSemaphoreCount = 2;
    GLuint semaphores[kSemaphoreCount];
    glGenSemaphoresEXT(kSemaphoreCount, semaphores);

    EXPECT_FALSE(glIsSemaphoreEXT(0));

    for (GLsizei i = 0; i < kSemaphoreCount; ++i)
    {
        EXPECT_TRUE(glIsSemaphoreEXT(semaphores[i]));
    }

    glDeleteSemaphoresEXT(kSemaphoreCount, semaphores);

    EXPECT_GL_NO_ERROR();
}

// Use this to select which configurations (e.g. which renderer, which GLES major version) these
// tests should be run against.
ANGLE_INSTANTIATE_TEST(SemaphoreTest,
                       ES2_D3D9(),
                       ES2_D3D11(),
                       ES3_D3D11(),
                       ES2_OPENGL(),
                       ES3_OPENGL(),
                       ES2_OPENGLES(),
                       ES3_OPENGLES(),
                       ES2_VULKAN());

}  // namespace angle
