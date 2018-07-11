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

#include <Geometry.h>

#include <math.h>

/*
 * Definitions of Vector3D
*/
template <typename T>
Vector3D<T>::Vector3D(T x, T y, T z) : x(x), y(y), z(z) {}

template <typename T>
Vector3D<T>::Vector3D(T x, T y) : x(x), y(y), z(0) {}

template <typename T>
Vector3D<T>::Vector3D() : x(0), y(0), z(0) {}

template <typename T>
Vector3D<T>::~Vector3D() {}

template <typename T>
T Vector3D<T>::dist() {
    return sqrt(x*x + y*y + z*z);
}

template <typename T>
Vector3D<T> Vector3D<T>::normalize() {
    T norm = dist();
    Vector3D normalized(x/norm, y/norm, z/norm);
    return normalized;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator+(Vector3D& v) {
    Vector3D sum(x+v.x, y+v.y, z+v.z);
    return sum;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator-(Vector3D& v) {
    Vector3D<T> sum(x-v.x, y-v.y, z-v.z);
    return sum;
}

template <typename T>
T Vector3D<T>::dot(Vector3D<T>& v) {
    return x*v.x + y*v.y + z*v.z;
}

template <typename T>
Vector3D<T> Vector3D<T>::cross(Vector3D& v) {
    Vector3D<T> cross(
        y*v.z - z*v.y,
        z*v.x - x*v.z,
        x*v.y - y*v.x);
    return cross;
}

template <typename T>
Vector3D<T> operator*(T k, Vector3D<T>& v) {
    Vector3D<T> mult(k*v.x, k*v.y, k*v.z);
    return mult;
}

template <typename T>
Vector3D<T> operator*(Vector3D<T>& v, T k) {
    Vector3D<T> mult(k*v.x, k*v.y, k*v.z);
    return mult;
}

/* Specialisations of Vector3D */
template class Vector3D<float>;
template class Vector3D<double>;