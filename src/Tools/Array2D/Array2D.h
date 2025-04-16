#pragma once
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
class Array2D
{
protected:
    const int width;
    const int height;
    const int size;
    T* arr;

    void ThrowException() const
    {
        throw std::out_of_range ("Range of array is "
                                "x: (0 - " + std::to_string(width) + "), "
                                "y: (0 - " + std::to_string(height) + ")");
    }
    bool CheckIfInRange(const int x, const int y) const
    {
        return !(x < 0 || y < 0 || x >= width || y >= height);
    }
public:
    Array2D(unsigned int w, unsigned int h) : width(w), height(h),
        size(width * height)
    {
        arr = new T[size];
    }
    virtual ~Array2D()
    {
        delete[] arr;
    }

    T* at(int x, int y)
    {
        return CheckIfInRange(x, y) ? &arr[y*width + x] : nullptr;
    }

    const T* at(int x, int y) const
    {
        return CheckIfInRange(x, y) ? &arr[y*width + x] : nullptr;
    }

    void assign(int x, int y, T* data)
    {
        if (CheckIfInRange(x, y))
            arr[y*width + x] = *data;
        else
            ThrowException();
    }

    int Size() const { return size; }
    int Width() const { return width; }
    int Height() const { return height; }
};