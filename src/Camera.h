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

#ifndef _INCLUDE_RAYTRACER_CAMERA_H_
#define _INCLUDE_RAYTRACER_CAMERA_H_

#include "Common.h"

#include "Geometry.h"
#include "Light.h"


class Camera {
    public:
        Camera(unsigned width, unsigned height);
        Camera(unsigned width, unsigned height, Vec3D pos, Vec3D looking);
        Camera(unsigned width, unsigned height, Vec3D pos, Vec3D looking, Vec3D up);
        virtual ~Camera();

        /** Get a Ray from the eye to pixel [i, j] */
        Ray getRayToPixel();
    
    private:
        /** Screen width in pixels */
        unsigned width;
        /** Screen height in pixels */
        unsigned height;

        /** Position of the camera <i>eye</i> */
        Vec3D position;

        /** <br><b>u</b> is the <b>x</b> axis, or the right. */
        Vec3D u;
        /** <br><b>v</b> is the <b>y</b> axis, or the right. */
        Vec3D v;
        /** <br><b>w</b> is the <b>z</b> axis, or the right. */
        Vec3D w;

        /** Get a vector from the eye to pixel [i, j] */
        Vec3D getVectorToPixel(unsigned i, unsigned j);
};

#endif // _INCLUDE_RAYTRACER_CAMERA_H_