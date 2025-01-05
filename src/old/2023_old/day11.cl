#define SIZE 140

struct Point {
  int x;
  int y;
};

__kernel void calculate(const unsigned galax_count,
                        __global struct Point *galaxies,
                        __global int distances[2][SIZE + 1],
                        __global long *ans) {
  const int i = get_global_id(0);

  long sum = 0;

  __global int *dist_hor = distances[0];
  __global int *dist_ver = distances[1];

  for (int j = i + 1; j < galax_count; ++j) {
    sum += dist_ver[galaxies[j].y] - dist_ver[galaxies[i].y];

    if (dist_hor[galaxies[j].x] > dist_hor[galaxies[i].x]) {
      sum += dist_hor[galaxies[j].x] - dist_hor[galaxies[i].x];
    } else {
      sum -= dist_hor[galaxies[j].x] - dist_hor[galaxies[i].x];
    }
  }

  ans[i] = sum;
}
