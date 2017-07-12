#include "e.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

list<Event> GEL;
list<Event> in_transit;

Event& Event::insert(double time, bool type)
{
  Event_node *node_data;
  Event_node *node_ptr;
  Event_node *prev_node = NULL;

  node_data = new Event_node;
  node_data -> time = time;
  node_data -> type = type;

  if(front == NULL)
  {
    front = node_data;
    node_data -> next_event = NULL;
    node_data -> prev_event = NULL;
  }
  else
  {
    node_ptr = front;
    while(node_ptr != NULL)
    {
      if((node_ptr -> time) < time)
      {
        prev_node = node_ptr;
        node_ptr = node_ptr -> next_event;
      }
      else
      {
        break;
      }
    }
    if(prev_node == NULL && (node_ptr == front))
    {
      Event_node *temp = NULL;
      temp = front;
      temp->time = front->time;
      temp->type = front->type;
      temp->next_event = front->next_event;
      front = node_data;
      front->time = node_data->time;
      front->type = node_data->type;
      front->next_event = temp;
    }
    else
    {
      prev_node->next_event = node_data;
      if(prev_node != front && node_ptr != NULL)
      {
        node_ptr->prev_event = node_data;
      }
      node_data->prev_event = prev_node;
      node_data->next_event = node_ptr;


    }
  }
  return *this;
}

Event& Event::deleting()
{
  if((front->next_event) != NULL)
  {
    Event_node* temp_ptr = NULL;
    temp_ptr = (front->next_event);
    temp_ptr->next_event = (front->next_event)->next_event;
    temp_ptr->time = (front->next_event)->time;
    temp_ptr->type = (front->next_event)->type;
    front->time = temp_ptr->time;
    front->next_event = temp_ptr->next_event;
    front->time = temp_ptr->time;
    front->type = temp_ptr->type;
  }
  else
  {
    front = NULL;
  }
  return *this;
}

Event_node& Event::front_return()
{
  return *front;
}

int Event::check_front()
{
  if(front == NULL)
  {
    return 1;
  }
  return 0;
}

int Event::print()
{
  int i = 0;
  Event_node *curr_node;
  curr_node = front;
  while(curr_node != NULL)
  {
    cout<< "Node"<< i <<": ";
    cout<< (curr_node->time)<< " - ";
    cout<< (curr_node->type)<< "\n";
    curr_node = curr_node->next_event;
    i++;
  }
  return 0;
}

Data::Data(int MAXBUFFER)
{
  length = 0;
  queue = new packet[MAXBUFFER];
}

double Data::rmv_head()
{
  double next_departure = 0;
  int j = 1;
  for(int i = 0; i < length + 1; i++)
  {
    queue[i].time = queue[j].time;
  }
  if(length != 0)
  {
    next_departure = queue[0].time;
  }
  return next_departure;
}

Event& Event::insert_GEL(Event new_event)
{
  list<Event>::iterator it;
  Event temp;
  temp = GEL.back();
  if(new_event.time < temp.time){
    for(it = GEL.begin() < (it->time)){
      if(new_event.time < (it->time)) {
        GEL.insert(it, new_event);
        break;
      }
    }
  }
  else{
    GEL.push_back(new_event);
  }
}

