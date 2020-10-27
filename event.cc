#include "event.h"

Event::Event(int priority, std::shared_ptr<Data> data):priority_(priority),data_(data){}
