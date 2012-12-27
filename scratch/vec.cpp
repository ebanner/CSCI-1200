#include <iostream>
#include <vector>

main()
{
    std::vector<double> v(100, 55.5);

    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << std::endl;

    return 0;
}
