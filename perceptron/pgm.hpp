#ifndef AZ_PGM_HPP_
#define AZ_PGM_HPP_

#include <vector>
#include <fstream>

struct PgmFile {
    PgmFile(const char* file_path, unsigned img_width, unsigned img_height);
    void write(const std::vector<float>& img_data);
private:
    void write_headers(std::ofstream& pgm_file);
    const char* file_path;
    unsigned img_width;
    unsigned img_height;
};

#endif // AZ_PGM_HPP_
