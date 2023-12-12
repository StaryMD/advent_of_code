#include <CL/cl.h>
#include <CL/cl_ext.h>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define CL_HPP_ENABLE_EXCEPTIONS
#include <CL/opencl.hpp>

constexpr int kGPUBetterThreshold = 1300;

constexpr uint_fast32_t kIterations = 1;

constexpr uint_fast32_t kSize = 140;
constexpr int_fast64_t kExpansionRate = 2;

cl::Device GetFastestGPU() {
  cl::Device best_device;

  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);

  size_t device_speed_best = 0;

  for (const cl::Platform& platform : platforms) {
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

    for (const cl::Device& device : devices) {
      const size_t max_compute_units = device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
      const size_t max_clock_frequency = device.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>();

      const size_t device_speed = max_compute_units * max_clock_frequency;

      if (device_speed > device_speed_best) {
        device_speed_best = device_speed;
        best_device = device;
      }
    }
  }

  if (best_device.get() == nullptr) {
    std::cout << "No devices have been found\n";
    return cl::Device();
  }

  std::cout << "Using device: " << best_device.getInfo<CL_DEVICE_NAME>() << '\n';

  return best_device;
}

struct Timer {
  std::chrono::steady_clock::time_point start;

  Timer() { reset(); }

  void reset() { start = std::chrono::steady_clock::now(); }

  double elapsed_time() const {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::duration<double> interval = now - start;
    return interval.count();
  }
};

std::string GetFileContent(const std::string& str) {
  std::ifstream file(str);
  std::ostringstream ss;

  ss << file.rdbuf();

  return ss.str();
}

struct Point {
  const uint_fast32_t x;
  const uint_fast32_t y;

  Point(const uint_fast32_t x_, const uint_fast32_t y_) : x(x_), y(y_) {}
};

int main() try {
  uint_fast64_t sum = 0;

  cl::Device d_device = GetFastestGPU();

  if (d_device.get() == nullptr) {
    std::cout << "Life is not good\n";
    return EXIT_FAILURE;
  }

  cl::Context d_context(d_device);
  cl::CommandQueue d_queue(d_context);
  cl::Program d_program(d_context, GetFileContent("day11.cl").c_str(), true);
  cl::Kernel d_kernel(d_program, "calculate");

  const Timer total_timer;

  for (uint_fast32_t i = 0; i < kIterations; ++i) {
    std::vector<Point> galaxies;

    std::vector<int_fast32_t> distances((kSize + 1) * 2);

    {  // Read input
      std::ifstream fin("data/day11.in");
      std::stringstream ss;

      ss << fin.rdbuf();

      const std::string world = ss.str();

      galaxies.reserve(kSize * kSize);

      for (uint_fast32_t i = 0; const char ch : world) {
        switch (ch) {
          case '#': {
            galaxies.emplace_back(i % kSize + 1, i / kSize + 1);
          }
          case '.': {
            ++i;
            break;
          }
        }
      }
    }

    {  // Calculate distances
      int_fast32_t* const dist_hor = distances.data();
      int_fast32_t* const dist_ver = distances.data() + kSize + 1;

      for (int_fast64_t x = 1; x <= kSize; ++x) {
        bool is_empty = true;

        for (const Point galaxy : galaxies) {
          if (galaxy.x == x) {
            is_empty = false;
          }
        }
        dist_hor[x] = dist_hor[x - 1] + 1 + static_cast<int_fast64_t>(is_empty) * (kExpansionRate - 1);
      }

      for (int_fast64_t y = 1; y <= kSize; ++y) {
        bool is_empty = true;

        for (const Point galaxy : galaxies) {
          if (galaxy.y == y) {
            is_empty = false;
          }
        }

        dist_ver[y] = dist_ver[y - 1] + 1 + static_cast<int_fast64_t>(is_empty) * (kExpansionRate - 1);
      }
    }

    {  // Calculator
      double reference_time;
      double device_time;

      uint_fast64_t local_sum = 0;

      if (galaxies.size() >= kGPUBetterThreshold) {
        std::vector<int_fast64_t> ans(galaxies.size() - 1, 0);

        cl::Buffer d_galaxies(d_context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR,
                              galaxies.size() * sizeof(galaxies[0]), galaxies.data());

        cl::Buffer d_distances(d_context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR,
                               distances.size() * sizeof(distances[0]), distances.data());

        cl::Buffer d_ans(d_context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, ans.size() * sizeof(ans[0]), ans.data());

        d_kernel.setArg(0, static_cast<unsigned>(galaxies.size()));
        d_kernel.setArg(1, d_galaxies);
        d_kernel.setArg(2, d_distances);
        d_kernel.setArg(3, d_ans);

        d_queue.enqueueNDRangeKernel(d_kernel, cl::NullRange, cl::NDRange(galaxies.size() - 1));

        d_queue.enqueueReadBuffer(d_ans, CL_TRUE, 0, ans.size() * sizeof(ans[0]), ans.data());

        for (const auto x : ans) {
          local_sum += x;
        }
      } else {
        const int_fast32_t* const dist_hor = distances.data();
        const int_fast32_t* const dist_ver = distances.data() + kSize + 1;

        for (uint_fast32_t i = 0; i < static_cast<uint_fast32_t>(galaxies.size()) - 1; ++i) {
          for (uint_fast32_t j = i + 1; j < static_cast<uint_fast32_t>(galaxies.size()); ++j) {
            local_sum += std::abs(dist_hor[galaxies[j].x] - dist_hor[galaxies[i].x]) +
                         (dist_ver[galaxies[j].y] - dist_ver[galaxies[i].y]);
          }
        }
      }

      sum = local_sum;
    }
  }

  const double time = total_timer.elapsed_time();

  std::cout << "Answer: " << sum << '\n';
  std::cout << "Elapsed time: " << time * 1000 / kIterations << "ms\n";

  return EXIT_SUCCESS;
} catch (const cl::BuildError& error) {

  const cl::BuildLogType logs = error.getBuildLog();

  for (const auto [device, log] : logs) {
    std::cout << "Opencl Build error logs for " << device.getInfo<CL_DEVICE_NAME>() << '\n' << log << '\n';
  }
} catch (const cl::Error& error) {

  std::cout << "Opencl error : " << error.err() << " : " << error.what() << '\n';
} catch (...) {

  std::cout << "Error, fuck\n";
}
