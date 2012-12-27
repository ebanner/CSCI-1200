#include <iostream>
#include <fstream>

main()
{
    // create an input stream on the file
    std::ifstream input_str("foo.txt");

    int num;

    while (input_str >> num) {
        // there's another number in the file
        std::cout << num << ' ';
    }
    std::cout << std::endl;

    return 0;
}
