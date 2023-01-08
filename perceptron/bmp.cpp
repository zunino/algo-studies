#include <bitset>
#include <cmath>
#include <iostream>

#include "bmp.hpp"

BmpFile::BmpFile(const char* file_path, unsigned img_width, unsigned img_height)
: file_path{file_path}, img_width{img_width}, img_height{img_height} {
}

void BmpFile::write(std::vector<float> img_data) {
    bmp_file.open(file_path, std::ios::binary);
    write_headers();
    for (int row = img_height - 1; row >= 0; --row) {
        BmpScanLine scan_line;
        for (unsigned col = 0; col < img_width; ++col) {
            scan_line.add(img_data[row * img_width + col]);
        }
        bmp_file.write((const char*) &scan_line.buffer[0], scan_line.buffer.size());
    }
    this->bmp_file.close();
}

void BmpFile::write_headers() {
    file_header.file_size = file_size();
    char* p = (char*) &file_header;
    bmp_file.write(p, BMP_FILE_HEADER_LENGTH);

    info_header.image_width = this->img_width;
    info_header.image_height = this->img_height;
    p = (char*) &info_header;
    bmp_file.write(p, BMP_INFO_HEADER_LENGTH);

    Bmp1BitColorHeader color_header;
    p = (char*) &color_header;
    bmp_file.write(p, BMP_COLOR_HEADER_LENGTH);
}

std::size_t BmpFile::file_size() const {
    const size_t pixel_data_width = std::ceil(img_width / 32.0f) * 4 * img_height;
    return BMP_HEADERS_TOTAL_LENGTH + pixel_data_width;
}

BmpScanLine::BmpScanLine() : buffer(4, 0) {
}

void BmpScanLine::add(float value) {
    if (bit_offset > 7) {
        ++byte_idx;
        bit_offset = 0;
        if (byte_idx % 4 == 0) {
            buffer.insert(buffer.end(), {0, 0, 0, 0});
        }
    }
    if (value != 0.0f) {
        buffer[byte_idx] |= 1 << (7 - bit_offset);
    }
    ++bit_offset;
}
