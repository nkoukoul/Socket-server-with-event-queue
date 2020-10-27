#ifndef EVENT_H
#define EVENT_H

#include "project.h"
//#include "EventQueue.hpp"

typedef struct s_data{
	std::string name_;
}Data;

class Event{
public:
  Event(int priority, std::shared_ptr<Data> data);
  bool operator < (Event const & m_event) const{
    return priority_ < m_event.priority_;
  }
  friend class EventQueue;
private:
  int priority_;
  std::shared_ptr<Data> data_;
};

#endif // EVENT_H
