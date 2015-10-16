#pragma once
#include <Frontier.h>

inline void expectFuzzyEq(float a, float b, float epsilon = FLT_EPSILON) {
    float delta = fabsf(a - b);
    EXPECT_LT(delta, epsilon);
}

inline void expectMatrixEqual(const glm::mat4& a, const glm::mat4& b, float epsilon = FLT_EPSILON) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            expectFuzzyEq(a[i][j], b[i][j], epsilon);
        }
    }
}

inline void expectVectorEqual(const glm::vec3& a, const glm::vec3& b, float epsilon = FLT_EPSILON) {
    for (int i = 0; i < 3; i++) {
        expectFuzzyEq(a[i], b[i], epsilon);
    }
}
