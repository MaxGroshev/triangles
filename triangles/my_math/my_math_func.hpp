#pragma once

//-----------------------------------------------------------------------------------------

//double find_det(const vector_t& vec1, const vector_t& vec2, const vector_t& vec3);

template<typename T>
T my_abs(T val) {
    if (val < 0) return (-val);
    return val;
};
