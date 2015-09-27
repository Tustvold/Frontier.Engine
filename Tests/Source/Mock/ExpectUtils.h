#pragma once
#include <Frontier.h>

inline void expectMatrixEqual(const glm::mat4& a, const glm::mat4& b, float epsilon = FLT_EPSILON) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float delta = fabsf(a[i][j] - b[i][j]);
            EXPECT_TRUE(delta < epsilon);
        }
    }
}