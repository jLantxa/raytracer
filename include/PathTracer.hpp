/*
 * This source file is part of PathTracer
 *
 * Copyright 2018, 2019 Javier Lancha Vázquez
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#ifndef _INCLUDE_PATHTRACER_PATHTRACER_H_
#define _INCLUDE_PATHTRACER_PATHTRACER_H_

#include "Renderer.hpp"

#include "Common.hpp"
#include "Surface.hpp"
#include "Objects.hpp"
#include "Light.hpp"
#include "Camera.hpp"

#include <cstdint>
#include <vector>

/** A container of objects and light sources */
struct Scene {
    std::vector<IObject3D*> objects;
    Vec3D backgroundColor;
};

class PathTracer : public IRenderer {
public:
    PathTracer(unsigned spp, unsigned depth);
    virtual ~PathTracer();

    virtual void renderScene(struct Scene& scene, Camera& camera);

    //virtual void setCallback(void (*partialResultCallback)(Surface*));

private:
    Vec3D traceRay(unsigned depth, Ray& ray, struct Scene& scene);
    IObject3D* intersect(Ray& ray, Scene& scene, Real& t);
    unsigned mMaxDepth;
    unsigned mSPP;

    // Random seed for erand48
    uint16_t Xi[3];

    // Partial result callback
    void (*partialResultCallback)(Surface*) = nullptr;

    //void notifyCallback(Surface* surface);
};

#endif // _INCLUDE_PATHTRACER_PATHTRACER_H_
