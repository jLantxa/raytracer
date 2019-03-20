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

#include "PathTracer.hpp"

#include "Common.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Objects.hpp"
#include "Surface.hpp"
#include "Utils.hpp"

#include <chrono>
#include <limits>
#include <vector>

#include "debug.hpp"

static const char* TAG = "PathTracer";

// TODO: This value is completely random
Real ACCURACY = 0.0001;

PathTracer::PathTracer(unsigned spp, unsigned depth)
:   mSPP(spp), mMaxDepth(depth)
{ }

PathTracer::~PathTracer() { }

void PathTracer::render(struct Scene& scene, Camera& camera) {
    Surface& surface = camera.getSurface();
    const unsigned width = surface.getWidth();
    const unsigned height = surface.getHeight();
    Debug::Log::i(TAG, "Render scene: %dx%d", width, height);

#ifdef PATH_TRACER_TIME_ESTIMATION
    CircularTimeArray<int> durations(3);
#endif

    for (int n = 1; n <= mSPP; n++) {
#ifdef PATH_TRACER_TIME_ESTIMATION
        auto start = std::chrono::high_resolution_clock::now();
        Debug::Log::i(TAG, "Rendering %d/%d: %.2f%% ETA: %.0f s",
            n, mSPP, 100.0*(n-1)/(mSPP), (mSPP+1-n)*durations.mean()/1000.0);
#else
        Debug::Log::i(TAG, "Rendering %d/%d: %.2f%%", n, mSPP, 100.0*(n-1)/(mSPP));
#endif

        #pragma omp parallel for schedule(static)
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                Ray ray = camera.getRayToPixel(i, j);
                surface[i][j] += traceRay(0, ray, scene);
            }
        }

#ifdef PATH_TRACER_TIME_ESTIMATION
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        durations.add(duration);
#endif
    }

    const Real ispp = 1.0f/mSPP;
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            surface[i][j] *= ispp;
        }
    }
}

Color PathTracer::traceRay(unsigned depth, Ray& ray, struct Scene& scene) {
    if (depth >= mMaxDepth) {
        return Color();
    }

    Real t;
    IObject3D* iObject = intersectObjects(ray, scene.objects, t);
    if (iObject == nullptr) {
        return Color();
    }

    Vec3D iPoint_v = ray.point(t);
    Vec3D iDirection_v = ray.getDirection();
    Vec3D iNormal_v = iObject->getHitNormal(iPoint_v, iDirection_v);
    iPoint_v.set(iPoint_v + ACCURACY*iNormal_v);

    Color iColor = iObject->color();
    Color emission = iObject->material().emission*iColor;

    Vec3D sample_v = sampleHemisphere(iNormal_v, Xi);
    Real cos_theta = sample_v.dot(iNormal_v);

    const Real p = 1.0/(2*M_PI);
    Ray sampleRay(iPoint_v, sample_v);

    Color incoming = iColor * traceRay(depth+1, sampleRay, scene);
    return emission + p*incoming;
}
