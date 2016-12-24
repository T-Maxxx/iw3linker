#include "loader/loader.h"

typedef int(*entry_point_t)();

int main(int argc, const char* argv[])
{
    entry_point_t start = (entry_point_t)load_original_binary();
    start();
    return 0;
}
