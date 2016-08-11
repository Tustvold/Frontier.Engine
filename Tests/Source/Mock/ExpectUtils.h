#pragma once
#include <Frontier.h>

inline void expectFuzzyEq(float A, float B) {
    const float maxRelativeError = 0.00001f;
    const float maxAbsoluteError = 1e-5f;

    if (fabs(A - B) < maxAbsoluteError)
        return;
    float relativeError;
    if (fabs(B) > fabs(A))
        relativeError = fabs((A - B) / B);
    else
        relativeError = fabs((A - B) / A);

    EXPECT_LE(relativeError, maxRelativeError);
}

inline void expectMatrixEqual(const glm::mat4& a, const glm::mat4& b) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            expectFuzzyEq(a[i][j], b[i][j]);
        }
    }
}

inline void expectVectorEqual(const glm::vec3& a, const glm::vec3& b) {
    for (int i = 0; i < 3; i++) {
        expectFuzzyEq(a[i], b[i]);
    }
}
