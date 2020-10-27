#include "tcp_server.h"
#include "project.h"
#include "event_queue.h"
#include <pthread.h>

std::string ReadFile(std::string filename)
{
    std::string line;
    std::ifstream my_file (filename);
    if (my_file.is_open())
    {
	getline(my_file,line);
	my_file.close();
    }
    return line;
}


int main()
{
  pthread_t server_thread;
  int s, w;
  void * res;
  s = pthread_create(&server_thread, NULL, tcp_server::SocketServerServe, NULL);
  if (s != 0)
    std::cout << "server thread creation failed.. exiting\n";

  EventQueue * eq = new EventQueue(100);

  while(true){
    ;;
  }
  s = pthread_join(server_thread, &res);
  if (s != 0)
    std::cout << "server thread join failed.. exiting\n";
  return 0;
}
