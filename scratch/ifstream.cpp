#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " grades-file" << std::endl;
        return 1;
    }

    // create a new input stream on the supplied filename
    char *filename = argv[1];
    std::ifstream grades_stream(filename);

    if (! grades_stream) {
        std::cerr << "Cannot open the grades file " << filename << std::endl;
        return 1;
    }

    // create a vector to hold the scores
    std::vector<int> scores;

    int grade;
    // keep reading scores from the file until there are no more scores
    while (grades_stream >> grade)
        scores.push_back(grade);

    if (scores.size() == 0) {
        std::cout << "No scores recorded." << std::endl;
        return 1;
    }

    double sum = 0;
    for (int i = 0; i < scores.size(); i++) {
        std::cout << scores[i] << std::endl;
        sum += scores[i];
    }

    // compute the average (mu)
    double average = sum / scores.size();
    std::cout << "Average: " << average << std::endl;

    // compute standard deviation
    double stddev_numerator = 0;
    for (int i = 0; i < scores.size(); i++) {
        stddev_numerator += pow((scores[i]-average), 2);
        std::cout << "Numerator now: " << stddev_numerator << std::endl;
    }

    std::cout << "Numerator: " << stddev_numerator << std::endl;

    double stddev_num = stddev_numerator / (scores.size()-1);
    std::cout << "Number about to be square-rooted: " << stddev_num << std::endl;

    double stddev = sqrt(stddev_num);
    std::cout << "Standard deviation: " << stddev << std::endl;

    return 0;
}
