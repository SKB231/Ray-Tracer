#include <iostream>


int main() {
    // Image

    const int image_width = 256;
    const int image_height = 256;

    // Render
    std::cout<< "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j>=0; --j) {
        std::cerr << "\rScanlines Remaining: " << j << ' '<< std::flush;
        for (int i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 1.00;

            int ir = static_cast<int> (r * 255.9999);
            int ig = static_cast<int> (g * 255.9999);
            int ib = static_cast<int> (b * 255.9999);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\nDone\n";
}