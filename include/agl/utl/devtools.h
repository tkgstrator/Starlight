#include "types.h"
#include "agl/DrawContext.h"
#include "sead/vector.h"
#include "sead/color.h"

#pragma once

namespace agl {
    namespace utl {
        class DevTools{
            public:
            void static drawTriangleImm(agl::DrawContext*, sead::Vector3<float> const&, sead::Vector3<float> const&, sead::Vector3<float> const&, sead::Color4f const&);
        };
    };
};