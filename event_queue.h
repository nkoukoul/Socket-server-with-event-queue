#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include<pthread.h>
#include"event.h" 

class EventQueue{
public:
  EventQueue(int const capacity);
  ~EventQueue();
  int Size() const;
  bool Empty() const;
  void AddEvent(std::string const name);
  void ProcessEvent();
  void PrintQueueElements() const;
private:
  int GetPriority(std::string const action) const;
  std::vector<Event> ve_;
  const int capacity_;
};


#endif // EVENT_QUEUE_H
