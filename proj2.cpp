#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <queue>
#include <ctime>
#include "e.h"

using namespace std;
int mu = 1;

double nedt(double rate)//packets arrive at rate lambda
{
    double u;
    u = drand48();
    return((-1/rate) * log(1-u));
}

Event new_event(int type, int source, double time)
{
  Event test;
  test.type = type;
  test.source = source;
  test.dest = rand() % num_hosts;
  while(test.source == test.dest){
    test.dest = rand() % num_hosts;
  }
  if(type == 0){
    test.time = time + nedt(lambda);
  }
  else if(type == 1){
    test.time = time + nedt(mu);
  }
  else if(type == 2){
    test.time = time + 0.01;
  }
  else if(type == 3){
    test.time = time;
  }
  else{
    cout << "Error"<<endl;
  }
  return test;
}


/*double nedt2()//packets depart at rate 1 which is why rate no longer plays a factor
{
    double u;
    u = drand48();
    return((-1) * log(1-u));
}*/

int main()
{
  int num_packets = 100000;
  double MAXBUFFER = 1000000;
  int packs_dropped = 0;
  double p_in_queue = 0;
  double total_time;
  double arriv_time;
  double depart_time;
  double prev_time = 0;
  double idle_time = 0;
  double idle_start = 0;
  double lambda;
  double DIFS = 0.1;
  double SIFS = 0.05;
  //double delta = 0.0001;
  int T;
  int num_hosts = 0;
  Event GEL;

  cout << "Lambda: ";
  cin >> lambda;
  cout<< "Number of hosts: ";
  cin >> num_hosts;
  cout << "T value: "; //value used for random backoff
  cin >> T;

  host hosts[num_hosts];
  //initialize variables in host
  for(int i = 0; i < num_hosts; i++){
    Event Event1 = newEvent(0, i, time);
    Event1.type2 - 0;
    insertGEL(Event1);
    hosts[i].length = 0;
    hosts[i].tot_length = 0;
    hosts[i].dropped = 0;
    hosts[i].N = 0;
    hosts[i].trans_time = 0;
    hosts[i].q_time = 0;
    hosts[i].backoff = 0;
  }

  for(int i = 0; i < num_packets; i++)
  {
    Event curr_event;
    curr_event = GEL.front();
    time = curr_event.time;

    //process queue arrival event
    if(curr_event.type == 0){
      //process beginning of arrival event
      if(curr_event.type2 == 0){
        //arrival event
        Event new_arriv = new_event(0, curr_event.source, time)
        new_arriv.type2 = 0;
        insert_GEL(new_arriv);

        //Create new packets
        packet new_packet;
        new_packet.size = nedt(mu); //not sure if right
        new_packet.service_t = nedt(mu);

        //departure event
        if(hosts[curr_event.source].length == 0){
          hosts[curr_event.source].Queue.push(new_packet);
          Event new_depart = new_event(1, curr_event.source, time);
          new_depart.time = time + new_packet.service_t;
          new_depart.dest = curr_event.dest;
          new_depart.type2 = 0;
          insert_GEL(new_depart);
          hosts[curr_event.source].length++;
        }
        else if(hosts[curr_event.source].length > 0 && ((hosts[curr_event.source].length) < MAXBUFFER))
        {
          hosts[curr_event.source].Queue.push(new_packet);
          hosts[curr_event.source].tot_length += hosts[curr_event.source].length *(time-prev_time);
          hosts[curr_event.source].length++;
        }
        else{
          hosts[curr_event.source].tot_length += hosts[curr_event.source].length *(time-prev_time);
        }
      }
      else if(curr_event.type2 == 1){
        Event check_event = in_transit.front();
        if(check_event.corrupt == 0){
          Event ack_depart = new_event(1, curr_event.source, time);
          ack_depart.dest = curr_event.dest;
          ack_depart.type2 = 1;
          ack_depart.size = curr_event.size;
          ack_depart.time = time + SIFS;
          insert_GEL(ack_depart);
        }
        else{
          cout << "Error" <<endl;
        }
      }
    }
    else if(curr_event.type = 1){//queue departure event
      packet new_packet = hosts[curr_event.source].Queue.front();
      hosts[curr_event.source].q_time += new_packet.service_t;
      hosts[curr_event.source].tot_length += hosts[curr_event.source].length*(time-prv_time);
    }
  }
  cout << "Throughput: " <<tot_bytes/time << endl;
  cout << "Avg Network Delay: " << tot_delay/ (tot_bytes/time) << endl;
}

