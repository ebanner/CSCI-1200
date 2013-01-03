#include <iostream>
#include <cstdlib>
#include <cassert>

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
        JaggedArray(const unsigned int bins);

        // destructor
        ~JaggedArray();

        // accessors
        int numElements() const { return num_elements; }
        int numBins() const { return num_bins; }
        int numElementsInBin(const int bin) const { return counts[bin]; }
        T getElement(const int bin, const int offset) const;
        bool isPacked() const { return packed; }

        // modifiers
        void addElement(const int bin, const T &element);
        void removeElement(const int bin, const int offset);
        void clear();

        // change the packing structure
        void pack();
        void unpack();

        // visulization
        void print() const;
};

template <class T> JaggedArray<T>::JaggedArray() {
    num_bins = num_elements = 0;
    packed = false;
    counts = NULL;
    offsets = NULL;
    packed_values = NULL;
    unpacked_values = NULL;
}

template <class T> JaggedArray<T>::JaggedArray(const unsigned int bins) {
    num_bins = bins;
    num_elements = 0;
    packed = false;
    counts = new int[bins];
    offsets = new int[bins];
    packed_values = NULL;
    unpacked_values = new T*[bins];
}

template <class T> JaggedArray<T>::~JaggedArray() {
    if (offsets != NULL)
        delete [] offsets;

    if (packed_values != NULL)
        delete [] packed_values;

    if (counts != NULL)
        delete [] counts;

    for (int i = 0; i < num_bins; i++)
        if (unpacked_values[i] != NULL)
            delete [] unpacked_values[i];
}

template <class T> T JaggedArray<T>::getElement(const int bin, const int offset) const {
    if (packed)
        return packed_values[offsets[bin]+offset];
    else // unpacked
        return unpacked_values[bin][offset];
}

template <class T> void JaggedArray<T>::addElement(const int bin, const T &element) {
    if (packed) {
        std::cerr << "Attempted to add element while in packed mode" << std::endl;
        exit(1);
    }

    // -- We're in unpacked mode -- \\

    // get the size of the old bin
    int old_bin_size = counts[bin];

    // get the old bin and allocate a new bin one size bigger
    T *old_bin = unpacked_values[bin];
    T *new_bin = new T[old_bin_size+1];

    if (old_bin_size > 0) {
        // copy old bin elements into new bin
        for (int i = 0; i < old_bin_size; i++)
            new_bin[i] = old_bin[i];
    
        // delete the old bin
        delete [] old_bin;
    }

    // increment the number of elements in this bin
    counts[bin]++;

    // insert new element into the new bin
    new_bin[old_bin_size] = element;

    
    // make the new bin the one recognized by the `unpacked_values' array
    unpacked_values[bin] = new_bin; // -- THERE MAY BE A MEMORY LEAK HERE -- \\

    // increment number of elements total
    num_elements++;
}

template <class T> void JaggedArray<T>::removeElement(const int bin, const int offset) {
    if (packed) {
        std::cerr << "Attempted to add element while in packed mode" << std::endl;
        exit(1);
    }

    // get the size of the bin that we're going to remove an element from
    int old_bin_size = counts[bin];

    // make sure the element to be removed is in range
    assert(offset < old_bin_size);
    
    // get a pointer to the old bin to be more verbose
    T *old_bin = unpacked_values[bin];
    // allocate memory for the new bin of size one less
    T *new_bin = new T[old_bin_size-1];

    for (int i = 0, j = 0; i < old_bin_size; i++) {
        if (i == offset) // don't add the element we want to remove
            continue;

        // copy over the old elements to the new bin
        new_bin[j] = old_bin[i];
        j++;
    }

    // free the memory used by the old bin
    delete [] old_bin;

    // give the new bin to the unpacked values array
    unpacked_values[bin] = new_bin;
    
    // decrease the number of overall elements
    num_elements--;

    // decrease the number of elements in the bin
    counts[bin]--;
}

