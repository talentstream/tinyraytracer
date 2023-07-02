#ifndef _IMAGE_TEXTURE_HPP_
#define _IMAGE_TEXTURE_HPP_


#include "../core/texture.hpp"

class ImageTexture : public Texture
{
private:
    unsigned char *data_;
    int width_;
    int height_;
    int bytes_per_scanline_;

public:
    const static int bytes_per_pixel_ = 3;

public:
    ImageTexture() : data_(nullptr), width_(0), height_(0), bytes_per_scanline_(0) {}
    ImageTexture(const char *filename);
    ~ImageTexture() { delete data_; }

    virtual Color Value(double u, double v, const Point3 &p) const override;
};

#endif /* _IMAGE_TEXTURE_HPP_ */