/*
 * This source file is part of raytracer
 *
 * Copyright 2018 Javier Lancha Vázquez
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

#ifndef _INCLUDE_RAYTRACER_LIGHT_H_
#define _INCLUDE_RAYTRACER_LIGHT_H_

#include "Common.h"

/**
 * A ray of light with an origin and a direction
 */
class Ray {
    public:
        /**
         * A source point and the direction of propagation.
         * If any of the vectors are not unit they will be normalised.
         */
        Ray(Vec3D origin, Vec3D direction);
        virtual ~Ray();

        /**
         * Get a point in the trajectory of the ray. The parameter
         * t represents the distance from the origin.
         */
        Vec3D point(Real t);

        /** Return the origin vector of the ray */
        Vec3D getOrigin();

        /** Return the direction vector of the ray */
        Vec3D getDirection();

    private:
        /** Origin vector */
        Vec3D origin;
        Vec3D direction;
};

#endif // _INCLUDE_RAYTRACER_LIGHT_H_