template <class T> void JaggedArray<T>::clear() {
    for (int i = 0; i < num_bins; i++) {
        // clear out the bins
        counts[i] = offsets[i] = 0;

        // set the packed & unpacked values arrays to NULL;
        unpacked_values[i] = NULL;
    }

    // free the memory hogged by packed & unpacked values
    delete [] packed_values;
    delete [] unpacked_values;
    
    // set the packed values to NULL
    packed_values = NULL;

    // reset number of elements
    num_elements = 0;
}

template <class T> void JaggedArray<T>::pack() {
    if (packed) // we're done if we're already packed
        return;
    
    // -- We must be unpacked -- \\
    
    // allocate a new array for packed_value
    T *new_packed_values = new T[num_elements];

    int offset = 0; // start the offset of the packed offsets at zero
    for (int bin = 0; bin < num_bins; bin++) {
        offsets[bin] = offset;
        
        // copy the unpacked bin into the packed flat array
        for (int j = 0; j < counts[bin]; j++, offset++)
            new_packed_values[offset] = unpacked_values[bin][j];
    }

    if (packed_values != NULL)
        delete [] packed_values;

    packed_values = new_packed_values;

    packed = true;
}

template <class T> void JaggedArray<T>::unpack() {
    if (! packed) // we're done
        return;

    // -- We must be packing some heat -- \\
    
    /* Create the array that counts how many of each element goes in each bin 
     * from the offsets array owned by packed mode. */
    for (int i = 0; i < num_bins; i++) {
        // populate the `counts' array from the `offsets' array
        if (i == num_bins-1) // final bin
            counts[i] = num_elements - offsets[i];
        else // not the final bin
            counts[i] = offsets[i+1] - offsets[i];
    }

    // create the unpacked values from the `counts' array
    for (int i = 0; i < num_bins; i++) {
        /* The `unpacked_values' array is already the correct size. It never
         * changes (we never add nor take away a bin). */
        /* Create an array large enough to fit all of the new elements for the 
         * current bin. */
        T *new_bin_of_elements = new T[counts[i]];

        /* The bin we are currently at matches up with the bin from the
         * `offsets' array that we need to get the elements from. */
        for (int j = 0; j < counts[i]; j++)
            new_bin_of_elements[j] = packed_values[offsets[i]+j];

        if (unpacked_values[i] != NULL) {
            // free the memory that the old `unpacked_values[i]' was taking up
            delete unpacked_values[i];
        }

        /* This bin should be all filled up, so let's add it to the unpacked
         * array. */
        unpacked_values[i] = new_bin_of_elements;
    }

    // we're unpacked now
    packed = false;
}

template <class T> void JaggedArray<T>::print() const {
    if (packed) {

        std::cout << "Packed: " << std::endl << std::endl;

        std::cout << "Number of elements: " << num_elements << std::endl;
        std::cout << "Number of bins: " << num_bins << std::endl;

        std::cout << "Offsets: ";
        for (int i = 0; i < num_bins; i++)
            std::cout << offsets[i] << ' ';
        std::cout << std::endl;

        std::cout << "Packed values: " << std::endl;
        for (int i = 0; i < num_elements; i++)
            std::cout << packed_values[i] << std::endl;
    } else { // unpacked

        std::cout << "Unpacked:" << std::endl << std::endl;

        std::cout << "Number of elements: " << num_elements << std::endl;
        std::cout << "Number of bins: " << num_bins << std::endl;

        std::cout << "Counts: ";
        for (int i = 0; i < num_bins; i++)
            std::cout << counts[i] << ' ';
        std::cout << std::endl;

        std::cout << "Unpacked values: " << std::endl;

        for (int i = 0; i < num_bins; i++)
            for (int j = 0; j < counts[i]; j++)
                std::cout << "Element in bin " << i << " offset " << j << 
                    ": " << unpacked_values[i][j] << std::endl;
        std::cout << std::endl;
    }
}
