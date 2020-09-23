#pragma once

class MapGenerator
{
public:
    // generate random tilemap of given size
    template<int WIDTH, int HEIGHT>
    static int* generate(const float fill, const int smooths)
    {
        // generate random noise
        int* input = seed<WIDTH + 1, HEIGHT + 1>(fill);

        std::cout << "SEED:" << std::endl;
        print<WIDTH + 1, HEIGHT + 1>(input);
        std::cout << std::endl;

        // smooth noise
        int* smoothed = new int[(WIDTH + 1) * (HEIGHT + 1)];

        for (int i = 0; i < smooths; i++)
        {
            smoothed = smooth<WIDTH + 1, HEIGHT + 1>(input);

            if (i < smooths - 1) {
                // copy result back to input
                std::copy(&smoothed[0], &smoothed[0] + (WIDTH + 1) * (HEIGHT + 1), &input[0]);
            }
        }

        std::cout << "SMOOTHED:" << std::endl;
        print<WIDTH + 1, HEIGHT + 1>(smoothed);
        std::cout << std::endl;

        // marching squares
        return marchingSquares<WIDTH, HEIGHT>(smoothed);
    }

    // generate tilemap from input
    template<int WIDTH, int HEIGHT>
    static int* marchingSquares(int* input)
    {
        int* output = new int[WIDTH * HEIGHT];

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                int val = 0;
                val += input[x + ((y + 1) * (WIDTH + 1))];
                val += input[(x + 1) + ((y + 1) * (WIDTH + 1))] << 1;
                val += input[(x + 1) + (y * (WIDTH + 1))] << 2;
                val += input[x + (y * (WIDTH + 1))] << 3;
                output[x + (y * WIDTH)] = val;
            }
        }

        return output;
    }

    // print array (for debugging)
    template<int WIDTH, int HEIGHT>
    static void print(int* array)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                std::cout << ((array[x + (y * WIDTH)] == 1) ? '#' : ' ');
            }
            std::cout << std::endl;
        }
    }

    // check collision with tile
    bool collides(int tile, int x, int y)
    {
        // TODO
        return false;
    }

private:
    template<int WIDTH, int HEIGHT>
    static int* seed(const float fill)
    {
        int* output = new int[WIDTH * HEIGHT];

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH + 1; x++)
            {
                if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                    output[x + y * WIDTH] = 1;
                }
                else {
                    output[x + y * WIDTH] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) > fill ? 0 : 1;
                }
            }
        }

        return output;
    }

    template<int WIDTH, int HEIGHT>
    static int* smooth(int* input)
    {
        int* output = new int[WIDTH * HEIGHT];

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                    output[x + WIDTH * y] = 1;
                }
                else {
                    int neighbours = countNeighbours(input, WIDTH, x, y);

                    if (neighbours > 4) {
                        output[x + WIDTH * y] = 1;
                    }
                    else if (neighbours < 4) {
                        output[x + WIDTH * y] = 0;
                    }
                    else {
                        output[x + WIDTH * y] = input[x + WIDTH * y];
                    }
                }
            }
        }

        return output;
    }

    static int countNeighbours(int* input, int width, int x, int y)
    {
        int neighbours = 0;

        if (input[(x - 1) + ((y - 1) * width)] == 1) {
            neighbours++;
        }
        if (input[x + ((y - 1) * width)] == 1) {
            neighbours++;
        }
        if (input[(x + 1) + ((y - 1) * width)] == 1) {
            neighbours++;
        }
        if (input[(x - 1) + (y * width)] == 1) {
            neighbours++;
        }
        if (input[(x + 1) + (y * width)] == 1) {
            neighbours++;
        }
        if (input[(x - 1) + ((y + 1) * width)] == 1) {
            neighbours++;
        }
        if (input[x + ((y + 1) * width)] == 1) {
            neighbours++;
        }
        if (input[(x + 1) + ((y + 1) * width)] == 1) {
            neighbours++;
        }

        return neighbours;
    }
};
