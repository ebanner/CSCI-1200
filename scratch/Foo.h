#ifndef FOO_H
#define FOO_H

class Foo {
    public:
        // constructor
        Foo();

        void setBar(const int bar);
        int getBar() const;

    private:
        int bar;
};

#endif
