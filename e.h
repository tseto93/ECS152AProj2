#ifndef E_H
#define E_H
#include <iostream>
class Event_node
{
public:
  Event_node *next_event;
  Event_node *prev_event;
  double time;
  double type;
  int source;
  int dest;
  int type2;
  double size;
  int corrupt
  Event_node(){};
  friend class Event;
};


class Event
{
private:
    Event_node* front;
  public:
    Event()
    {
      front = NULL;
    };
    ~Event(){};
    Event& insert(double time, bool type);
    Event& deleting();
    Event_node& front_return();
    int check_front();
    int print();
};

class Data
{
private:

    public:
        int length;
        Data(int MAXBUFFER);
        struct packet{
            double time;
        };
        double rmv_head();
        packet* queue;
};

class host{
public:
  int length;
  int tot_length;
  int dropped;
  int N;
  int trans_time;
  int q_time;
  int backoff;
}

class packet{
public:
  double service_time;
  double size;
}
#endif

