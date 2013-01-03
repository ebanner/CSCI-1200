#include <iostream>
#include <cstdlib>

template <class T> class JaggedArray {
    private:
        unsigned int num_elements;
        unsigned int num_bins;

        // packed
        int *offsets;
        T *packed_values;

        // unpacked
        int *counts;
        T **unpacked_values;

        bool packed;

    public:
        // constructor
        JaggedArray();

        // accessors
        int numElements() const { return num_elements; }
        int numBins() const { return num_bins; }
        int numElementsInBin(const int bin) const { return counts[bin]; }
        T getElement(const int bin, const int offset) const;
        bool isPacked() const { return packed; }

        // modifiers
        void addElement(const int bin, const T &element) const;
        void removeElement(const int bin, const int offset) const;
        void clear() const;

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

template <class T> T JaggedArray<T>::getElement(const int bin, const int offset) const {
    if (packed)
        return packed_values[offsets[bin]+offset];
    else // unpacked
        return unpacked_values[bin][offset];
}

template <class T> void JaggedArray<T>::addElement(const int bin, const T &element) const {
    if (packed) {
        std::cerr << "Attempted to add element while in packed mode" << std::endl;
        exit(1);
    }

    // -- We're in unpacked mode -- //

    // get the size of the old bin
    int old_bin_size = counts[bin];

    // get the old bin and allocate a new bin one size bigger
    T *old_bin = unpacked_values[bin];
    T *new_bin = new T[old_bin_size+1];

    // copy old bin elements into new bin
    for (int i = 0; i < old_bin_size; i++)
        new_bin[i] = old_bin[i];

    // insert new element into the new bin
    new_bin[old_bin_size] = &element;

    // delete the old bin
    delete [] old_bin;

    // make the new bin the one recognized by the `unpacked_values' array
    unpacked_values[bin] = new_bin;
}

template <class T> void JaggedArray<T>::removeElement(const int bin, const int offset) const {
    if (packed) {
        std::cerr << "Attempted to add element while in packed mode" << std::endl;
        exit(1);
    }

    int old_bin_size = counts[bin];
    
    T *old_bin = unpacked_values[bin];
    T *new_bin = new T[old_bin_size-1];

    for (int i = 0, j = 0; i < old_bin_size-1; i++) {
        if (i == offset)
            continue;

        new_bin[j] = old_bin[j];
        j++;
    }

    delete [] old_bin;

    unpacked_values[bin] = new_bin;
}
