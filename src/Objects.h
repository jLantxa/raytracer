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

#ifndef _INCLUDE_RAYTRACER_OBJECTS_H_
#define _INCLUDE_RAYTRACER_OBJECTS_H_

#include "Common.h"
#include "Geometry.h"
#include "Light.h"

typedef Vector3D<float> Color;

/**
 * 3D Object base
 */
class Object3D {
    public:
        Object3D();
        virtual ~Object3D() = 0;

        virtual Color getColor() = 0;
        virtual Real intersect(const Ray& ray) = 0;
    
    private:
        Color color;
};


/** A sphere object derived from the Object3D base */
class Sphere : public Object3D {
    public:
        Sphere(Color color, Vec3D center, Real radius);
        virtual ~Sphere();

        virtual Color getColor();
        virtual Real intersect(const Ray& ray);

    private:
        Vec3D center;
        Real radius;
};

/** A plane object derived from the Object3D base */
class Plane : public Object3D {
    public:
        Plane(Color color, Vec3D position, Vec3D normal);
        virtual ~Plane();

        virtual Color getColor();
        virtual Real intersect(const Ray& ray);

    private:
        Vec3D position;
        Vec3D normal;
};

#endif // _INCLUDE_RAYTRACER_OBJECTS_H_