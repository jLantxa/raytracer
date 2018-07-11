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

#include "Common.h"
#include "Light.h"

#include "Geometry.h"

Ray::Ray(Vec3D origin, Vec3D direction) :
    origin(origin.normalize()),
    direction(direction.normalize()) {}

Ray::~Ray() {}

Vec3D Ray::getOrigin() {
    return origin;
}

Vec3D Ray::getDirection() {
    return direction;
}

Vec3D Ray::point(Real t) {
    return origin + t*direction;
}