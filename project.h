#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <vector>
#include <stack>
#include <unordered_map>
#include <typeinfo>
#include <tuple>
#include <pqxx/pqxx> 


/* server */
#define MAXBUF 512
#define GUESS_PORT 1500

/* database */
#define DBNAME "horizonsb_db"
#define USER "horizonsb"
#define PASSWORD "horizonsb"
#define HOSTADDR "127.0.0.1"
#define PORT "5432"

#endif //PROJECT_H
