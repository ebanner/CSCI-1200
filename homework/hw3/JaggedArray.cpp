#include <cstdlib>

template <class T> class JaggedArray {
    private:
        unsigned int num_elements;
        unsigned int num_bins;
        bool packed;
        int *counts;
        T *packed_values;
        T **unpacked_values;

    public:
        // constructor
        JaggedArray();

        // accessors
        int numElements() const { return num_elements; }
        int numBins() const { return num_bins; }
        int numElementsInBin(const int bin) const { return counts[bin]; }
        int getElement(const int bin, const int offset) const { return ...; }
        bool isPacked() const;
        void clear() const;

        // modifiers
        void addElement(const int bin, const T &element) const;
        void removeElement(const int bin, const int offset) const;

        // change the packing structure
        void pack();
        void unpack();

        // visulization
        void print() const;
};

template <class T> JaggedArray<T>::JaggedArray() {
    num_elements = 0;
    num_bins = 0;
    packed = false;
    counts = NULL;
    packed_values = NULL;
    unpacked_values = NULL;
}
