#include "image_texture.hpp"
#include "../external/rt_stb_image.hpp"

#include <iostream>

double double_clamp(double value, double minimum, double maximum);

ImageTexture::ImageTexture(const char *filename)
{
    auto components_per_pixel = bytes_per_pixel_;

    data_ = stbi_load(filename, &width_, &height_, &components_per_pixel, components_per_pixel);

    if (!data_)
    {
        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
        width_ = height_ = 0;
    }

    bytes_per_scanline_ = bytes_per_pixel_ * width_;
}

Color ImageTexture::Value(double u, double v, const Vec3 &p) const
{
    if (data_ == nullptr)
        return Color(0, 1, 1);

    u = double_clamp(u, 0.0, 1.0);
    v = 1.0 - double_clamp(v, 0.0, 1.0);

    auto i = static_cast<int>(u * width_);
    auto j = static_cast<int>(v * height_);

    if(i >= width_) i = width_ - 1;
    if(j >= height_) j = height_ - 1;

    const auto color_scale = 1.0 / 255.0;
    auto pixel = data_ + j * bytes_per_scanline_ + i * bytes_per_pixel_;
    return Color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}

double double_clamp(double value, double minimum, double maximum)
{
    if (value < minimum)
        return minimum;
    if (value > maximum)
        return maximum;
    return value;
}