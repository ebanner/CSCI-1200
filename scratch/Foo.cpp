#include "Foo.h"

Foo::Foo() {
    bar = 0;
}

void Foo::setBar(const int bar) {
    this->bar = bar;
}

int Foo::getBar() const {
    return bar;
}
