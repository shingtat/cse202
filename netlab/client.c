/*
 * client.c - A client that connects to a web server to test one of the
 *            requested functions
 */
#include <stdio.h>
#include <unistd.h>
#include "support.h"
#include "csapp.h"

/*
 * Information about this student team (fill it in in team.c)
 */
extern struct team_t team;

/*
 * forward declarations
 */
void usage(char* progname);

/*
 * main - The main routine should
 */
int main(int argc, char **argv) {
  /* for getopt */
  long opt;

  /* parameters */
  long port = 8080;
  unsigned seed = 0;
  int iters = 1;
  char *uri = "localhost";

  /* run a team name check */
  if (strcmp("", team.name1) == 0) {
    printf("%s: Please fill in the team struct in team.c\n", argv[0]);
    exit(1);
  }
  printf("Member 1: %s\n", team.name1);
  printf("Email 1: %s\n", team.email1);
  if (*team.name2 || *team.email2) {
    printf("Member 2: %s\n", team.name2);
    printf("Email 2: %s\n", team.email2);
  }
  printf("\n");

  /*
   * parse the command-line options.  They are -p <int> for the port, and -h
   * (no parameter) to print help and quit.  -t is for doing very simple
   * tests without starting a web client
   */
  while ((opt = getopt(argc, argv, "u:p:s:i:h")) != -1) {
    switch(opt) {
     case 'p': port  = strtol(optarg, NULL, 10); break;
     case 's': seed  = strtol(optarg, NULL, 10); break;
     case 'i': iters = strtol(optarg, NULL, 10); break;
     case 'u': uri = optarg; break;
     case 'h': usage(argv[0]); break;
     default : usage(argv[0]); break;
    }
  }

  /* TODO: complete remainder of this function */
  int z;
  int fd;
  char request[MAXLINE];
  char buf[MAXLINE];
  char *a1, *a2;
  int num;

  for (z = 0; z < iters; z++){
    fd = Open_clientfd(uri, port);
    char endRequest[MAXLINE];
    //send request
    strcpy(request, "GET /cgi-bin/getrand.so?seed=");
    sprintf(endRequest, "%u&submit=Submit HTTP/1.0\r\n\r\n", seed);
    strcat(request, endRequest);
    Rio_writen(fd, request, MAXLINE);
    //read and parse output
    Rio_readn(fd, buf, MAXLINE);
    a1 = strchr(buf, '(');
    a2 = strchr(a1, ',');
    a2 += 2;
    a1 = strchr(a2, ')');
    *a1 = '\0';
    num = atoi(a2);
    //new seed
    seed = (unsigned int) num;
  }
  printf("Number = %d\n", num); 
}

/*
 * usage - explain program invocation
 */
void usage(char* progname) {
  fprintf(stderr, "usage: %s -u <uri> -p <port> -s <seed> -i <iters>\n", progname);
  exit(1);
}
