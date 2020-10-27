#include "event_queue.h"

void EventQueue::PrintQueueElements() const{
  for (auto it = ve_.begin(); it!= ve_.end(); ++it){
    std::cout<<" "<<it->data_->name_;
  }
  std::cout<<"\n";
}

int EventQueue::Size() const {return ve_.size();}
bool EventQueue::Empty() const {return ve_.empty();}

EventQueue::EventQueue(int const capacity):capacity_(capacity){
  ve_.reserve(capacity_);
  std::make_heap(ve_.begin(),ve_.end());
}

EventQueue::~EventQueue(){
  while (!Empty())
    ProcessEvent();
  std::cout<<"queue destroyed\n";
}

void EventQueue::AddEvent(std::string const name){
  if (ve_.size()>capacity_)
    return;
  std::shared_ptr<Data> data = std::make_shared<Data>();
  data->name_ = name;
  Event event(GetPriority(name),data);//= new event;
  //m_event.m_data = m_data;
  //m_event.m_priority = getPriority(m_name);
  ve_.push_back(event);
  //delete m_data;
  //delete m_event;
  std::push_heap(ve_.begin(),ve_.end());
  return;
}


void EventQueue::ProcessEvent(){
  if (!Empty()){
    std::pop_heap(ve_.begin(), ve_.end());
    Event event = ve_.back();
    std::cout<<"Action "<<event.data_->name_<<" with priority "<<event.priority_<<"\n";
    //delete event.data_;
    ve_.pop_back();
  }
  return;
}

int EventQueue::GetPriority(std::string const action) const{
  int priority=0;
  if (action=="front")
    priority = 100;
  else if (action=="back")
    priority = 30;
  else if (action=="left" || action=="right")
    priority = 15;
  else
    priority = 10;
  return priority;
}

