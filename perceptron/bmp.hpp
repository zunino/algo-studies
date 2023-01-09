#ifndef AZ_BMP_HPP_
#define AZ_BMP_HPP_

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <vector>

inline const size_t BMP_FILE_HEADER_LENGTH = 14;
inline const size_t BMP_INFO_HEADER_LENGTH = 40;
inline const size_t BMP_COLOR_HEADER_LENGTH = 8;
inline constexpr size_t BMP_HEADERS_TOTAL_LENGTH = 
    BMP_FILE_HEADER_LENGTH + BMP_INFO_HEADER_LENGTH + BMP_COLOR_HEADER_LENGTH;

#pragma pack(push, 1)
struct BmpFileHeader {
    uint8_t file_type[2] = {'B', 'M'};
    uint32_t file_size;
    uint32_t reserved;
    uint32_t pixel_data_offset = BMP_HEADERS_TOTAL_LENGTH;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BmpInfoHeader {
    uint32_t header_size = 40;
    uint32_t image_width;
    uint32_t image_height;
    uint16_t planes = 1;
    uint16_t bits_per_pixel = 1;
    uint32_t compression = 0;
    uint32_t image_size = 0;
    uint32_t x_pixels_per_meter = 0;
    uint32_t y_pixels_per_meter = 0;
    uint32_t total_colors = 0;
    uint32_t important_colors = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Bmp1BitColorHeader {
    uint8_t color_1[4] = {255, 255, 255, 0};
    uint8_t color_2[4] = {96, 96, 96, 0};
};
#pragma pack(pop)

struct BmpScanLine {
    BmpScanLine();
    std::vector<uint8_t> buffer;
    void add(float value);
private:
    std::size_t byte_idx = 0;
    std::size_t bit_offset = 0;
};

struct BmpFile {
    BmpFile(const char* file_path, unsigned img_width, unsigned img_height);
    void write(const std::vector<float>& img_data);
    std::size_t file_size() const;
private:
    void write_headers(std::ofstream& bmp_file);
    const char* file_path;
    unsigned img_width;
    unsigned img_height;
    BmpFileHeader file_header;
    BmpInfoHeader info_header;
    Bmp1BitColorHeader color_header;
};

#endif // AZ_BMP_HPP_
